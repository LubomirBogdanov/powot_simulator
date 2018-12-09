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
    QString tag_text;

    qDebug()<<"(powotsimulator) Parsing auxiliary model XML file ...";

    QFile file(bin_model_aux_xml_file);
    file.open(QFile::ReadOnly | QFile::Text);
    QXmlStreamReader reader(&file);

    if (reader.readNextStartElement()) {
        if (reader.name() == "auxiliary_model"){
            while(reader.readNextStartElement()){
                if(reader.name() == "metrics"){
                    tag_text = reader.readElementText();
                    qDebug()<<"-->"<<tag_text;
                }
                else if(reader.name() == "divisor"){
                    tag_text = reader.readElementText();
                    qDebug()<<"++>"<<tag_text;
                }
                else if(reader.name() == "domains"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "memory"){
                            while(reader.readNextStartElement()){
                                if(reader.name() == "flash_memory"){
                                    while(reader.readNextStartElement()){
                                        if(reader.name() == "start"){
                                            tag_text = reader.readElementText();
                                            qDebug()<<"++>flash_memory_start: "<<tag_text;
                                        }
                                        else if(reader.name() == "end"){
                                            tag_text = reader.readElementText();
                                            qDebug()<<"++>flash_memory_end: "<<tag_text;
                                        }
                                    }
                                }
                                else if(reader.name() == "sram_memory"){
                                    while(reader.readNextStartElement()){
                                        if(reader.name() == "start"){
                                            tag_text = reader.readElementText();
                                            qDebug()<<"++>sram_memory_start: "<<tag_text;
                                        }
                                        else if(reader.name() == "end"){
                                            tag_text = reader.readElementText();
                                            qDebug()<<"++>sram_memory_end: "<<tag_text;
                                        }
                                    }
                                }
                            }
                        }
                        else if(reader.name() == "temperatures"){
                            while(reader.readNextStartElement()){
                                if(reader.name() == "temperature"){
                                    tag_text = reader.readElementText();
                                    qDebug()<<"++>temperature: "<<tag_text;
                                }
                            }
                        }
                        else if(reader.name() == "voltages"){
                            while(reader.readNextStartElement()){
                                if(reader.name() == "voltage"){
                                    tag_text = reader.readElementText();
                                    qDebug()<<"++>voltage: "<<tag_text;
                                }
                            }
                        }
                        else if(reader.name() == "frequencies"){
                            while(reader.readNextStartElement()){
                                if(reader.name() == "frequency"){
                                    tag_text = reader.readElementText();
                                    qDebug()<<"++>frequency: "<<tag_text;
                                }
                            }
                        }
                        else if(reader.name() == "number_of_operands"){
                            while(reader.readNextStartElement()){
                                if(reader.name() == "operands"){
                                    tag_text = reader.readElementText();
                                    qDebug()<<"++>operands: "<<tag_text;
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
                                    qDebug()<<"++>dvs_api_prototype: "<<tag_text;
                                }
                                else if(reader.name() == "voltage"){
                                    tag_text = reader.readElementText();
                                    qDebug()<<"++>voltage: "<<tag_text;
                                }
                                else if(reader.name() == "exec_time"){
                                    tag_text = reader.readElementText();
                                    qDebug()<<"++>exec_time: "<<tag_text;
                                }
                                else if(reader.name() == "energy"){
                                    tag_text = reader.readElementText();
                                    qDebug()<<"++>energy: "<<tag_text;
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
                                    qDebug()<<"++>dfs_api_prototype: "<<tag_text;
                                }
                                else if(reader.name() == "frequency"){
                                    tag_text = reader.readElementText();
                                    qDebug()<<"++>frequency: "<<tag_text;
                                }
                                else if(reader.name() == "exec_time"){
                                    tag_text = reader.readElementText();
                                    qDebug()<<"++>exec_time: "<<tag_text;
                                }
                                else if(reader.name() == "energy"){
                                    tag_text = reader.readElementText();
                                    qDebug()<<"++>energy: "<<tag_text;
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
}
