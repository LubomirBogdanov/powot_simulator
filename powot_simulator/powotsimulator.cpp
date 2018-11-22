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

powotsimulator::powotsimulator(void){
    e_table = NULL;
    e_table_size = 0;
    mdl_domains.addr_ranges = NULL;
    mdl = NULL;
    arch_model_type = MODEL_TAB_LUT;
    bin_model_prev_instr_max = BIN_MODEL_MAX_PREVIOUS_INSTRUCTIONS;
    bin_model_follow_instr_max = BIN_MODEL_MAX_FOLLOWING_INSTRUCTIONS;
    qDebug()<<"(powotsimulator) Starting ...";
}

powotsimulator::~powotsimulator(void){
    if(e_table){
        delete [] e_table;
    }

    if(mdl){
        delete [] mdl;
    }

    if(mdl_domains.addr_ranges){
        delete [] mdl_domains.addr_ranges;
    }

    qDebug()<<"(powotsimulator) Finished!";
}

powotsimulator::powotsimulator(QString *provider, QString *arch, QString *mcu){
    provider_name = *provider;
    arch_name = *arch;
    mcu_name = *mcu;

    e_table_size = 0;
    e_table = NULL;
    mdl_domains.addr_ranges = NULL;
    mdl = NULL;
    bin_model_prev_instr_max = BIN_MODEL_MAX_PREVIOUS_INSTRUCTIONS;
    bin_model_follow_instr_max = BIN_MODEL_MAX_FOLLOWING_INSTRUCTIONS;

    readconfiguration();

    qDebug()<<"(powotsimulator) MCU provider: "<<provider_name;
    qDebug()<<"(powotsimulator) MCU: "<<mcu_name;
}

powotsimulator::powotsimulator(sim_params_t *sim_prms){
    qDebug()<<"(powotsimulator) Starting ...";

    provider_name = sim_prms->provider;
    arch_name = sim_prms->arch;
    mcu_name = sim_prms->mcu;
    source_entry_point = sim_prms->entry;
    objectfile_dir = sim_prms->objectfile_path;
    arch_model_type = sim_prms->arch_model_type;
    bin_model_prev_instr_max = sim_prms->pipeline_previous;
    bin_model_follow_instr_max = sim_prms->pipeline_following;

    e_table = NULL;
    e_table_size = 0;
    mdl_domains.addr_ranges = NULL;
    mdl = NULL;

    readconfiguration();

    parse_model_def_domains(&sim_prms->default_domains, &def_domains);

    qDebug()<<"(powotsimulator) Architecture: "<<arch_name;
    qDebug()<<"(powotsimulator) MCU provider: "<<provider_name;
    qDebug()<<"(powotsimulator) MCU: "<<mcu_name;
    qDebug()<<"(powotsimulator) source entry point: "<<source_entry_point;
    qDebug()<<"(powotsimulator) objfile: "<<objectfile_dir;
    switch(arch_model_type){
    case MODEL_TAB_LUT:
        qDebug()<<"(powotsimulator) Model type: TAB_LUT";
        break;
    case MODEL_BINARY:
        qDebug()<<"(powotsimulator) Model type: BIN";
        qDebug()<<"(powotsimulator) Pipeline depth: [-"<<bin_model_prev_instr_max<<", +"<<bin_model_follow_instr_max<<"]";
        break;
    }

    /*
    qDebug()<<"Default domains------------------------------------------";
    qDebug()<<"MEM: "<<def_domains.default_addr_range;
    qDebug()<<"FREQ: "<<def_domains.default_frequency<<" MHz";
    qDebug()<<"OPS: "<<def_domains.default_operand;
    qDebug()<<"TEMP: "<<def_domains.default_temperature<<" C";
    qDebug()<<"VOLT: "<<def_domains.default_voltage<<" V";
    qDebug()<<"---------------------------------------------------------";

    for(int i = 0; i < source_file_contents.size(); i++){
        qDebug()<<"(powotsimulator) src: "<<source_file_contents.at(i);
    }

    for(int i = 0; i < object_file_contents.size(); i++){
        qDebug()<<"(powotsimulator) obj: "<<object_file_contents.at(i);
    }
    */
}
