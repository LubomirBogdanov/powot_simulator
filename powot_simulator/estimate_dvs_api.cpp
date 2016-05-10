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

float powotsimulator::estimate_dvs_api(QString *statement, float *dvs_api_energy)
{
    float result = 0.0;

    for(long i = 0; i < dvs_api.dvs_api.size(); i++){
        if(*statement == dvs_api.dvs_api.at(i)){
            result = dvs_api.api_voltage.at(i);
            *dvs_api_energy = dvs_api.exec_energy.at(i);
        }
    }

    return result;
}
