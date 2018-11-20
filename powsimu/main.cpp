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
#include <getopt.h>
#include <iostream>
#include <iomanip>
#include <QString>
#include <QDebug>
#include <QElapsedTimer>
#include "../powot_simulator/powotsimulator.h"
#include "../powot_simulator/model_lut.h"

using namespace std;

extern int opterr;

static const char *short_options = "vhzbt:w:f:o:d:j:p:m:e:a:";

static const struct option long_options[] = {
{ "version", no_argument, 0, 'v' },
{ "help", no_argument, 0, 'h' },
{ "obj_path", required_argument, 0, 'j' },
{ "provider", required_argument, 0, 'p' },
{ "arch", required_argument, 0, 'a' },
{ "mcu", required_argument, 0, 'm' },
{ "entry", required_argument, 0, 'e' },
{ "get_model_domains", no_argument, 0, 'z' },
{ "use_bin_models", no_argument, 0, 'b' },
{ 0, 0, 0, 0 }
};

void printusage(){
    cout<<"\n\nUsage:\n"
          "powot -[SHORT COMMAND] [PARAMETER]\n"
          "or\n"
          "powot --[LONG COMMAND] [PARAMETER]\n\n"
          "-h or - -help - displays a list of the available command-line options\n"
          "-v or - -version - displays the current simulator version and license.\n"
          "-a [ARCH NAME] or - -arch [ARCH NAME] - pass the name of the target microprocessor architecture (check the simulator_configs directory)\n"
          "-j [PATH] or - -obj_path [PATH] - pass absolute path to the linked object file to be simulated.\n"
          "-p [PROVIDER NAME] or - -provider [PROVIDER NAME] - pass the name of the mcu's provider (check the models directory)\n"
          "-m [MCU NAME] or - -mcu [MCU NAME] - pass the name of the target microcontroller (check the models directory)\n"
          "-e [FUNCTION NAME] or - -entry [FUNCTION NAME] - the function in the source file to be considered as entry point. The simulator will calculate consumption starting from it.\n"
          "-t [0.0] - assign default temperature (float)\n"
          "-w [0.0] - assign default voltage (float)\n"
          "-f [0.0] - assign default frequency (float)\n"
          "-o [0] - assign default number of operands (int)\n"
          "-d [MEMORY DOMAIN] - assign default memory domain (string)\n"
          "-z or - -get_model_domains - prints the available domains for a model. Must be used with provider, arch and mcu (-p, -a and -m)\n"
          "-b or - -use_bin_models - use binary arch models instead of LUT, text-based, TAB-separated ones\n"
          "\nExample launch:"
          "\n./powsimu -z -p test -a arm-cortex-m4 -m test_model_1\n\n"
          "All your sources must be compiled with the -g -O0 options, including the libraries.\n"
          "\nExample launch:"
          "\n./powsimu -j /home/user/myproject/main.axf -a arm-cortex-m4 -p texas_instruments -m lm4f232 -e my_function\n"<<endl;
}

#define LINE                    4
#define ENERGY                  16
#define MEM                     8
#define VDD                     6
#define FREQ                    8
#define OPS                    4
#define VMA                     10
#define INSTRUCTION             35
#define INSTRENERGY             14
#define INSTRREPEAT             7
#define INSTRREPEATENERGY       14

