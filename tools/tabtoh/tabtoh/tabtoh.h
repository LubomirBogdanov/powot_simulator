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
#ifndef TABTOH_H
#define TABTOH_H

#include <QtDebug>
#include <QString>
#include <QFile>
#include "common.h"

class tabtoh{
private:
    QString model_name_str;
    QString input_file_str;
    QString output_file_str;
    QStringList input_file;
    QStringList output_file;
public:
    tabtoh();
    tabtoh(QString &in_file_str, QString &out_file_str, QString &mod_name_str);
    ~tabtoh();

    bool read_entire_file(const QString &filename, QStringList &contents);
    bool write_entire_file(QString &filename, QStringList &contents);
    int convert();
    int count_instructions();
    bool is_empty_line(const QString &line);
    QStringList parse_and_convert_instr(QStringList &instr_desc);
    void insert_comment(const char *comment_str, QStringList &string_list);
    void insert_ifndef(const char *ifndef_str, QStringList &string_list);
    void insert_endif(QStringList &string_list);
    void insert_include(const char *include_str, QStringList &string_list);
    void insert_define(const char *define_name, const char *define_value, QStringList &string_list);
    void insert_newline(QStringList &string_list);
    void insert_array(const char *arr_type, const char *arr_name, const char *arr_size, QStringList &arr_elements, QStringList &string_list);
    void insert_struct(const char *struct_type, const char *struct_name, int tabs_before, QStringList &string_list);
    void insert_struct_field(const char *field_name, const char *field_value, int tabs_before, QStringList &string_list);
    void insert_struct_struct_field(const char *field_name, int tabs_before, QStringList &string_list);
    void insert_struct_initializers(QStringList init_names, QStringList init_values, int tabs_before, QStringList &string_list);
    void find_in_list_add(QString &search_value, QStringList &string_list);
    void detect_domain_sizes(QStringList &instr_desc, QString &mem_sz_str, QString &tempr_sz_str, QString &volt_sz_str, QString &freq_sz_str, QString &ops_sz_str);
    QString convert_dot_to_slash(const QString &string_val);
};



#endif // TABTOH_H
