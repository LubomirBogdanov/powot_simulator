/*
    Copyright (C) 2018 Lubomir Bogdanov

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

void powotsimulator::parse_aux_model_xml(void){
    bool ok;
    QString tag_text;
    QList<unsigned long> temp_addr_ranges;

    qDebug()<<"(powotsimulator) Parsing auxiliary model XML file ...";

    if(mdl_domains.addr_ranges != NULL){
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

    QFile file(bin_model_aux_xml_file);
    file.open(QFile::ReadOnly | QFile::Text);
    QXmlStreamReader reader(&file);

    if (reader.readNextStartElement()) {
        if (reader.name() == "auxiliary_model"){
            while(reader.readNextStartElement()){
                if(reader.name() == "metrics"){
                    tag_text = reader.readElementText();
                    mdl_domains.metrics = tag_text;
                }
                else if(reader.name() == "divisor"){
                    tag_text = reader.readElementText();
                    mdl_domains.metrics_div = tag_text.toFloat(&ok);
                }
                else if(reader.name() == "domains"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "memory_ranges"){
                            while(reader.readNextStartElement()){
                                mdl_domains.num_addr_ranges++;
                                if(reader.name() == "memory"){
                                    while(reader.readNextStartElement()){
                                        if(reader.name() == "memory_name"){
                                            tag_text = reader.readElementText();
                                            mdl_domains.addr_ranges_names << tag_text;
                                        }
                                        else if(reader.name() == "start"){
                                            tag_text = reader.readElementText();
                                            temp_addr_ranges << tag_text.toULong(&ok, 16);
                                        }
                                        else if(reader.name() == "end"){
                                            tag_text = reader.readElementText();
                                            temp_addr_ranges << tag_text.toULong(&ok, 16);
                                        }
                                    }
                                }
                            }
                        }
                        else if(reader.name() == "temperatures"){
                            while(reader.readNextStartElement()){
                                if(reader.name() == "temperature"){
                                    tag_text = reader.readElementText();
                                    mdl_domains.temperature_domains << tag_text.toFloat(&ok);
                                }
                            }
                        }
                        else if(reader.name() == "voltages"){
                            while(reader.readNextStartElement()){
                                if(reader.name() == "voltage"){
                                    tag_text = reader.readElementText();
                                    mdl_domains.voltage_domains << tag_text.toFloat(&ok);
                                }
                            }
                        }
                        else if(reader.name() == "frequencies"){
                            while(reader.readNextStartElement()){
                                if(reader.name() == "frequency"){
                                    tag_text = reader.readElementText();
                                    mdl_domains.frequency_domains << tag_text.toFloat(&ok);
                                }
                            }
                        }
                        else if(reader.name() == "number_of_operands"){
                            while(reader.readNextStartElement()){
                                if(reader.name() == "operands"){
                                    tag_text = reader.readElementText();
                                    mdl_domains.operand_domains << tag_text.toULong(&ok, 10);
                                }
                            }
                        }
                    }
                }
                else if(reader.name() == "dvs_apis"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "dvs_api"){
                            while(reader.readNextStartElement()){
                                if(reader.name() == "dvs_api_prototype"){
                                    tag_text = reader.readElementText();
                                    mdl_domains.dvs_api.dvs_api << tag_text;
                                }
                                else if(reader.name() == "voltage"){
                                    tag_text = reader.readElementText();
                                    mdl_domains.dvs_api.api_voltage << tag_text.toFloat(&ok);
                                }
                                else if(reader.name() == "exec_time"){
                                    tag_text = reader.readElementText();
                                    mdl_domains.dvs_api.exec_time << tag_text.toFloat(&ok);
                                }
                                else if(reader.name() == "energy"){
                                    tag_text = reader.readElementText();
                                    mdl_domains.dvs_api.exec_energy << tag_text.toFloat(&ok);
                                }
                            }
                        }
                    }
                }
                else if(reader.name() == "dfs_apis"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "dfs_api"){
                            while(reader.readNextStartElement()){
                                if(reader.name() == "dfs_api_prototype"){
                                    tag_text = reader.readElementText();
                                    mdl_domains.dfs_api.dfs_api << tag_text;
                                }
                                else if(reader.name() == "frequency"){
                                    tag_text = reader.readElementText();
                                    mdl_domains.dfs_api.api_frequency << tag_text.toFloat(&ok);
                                }
                                else if(reader.name() == "exec_time"){
                                    tag_text = reader.readElementText();
                                    mdl_domains.dfs_api.exec_time << tag_text.toFloat(&ok);
                                }
                                else if(reader.name() == "energy"){
                                    tag_text = reader.readElementText();
                                    mdl_domains.dfs_api.exec_energy << tag_text.toFloat(&ok);
                                }
                            }
                        }
                    }
                }
                else{
                    reader.skipCurrentElement();
                }
            }
        }
    }

    if(!temp_addr_ranges.isEmpty()){
        int size = temp_addr_ranges.size();
        mdl_domains.addr_ranges = new QList<unsigned long>[mdl_domains.num_addr_ranges];
        for(unsigned long i = 0, j = 0; i < mdl_domains.num_addr_ranges; i++, j+=2){
            mdl_domains.addr_ranges[i] << temp_addr_ranges.at(j);
            mdl_domains.addr_ranges[i] << temp_addr_ranges.at(j+1);
        }
    }

    dvs_api = mdl_domains.dvs_api;
    dfs_api = mdl_domains.dfs_api;

/*    for(unsigned long m = 0; m < mdl_domains.num_addr_ranges; m++){
        qDebug()<<mdl_domains.addr_ranges_names.at(m)<<hex<<" low: "<<mdl_domains.addr_ranges[m].at(0)<<" high:"<<mdl_domains.addr_ranges[m].at(1);
    }

    for(long m = 0; m < mdl_domains.voltage_domains.size(); m++){
        qDebug()<<"VOLTAGES: "<<mdl_domains.voltage_domains.at(m);
    }

    for(long m = 0; m < mdl_domains.frequency_domains.size(); m++){
        qDebug()<<"FREQUENCIES: "<<mdl_domains.frequency_domains.at(m);
    }

    for(long m = 0; m < mdl_domains.temperature_domains.size(); m++){
        qDebug()<<"TEMPERATURES: "<<mdl_domains.temperature_domains.at(m);
    }

    for(long m = 0; m < mdl_domains.operand_domains.size(); m++){
        qDebug()<<"OPERANDS: "<<mdl_domains.operand_domains.at(m);
    }

    qDebug()<<"metrics: "<<mdl_domains.metrics;
    qDebug()<<"divisor: "<<mdl_domains.metrics_div;

    for(long i = 0; i < mdl_domains.dfs_api.api_frequency.size(); i++){
        qDebug()<<"=======================";
        qDebug()<<"dfs_api: "<<mdl_domains.dfs_api.dfs_api.at(i);
        qDebug()<<"api_frequency: "<<mdl_domains.dfs_api.api_frequency.at(i);
        qDebug()<<"exec_energy: "<<mdl_domains.dfs_api.exec_energy.at(i);
        qDebug()<<"exec_time: "<<mdl_domains.dfs_api.exec_time.at(i);
        qDebug()<<"=======================";
    }

    for(long i = 0; i < mdl_domains.dvs_api.api_voltage.size(); i++){
        qDebug()<<"=======================";
        qDebug()<<"dvs_api: "<<mdl_domains.dvs_api.dvs_api.at(i);
        qDebug()<<"api_voltage: "<<mdl_domains.dvs_api.api_voltage.at(i);
        qDebug()<<"exec_energy: "<<mdl_domains.dvs_api.exec_energy.at(i);
        qDebug()<<"exec_time: "<<mdl_domains.dvs_api.exec_time.at(i);
        qDebug()<<"=======================";
    }*/
}