void draw_table(energyfield_t *e_table, quint32 e_table_size, QString metrics, quint64 elpsd_time){
    bool flag = 0;
    long cstatement_max_size;
    long all;

    //Get the maximum string length
    cstatement_max_size = e_table[0].statement.size();
    for(unsigned int i = 0; i < e_table_size-1; i++){
        if(!(cstatement_max_size > e_table[i+1].statement.size())){
            cstatement_max_size = e_table[i+1].statement.size();
        }
    }

    all = LINE + cstatement_max_size + ENERGY + VMA + MEM + VDD + FREQ + OPS + INSTRUCTION + INSTRENERGY + INSTRREPEAT + INSTRREPEATENERGY + 13;

    for(int i = 0; i < all; i++)
        cout<<"-";
    cout<<endl;
    cout<<setiosflags(ios::left)<<"|"<<setw(LINE)<<"Line"<<"|";
    cout<<setw(cstatement_max_size)<<"C statement"<<"|";
    //cout<<setw(ENERGY)<<"Base Energy,"<<metrics.toStdString()<<"|";
    cout<<"Base Energy, "<<metrics.toStdString()<<" |";
    cout<<setw(MEM)<<"MEM"<<"|";
    cout<<setw(VDD)<<"Vdd,V"<<"|";
    cout<<setw(FREQ)<<"Fclk,MHz"<<"|";
    cout<<setw(OPS)<<"Ops"<<"|";
    cout<<setw(VMA)<<"VMA (hex)"<<"|";
    cout<<setw(INSTRUCTION)<<"Instruction"<<"|";
    //cout<<setw(INSTRENERGY)<<"Instr. E, "<<metrics.toStdString()<<"|";
    cout<<"Instr. E, "<<metrics.toStdString()<<"  |";
    cout<<setw(INSTRREPEAT)<<"Repeat"<<"|";
    //cout<<setw(INSTRREPEATENERGY)<<"Total E, "<<metrics.toStdString()<<"|";
    cout<<"Total E,  "<<metrics.toStdString()<<"  |";
    cout<<endl;
    for(int i = 0; i < all; i++)
        cout<<"-";
    cout<<endl;

    for(unsigned long i = 0; i < e_table_size; i++){

        cout<<"|"<<setw(LINE)<<dec<<e_table[i].line_number<<"|";
        cout<<setw(cstatement_max_size)<<e_table[i].statement.toStdString()<<"|";
        cout<<setw(ENERGY)<<fixed<<setprecision(3)<<e_table[i].statement_energy_cost<<"|";
        flag = 0;

        if(e_table[i].asm_instr.size() == 0){
            cout<<setw(MEM)<<" "<<"|";
            cout<<setw(VDD)<<" "<<"|";
            cout<<setw(FREQ)<<" "<<"|";
            cout<<setw(OPS)<<" "<<"|";
            cout<<setw(VMA)<<" "<<"|";
            cout<<setw(INSTRUCTION)<<" "<<"|";
            cout<<setw(INSTRENERGY)<<" "<<"|";
            cout<<setw(INSTRREPEAT)<<" "<<"|";
            cout<<setw(INSTRREPEATENERGY)<<" "<<"|";
            //cout<<endl;
        }
        for(long j = 0; j < e_table[i].asm_instr.size(); j++){
            if(flag){
                cout<<"|"<<setw(LINE)<<" "<<"|";
                cout<<setw(cstatement_max_size)<<" "<<"|";
                cout<<setw(ENERGY)<<" "<<"|";
            }

            flag = 1;

            cout<<setw(MEM)<<setiosflags(ios::left)<<e_table[i].addr_range_name.at(j).toStdString()<<"|";
            cout<<setw(VDD)<<setiosflags(ios::left)<<setprecision(2)<<e_table[i].voltage_domain.at(j)<<"|";
            cout<<setw(FREQ)<<setiosflags(ios::left)<<setprecision(2)<<e_table[i].frequency_domain.at(j)<<"|";
            cout<<setw(OPS)<<setiosflags(ios::left)<<e_table[i].num_of_operands.at(j)<<"|";
            cout<<setw(VMA)<<hex<<setiosflags(ios::left)<<e_table[i].asm_vma.at(j)<<"|";
            cout<<setw(INSTRUCTION)<<e_table[i].asm_instr.at(j).toStdString()<<"|";
            cout<<setw(INSTRENERGY)<<dec<<fixed<<setprecision(3)<<e_table[i].asm_base_energy_cost.at(j)<<"|";
            cout<<setw(INSTRREPEAT)<<dec<<e_table[i].repeated<<"|";
            cout<<setw(INSTRREPEATENERGY)<<dec<<fixed<<setprecision(3)<<e_table[i].asm_repeated.at(j)<<"|";
            cout<<endl;
        }
        if(!flag){
            cout<<endl;
        }
    }

    for(int i = 0; i < all; i++)
        cout<<"-";
    cout<<endl;
    cout<<"Elapsed time of simulation: "<<elpsd_time<<" ms"<<endl;
}

void draw_model_domains(model_domains_t *mdl_dom)
{
    cout<<"----------------------------------------"<<endl;
    cout<<"Model domains:"<<endl;
    for(unsigned long i = 0; i < mdl_dom->num_addr_ranges; i++){
        cout<<mdl_dom->addr_ranges_names.at(i).toStdString()<<":";
        cout<<"0x"<<hex<<setfill('0')<<setw(8)<<right<<mdl_dom->addr_ranges[i].at(0)<<" - ";
        cout<<"0x"<<hex<<setfill('0')<<setw(8)<<right<<mdl_dom->addr_ranges[i].at(1)<<endl;
    }
    cout<<"Temperatures: ";
    for(long i = 0; i < mdl_dom->temperature_domains.size(); i++){ cout<<fixed<<setprecision(3)<<mdl_dom->temperature_domains.at(i)<<" "; }
    cout<<endl;
    cout<<"Voltages: ";
    for(long i = 0; i < mdl_dom->voltage_domains.size(); i++){ cout<<fixed<<setprecision(3)<<mdl_dom->voltage_domains.at(i)<<" "; }
    cout<<endl;
    cout<<"Frequencies: ";
    for(long i = 0; i < mdl_dom->frequency_domains.size(); i++){ cout<<fixed<<setprecision(3)<<mdl_dom->frequency_domains.at(i)<<" "; }
    cout<<endl;
    cout<<"Operands: ";
    for(long i = 0; i < mdl_dom->operand_domains.size(); i++){ cout<<mdl_dom->operand_domains.at(i)<<" "; }
    cout<<endl;
    cout<<"Metrics: "<<mdl_dom->metrics.toStdString()<<endl;
    cout<<"Metrics divisor: "<<mdl_dom->metrics_div<<endl;

    cout<<"DFS APIs:"<<mdl_dom->dfs_api.dfs_api.size()<<endl;
    for(long i = 0; i < mdl_dom->dfs_api.dfs_api.size(); i++){
        cout<<mdl_dom->dfs_api.dfs_api.at(i).toStdString()<<"   ";
        cout<<"f"<<mdl_dom->dfs_api.api_frequency.at(i)<<" ";
        cout<<"t"<<mdl_dom->dfs_api.exec_time.at(i)<<" ";
        cout<<"e"<<mdl_dom->dfs_api.exec_energy.at(i)<<endl;
    }
    cout<<"DVS APIs:"<<mdl_dom->dvs_api.dvs_api.size()<<endl;
    for(long i = 0; i < mdl_dom->dvs_api.dvs_api.size(); i++){
        cout<<mdl_dom->dvs_api.dvs_api.at(i).toStdString()<<"   ";
        cout<<"v"<<mdl_dom->dvs_api.api_voltage.at(i)<<" ";
        cout<<"t"<<mdl_dom->dvs_api.exec_time.at(i)<<" ";
        cout<<"e"<<mdl_dom->dvs_api.exec_energy.at(i)<<endl;
    }

}

