/*
    Copyright (C) 2016 Lubomir Bogdanov

    Contributor Lubomir Bogdanov <lubomirb@yahoo.com>

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

void powotsimulator::assign_energy_cost(QString asm_mnemonic, long asm_mnemonic_num, energyfield_t *enrgfield){
    float energy = 0;
    long index_addr = -1;
    long index_temp = -1;
    long index_voltage = -1;
    long index_frequency = -1;
    long index_operands = -1;
    bool err = 0;    

    //cout<<"assign_energy_cost: asm_mnemonic = "<<asm_mnemonic.toStdString()<<endl;

    //--------------------------------------------------------------------
    //Extract the corresponding energy value from the model file----------
    //--------------------------------------------------------------------
    for(unsigned long i = 0; i < num_instr_in_mdl_file; i++){
        if(mdl[i].mnemonic == asm_mnemonic){

            //cout<<"assign_energy_cost: mdl[i].mnemonic = "<<mdl[i].mnemonic.toStdString()<<endl;

            for(long j = 0; j < mdl[i].addr_range_name.size(); j++){
                if(enrgfield->addr_range_name.at(asm_mnemonic_num) == mdl[i].addr_range_name.at(j)){
                    index_addr = j;
                    break;
                }
            }
            if(index_addr == -1){
                cout<<"(powotsimulator) ERROR: index_addr <<"<<enrgfield->addr_range_name.at(asm_mnemonic_num).toStdString()<<">> domain error!"<<endl;
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
                cout<<"(powotsimulator) ERROR: index_temp <<"<<enrgfield->temperature_domain.at(asm_mnemonic_num)<<">> domain error!"<<endl;
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
                cout<<"(powotsimulator) ERROR: index_voltage <<"<<enrgfield->voltage_domain.at(asm_mnemonic_num)<<">> domain error!"<<endl;
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
                cout<<"(powotsimulator) ERROR: index_frequency <<"<<enrgfield->frequency_domain.at(asm_mnemonic_num)<<">> domain error!"<<endl;
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
                cout<<"(powotsimulator) ERROR: index_operands <<"<<enrgfield->num_of_operands.at(asm_mnemonic_num)<<">> domain error!"<<endl;
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

/*
void powotsimulator::assign_energy_cost(QString asm_mnemonic, energyfield_t *enrgfield)
{
    float energy = 0;
    long index_addr = 0;
    long index_temp = 0;
    long index_voltage = 0;
    long index_frequency = 0;
    long index_main = 0;    

    //--------------------------------------------------------------------
    //Extract the corresponding energy value from the model file----------
    //--------------------------------------------------------------------
    for(unsigned long i = 0; i < num_instr_in_mdl_file; i++)
    {        
        if(mdl[i].mnemonic == asm_mnemonic){            
            index_addr = mdl[i].addr_range_name.indexOf(enrgfield->addr_range_name.last(), 0);                        
            if(index_addr == -1) break;                        
            index_temp = mdl[i].temperature_domain.indexOf(enrgfield->temperature_domain.last(), index_addr);                        
            if(index_temp == -1) break;                        
            index_voltage = mdl[i].voltage_domain.indexOf(enrgfield->voltage_domain.last(), index_temp);                        
            if(index_voltage == -1) break;            
            index_frequency = mdl[i].frequency_domain.indexOf(enrgfield->frequency_domain.last(), index_voltage);
            if(index_frequency == -1) break;
            index_main = index_addr + index_temp + index_voltage + index_frequency;            
            energy = mdl[i].energy.at(index_main);                        
            break;
        }

        if((index_addr == -1)||
           (index_temp == -1)||
           (index_voltage == -1)||
           (index_frequency == -1)
          ){            
            err_message.display_error(DOMAIN_NOT_FOUND_IN_MDL, &asm_mnemonic);
            energy = 0.0;
        }
    }
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------

    enrgfield->asm_base_energy_cost << energy;    
}
*/
