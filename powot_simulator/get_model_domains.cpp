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

void powotsimulator::get_modeldomains(model_domains_t *mdl_dom){

    parse_model_domains();

    mdl_dom->addr_ranges = new QList<unsigned long>[mdl_domains.addr_ranges->size()];

    mdl_dom->addr_ranges = mdl_domains.addr_ranges;

    mdl_dom->addr_ranges_names = mdl_domains.addr_ranges_names;

    mdl_dom->num_addr_ranges = mdl_domains.num_addr_ranges;

    for(long i = 0; i < mdl_domains.temperature_domains.size(); i++){
        mdl_dom->temperature_domains = mdl_domains.temperature_domains;
    }

    for(long i = 0; i < mdl_domains.voltage_domains.size(); i++){
        mdl_dom->voltage_domains = mdl_domains.voltage_domains;
    }

    for(long i = 0; i < mdl_domains.frequency_domains.size(); i++){
        mdl_dom->frequency_domains = mdl_domains.frequency_domains;
    }

    for(long i = 0; i < mdl_domains.operand_domains.size(); i++){
        mdl_dom->operand_domains = mdl_domains.operand_domains;
    }

    mdl_dom->metrics = mdl_domains.metrics;
    mdl_dom->metrics_div = mdl_domains.metrics_div;

    mdl_dom->dfs_api = mdl_domains.dfs_api;
    mdl_dom->dvs_api = mdl_domains.dvs_api;
}