int main(int argc, char *argv[]){    
    quint8 no_opt_entered = 0;
    signed int opt = 0;
    signed int opt_index = 1;
    quint8 display_version = 0;
    sim_params_t sim_prms;
    energyfield_t *e_table;
    quint32 e_table_size;
    model_domains_t mdl_dom;
    QString metrics;
    QString tempr, volt, freq, ops, addr;
    quint8 display_model_domains = 0;
    bool ok;
    QElapsedTimer performance_timer;
    quint64 elapsed_time;

    sim_prms.default_domains = {
        " ", 0, 0, 0, 0, " ", 0
    };

    sim_prms.arch_model_type = MODEL_TAB_LUT;

    opterr = 0; //Disable printing errors to stderr by getopt_long().

    while(1){
        opt = getopt_long(argc, argv, short_options, long_options, &opt_index);

        if(opt == -1){
            if(no_opt_entered == 0){
                printusage();
            }
            break;
        }
        no_opt_entered = 1;

        switch(opt){
        case 'j':
            sim_prms.objectfile_path = optarg;
            break;
        case 'b':
            sim_prms.arch_model_type = MODEL_BINARY;
            break;
        case 'v':
            display_version = 1;
            break;
        case 'p':
            sim_prms.provider = optarg;
            break;
        case 'm':
            sim_prms.mcu = optarg;
            break;
        case 'a':
            sim_prms.arch = optarg;
            break;
        case 'e':
            sim_prms.entry = optarg;
            break;
        case 'z':
            display_model_domains = 1;
            break;
        case 't':
            tempr = optarg;
            sim_prms.default_domains.default_temperature = tempr.toFloat(&ok);
            break;
        case 'w':
            volt = optarg;
            sim_prms.default_domains.default_voltage = volt.toFloat(&ok);
            break;
        case 'f':
            freq = optarg;
            sim_prms.default_domains.default_frequency = freq.toFloat(&ok);
            break;
        case 'o':
            ops = optarg;
            sim_prms.default_domains.default_operand = ops.toInt(&ok, 10);
            break;
        case 'd':
            sim_prms.default_domains.default_addr_range = optarg;
            break;
        case 'h':
        case '?':
        default:
            printusage();
            break;
        }
    }

    if(display_version){
        QString version_string;
        powotsimulator sim;        
        version_string = sim.get_copyright_info();
        version_string += "\n\nVersion ";
        version_string += QString::number(sim.get_version(), 'f', 2);
        version_string += "\n";
        version_string += sim.get_build_info();
        cout<<version_string.toStdString()<<endl;

        return EXIT_SUCCESS;
    }

    QFile file_check(sim_prms.objectfile_path);
    if(!file_check.exists()){
        cout<<"ERROR: file \""<<sim_prms.objectfile_path.toStdString()<<"\" does not exist!"<<endl;
        return EXIT_FAILURE;
    }

    if(display_model_domains){
        if(sim_prms.provider.isEmpty() || sim_prms.arch.isEmpty() || sim_prms.mcu.isEmpty()){
            cout<<"ERROR: You must specify all: provider + arch + mcu!"<<endl<<endl;
            printusage();
            return EXIT_FAILURE;
        }
        powotsimulator sim(&sim_prms.provider, &sim_prms.arch, &sim_prms.mcu);
        sim.get_modeldomains(&mdl_dom);
        draw_model_domains(&mdl_dom);

        return EXIT_SUCCESS;
    }

    if(!sim_prms.objectfile_path.isEmpty()){
        powotsimulator sim(&sim_prms);
        performance_timer.start();
        e_table = sim.start_simulation(&e_table_size);
        metrics = sim.get_model_metrics();
        elapsed_time = performance_timer.elapsed();
        draw_table(e_table, e_table_size, metrics, elapsed_time);
    }


    return EXIT_SUCCESS;
}
