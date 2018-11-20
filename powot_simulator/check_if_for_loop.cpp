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

bool powotsimulator::check_if_for_loop(QString statement){
    bool flag = 0;
    int num_of_semicolon = 0;
    int i = 0;

    if(statement.contains("/*")){
        int start = statement.indexOf('/');
        int end = statement.indexOf('/', start+1);
        statement.remove(start, end);
        //qDebug()<<"check_if_for_loop: no comments statement = "<<statement;
    }

    //qDebug()<<"statement: "<<statement;
    if(statement.contains("for")){
        if(statement.contains(";")){
            while(statement.indexOf(";", i) != -1){
                i++;
                num_of_semicolon++;
                if(num_of_semicolon == 2){
                    flag = 1;
                    break;
                }
            }
        }
    }
    //qDebug()<<" ";

    return flag;
}
