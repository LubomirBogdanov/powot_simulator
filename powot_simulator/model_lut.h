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
#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QStringList>

typedef struct {
    QStringList dvs_api;
    QList<float> api_voltage;
    QList<float> exec_time;
    QList<float> exec_energy; //If not provided will be simulated
}dvs_api_t;

typedef struct {
    QStringList dfs_api;
    QList<float> api_frequency;
    QList<float> exec_time;
    QList<float> exec_energy; //If not provided will be simulated
}dfs_api_t;

typedef struct {
    QString default_addr_range;    
    unsigned long default_operand;
    float default_temperature;
    float default_voltage;
    float default_frequency;
    QString default_metrics;
    float default_metrics_div;
} default_model_domains_t;

//Info structure describing the domains in a model
typedef struct {
    QList <unsigned long> *addr_ranges;
    unsigned long num_addr_ranges;    
    //-------------Domains----------------
    QStringList addr_ranges_names;
    QList <unsigned long> operand_domains;
    QList <float> temperature_domains;
    QList <float> voltage_domains;
    QList <float> frequency_domains;
    //------------------------------------
    QString metrics;
    float metrics_div;

    dfs_api_t dfs_api;
    dvs_api_t dvs_api;

} model_domains_t;

//Assembly info extracted from the model file
typedef struct {
    QString mnemonic;
    QString instr_type;
    QStringList addr_range_name;
    QList<unsigned long> num_of_operands;
    QList<float> current;
    QList<float> exec_time;
    QList<float> frequency_domain;
    QList<float> voltage_domain;
    QList<float> temperature_domain;
    QList<float> energy;
} model_data_t;

/*
Available instruction types:
- mem   - memory access
- datap - data processing
- contr - branch and control
- misc  - miscellaneous
*/

#endif // MODEL_H
