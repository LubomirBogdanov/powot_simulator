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

void powotsimulator::convert_bytearray_stringlist(QByteArray *input, QStringList *output){
    quint32 cnt = 0;
    char linebuff[300];

    for(qint32 i = 0; i < input->size(); i++){
        linebuff[cnt++] = input->at(i);
        if(input->at(i) == '\n'){
            linebuff[cnt+1] = '\0';
            QString temp = linebuff;
            *output << temp;
            cnt = 0;
            for(int j = 0; j < 300; j++){
                linebuff[j] = '\0';
            }
        }
    }
}
