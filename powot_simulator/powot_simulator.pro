#-------------------------------------------------
#
# Project created by QtCreator 2014-09-03T14:31:37
#
#-------------------------------------------------

QT       -= gui
QT       += xml

TARGET = powot_simulator
TEMPLATE = lib

DEFINES += POWOT_SIMULATOR_LIBRARY

SOURCES += powotsimulator.cpp \
    fileio.cpp \
    errormsg.cpp \
    gdbdump_file.cpp \
    analyze_statements.cpp \
    count_number_of_statements.cpp \
    assign_energy_cost.cpp \
    parse_model_data.cpp \
    check_if_function_call.cpp \
    estimate_function_call.cpp \
    analyze_assembly.cpp \
    check_if_for_loop.cpp \
    estimate_for_loop.cpp \
    estimate_for_loop_extend.cpp \
    remove_white_spaces.cpp \
    objdump_file.cpp \
    remove_empty_lines.cpp \
    parse_model_domains.cpp \
    get_model_domains.cpp \
    parse_model_def_domains.cpp \
    find_mnemonic_in_mdl.cpp \
    dvs_api_readconfig.cpp \
    check_if_dvs_api.cpp \
    estimate_dvs_api_extend.cpp \
    estimate_dvs_api.cpp \
    dfs_api_readconfig.cpp \
    estimate_dfs_api.cpp \
    estimate_dfs_api_extend.cpp \
    check_if_dfs_api.cpp \
    estimate_num_operands.cpp \
    get_model_metrics.cpp \
    version.cpp \
    invoke_cmd_line.cpp \
    parse_aux_model_xml.cpp \
    read_configuration.cpp \
    start_simulation.cpp \
    convert_bytearray_stringlist.cpp \
    symbol_list_file.cpp

HEADERS += powotsimulator.h\
        powot_simulator_global.h \
    fileio.h \
    errormsg.h \
    configfilepaths.h \
    version.h \
    model_lut.h \
    config.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
