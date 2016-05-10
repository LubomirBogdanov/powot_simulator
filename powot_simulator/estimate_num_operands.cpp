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

unsigned long powotsimulator::estimate_num_operands(QString asm_instruction)
{  
    unsigned long result = 0;

    //qDebug()<<"estimate_num_operands: asm = "<<asm_instruction;
    if(asm_instruction.contains(';')){
        unsigned long pos = asm_instruction.indexOf(';');
        asm_instruction.truncate(pos);
    }
    //qDebug()<<"estimate_num_operands: AFTER asm = "<<asm_instruction;

    if(asm_instruction.contains('[')){
        QString str = asm_instruction.section('[', 0, 0);
        //qDebug()<<"cut [ "<<asm_instruction<<" <->"<<str;
        result = str.count(',');
        result++;
    }
    else if(asm_instruction.contains('{')){
         QString str = asm_instruction.section('{', 0, 0);
         //qDebug()<<"cut [ "<<asm_instruction<<" <->"<<str;
         result = str.count(',');
         result++;
    }
    else if(asm_instruction.contains(',')){
        result = asm_instruction.count(',');
        result++;
    }
    else if(asm_instruction.contains(' ')){
        QString str = asm_instruction.section(' ', 1, 1);
        //qDebug()<<"cut <space> "<<asm_instruction<<" <->"<<str;
        if(str.isEmpty()){
            result = 0;
        }
        else{
            result = 1;
        }
    }

    return result;
}
