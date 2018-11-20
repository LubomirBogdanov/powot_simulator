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

bool powotsimulator::check_if_function_call(QString statement){    
    bool is_function_call = 0;

/*    if(
            statement.contains('(') &&
            !statement.contains("for") &&
            !statement.contains("while") &&
            !statement.contains("Copyright")
            ){
        is_function_call = 1;
    }
    else {
        is_function_call = 0;
    }
    */

    //qDebug()<<"check_if_function_call: statement = "<<statement;

    if(statement.contains('(')){
        statement = statement.section('(', 0, 0);
        if(!statement.isEmpty()){

            if(statement.contains('=')){
                statement = statement.section('=', -1, 1);
            }

            for(long i = 0; i < symbollist_contents.size(); i++){

                if(statement.trimmed().isEmpty()){
                    break;
                }

                if(statement.trimmed() == symbollist_contents.at(i).trimmed()){
                    //qDebug()<<"check_if_function_call: #########found in list of symbols!###########";
                    //qDebug()<<"check_if_function_call: statement.trimmed() = "<<statement.trimmed()<<" <-> "<<symbollist_contents.at(i).trimmed();
                    is_function_call = 1;
                    break;
                }
            }
        }
    }

    return is_function_call;
}
