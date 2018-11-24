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

void powotsimulator::assign_energy_cost_tab_lut(QString asm_mnemonic, long asm_mnemonic_num, energyfield_t *enrgfield){
    float energy = 0;
    long index_addr = -1;
    long index_temp = -1;
    long index_voltage = -1;
    long index_frequency = -1;
    long index_operands = -1;
    bool err = 0;

    //--------------------------------------------------------------------
    //Extract the corresponding energy value from the model file----------
    //--------------------------------------------------------------------
    for(unsigned long i = 0; i < num_instr_in_mdl_file; i++){
        if(mdl[i].mnemonic == asm_mnemonic){

            //qDebug()<<"assign_energy_cost: mdl[i].mnemonic = "<<mdl[i].mnemonic;

            for(long j = 0; j < mdl[i].addr_range_name.size(); j++){
                if(enrgfield->addr_range_name.at(asm_mnemonic_num) == mdl[i].addr_range_name.at(j)){
                    index_addr = j;
                    break;
                }
            }
            if(index_addr == -1){
                qDebug()<<"(powotsimulator) ERROR: index_addr <<"<<enrgfield->addr_range_name.at(asm_mnemonic_num)<<">> domain error!";
                err = 1;
                index_addr = 0;
            }

            for(long j = index_addr; j < mdl[i].temperature_domain.size(); j++){
                if(enrgfield->temperature_domain.at(asm_mnemonic_num) == mdl[i].temperature_domain.at(j)){
                    index_temp = j;
                    break;
                }
            }
            if(index_temp == -1){
                qDebug()<<"(powotsimulator) ERROR: index_temp <<"<<enrgfield->temperature_domain.at(asm_mnemonic_num)<<">> domain error!";
                err = 1;
                index_temp = 0;
            }

            for(long j = index_temp; j < mdl[i].voltage_domain.size(); j++){
                if(enrgfield->voltage_domain.at(asm_mnemonic_num) == mdl[i].voltage_domain.at(j)){
                    index_voltage = j;
                    break;
                }
            }
            if(index_voltage == -1){
                qDebug()<<"(powotsimulator) ERROR: index_voltage <<"<<enrgfield->voltage_domain.at(asm_mnemonic_num)<<">> domain error!";
                err = 1;
                index_voltage = 0;
            }

            for(long j = index_voltage; j < mdl[i].frequency_domain.size(); j++){
                if(enrgfield->frequency_domain.at(asm_mnemonic_num) == mdl[i].frequency_domain.at(j)){
                    index_frequency = j;
                    break;
                }
            }
            if(index_frequency == -1){
                qDebug()<<"(powotsimulator) ERROR: index_frequency <<"<<enrgfield->frequency_domain.at(asm_mnemonic_num)<<">> domain error!";
                err = 1;
                index_frequency = 0;
            }

            for(long j = index_frequency; j < mdl[i].num_of_operands.size(); j++){
                if(enrgfield->num_of_operands.at(asm_mnemonic_num) == mdl[i].num_of_operands.at(j)){
                    index_operands = j;
                    break;
                }
            }
            if(index_operands == -1){
                qDebug()<<"(powotsimulator) ERROR: index_operands <<"<<enrgfield->num_of_operands.at(asm_mnemonic_num)<<">> domain error!";
                err = 1;
                index_operands = 0;
            }

            //++++++++++++++++++++++++++++
            if(err != 1){
                energy = mdl[i].energy.at(index_operands);
                /*
                qDebug()<<"-----------------------------------------";
                qDebug()<<"asm: "<<asm_mnemonic;
                qDebug()<<"index_temp: "<<index_temp;
                qDebug()<<"index_voltage: "<<index_voltage;
                qDebug()<<"index_frequency: "<<index_frequency;
                qDebug()<<"index_operands: "<<index_operands;
                qDebug()<<"main index: "<<index_main;
                qDebug()<<"energy: "<<energy;
                */
                break;
            }
            //++++++++++++++++++++++++++++
        }

        if(err){
            err_message.display_error(DOMAIN_NOT_FOUND_IN_MDL, &asm_mnemonic);
            energy = 0.0;
        }
    }
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------

    enrgfield->asm_base_energy_cost << energy;
}

