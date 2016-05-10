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

void powotsimulator::parse_model_def_domains(default_model_domains_t *source_domain, default_model_domains_t *dest_domain)
{
    if(source_domain->default_addr_range.isEmpty()){
        dest_domain->default_addr_range = mdl_domains.addr_ranges_names.at(0);
    }
    else{
        dest_domain->default_addr_range = source_domain->default_addr_range;
    }

    if(source_domain->default_frequency == 0.0){
        dest_domain->default_frequency = mdl_domains.frequency_domains.at(0);
    }
    else{
        dest_domain->default_frequency = source_domain->default_frequency;
    }

    if(source_domain->default_operand == 0){
        dest_domain->default_operand = mdl_domains.operand_domains.at(0);
    }
    else{
        dest_domain->default_operand = source_domain->default_operand;
    }

    if(source_domain->default_temperature == 0.0){
        dest_domain->default_temperature = mdl_domains.temperature_domains.at(0);
    }
    else{
        dest_domain->default_temperature = source_domain->default_temperature;
    }

    if(source_domain->default_voltage == 0.0){
        dest_domain->default_voltage = mdl_domains.voltage_domains.at(0);
    }
    else{
        dest_domain->default_voltage = source_domain->default_voltage;
    }

    if(source_domain->default_metrics.isEmpty()){
        dest_domain->default_metrics = " ";
    }
    else{
        dest_domain->default_metrics = source_domain->default_metrics;        
    }

    if(source_domain->default_metrics_div == 0.0){
        dest_domain->default_metrics_div = 1.0;
    }
    else{
        dest_domain->default_metrics_div = source_domain->default_metrics_div;        
    }
}
