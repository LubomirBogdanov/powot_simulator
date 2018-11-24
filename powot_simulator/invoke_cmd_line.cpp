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

QStringList powotsimulator::invoke_cmd_line(QString *path_to_binary, QString *binary_name, QString *cmd_line_params){
    QStringList cmd_output;
    QString cmd = *path_to_binary + *binary_name + *cmd_line_params;

    QProcess terminal;
    terminal.setProcessChannelMode(QProcess::MergedChannels);
    terminal.start(cmd);
    terminal.waitForFinished(-1);
    QByteArray temp = terminal.readAllStandardOutput();
    convert_bytearray_stringlist(&temp, &cmd_output);

    /*for(int i = 0; i < symbol_contents->size(); i++){
        qDebug()<<"+++"<<symbol_contents->at(i);
    }*/

    if(cmd_output.isEmpty()){
        err_message.display_error(CMD_LINE_EXEC_FAILED, binary_name);
    }

    return cmd_output;
}