void powotsimulator::assign_energy_cost_binary(energyfield_t *enrgfield, unsigned long enrgfield_size, unsigned long statement_num, long asm_mnemonic_num){    
    unsigned long asm_following_count = 0;    
    unsigned long asm_previous_count = 0;
    unsigned long asm_mnemonics_in_statement;    
    bool stop_through_statements = 0;
    unsigned long temp_statement_num;
    float energy = 1.0;
    QStringList cmd_line_previous;
    QString cmd_line_current;
    QStringList cmd_line_following;
    QString cmd_line_final;

    if(statement_num < enrgfield_size){
        //----------------------------------------------------------------------
        //List the previous [bin_model_prev_instr_max] instructions in sym file-
        //----------------------------------------------------------------------
        if(bin_model_prev_instr_max){
            for(int j = asm_mnemonic_num-1; j >= 0; j--){                
                cmd_line_previous << generate_cmd_line(&enrgfield[statement_num], j, asm_previous_count, INSTRUCTION_PREVIOUS);
                asm_previous_count++;
                if(asm_previous_count >= bin_model_prev_instr_max){
                    break;
                }
            }

            if(asm_previous_count < bin_model_prev_instr_max){
                temp_statement_num = statement_num - 1;
                for(int i = temp_statement_num; i >= 0; i--){
                    asm_mnemonics_in_statement = enrgfield[i].asm_mnemonic.size();
                    for(int j = asm_mnemonics_in_statement-1; j >= 0; j--){                        
                        cmd_line_previous << generate_cmd_line(&enrgfield[i], j, asm_previous_count, INSTRUCTION_PREVIOUS);
                        asm_previous_count++;
                        if(asm_previous_count >= bin_model_prev_instr_max){
                            stop_through_statements = 1;
                            break;
                        }
                    }
                    if(stop_through_statements){
                        break;
                    }
                }
            }

            for(int i = cmd_line_previous.size()-1; i >= 0; i--){
                qDebug()<<"----Prev instruction: "<<cmd_line_previous.at(i);
            }
        }
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------

        cmd_line_current = generate_cmd_line(&enrgfield[statement_num], asm_mnemonic_num, 3,INSTRUCTION_CURRENT);
        qDebug()<<"@@@@Current instruction: "<<cmd_line_current;

        //--------------------------------------------------------------------
        //List the next [bin_model_follow_instr_max] instructions in sym file-
        //--------------------------------------------------------------------
        if(bin_model_follow_instr_max){            
            stop_through_statements = 0;
            asm_mnemonics_in_statement = enrgfield[statement_num].asm_mnemonic.size();
            for(unsigned long j = asm_mnemonic_num+1; j < asm_mnemonics_in_statement; j++){                
                cmd_line_following << generate_cmd_line(&enrgfield[statement_num], j, asm_following_count, INSTRUCTION_FOLLOWING);
                asm_following_count++;
                if(asm_following_count >= bin_model_follow_instr_max){
                    break;
                }
            }

            if(asm_following_count < bin_model_follow_instr_max){
                temp_statement_num = statement_num + 1;
                for(unsigned long i = temp_statement_num; i < enrgfield_size; i++){
                    asm_mnemonics_in_statement = enrgfield[i].asm_mnemonic.size();
                    for(unsigned long j = 0; j < asm_mnemonics_in_statement; j++){                        
                        cmd_line_following << generate_cmd_line(&enrgfield[i], j, asm_following_count, INSTRUCTION_FOLLOWING);
                        asm_following_count++;
                        if(asm_following_count >= bin_model_follow_instr_max){
                            stop_through_statements = 1;
                            break;
                        }
                    }
                    if(stop_through_statements){
                        break;
                    }
                }
            }

            for(int i = 0; i < cmd_line_following.size(); i++){
                qDebug()<<"++++Next instruction: "<<cmd_line_following.at(i);
            }
        }
        //--------------------------------------------------------------------
        //--------------------------------------------------------------------
        //--------------------------------------------------------------------
    }


    //Sum all of the command line parameters in a single string.
    cmd_line_final = ' ';
    for(int i = 0; i < cmd_line_previous.size(); i++){
        cmd_line_final += cmd_line_previous.at(i);
        cmd_line_final += ' ';
    }
    cmd_line_final += cmd_line_current;
    cmd_line_final += ' ';
    for(int i = 0; i < cmd_line_following.size(); i++){
        cmd_line_final += cmd_line_following.at(i);
        cmd_line_final += ' ';
    }
    qDebug()<<"****"<<cmd_line_final;

    invoke_cmd_line(&bin_model_path, &bin_model_file, &cmd_line_final);

    enrgfield[statement_num].asm_base_energy_cost << energy;
}

QString powotsimulator::generate_cmd_line(energyfield_t *enrgfield, long asm_mnemonic_num, unsigned long cmd_index, instr_pipln_t instr_type){
    QString temp_line;

    temp_line = "--instr_";

    switch(instr_type){
    case INSTRUCTION_PREVIOUS:
        temp_line += "prev_";
        temp_line += QString::number(cmd_index, 10);
        break;
    case INSTRUCTION_CURRENT:
        temp_line += 'c';
        break;
    case INSTRUCTION_FOLLOWING:
        temp_line += "foll_";
        temp_line += QString::number(cmd_index, 10);
        break;
    default:
        temp_line += 'c';
    }

    temp_line += " \"";
    temp_line += QString::number(enrgfield->frequency_domain.at(asm_mnemonic_num), 'f', 3);
    temp_line += " ";
    temp_line += QString::number(enrgfield->voltage_domain.at(asm_mnemonic_num), 'f', 3);
    temp_line += " ";
    temp_line += QString::number(enrgfield->temperature_domain.at(asm_mnemonic_num), 'f', 3);
    temp_line += " 0x";
    temp_line += QString::number(enrgfield->asm_vma.at(asm_mnemonic_num), 16);
    temp_line += " ";
    temp_line += enrgfield->asm_instr.at(asm_mnemonic_num);
    temp_line += "\"";

    return temp_line;
}
