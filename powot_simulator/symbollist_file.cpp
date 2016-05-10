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

void powotsimulator::symbollist_file(QString *filepath, QStringList *symbol_list)
{
    QStringList symbol_dump;
    QString cmd;
    cmd = symbollist_cmd + *filepath;
    cout<<"(powotsimulator) symbollist cmd:"<<cmd.toStdString()<<endl;

    QProcess terminal;
    terminal.setProcessChannelMode(QProcess::MergedChannels);
    terminal.start(cmd);
    terminal.waitForFinished(-1);
    QByteArray temp = terminal.readAllStandardOutput();
    convert_bytearray_stringlist(&temp, &symbol_dump);

    if(symbol_dump.isEmpty())
    {
        err_message.display_error(SYMBOLLIST_FAILED);
        cout<<"(powotsimulator) Aborting ..."<<endl;
        exit(-1);
    }

    for(int i = 0; i < symbol_dump.size(); i++)
    {
        *symbol_list << symbol_dump.at(i).section(' ', 2, 2);
    }

    /*cout<<"SYMBOLS:"<<endl;
    for(int i = 0; i < symbol_list->size(); i++)
    {
        cout<<"symbollist_file: ***"<<symbol_list->at(i).toStdString()<<" size: "<<symbol_list->at(i).size()<<endl;
    }*/
}
