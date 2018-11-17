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

unsigned long powotsimulator::count_number_of_statements(QStringList *sym_cont, bool *no_debug_info){
    QString line;
    QStringList temp_symbol;
    long temp_symbol_size;
    bool is_digit;    

    //Get the line numbers from the source file that correspond to each statement in the symbol (function)
    for(long i = 0; i < sym_cont->size(); i++){
        line = sym_cont->at(i).simplified();
        line = line.trimmed();

        line = line.section(' ', 0, 0);
        if(line.contains("0x")){
            line = "";
        }

        line.toInt(&is_digit, 10);
        if(!is_digit){
            line = "";
        }
        temp_symbol << line;
    }

    //Remove all lines not containing line numbers at the beginning
    temp_symbol_size = temp_symbol.size();
    for(long i = 0; i < temp_symbol_size; i++){
        if(temp_symbol.at(i).isEmpty()){
            temp_symbol.removeAt(i);
            temp_symbol_size--;
            i--;
        }
    }

    *no_debug_info = 0;

    //If no debugging information is included this may result in number of line = 0
    //which would crash the process. So check if this is the case and handle it
    //accordingly.
    temp_symbol_size = temp_symbol.size();
    if(temp_symbol_size == 0){
        for(long i = 0; i < sym_cont->size(); i++){
            line = sym_cont->at(i).simplified();
            line = line.trimmed();

            line = line.section(' ', 0, 0);
            if(line.contains("0x")){
                temp_symbol<<line;
            }
        }

        *no_debug_info = 1;
    }


 /*   for(long i = 0; i < temp_symbol.size(); i++)
    {
        cout<<"vvv"<<temp_symbol.at(i).toStdString()<<endl;
    }*/

    return temp_symbol.size();
}
