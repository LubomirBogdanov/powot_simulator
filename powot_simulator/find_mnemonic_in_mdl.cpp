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

bool powotsimulator::find_mnemonic_in_mdl(QString *asm_mnemonic){
    bool instr_found = 0;

    //qDebug()<<"find_mnemonic_in_mdl: asm_mnemonic = "<<asm_mnemonic;

    //Check to see if we can find the asm_mnemonic in the model file
    for(unsigned long i = 0; i < num_instr_in_mdl_file; i++){
        if(mdl[i].mnemonic == *asm_mnemonic){
            instr_found = 1;
            break;
        }
    }

    if(!instr_found){
        err_message.display_error(INSTR_NOT_FOUND_IN_MDL, asm_mnemonic);
    }

    return instr_found;
}
