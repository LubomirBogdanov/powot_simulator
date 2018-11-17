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
#ifndef FILEIO_H
#define FILEIO_H
#include "powot_simulator_global.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include "errormsg.h"

class fileio{
private:
    errormsg error;
public:
    fileio();
    ~fileio();
    bool read_entire_file(const QString *filename, QStringList *contents);
    bool read_entire_config_file(const QString *filename, QStringList *contents);
    bool write_entire_file(QString *filename, QStringList *contents);
};

#endif // FILEIO_H


