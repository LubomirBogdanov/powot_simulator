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
#ifndef ERRORMSG_H
#define ERRORMSG_H

#include <QString>
#include <QDebug>

/*!
  \brief An enumeration declaration for the different kinds of errors.
  It is easier to use the enumerations than the digits.

  \var errors
  */
enum errors{
    CANT_OPEN_FILE, //Requires a file name as the second parameter.
    CANT_WRITE_FILE, //Requires a file name as the second parameter.
    GDBDUMP_FAILED,
    OBJDUMP_FAILED,
    SYMBOLLIST_FAILED,
    MODEL_NOT_LOADED,
    CONFIG_NOT_LOADED, //Requires a file name as the second parameter.
    SRC_ENTRY_NOT_FOUND, //Requires a name of a function as the second parameter.
    LOOP_LOW_INVALID, //Requires the for( ) loop that failed as the second parameter.
    LOOP_HIGH_INVALID, //Requires the for( ) loop that failed as the second parameter.
    LOOP_WRONG_EXPR, //Expression inside for( ) loop condition cannot be evaluated
    LOOP_WRONG_COND, //The condition sign in a loop cannot be processed.
                    //Requires the for( ) loop that failed as the second parameter.
    INSTR_NOT_FOUND_IN_MDL, //Requires a string of the missing instruction as the second parameter
    DOMAIN_NOT_FOUND_IN_MDL, //Requires a string of the instruction whose domain cannot be found in the mdl as the second parameter
};


class errormsg{
private:

public:
    errormsg();
    ~errormsg();
    void display_error(int errnum, const QString *msg = NULL);
};

#endif // ERRORMSG_H
