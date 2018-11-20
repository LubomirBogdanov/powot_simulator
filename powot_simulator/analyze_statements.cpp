/*
    Copyright (C) 2016 Lubomir Bogdanov

    Contributor Lubomir Bogdanov <lbogdanov@tu-sofia.bg>

    This file is part of Powot Simulator.

    Powot Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Powot Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Powot Simulator.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "powotsimulator.h"

/*!
 * \brief powotsimulator::analyze_statements - extracts the number of assembler instructions
 * for each C statement. It then assigns energy cost per instruction. The energy cost is read
 * from a model file.
 *
 * \param sym_cont - symbol contents - a QStringList variable whose members represent each line
 * of the symbol as seen in the object file dumped by GDB.
 * \param arr - an array of energyfield values. Every field represents one line of code in the
 * source file.
 */
void powotsimulator::analyze_statements(QStringList *sym_cont, energyfield_t *arr){
    QString line, line1, line2, asm_mnemonic;
    bool is_digit;
    bool flag = 0;
    bool instr_found = 0;
    energyfield_t e_field;
    unsigned long energy_field_num = 0;
    unsigned long for_loop_start = 0;
    unsigned long for_loop_end = 0;
    unsigned long num_loops = 0;
    unsigned long loop_count = 0;
    unsigned long *arr_loop_boundaries;

    //    for(int i = 0; i < sym_cont->size(); i++){
    //        qDebug()<<"***"<<sym_cont->at(i);
    //    }

    for(long i = 0; i < sym_cont->size(); i++){
        line = sym_cont->at(i).simplified();
        line = line.trimmed();

        //qDebug()<<"----"<<line;
        line1 = line.section(' ', 0, 0);
        if(line1.contains("0x")){

            //Extract assembly instruction
            e_field.asm_instr << line.section(' ', 2);
            arr[energy_field_num-1].asm_instr << e_field.asm_instr.last();
            //qDebug()<<e_field.asm_instr.last();

            //Extract virtual memory address of the assembly instruction
            line2 = line1.section('x', 1);
            line2 = line2.prepend("0x");
            e_field.asm_vma << line2.toInt(&is_digit, 16);
            arr[energy_field_num-1].asm_vma << e_field.asm_vma.last();

            //-------------------------------------------------------------------------------------------------------------
            //-----------------------Assign temporary energy cost of the assembly mnemonic---------------------------------
            //-------------------------------------------------------------------------------------------------------------
            asm_mnemonic = e_field.asm_instr.last().section(' ', 0, 0);
            arr[energy_field_num-1].asm_mnemonic << asm_mnemonic;
            //qDebug()<<"analyze_statements: asm_mnemonic = "<<asm_mnemonic;

            if(find_mnemonic_in_mdl(&asm_mnemonic)){

                //Match the address asm_vma with the corresponding address domain name from the model file and fill in the corresponding ASM field.
                for(unsigned long j = 0; j < mdl_domains.num_addr_ranges; j++){
                    if((mdl_domains.addr_ranges[j].at(0) <= e_field.asm_vma.last()) && (e_field.asm_vma.last() <= mdl_domains.addr_ranges[j].at(1))){
                        //qDebug()<<"instruction "<<asm_mnemonic<<" at 0x"<<hex<<asm_vma<<" is in: "<<mdl_domains.addr_ranges_names[i];
                        arr[energy_field_num-1].addr_range_name << mdl_domains.addr_ranges_names[j];
                        instr_found = 1;
                        break;
                    }
                }

                if(!instr_found){
                    instr_found = 0;
                    err_message.display_error(DOMAIN_NOT_FOUND_IN_MDL, &asm_mnemonic);
                    arr[energy_field_num-1].addr_range_name << def_domains.default_addr_range;
                }

                //Assign defaults for the mnemonic
                arr[energy_field_num-1].temperature_domain << def_domains.default_temperature;
                arr[energy_field_num-1].voltage_domain << def_domains.default_voltage;
                arr[energy_field_num-1].frequency_domain << def_domains.default_frequency;
                arr[energy_field_num-1].num_of_operands << def_domains.default_operand;

                //assign_energy_cost(asm_mnemonic, &arr[energy_field_num-1]);
                arr[energy_field_num-1].asm_base_energy_cost << 1.00;
            }
            else{
                //Mnemonic not found in model. Assign default values for everything and energy cost of zero.
                arr[energy_field_num-1].addr_range_name << def_domains.default_addr_range;
                arr[energy_field_num-1].frequency_domain << def_domains.default_frequency;
                arr[energy_field_num-1].num_of_operands << def_domains.default_operand;
                arr[energy_field_num-1].temperature_domain << def_domains.default_temperature;
                arr[energy_field_num-1].voltage_domain << def_domains.default_voltage;
                arr[energy_field_num-1].asm_base_energy_cost << 0.0;
            }
            //-------------------------------------------------------------------------------------------------------------
            //-------------------------------------------------------------------------------------------------------------
            //-------------------------------------------------------------------------------------------------------------

            //Multiply the energy cost if the assembly instruction is inside a loop
            //qDebug()<<"+++"<<energy_cost<<" "<<arr[energy_field_num-1];
            arr[energy_field_num-1].asm_repeated << (arr[energy_field_num-1].asm_base_energy_cost.last() * arr[energy_field_num-1].repeated);
        }
        else {
            if(!line.isEmpty()){

                //Extract C statement
                e_field.statement = line.section(' ', 1);
                arr[energy_field_num].statement = e_field.statement;

                //Check if statement is a function call----------------
                e_field.function_call = check_if_function_call(e_field.statement);
                arr[energy_field_num].function_call = e_field.function_call;
                //qDebug()<<"analyze_statements: ----function = "<<e_field.function_call<<" "<<e_field.statement;
                arr[energy_field_num].dvs_api = 0;
                arr[energy_field_num].dfs_api = 0;

                if(e_field.function_call){
                    if(check_if_dvs_api(&e_field.statement)){
                        qDebug()<<"(powotsimulator) DVS api detected on line "<<e_field.line_number+1;
                        arr[energy_field_num].dvs_api = 1;
                    }
                    else if(check_if_dfs_api(&e_field.statement)){
                        qDebug()<<"(powotsimulator) DFS api detected on line "<<e_field.line_number+1;
                        arr[energy_field_num].dfs_api = 1;
                    }
                    else{
                        //qDebug()<<"analyze_statements: ----function name = "<<e_field.statement.section('(', 0, 0);
                        e_field.statement = e_field.statement.section('(', 0, 0);
                        if(!e_field.statement.isEmpty()){
                            arr[energy_field_num].statement_energy_cost = estimate_function_call(e_field.statement);
                        }
                    }
                }
                //----------------------------------------------------

                //Preprocess for( ) loops-----------------------------
                arr[energy_field_num].repeated = 1;
                e_field.for_loop = check_if_for_loop(e_field.statement);
                arr[energy_field_num].for_loop = e_field.for_loop;
                //qDebug()<<e_field.for_loop<<":"<<e_field.statement;
                //qDebug()<<arr[energy_field_num].for_loop<<":"<<arr[energy_field_num].statement;
                //----------------------------------------------------
            }
        }

        e_field.line_number = line1.toInt(&is_digit, 10);
        if(is_digit){
            //Extract line number of the C statement
            arr[energy_field_num].line_number = e_field.line_number;
            e_field.asm_instr.clear();
            energy_field_num++;
        }
    }

    /*   energy_field_num--;
    for(unsigned long i = 0; i < energy_field_num; i++){
        qDebug()<<"++++ "<<arr[i].statement;
        for(unsigned long j = 0; j < arr[i].asm_instr.size(); j++){
            qDebug()<<"+++ "<<arr[i].asm_instr.at(j)<<" "<<arr[i].asm_repeated.at(j)<<"mJ "<<arr[i];
        }
    }
    energy_field_num++;
    */


    //Process for( ) loops-------------------------
    //Assigns energy to each asm X the number of the execution times of the asm (if placed
    //in a for( ) loop. The number of the execution times is inherently known here. But
    //we want to make a list of this number for each for loop. This is done separately
    //later in this method.

    energy_field_num--;
    //Estimate each loop start and end-----
    for(unsigned long i = 0; i < energy_field_num; i++){
        //qDebug()<<"+++ "<<arr[i].for_loop<<arr[i].statement;
        if(arr[i].for_loop){
            for_loop_start = arr[i].line_number;
            for_loop_end = estimate_for_loop_extend(arr, i, energy_field_num);
            //qDebug()<<"for_loop_extend: "<<for_loop_start<<" <--> "<<for_loop_end;

            arr[i].for_loop_start = for_loop_start;
            arr[i].for_loop_end = for_loop_end;

            arr[i].repeated = estimate_for_loop(arr[i].statement);


            for(unsigned long k = 0; k < energy_field_num; k++){
                //qDebug()<<"+++"<<arr[k].statement;
                if(arr[k].line_number == for_loop_start){
                    //qDebug()<<"---"<<arr[k].statement;
                    flag = 1;
                }

                if(flag == 1){
                    //qDebug()<<"---"<<arr[k].statement<<" "<<arr[i];
                    arr[k].repeated = arr[i].repeated;
                    for(long m = 0; m < arr[k].asm_repeated.size(); m++){
                        arr[k].asm_repeated.operator [](m) *= arr[i].repeated;
                        //qDebug()<<"+++"<<arr[k].asm_repeated.at(m);
                    }
                }

                if(arr[k].line_number == for_loop_end){
                    //qDebug()<<"---"<<arr[k].statement;
                    flag = 0;
                    arr[k].repeated *= arr[i].repeated;
                }
            }


            /*
            qDebug()<<"i = "<<for_loop_start<<" for_loop_end = "<<for_loop_end;
            for(unsigned long j = for_loop_start; j <= for_loop_end; j++){
                arr[j].repeated = arr[for_loop_start].repeated;
            }
            qDebug()<<"arr[i].repeated = "<<arr[i].repeated;
            */
        }
    }
    //-------------------------------------

    //List for( ) loop execution times------------------------------------
    //Make a list of the number of execution times for each for( ) loop.
    //What we do here is basically update the field "arr[i].repeated" for each
    //section of code with the correspodning for( ) loop multiplier.

    //Count number of loops
    for(unsigned long i = 0; i < energy_field_num; i++){
        if(arr[i].for_loop){
            num_loops++;
            //qDebug()<<"for_loop_extend: "<<arr[i].for_loop_start<<" <--> "<<arr[i].for_loop_end;
        }
    }

    //Make a list of the loops in an array. Use the format: loop_start <-> loop_end <-> statement number
    num_loops *= 3;
    arr_loop_boundaries = new unsigned long[num_loops];

    for(unsigned long i = 0; i < energy_field_num; i++){

        //qDebug()<<"|"<<i<<" "<<arr[i].statement;
        if(arr[i].for_loop){
            arr_loop_boundaries[loop_count] = arr[i].for_loop_start;
            arr_loop_boundaries[loop_count+1] = arr[i].for_loop_end;
            arr_loop_boundaries[loop_count+2] = i;
            loop_count+=3;
        }
    }

    /*for(unsigned long i = 0; i < num_loops; i++){
        if(i%3 == 0){
            qDebug()<<" ";
            qDebug()<<"arr_loop_boundaries["<<i<<"]: ";
        }
        qDebug()<<arr_loop_boundaries[i]<<" ";

    }
    qDebug()<<" ";

    qDebug()<<" ";<<"starting check...";
    */

    unsigned long last_loop_start = 0;
    unsigned long i;
    unsigned long j;
    unsigned long loop_nest_factor;
    unsigned long *for_loop_deps;
    for_loop_deps = new unsigned long[num_loops];
    memset(for_loop_deps, 0, num_loops);

    for(i = 0; i < num_loops; i+=3){
        loop_nest_factor = 0;

        if(arr_loop_boundaries[i+1] > arr_loop_boundaries[i+4]){

        }
        else{
            //qDebug()<<"---------------------------------------------";
            //qDebug()<<"Loop end: "<<arr_loop_boundaries[i]<<" "<<arr_loop_boundaries[i+1]<<" "<<arr_loop_boundaries[i+2];
            for(j = last_loop_start; j < i; j+=3){
                //qDebug()<<"dependent loop: "<<arr_loop_boundaries[j]<<" "<<arr_loop_boundaries[j+1]<<" "<<arr_loop_boundaries[j+2];
                for_loop_deps[j] = arr_loop_boundaries[j];
                for_loop_deps[j+1] = arr_loop_boundaries[j+1];
                for_loop_deps[j+2] = arr_loop_boundaries[j+2];

                loop_nest_factor++;
            }
            //qDebug()<<"dependent loop: "<<arr_loop_boundaries[i]<<" "<<arr_loop_boundaries[i+1]<<" "<<arr_loop_boundaries[i+2];
            for_loop_deps[j] = arr_loop_boundaries[i];
            for_loop_deps[j+1] = arr_loop_boundaries[i+1];
            for_loop_deps[j+2] = arr_loop_boundaries[i+2];

            //Reverse order
            for(long k = j, n = 0; k >= 0 ; k-=3, n+=3){
                arr_loop_boundaries[n] = for_loop_deps[k];
                arr_loop_boundaries[n+1] = for_loop_deps[k+1];
                arr_loop_boundaries[n+2] = for_loop_deps[k+2];
            }
            loop_nest_factor *= 3;

            /*for(unsigned long k = 0; k < j; k++){

                if(k == loop_nest_factor){
                    break;
                }

                if(k%3 == 0){
                    qDebug()<<" ";
                    qDebug()<<"arr_loop_boundaries["<<k<<"]: ";
                }
                qDebug()<<arr_loop_boundaries[k]<<" ";
            }
            qDebug()<<" ";*/

            for(unsigned long k = 0; k < j; k+=3){
                if(k == loop_nest_factor){
                    break;
                }
                multiply_nested_loops(arr_loop_boundaries, num_loops, k+2, arr, energy_field_num);
            }

            last_loop_start = j+3;
            i = j;
        }
    }
    //-------------------------------------

    //Process voltage domains (DVS)--------------------------------------------------------------------------------
    unsigned long dvs_api_extend;
    float voltage = 0.0;
    float dvs_energy = 0.0;
    for(unsigned long i = 0; i < energy_field_num+1; i++){
        //qDebug()<<"+++"<<arr[i].dvs_api<<"   "<<arr[i].statement;
        if(arr[i].dvs_api){
            dvs_api_extend = estimate_dvs_api_extend(arr, i, energy_field_num);

            arr[i].dvs_start = arr[i+1].line_number; //Exlude the DVS api itself

            arr[i].dvs_end = arr[i].dvs_start + dvs_api_extend;
            //qDebug()<<"arr[i].dvs "<<arr[i].dvs_start<<" <-> "<<arr[i].dvs_end;

            voltage = estimate_dvs_api(&arr[i].statement, &dvs_energy);
            arr[i].statement_energy_cost = dvs_energy;
            //qDebug()<<"assign to dvs api: "<<arr[i].statement<<" the following energy value: "<<dvs_energy;

            for(unsigned long j = i+1; j < energy_field_num+1; j++){
                //qDebug()<<"line_number: "<<arr[j].line_number<<" dvs_end: "<<arr[i].dvs_end;
                if(arr[j].line_number > arr[i].dvs_end){
                    break;
                }

                arr[j].voltage_domain.clear();

                for(long k = 0; k < arr[j].asm_instr.size(); k++){
                    arr[j].voltage_domain<<voltage;
                    //qDebug()<<" ..."<<arr[j].voltage_domain.last();
                }
            }
        }
    }
    //-------------------------------------------------------------------------------------------------------------

    //Process frequency domains (DFS)------------------------------------------------------------------------------
    unsigned long dfs_api_extend;
    float frequency = 0.0;
    float dfs_energy = 0.0;
    for(unsigned long i = 0; i < energy_field_num+1; i++){
        //qDebug()<<"+++"<<arr[i].dfs_api<<"   "<<arr[i].statement;
        if(arr[i].dfs_api){
            dfs_api_extend = estimate_dfs_api_extend(arr, i, energy_field_num);

            arr[i].dfs_start = arr[i+1].line_number; //Exlude the DfS api itself

            arr[i].dfs_end = arr[i].dfs_start + dfs_api_extend;
            //qDebug()<<"arr[i].dfs "<<arr[i].dfs_start<<" <-> "<<arr[i].dfs_end;

            frequency = estimate_dfs_api(&arr[i].statement, &dfs_energy);
            arr[i].statement_energy_cost = dfs_energy;
            //qDebug()<<"assign to dfs api: "<<arr[i].statement<<" the following energy value: "<<dfs_energy;

            for(unsigned long j = i+1; j < energy_field_num+1; j++){
                //qDebug()<<"line_number: "<<arr[j].line_number<<" dfs_end: "<<arr[i].dfs_end;
                if(arr[j].line_number > arr[i].dfs_end){
                    break;
                }

                arr[j].frequency_domain.clear();

                for(long k = 0; k < arr[j].asm_instr.size(); k++){
                    arr[j].frequency_domain<<frequency;
                    //qDebug()<<" ..."<<arr[j].frequency_domain.last();
                }
            }
        }
    }
    //-------------------------------------------------------------------------------------------------------------

    //Process number of operands-----------------------------------------------------------------------------------
    for(unsigned long i = 0; i < energy_field_num+1; i++){
        for(long j = 0; j < arr[i].asm_instr.size(); j++){
            arr[i].num_of_operands.operator [](j) = estimate_num_operands(arr[i].asm_instr.at(j));
        }
    }
    //-------------------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------------------
    //-----------------------Assign energy cost of the assembly mnemonic-------------------------------------------
    //-------------------------------------------------------------------------------------------------------------
    for(unsigned long i = 0; i < energy_field_num+1; i++){
        arr[i].asm_base_energy_cost.clear();
        arr[i].asm_repeated.clear();
        //qDebug()<<"Processing statement: "<<arr[i].statement<<" dvs: "<<arr[i].voltage_domain;
        //if(arr[i].dvs_api){
        //    qDebug()<<arr[i].dvs_start<<" <-> "<<arr[i].dvs_end;
        //}
        for(long j = 0; j < arr[i].asm_mnemonic.size(); j++){
            switch(arch_model_type){
            case MODEL_TAB_LUT:
                assign_energy_cost_tab_lut(arr[i].asm_mnemonic.at(j), j, &arr[i]);
                break;
            case MODEL_BINARY:
                assign_energy_cost_binary(arr[i].asm_mnemonic.at(j), j, &arr[i]);
                break;
            }
            arr[i].asm_repeated << (arr[i].asm_base_energy_cost.last() * arr[i].repeated);
        }
    }

    /*for(unsigned long i = 0; i < energy_field_num; i++){
       qDebug()<<"+++ "<<arr[i].statement;
       for(long j = 0; j < arr[i].asm_instr.size(); j++){
           qDebug()<<"arr[i].voltage_domain.size "<<arr[i].voltage_domain.size();
           qDebug()<<" "<<arr[i].asm_instr.at(j)<<" "<<arr[i].voltage_domain.at(j);
       }
   }*/
    //-------------------------------------

    /* for(unsigned long i = 0; i < energy_field_num; i++){
       for(long j = 0; j < arr[i].asm_instr.size(); j++){
           assign_energy_cost(arr[i].asm_instr.at(j), &arr[i]);
           //qDebug()<<" "<<arr[i].asm_instr.at(j)<<" "<<arr[i].voltage_domain.at(j);
       }
   }*/
}

void powotsimulator::multiply_nested_loops(unsigned long *arr_loop_boundaries, unsigned long num_of_loops, unsigned long loop_index, energyfield_t *arr, unsigned long energy_field_num){
    unsigned long loop;
    unsigned long next_loop;

    loop = arr_loop_boundaries[loop_index];
    next_loop = arr_loop_boundaries[loop_index + 3];

    //qDebug()<<"multiply_nested_loops "<<loop<<" "<<next_loop<<" "<<""<<"";

    if(loop_index < num_of_loops){
        arr[loop].repeated *= arr[next_loop].repeated;

        for(unsigned long i = loop+1; i < energy_field_num; i++){
            if(arr[i].line_number >= arr[loop].for_loop_end){
                break;
            }
            arr[i].repeated *= arr[next_loop].repeated;
        }
    }
}
