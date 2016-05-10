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

void powotsimulator::readconfiguration()
{
    QStringList contents;
    QString path;

    path = configfile_dir + "/" + arch_name + ".cfg";

    cout<<"(powotsimulator) Reading configuration ..."<<endl;
    if(config_file.read_entire_config_file(&path, &contents))
    {
       for(qint32 i=0; i < contents.size(); i++)
       {
            if(contents.at(i).contains("GDBDUMP_COMMAND"))
            {
               gdbdump_cmd = contents.at(i).section(' ', 1, -1);
               gdbdump_cmd += ' ';
            }

            if(contents.at(i).contains("SYMBOLLIST_COMMAND"))
            {
               symbollist_cmd = contents.at(i).section(' ', 1, -1);
               symbollist_cmd += ' ';
            }

            if(contents.at(i).contains("OBJDUMP_COMMAND"))
            {
               objdump_cmd = contents.at(i).section(' ', 1, -1);
               objdump_cmd += ' ';
            }
        }
    }
    else
    {
        err_message.display_error(CONFIG_NOT_LOADED, &path);
        cout<<"(powotsimulator) Aborting ..."<<endl;
        exit(-1);
    }

    path = modelsdir + "/mcu/" + provider_name + '/' + mcu_name + ".mdl";

    cout<<"(powotsimulator) model file: "<<path.toStdString()<<endl;

    if(!config_file.read_entire_config_file(&path, &mcu_model))
    {
        err_message.display_error(MODEL_NOT_LOADED);
        cout<<"(powotsimulator) Aborting ..."<<endl;
        exit(-1);
    }

    remove_empty_lines(&mcu_model);

    parse_model_domains();
    parse_model_data();
    dvs_api_readconfig();
    dfs_api_readconfig();
}
