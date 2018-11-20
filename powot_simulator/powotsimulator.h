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
#ifndef POWOTSIMULATOR_H
#define POWOTSIMULATOR_H

#include "powot_simulator_global.h"
#include <QProcess>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include "fileio.h"
#include "configfilepaths.h"
#include "errormsg.h"
#include "model_lut.h"

typedef enum{
    MODEL_TAB_LUT,
    MODEL_BINARY
}model_type_t;

typedef struct{
    QString objectfile_path;
    QString provider;
    QString arch;
    QString mcu;
    QString entry;
    default_model_domains_t default_domains;
    model_type_t arch_model_type;
}sim_params_t;

//C statement info extracted by analyze_statements method
typedef struct {
    unsigned long line_number;          //The line number of the stament in the C source code
    QString statement;                  //A statement of interest that will be analyzed
    QStringList asm_instr;              //A list with all the instructions that make up the statement of interest    
    QStringList asm_mnemonic;           //A list with all the assembler mnemonics that make up the statement of interest
    QList<unsigned long> asm_vma;       //The virtual memory address of the corresponding instruction
    QList<float> asm_base_energy_cost;  //The energy cost of one instruction if executed once
    QList<float> asm_repeated;          //The energy cost of one instruction = asm_base_energy_cost * execution times (in a for loop)
    float statement_energy_cost;        //The sum of the asm_repeated variables for the current statement
    unsigned long repeated;             //The number of loops in a for( ) loop
    bool function_call;                 //Flag for the current statement. 1 - it is a function call, 0 - it is a simple statement
    bool for_loop;                      //Flag for the current statement. 1 - it is a for( ) loop, 0 - it is a simple statement
    unsigned long for_loop_start;
    unsigned long for_loop_end;
    bool dvs_api;                       //Flag that denotes whether it is a normal or a voltage scaling API.
    unsigned long dvs_start;
    unsigned long dvs_end;    
    bool dfs_api;                       //Flag that denotes whether it is a normal or a frequency scaling API.
    unsigned long dfs_start;
    unsigned long dfs_end;

    QStringList addr_range_name;        //A list with strings that describe the memory domain from which the instructions are executed.
    QList<unsigned long> num_of_operands;
    QList<float> current;
    QList<float> exec_time;
    QList<float> frequency_domain;
    QList<float> voltage_domain;
    QList<float> temperature_domain;
    QList<float> energy;
} energyfield_t;

class POWOT_SIMULATORSHARED_EXPORT powotsimulator{
private:
    errormsg err_message;
    fileio config_file;
    fileio source_file;
    fileio object_file;
    QStringList source_file_contents;
    QStringList object_file_contents;
    QStringList entry_point_symbol_contents; //populated by gdbdump
    QStringList symbollist_contents;
    QString objectfile_dir;
    QString gdbdump_cmd;
    QString symbollist_cmd;
    QString objdump_cmd;
    QString provider_name;
    QString arch_name;
    QString mcu_name;
    QString source_entry_point;
    unsigned long source_entry_point_line_num; //in source file
    unsigned long object_entry_point_line_num; //in object file
    QStringList mcu_model;
    model_data_t *mdl;
    unsigned long num_instr_in_mdl_file; //Number of instr. in the model file
    model_domains_t mdl_domains;
    QStringList parsed_source;
    energyfield_t *e_table;
    unsigned long e_table_size;
    default_model_domains_t def_domains;
    dvs_api_t dvs_api;
    dfs_api_t dfs_api;
    model_type_t arch_model_type;

    void objdump_file(QString *filepath, QStringList *objfile_contents);
    void gdbdump_file(QString *filepath, QString *source_entry_point, QStringList *symbol_contents);
    void symbollist_file(QString *filepath, QStringList *symbol_list);
    void readconfiguration(void);
    void remove_empty_lines(QStringList *file_contents);
    void convert_bytearray_stringlist(QByteArray *input, QStringList *output);
    void parsestatements(void);
    void find_entry_point(void);
    void link_source_and_object(void);
    void object_to_sequential(void);
    void analyze_statements(QStringList *sym_cont, energyfield_t *arr);
    float analyze_assembly(QStringList *asm_section);
    unsigned long count_number_of_statements(QStringList *sym_cont, bool *no_debug_info);
    void assign_energy_cost_tab_lut(QString asm_mnemonic, long asm_mnemonic_num, energyfield_t *enrgfield);
    void assign_energy_cost_binary(QString asm_mnemonic, long asm_mnemonic_num, energyfield_t *enrgfield);
    void parse_model_data(void);
    void parse_model_domains(void);
    bool check_if_function_call(QString statement);
    float estimate_function_call(QString function_name);
    bool check_if_for_loop(QString statement);
    unsigned long estimate_for_loop(QString statement);
    unsigned long estimate_for_loop_extend(energyfield_t *arr, unsigned long current_statement, unsigned long energy_field_num);
    void remove_white_spaces(QString *str);
    unsigned long process_arithmetic_operators_in_loops(QString *expression);
    unsigned long process_increments_in_loops(QString *expression, unsigned long low, unsigned long high, bool *non_linear, bool greater_than_and_equal);
    unsigned long check_if_defined(QString *for_loop_cond);
    void multiply_nested_loops(unsigned long *arr_loop_boundaries, unsigned long num_of_loops, unsigned long loop_index, energyfield_t *arr, unsigned long energy_field_num);
    void parse_model_def_domains(default_model_domains_t *source_domain, default_model_domains_t *dest_domain);
    bool find_mnemonic_in_mdl(QString *asm_mneumonic);
    void dvs_api_readconfig(void);
    bool check_if_dvs_api(QString *function_name);
    float estimate_dvs_api(QString *statement, float *dvs_api_energy);
    unsigned long estimate_dvs_api_extend(energyfield_t *arr, unsigned long current_statement, unsigned long energy_field_num);
    void dfs_api_readconfig(void);
    bool check_if_dfs_api(QString *function_name);
    float estimate_dfs_api(QString *statement, float *dfs_api_energy);
    unsigned long estimate_dfs_api_extend(energyfield_t *arr, unsigned long current_statement, unsigned long energy_field_num);
    unsigned long estimate_num_operands(QString asm_instruction);

public:
    powotsimulator(void);
    ~powotsimulator(void);
    powotsimulator(QString *provider, QString *arch, QString *mcu);
    powotsimulator(sim_params_t *sim_prms);
    energyfield_t* start_simulation(quint32 *size);
    void get_modeldomains(model_domains_t *mdl_dom);
    double get_version(void);
    QString get_build_info(void);
    QString get_copyright_info(void);
    QString get_model_metrics(void);

};

#endif // POWOTSIMULATOR_H
