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
#include "powotsimulator.h"
#include "version.h"

double powotsimulator::get_version(void){
    return POWOT_SIMULATOR_VERSION;
}

QString powotsimulator::get_build_info(void){
    QString build_info;
    build_info = OS_X86_X64;
    build_info += "-bit, compiled on ";
    build_info += OS_NAME;
    return build_info;
}

QString powotsimulator::get_copyright_info(void){
    QString copyright_notice;

    copyright_notice = "                     --********--\n";
    copyright_notice += "                     --********--\n";
    copyright_notice += "                     --**----**--\n";
    copyright_notice += "                     --******----\n";
    copyright_notice += "                     --***-------\n";
    copyright_notice += "                     --***-------\n";
    copyright_notice += "                     --***-------\n";
    copyright_notice += COPYRIGHT;

    return copyright_notice;
}
