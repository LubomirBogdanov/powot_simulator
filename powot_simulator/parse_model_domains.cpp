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

void powotsimulator::parse_model_domains()
{
    QString line;
    QString temp_str;
    unsigned long addr_temp;
    unsigned long volt_domains;
    unsigned long freq_domains;
    unsigned long tempr_domains;
    unsigned long operand_domains;
    unsigned long operand_temp;
    float volt_temp;
    float freq_temp;
    float tempr_temp;
    bool ok;

    if(!(mdl_domains.addr_ranges == NULL)){
        delete [] mdl_domains.addr_ranges;
    }
    mdl_domains.addr_ranges_names.clear();
    mdl_domains.frequency_domains.clear();
    mdl_domains.num_addr_ranges = 0;
    mdl_domains.operand_domains.clear();
    mdl_domains.temperature_domains.clear();
    mdl_domains.voltage_domains.clear();    
    mdl_domains.metrics = "  ";
    mdl_domains.metrics_div = 1.0;

    for(long i = 0; i < mcu_model.size(); i++){
        line = mcu_model.at(i);

        if(line.contains("DOMAIN_START")){
            for(long j = i; j < mcu_model.size(); j++){
                line = mcu_model.at(j);
                //cout<<"---"<<mcu_model.at(j).toStdString()<<endl;
                if(line.contains("DOMAIN_END")){
                    break;
                }

                if(line.contains("ADDR")){                    
                    mdl_domains.num_addr_ranges++;
                }

                if(line.contains("VOLTAGES")){
                    volt_domains = line.count('\t');
                    volt_domains++;
                    for(unsigned long m = 1; m < volt_domains; m++){
                        temp_str = line.section('\t', m, m);
                        volt_temp = temp_str.toFloat(&ok);
                        if(!ok){
                            volt_temp = 0.0;
                        }
                        mdl_domains.voltage_domains<<volt_temp;
                    }
                }

                if(line.contains("FREQUENCIES")){
                    freq_domains = line.count('\t');
                    freq_domains++;
                    for(unsigned long m = 1; m < freq_domains; m++){
                        temp_str = line.section('\t', m, m);
                        freq_temp = temp_str.toFloat(&ok);
                        if(!ok){
                            freq_temp = 0.0;
                        }
                        mdl_domains.frequency_domains<<freq_temp;
                    }
                }

                if(line.contains("TEMPERATURES")){
                    tempr_domains = line.count('\t');
                    tempr_domains++;
                    for(unsigned long m = 1; m < tempr_domains; m++){
                        temp_str = line.section('\t', m, m);
                        tempr_temp = temp_str.toFloat(&ok);
                        if(!ok){
                            tempr_temp = 0.0;
                        }
                        mdl_domains.temperature_domains<<tempr_temp;
                    }
                }

                if(line.contains("OPERANDS")){
                    operand_domains = line.count('\t');
                    operand_domains++;
                    for(unsigned long m = 1; m < operand_domains; m++){
                        temp_str = line.section('\t', m, m);
                        operand_temp = temp_str.toInt(&ok, 10);
                        if(!ok){
                            operand_temp = 0;
                        }
                        mdl_domains.operand_domains<<operand_temp;
                    }
                }
            }

            //Allocate memory for the address ranges
            mdl_domains.addr_ranges = new QList<unsigned long>[mdl_domains.num_addr_ranges];
            unsigned long k = 0;
            for(long j = i; j < mcu_model.size(); j++){

                line = mcu_model.at(j);

                if(line.contains("DOMAIN_END")){
                    break;
                }

                if(line.contains("ADDR")){
                    mdl_domains.addr_ranges_names << line.section('\t', 1, 1);
                    temp_str = line.section('\t', 2, 2);
                    addr_temp = temp_str.toInt(&ok, 16);
                    if(!ok){
                        addr_temp = 0x00;
                    }
                    mdl_domains.addr_ranges[k] << addr_temp;

                    temp_str = line.section('\t', 3, 3);
                    addr_temp = temp_str.toInt(&ok, 16);
                    if(!ok){
                        addr_temp = 0x00;
                    }
                    mdl_domains.addr_ranges[k] << addr_temp;

                    k++;
                }
            }


            /*for(unsigned long m = 0; m < mdl_domains.num_addr_ranges; m++){
                cout<<mdl_domains.addr_ranges_names.at(m).toStdString()<<hex<<" low: "<<mdl_domains.addr_ranges[m].at(0)<<" high:"<<mdl_domains.addr_ranges[m].at(1)<<endl;
            }*/

            /*for(long m = 0; m < mdl_domains.voltage_domains.size(); m++){
                cout<<"VOLTAGES: "<<mdl_domains.voltage_domains.at(m)<<endl;
            }*/

            /*for(long m = 0; m < mdl_domains.frequency_domains.size(); m++){
                cout<<"FREQUENCIES: "<<mdl_domains.frequency_domains.at(m)<<endl;
            }*/

            /*for(long m = 0; m < mdl_domains.temperature_domains.size(); m++){
                cout<<"TEMPERATURES: "<<mdl_domains.temperature_domains.at(m)<<endl;
            }*/

            /*for(long m = 0; m < mdl_domains.operand_domains.size(); m++){
                cout<<"OPERANDS: "<<mdl_domains.operand_domains.at(m)<<endl;
            }*/
            break;
        }

        if(line.contains("METRICS")){
            mdl_domains.metrics = line.section('\t', 1, 1);
            //qDebug()<<"metrics: "<<mdl_domains.metrics;

        }

        if(line.contains("DIVISOR")){
            bool ok;
            QString tmp = line.section('\t', 1, 1);
            float divisor = tmp.toFloat(&ok);
            if(ok){
                mdl_domains.metrics_div = divisor;
            }
            else{
                 mdl_domains.metrics_div = 1.0;
            }
            //qDebug()<<"divisor: "<<mdl_domains.metrics_div;
        }
    }
}
