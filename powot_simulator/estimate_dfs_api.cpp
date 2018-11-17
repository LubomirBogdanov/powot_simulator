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

float powotsimulator::estimate_dfs_api(QString *statement, float *dfs_api_energy){
    float result = 0.0;

    for(long i = 0; i < dfs_api.dfs_api.size(); i++){
        if(*statement == dfs_api.dfs_api.at(i)){
            result = dfs_api.api_frequency.at(i);
            *dfs_api_energy = dfs_api.exec_energy.at(i);
        }
    }

    return result;
}

