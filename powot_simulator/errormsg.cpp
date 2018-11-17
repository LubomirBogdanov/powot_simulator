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
        cout<<"(powotsimulator) ERROR: Can't open file: "<<msg->toStdString()<<"!"<<endl;
        break;
    case CANT_WRITE_FILE:
        cout<<"(powotsimulator) ERROR: Can't write to the file: "<<msg->toStdString()<<"!"<<endl;
        break;
    case GDBDUMP_FAILED:
        cout<<"(powotsimulator) ERROR: dump of a single symbol command failed!"<<endl;
        break;
    case OBJDUMP_FAILED:
        cout<<"(powotsimulator) ERROR: dump of all symbols command failed!"<<endl;
        break;
    case SYMBOLLIST_FAILED:
        cout<<"(powotsimulator) ERROR: symbol list command failed!"<<endl;
        break;
    case MODEL_NOT_LOADED:
        cout<<"(powotsimulator) ERROR: model failed to load!"<<endl;
        break;
    case CONFIG_NOT_LOADED:
        cout<<"(powotsimulator) ERROR: config file "<<msg->toStdString()<<" failed to load!"<<endl;
        break;
    case SRC_ENTRY_NOT_FOUND:
         cout<<"(powotsimulator) ERROR: Entry point <<"<<msg->toStdString()<<">> not found in object file!"<<endl;
        break;
    case LOOP_LOW_INVALID:
        cout<<"(powotsimulator) ERROR: Low boundary of loop cannot be processed (assigning 1 for repeat)! "<<msg->toStdString()<<endl;
        break;
    case LOOP_HIGH_INVALID:
        cout<<"(powotsimulator) ERROR: High boundary of loop cannot be processed (assigning 1 for repeat)! "<<msg->toStdString()<<endl;
        break;
    case LOOP_WRONG_EXPR:
        cout<<"(powotsimulator) ERROR: Integer expression cannot be converted"<<endl;
        break;
    case LOOP_WRONG_COND:
        cout<<"(powotsimulator) ERROR: Inside for( ; COND ; ) loop the COND cannot be evaluated (assigning 1 for repeat)! "<<msg->toStdString()<<endl;
        break;
    case INSTR_NOT_FOUND_IN_MDL:
        cout<<"(powotsimulator) ERROR: Instruction <<"<<msg->toStdString()<<">> not found in model file!"<<endl;
        break;
    case DOMAIN_NOT_FOUND_IN_MDL:
        cout<<"(powotsimulator) ERROR: Instruction <<"<<msg->toStdString()<<">> does not have data for this domain in the model file!"<<endl;
        break;
    default:
        cout<<"(powotsimulator) ERROR: General error!"<<endl;
    }
}
