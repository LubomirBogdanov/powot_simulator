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

void powotsimulator::parse_model_data(void){
    QString line;
    QString temp_str;

    unsigned long operand_temp;
    float volt_temp;
    float freq_temp;
    float tempr_temp;
    float exec_temp;
    float current_temp;

    bool ok;
    unsigned long instruction_count = 0;


    num_instr_in_mdl_file = 0;

    //Count the number of instructions in the entire file
    for(long i = 0; i < mcu_model.size(); i++){
        line = mcu_model.at(i);
        if(line.contains("INSTR")){
            num_instr_in_mdl_file++;
        }
    }
    //qDebug()<<"num_instr_in_mdl_file = "<<num_instr_in_mdl_file;

    mdl = new model_data_t[num_instr_in_mdl_file];

    qDebug()<<"(powotsimulator) Reading model data ... ";

    //Read instruction data---------------------------------------------
    for(long i = 0; i < mcu_model.size(); i++){
        line = mcu_model.at(i);
        //qDebug()<<"****"<<line;

        if(line.contains("INSTR")){
            //qDebug()<<"++++instruction_count = "<<instruction_count<<" "<<line;

            if(instruction_count >= num_instr_in_mdl_file){
                break;
            }

            mdl[instruction_count].mnemonic = line.section('\t', 1, 1);

            if((i+1) >= mcu_model.size()){
                break;
            }

            line = mcu_model.at(i+1);
            mdl[instruction_count].instr_type = line.section('\t', 1, 1);

            for(long j = i+2; j < mcu_model.size(); j++){
                line = mcu_model.at(j);
                //qDebug()<<"----"<<line;

                if(instruction_count >= num_instr_in_mdl_file){
                    break;
                }

                if(line.contains("INSTR")){ //INSTR is found a second time. This means that the previour intstruction has ended
                    //qDebug()<<",,,,INSTR tag found for 2nd time!";
                    //if((unsigned long) j >= num_instr_in_mdl_file){//Instruction processing completed
                    //    qDebug()<<"\\\\\\\\Instruction processing completed!";

                    //    break;
                    //}
                    instruction_count++;
                    //i = j; //Go to the next instruction

                    break;
                }

                temp_str = line.section('\t', 0, 0);
                mdl[instruction_count].addr_range_name << temp_str;

                temp_str = line.section('\t', 1, 1);
                tempr_temp = temp_str.toFloat(&ok);
                if(!ok){
                    tempr_temp = 0.0;
                }
                mdl[instruction_count].temperature_domain << tempr_temp;

                temp_str = line.section('\t', 2, 2);
                volt_temp = temp_str.toFloat(&ok);
                if(!ok){
                    volt_temp = 0.0;
                }
                mdl[instruction_count].voltage_domain << volt_temp;

                temp_str = line.section('\t', 3, 3);
                freq_temp = temp_str.toFloat(&ok);
                if(!ok){
                    freq_temp = 0.0;
                }
                mdl[instruction_count].frequency_domain << freq_temp;

                temp_str = line.section('\t', 4, 4);
                operand_temp = temp_str.toInt(&ok, 10);
                if(!ok){
                    operand_temp = 0.0;
                }
                mdl[instruction_count].num_of_operands << operand_temp;

                temp_str = line.section('\t', 5, 5);
                temp_str = temp_str.section(',', 0, 0);
                current_temp = temp_str.toFloat(&ok);
                if(!ok){
                    current_temp = 0.0;
                }
                mdl[instruction_count].current << current_temp;

                temp_str = line.section('\t', 5, 5);
                temp_str = temp_str.section(',', 1, 1);
                exec_temp = temp_str.toFloat(&ok);
                if(!ok){
                    exec_temp = 0.0;
                }
                mdl[instruction_count].exec_time << exec_temp;

                mdl[instruction_count].energy << (mdl[instruction_count].exec_time.last() * mdl[instruction_count].current.last() * mdl[instruction_count].voltage_domain.last())/mdl_domains.metrics_div;
            }
        }
    }

/*  qDebug()<<" ";
    for(unsigned long i = 0; i < num_instr_in_mdl_file; i++){
        qDebug()<<"@@@ "<<mdl[i].mnemonic;
        qDebug()<<"@@@ "<<mdl[i].instr_type;

        for(long j = 0; j < mdl[i].addr_range_name.size(); j++){
            qDebug()<<"@@@ "<<mdl[i].addr_range_name.at(j)<<" "<<mdl[i].temperature_domain.at(j)<<" "<<mdl[i].voltage_domain.at(j)<<" "<<mdl[i].frequency_domain.at(j)<<" "<<mdl[i].num_of_operands.at(j)<<" "<<mdl[i].current.at(j)" "<<mdl[i].exec_time.at(j)<<" "<<mdl[i].energy.at(j);
        }
    }
*/
}
