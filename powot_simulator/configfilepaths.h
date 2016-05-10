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
#ifndef CONFIGFILEPATHS_H
#define CONFIGFILEPATHS_H

#include <QString>

/*!
  \brief Path to the architecture configuration files that contain various strings for the simulator.
  \var configfile_dir
  */
const QString configfile_dir = "../../powot_simulator_project/powot_simulator/simulator_configs";

/*!
  \brief Contains the path to the model directory where all the device's energy models are.
  \var modelsdir
  */
const QString modelsdir = "../../powot_simulator_project/powot_simulator/models";

#endif // CONFIGFILEPATHS_H
