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
 * \brief powotsimulator::estimate_for_loop_extend - check how many statements are there inside the for( ) loop.
 * \param arr - an array with energy fields for each line of code.
 * \param energy_field_num - current energy field (line number of source code) being processed.
 *
 * \return An integer showing how many statements after the beginning of the for( ) loop are included in it.
 */
unsigned long powotsimulator::estimate_for_loop_extend(energyfield_t *arr, unsigned long current_statement, unsigned long energy_field_num){
    unsigned long open_bracket = 0;
    unsigned long close_bracket = 0;
    unsigned long i;

    //qDebug()<<"***"<<arr[current_statement].statement;

    for(i = current_statement; i <= energy_field_num; i++){
        if(arr[i].statement.contains("{")){
            open_bracket++;
        }
        if(arr[i].statement.contains("}")){
            close_bracket++;
        }

        if(open_bracket == close_bracket){
            //qDebug()<<"CLOSING:";
            //qDebug()<<"@@@@"<<arr[i].statement;
            break;
        }
        //qDebug()<<"@@@@"<<arr[i].statement;
    }

    return arr[i].line_number;
}
