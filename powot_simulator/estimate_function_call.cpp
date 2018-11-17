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

float powotsimulator::estimate_function_call(QString function_name){
    QStringList symbol_contents;
    energyfield_t *table;
    unsigned long table_size;
    float total_base_cost;
    bool no_debug_info;

    //cout<<"estimate_function_call: function_name = "<<function_name.toStdString()<<endl;

    if(function_name.contains('=')){
        function_name = function_name.section('=', -1, 1);
        //cout<<"estimate_function_call: function_name AFTER: "<<function_name.toStdString()<<endl;
    }

    gdbdump_file(&objectfile_dir, &function_name, &symbol_contents);

    if(!symbol_contents.isEmpty()){
        table_size = count_number_of_statements(&symbol_contents, &no_debug_info);
        //cout<<"(powotsimulator) Function "<<function_name.toStdString()<<" consists of "<<table_size<<" lines! "<<endl;

        if(no_debug_info){
            total_base_cost = analyze_assembly(&symbol_contents);            
        }
        else {
            table = new energyfield_t[table_size];
            analyze_statements(&symbol_contents, table);

            //Produce C statement energy costs out of the assembly costs.
            for(unsigned long i = 0; i < table_size; i++){
                if(!table[i].function_call){
                    table[i].statement_energy_cost = 0.0;
                }

                for(long j = 0; j < table[i].asm_instr.size(); j++){
                    table[i].statement_energy_cost += table[i].asm_repeated.at(j);
                }
            }

            for(unsigned long i = 0; i < table_size; i++){
                total_base_cost += table[i].statement_energy_cost;
            }

            delete [] table;
        }
    }

    cout<<"(powotsimulator) Total function "<<function_name.toStdString()<<" base energy cost: "<<fixed<<setprecision(3)<<total_base_cost<<" "<<mdl_domains.metrics.toStdString()<<endl;

    return total_base_cost;
}
