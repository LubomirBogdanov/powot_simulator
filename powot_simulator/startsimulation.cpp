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

/*!
 * \brief Start the energy simulation.
 * \param size - the size of the returned table. Equals the number of lines of the input source file.
 * \return A pointer to an array of 'energyfield' structs. The array is valid as long as the powotsimulator object is
 * not destroyed.
 */
energyfield_t *powotsimulator::start_simulation(quint32 *size){
    float total_base_cost = 0.0;
    bool no_debug_info;
    bool symbol_found = 0;

    objdump_file(&objectfile_dir, &object_file_contents);

    symbollist_file(&objectfile_dir, &symbollist_contents);

    gdbdump_file(&objectfile_dir, &source_entry_point, &entry_point_symbol_contents);

 /*   for(long i = 0; i < entry_point_symbol_contents.size(); i++){
        cout<<"entry_point_symbol_contents "<<entry_point_symbol_contents.at(i).toStdString()<<endl;
    }
 */

    for(long i = 0; i < entry_point_symbol_contents.size(); i++){
        if(entry_point_symbol_contents.at(i).contains('{')){
            symbol_found = 1;
        }
    }

    if(!entry_point_symbol_contents.isEmpty() && symbol_found){
        e_table_size = count_number_of_statements(&entry_point_symbol_contents, &no_debug_info);
        cout<<"(powotsimulator) Function "<<source_entry_point.toStdString()<<" consists of "<<e_table_size<<" lines! "<<endl;        
        e_table = new energyfield_t[e_table_size];        
        analyze_statements(&entry_point_symbol_contents, e_table);        

        //Produce C statement energy costs out of the assembly costs.
        for(unsigned long i = 0; i < e_table_size; i++){
            if((!e_table[i].function_call) && (!e_table[i].dvs_api) && (!e_table[i].dfs_api)){
                e_table[i].statement_energy_cost = 0.0;
            }

            if(e_table[i].function_call){
                e_table[i].statement_energy_cost *= e_table[i].repeated;
            }

            for(long j = 0; j < e_table[i].asm_instr.size(); j++){                
                e_table[i].statement_energy_cost += e_table[i].asm_repeated.at(j);
            }            
        }

        for(unsigned long i = 0; i < e_table_size; i++){
            total_base_cost += e_table[i].statement_energy_cost;
        }
        cout<<"(powotsimulator) Total function "<<source_entry_point.toStdString()<<" base energy cost: "<<fixed<<setprecision(3)<<total_base_cost<<" "<<mdl_domains.metrics.toStdString()<<endl;

        *size = e_table_size;
    }
    else{
        err_message.display_error(SRC_ENTRY_NOT_FOUND, &source_entry_point);
        exit(-1);
    }

    return e_table;
}
