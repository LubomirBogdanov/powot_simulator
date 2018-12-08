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
#include "errormsg.h"
#include <iostream>
using namespace std;

errormsg::errormsg(){

}

errormsg::~errormsg(){

}

/*!
  A method for displaying various error messages. The message is
  chosen with a number and if additional information needs to be
  displayed it can be done with the optional qstrMsg argument. \n

  \b errnum - the number of the error message to be displayed.

  \b msg - additional message to be displayed if needed. It
  defaults to a <space>.
  */
void errormsg::display_error(int errnum, const QString *msg){
    switch(errnum){
    case CANT_OPEN_FILE:
        qDebug()<<"(powotsimulator) ERROR: Can't open file: "<<*msg<<"!";
        break;
    case CANT_WRITE_FILE:
        qDebug()<<"(powotsimulator) ERROR: Can't write to the file: "<<*msg<<"!";
        break;
    case GDBDUMP_FAILED:
        qDebug()<<"(powotsimulator) ERROR: dump of a single symbol command failed!";
        break;
    case OBJDUMP_FAILED:
        qDebug()<<"(powotsimulator) ERROR: dump of all symbols command failed!";
        break;
    case SYMBOLLIST_FAILED:
        qDebug()<<"(powotsimulator) ERROR: symbol list command failed!";
        break;
    case MODEL_NOT_LOADED:
        qDebug()<<"(powotsimulator) ERROR: model failed to load!";
        break;
    case MODEL_XML_NOT_LOADED:
        qDebug()<<"(powotsimulator) ERROR: auxiliary XML model failed to load!";
        break;
    case CONFIG_NOT_LOADED:
        qDebug()<<"(powotsimulator) ERROR: config file "<<*msg<<" failed to load!";
        break;
    case SRC_ENTRY_NOT_FOUND:
        qDebug()<<"(powotsimulator) ERROR: Entry point <<"<<*msg<<">> not found in object file!";
        break;
    case LOOP_LOW_INVALID:
        qDebug()<<"(powotsimulator) ERROR: Low boundary of loop cannot be processed (assigning 1 for repeat)! "<<*msg;
        break;
    case LOOP_HIGH_INVALID:
        qDebug()<<"(powotsimulator) ERROR: High boundary of loop cannot be processed (assigning 1 for repeat)! "<<*msg;
        break;
    case LOOP_WRONG_EXPR:
        qDebug()<<"(powotsimulator) ERROR: Integer expression cannot be converted";
        break;
    case LOOP_WRONG_COND:
        qDebug()<<"(powotsimulator) ERROR: Inside for( ; COND ; ) loop the COND cannot be evaluated (assigning 1 for repeat)! ";
        break;
    case INSTR_NOT_FOUND_IN_MDL:
        qDebug()<<"(powotsimulator) ERROR: Instruction <<"<<*msg<<">> not found in model file!";
        break;
    case DOMAIN_NOT_FOUND_IN_MDL:
        qDebug()<<"(powotsimulator) ERROR: Instruction <<"<<*msg<<">> does not have data for this domain in the model file!";
        break;
    case CMD_LINE_EXEC_FAILED:
        qDebug()<<"(powotsimulator) ERROR: Invocation of "<<*msg<<"did not return any result!";
        break;
    default:
        qDebug()<<"(powotsimulator) ERROR: General error!";
    }
}
