/*
    Copyright (C) 2018 Lubomir Bogdanov

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
#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>

#define MAX_BUFF_SIZE	64

typedef struct {
	double freq_domain;
	double volt_domain;
	double tempr_domain;
	uint32_t mem_domain;
}domain_t;

typedef struct {
	domain_t domains;
	char instr_mnemonic[MAX_BUFF_SIZE];
	char instr_operands[MAX_BUFF_SIZE];
	char instr_comments[MAX_BUFF_SIZE];
}instruction_desc_t;


#endif /* COMMON_H_ */