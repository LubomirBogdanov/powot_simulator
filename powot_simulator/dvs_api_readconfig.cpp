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

void powotsimulator::dvs_api_readconfig(void){
    QString line;
    QString param;
    bool ok;
    float fl_param;

    for(long i = 0; i < mcu_model.size(); i++){
        line = mcu_model.at(i);

        if(line.contains("DVS_API_START")){
            for(long j = i+1; j < mcu_model.size(); j++){
                line = mcu_model.at(j);

                if(line.contains("DVS_API_END")){
                    break;
                }
                //qDebug()<<"---"<<mcu_model.at(j);


                param = line.section('\t', 0, 0);
                dvs_api.dvs_api<<param;
                //qDebug()<<"+++param "<<param;

                param = line.section('\t', 1, 1);
                fl_param = param.toFloat(&ok);
                if(ok == 0){
                    dvs_api.api_voltage << 0.0;
                }
                else{
                    dvs_api.api_voltage << fl_param;
                }
                //qDebug()<<"+++param "<<dvs_api.api_voltage.last();

                param = line.section('\t', 2, 2);
                fl_param = param.toFloat(&ok);
                if(ok == 0){
                    dvs_api.exec_time << 0.0;
                }
                else{
                    dvs_api.exec_time << fl_param;
                }
                //qDebug()<<"+++param "<<dvs_api.exec_time.last();

                param = line.section('\t', 3, 3);
                fl_param = param.toFloat(&ok);
                if(ok == 0){
                    dvs_api.exec_energy << 0.0;
                }
                else{
                    dvs_api.exec_energy << fl_param;
                }
                //qDebug()<<"+++param "<<dvs_api.exec_energy.last();
            }
        }
    }

    if(!dvs_api.dvs_api.isEmpty()){
        mdl_domains.dvs_api = dvs_api; //For get_model_domains
    }
}
