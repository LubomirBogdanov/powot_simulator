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

powotsimulator::powotsimulator()
{
    e_table = NULL;
    e_table_size = 0;
    mdl_domains.addr_ranges = NULL;
    mdl = NULL;
    cout<<"(powotsimulator) Starting ..."<<endl;
}

powotsimulator::~powotsimulator()
{    
    if(e_table){
        delete [] e_table;
    }

    if(mdl){
        delete [] mdl;
    }

    if(mdl_domains.addr_ranges){
      delete [] mdl_domains.addr_ranges;
    }

    cout<<"(powotsimulator) Finished!"<<endl;
}

powotsimulator::powotsimulator(QString *provider, QString *arch, QString *mcu)
{
    provider_name = *provider;
    arch_name = *arch;
    mcu_name = *mcu;

    e_table_size = 0;
    e_table = NULL;
    mdl_domains.addr_ranges = NULL;
    mdl = NULL;

    readconfiguration();

    cout<<"(powotsimulator) MCU provider: "<<provider_name.toStdString()<<endl;
    cout<<"(powotsimulator) MCU: "<<mcu_name.toStdString()<<endl;
}

powotsimulator::powotsimulator(QString *objectfile_path, QString *provider, QString *arch, QString *mcu, QString *entry, bool print_ver, default_model_domains_t *default_domains)
{
    if(print_ver){
        print_version();
    }

    cout<<"(powotsimulator) Starting ..."<<endl;

    provider_name = *provider;
    arch_name = *arch;
    mcu_name = *mcu;
    source_entry_point = *entry;
    objectfile_dir = *objectfile_path;

    e_table = NULL;
    e_table_size = 0;
    mdl_domains.addr_ranges = NULL;
    mdl = NULL;

    readconfiguration();

    parse_model_def_domains(default_domains, &def_domains);

    cout<<"(powotsimulator) Architecture: "<<arch_name.toStdString()<<endl;
    cout<<"(powotsimulator) MCU provider: "<<provider_name.toStdString()<<endl;
    cout<<"(powotsimulator) MCU: "<<mcu_name.toStdString()<<endl;
    cout<<"(powotsimulator) source entry point: "<<source_entry_point.toStdString()<<endl;    
    cout<<"(powotsimulator) objfile: "<<objectfile_path->toStdString()<<endl; 

    /*  
    cout<<"Default domains------------------------------------------"<<endl;
    cout<<"MEM: "<<def_domains.default_addr_range.toStdString()<<endl;
    cout<<"FREQ: "<<def_domains.default_frequency<<" MHz"<<endl;
    cout<<"OPS: "<<def_domains.default_operand<<endl;
    cout<<"TEMP: "<<def_domains.default_temperature<<" C"<<endl;
    cout<<"VOLT: "<<def_domains.default_voltage<<" V"<<endl;
    cout<<"---------------------------------------------------------"<<endl;

    for(int i = 0; i < source_file_contents.size(); i++)
    {
        cout<<"(powotsimulator) src: "<<source_file_contents.at(i).toStdString()<<endl;
    }

    for(int i = 0; i < object_file_contents.size(); i++)
    {
        cout<<"(powotsimulator) obj: "<<object_file_contents.at(i).toStdString();
    }
    */
}
