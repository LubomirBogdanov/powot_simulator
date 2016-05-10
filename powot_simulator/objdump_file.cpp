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

void powotsimulator::objdump_file(QString *filepath, QStringList *objfile_contents)
{
    QString cmd;
    cmd = objdump_cmd + *filepath;
    cout<<"(powotsimulator) objdump all cmd:"<<cmd.toStdString()<<endl;

    QProcess terminal;
    //terminal.setReadChannel(QProcess::StandardOutput);
    terminal.setProcessChannelMode(QProcess::MergedChannels);
    terminal.start(cmd);
    terminal.waitForFinished(-1);
    QByteArray temp = terminal.readAllStandardOutput();
    convert_bytearray_stringlist(&temp, objfile_contents);

    /*for(int i = 0; i < objfile_contents->size(); i++){
        cout<<"+++"<<objfile_contents->at(i).toStdString();
    }*/

    if(objfile_contents->isEmpty()){
        err_message.display_error(OBJDUMP_FAILED);
    }
}
