/*
    Copyright (C) 2019 Lubomir Bogdanov

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
#include <getopt.h>
#include <QCoreApplication>
#include <QtDebug>
#include "version.h"
#include "tabtoh.h"

static const char *short_options = "vhi:o:m:";

static const struct option long_options[] = {
{ "version", no_argument, nullptr, 'v' },
{ "help", no_argument, nullptr, 'h' },
{ "input", required_argument, nullptr, 'i' },
{ "output", required_argument, nullptr, 'o' },
{ "model_name", required_argument, nullptr, 'm' },
{ 0, 0, 0, 0 }
};

void printusage(){
    qDebug()<<"\n\nUsage:\n"
              "tabtoh -[SHORT COMMAND] [PARAMETER]\n"
              "or\n"
              "tabtoh --[LONG COMMAND] [PARAMETER]\n\n"
              "-h or - -help - displays a list of the available command-line options\n"
              "-v or - -version - displays the current simulator version.\n"
              "-i or - -input [FILE_NAME] - input file of type TAB_LUT model file.\n"
              "-o or - -output [FILE_NAME] - output file of type C header file.\n"
              "-m or - -model_name [MODEL_NAME] - the name of the modeled architecture.\n"
              "\nExample launch:"
              "\n./tabtoh -m tm4c123gh6pge -i /path/to/model/tm4c123gh6pge.mdl -o /path/to/model/isa.h\n";
}

int main(int argc, char *argv[]){
    quint8 no_opt_entered = 0;
    signed int opt = 0;
    signed int opt_index = 1;
    quint8 display_version = 0;
    QString input_file;
    QString output_file;
    QString model_name("default_model");
    tabtoh *tabtoh_converter = nullptr;

    while(1){
        opt = getopt_long(argc, argv, short_options, long_options, &opt_index);

        if(opt == -1){
            if(no_opt_entered == 0){
                printusage();
                return EXIT_FAILURE;
            }
            break;
        }
        no_opt_entered = 1;

        switch(opt){
        case 'i':
            input_file = optarg;
            break;
        case 'o':
            output_file = optarg;
            break;
        case 'm':
            model_name = optarg;
            break;
        case 'v':
            display_version = 1;
            break;
        case 'h':
        case '?':
        default:
            printusage();
            break;
        }
    }

    if(display_version){
        qDebug()<<"tabtoh v"<<VERSION<<"."<<SUBVERSION;
        return EXIT_SUCCESS;
    }

    if(!tabtoh_converter){
        tabtoh_converter = new tabtoh(input_file, output_file, model_name);
        if(tabtoh_converter){
            if(tabtoh_converter->convert()){
                qDebug()<<"ERROR: conversion failed!";
            }
            else{
                qDebug()<<"Conversion succeeded!";
            }
        }
    }

    if(tabtoh_converter){
        delete tabtoh_converter;
        tabtoh_converter = nullptr;
    }

    return EXIT_SUCCESS;
}
