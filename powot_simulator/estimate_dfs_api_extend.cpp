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

unsigned long powotsimulator::estimate_dfs_api_extend(energyfield_t *arr, unsigned long current_statement, unsigned long energy_field_num){
    unsigned long i;
    unsigned long dfs_extend = 0;
    bool end_found = 0;

    for(i = current_statement+1; i < energy_field_num; i++){
        for(long j = 0; j < dfs_api.dfs_api.size(); j++){
            if(arr[i].statement == dfs_api.dfs_api.at(j)){
                end_found = 1;
                break;
            }
        }

        if(end_found){
            break;
        }

        dfs_extend++;
    }

    if(i == energy_field_num){
        dfs_extend++;
    }

    return dfs_extend;
}

