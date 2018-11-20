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
#ifndef POWOT_SIMULATOR_GLOBAL_H
#define POWOT_SIMULATOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(POWOT_SIMULATOR_LIBRARY)
#  define POWOT_SIMULATORSHARED_EXPORT Q_DECL_EXPORT
#else
#  define POWOT_SIMULATORSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // POWOT_SIMULATOR_GLOBAL_H
