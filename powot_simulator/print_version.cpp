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
#include "version.h"

void powotsimulator::print_version()
{
    cout<<"                     --********--"<<endl;
    cout<<"                     --********--"<<endl;
    cout<<"                     --**----**--"<<endl;
    cout<<"                     --******----"<<endl;
    cout<<"                     --***-------"<<endl;
    cout<<"                     --***-------"<<endl;
    cout<<"                     --***-------"<<endl;
    cout<<COPYRIGHT<<endl;
    cout<<"(powotsimulator) Powot Simulator version "<<fixed<<setprecision(2)<<POWOT_SIMULATOR_VERSION<<endl;
    cout<<"(powotsimulator) "<<OS_X86_X64<<"-bit, compiled on "<<OS_NAME<<endl;    
}
