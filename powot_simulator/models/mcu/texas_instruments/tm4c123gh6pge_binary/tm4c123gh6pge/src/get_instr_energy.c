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
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "get_instr_energy.h"
#include "isa.h"

double get_instr_energy(instruction_desc_t *iut){
	double result = 0.0;
	int str_differ;
	unsigned long i, j, k, l, m, n;
	uint8_t instr_found = 0;

	for(i = 0; i < NUM_OF_INSTRUCTIONS; i++){
		str_differ = strcmp(iut->instr_mnemonic, tm4c_isa[i]->instr_mnemonic);
		if(!str_differ){
			for(j = 0; j < MAX_BUFF_SIZE; j++){
				if(iut->domains.mem_type == tm4c_isa[i]->domains[j].mem_type){
					for(k = j; k < MAX_BUFF_SIZE; k++){
						if(iut->domains.tempr_domain == tm4c_isa[i]->domains[k].tempr_domain){
							for(l = k; l < MAX_BUFF_SIZE; l++){
								if(iut->domains.volt_domain == tm4c_isa[i]->domains[l].volt_domain){
									for(m = l; m < MAX_BUFF_SIZE; m++){
										if(iut->domains.freq_domain == tm4c_isa[i]->domains[m].freq_domain){
											for(n = m; n < MAX_BUFF_SIZE; n++){
												if(iut->domains.num_of_operands == tm4c_isa[i]->domains[n].num_of_operands){
													instr_found = 1;
													result = tm4c_isa[i]->domains[n].consumed_time * tm4c_isa[i]->domains[n].consumed_current * tm4c_isa[i]->domains[n].volt_domain;
													goto end;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

end:
	DEBUG_GETINSTR("j%ld k%ld l%ld m%ld, n%ld\n", j, k, l, m, n);
	//DEBUG_GETINSTR("E = t * I * V <-> %f = %f * %f *%f\n", result, tm4c_isa[i]->domains[n].consumed_time, tm4c_isa[i]->domains[n].consumed_current, tm4c_isa[i]->domains[n].volt_domain);

	if(!instr_found){
		printf("err\n");
	}

	return result;
}
