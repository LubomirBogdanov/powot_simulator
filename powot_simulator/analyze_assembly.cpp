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
 * \brief powotsimulator::analyze_assembly - take a section of assembly code
 * and return the base energy cost of it. Only default values are considered
 * for the domains except the vma address & number of operands (it is available).
 *
 * \param asm_section - a list of assembly instructions to be analyzed.
 * \return A float number of the base energy cost.
 */
float powotsimulator::analyze_assembly(QStringList *asm_section){
    energyfield_t e_field;
    QString asm_mnemonic;
    QString asm_instruction;
    QString asm_vma_str;    
    unsigned long asm_vma;
    bool ok, instr_found = 0;
    float energy_cost_of_section = 0.0;    

    //qDebug()<<"analyze_assembly: ";

    for(long i = 0; i < asm_section->size(); i++){

        asm_mnemonic = asm_section->at(i).simplified();
        asm_instruction = asm_mnemonic.section(':', 1, 1);
        asm_instruction = asm_instruction.simplified();
        //qDebug()<<"analyze_assembly: asm_mnemonic = "<<asm_mnemonic;
        //qDebug()<<"analyze_assembly: asm_instruction = "<<asm_instruction;
        asm_mnemonic = asm_mnemonic.trimmed();        
        asm_vma_str = asm_mnemonic;        

        asm_mnemonic = asm_mnemonic.section(' ', 2, 2);        


        asm_vma_str = asm_vma_str.section('x', 1, 1);
        asm_vma_str = asm_vma_str.section(' ', 0, 0);
        //asm_vma_str = asm_vma_str.prepend("0x");

        asm_vma = asm_vma_str.toInt(&ok, 16);
        if(!ok){
            asm_vma = 0x00;
        }

        if(find_mnemonic_in_mdl(&asm_mnemonic)){

            //e_field.addr_range_name << def_domains.default_addr_range;
            e_field.frequency_domain << def_domains.default_frequency;
            //e_field.num_of_operands << def_domains.default_operand;
            e_field.temperature_domain << def_domains.default_temperature;
            e_field.voltage_domain << def_domains.default_voltage;
            e_field.asm_vma << asm_vma;


            //Process number of operands
            e_field.num_of_operands << estimate_num_operands(asm_instruction);


            //Match the address asm_vma with the corresponding address domain name from the model file and fill in the corresponding ASM field.
            for(unsigned long j = 0; j < mdl_domains.num_addr_ranges; j++){
                if((mdl_domains.addr_ranges[j].at(0) <= e_field.asm_vma.last()) && (e_field.asm_vma.last() <= mdl_domains.addr_ranges[j].at(1))){
                    //qDebug()<<"instruction "<<asm_mnemonic<<" at 0x"<<hex<<asm_vma<<" is in: "<<mdl_domains.addr_ranges_names[i];
                    e_field.addr_range_name << mdl_domains.addr_ranges_names[j];
                    instr_found = 1;
                    break;
                }
            }

            if(!instr_found){
                instr_found = 0;
                err_message.display_error(DOMAIN_NOT_FOUND_IN_MDL, &asm_mnemonic);
                e_field.addr_range_name << def_domains.default_addr_range;
            }

            assign_energy_cost_tab_lut(asm_mnemonic, i, &e_field);
        }
        else{
                e_field.asm_base_energy_cost << 0.0;
        }

        energy_cost_of_section += e_field.asm_base_energy_cost.last();
    }

    //qDebug()<<"analyze_assembly: "<<energy_cost_of_section;

    return energy_cost_of_section;
}
