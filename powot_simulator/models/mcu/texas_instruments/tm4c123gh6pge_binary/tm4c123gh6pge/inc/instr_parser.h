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
#ifndef INSTR_PARSER_H_
#define INSTR_PARSER_H_
# include <stddef.h>
# include <features.h>
# include <bits/types.h>
#include <stdarg.h>
#include "tm4c123gh6pge.h"

#ifdef DEBUG_PARSER_ENABLE
	#define DEBUG_PARSER(...) printf(__VA_ARGS__)
#else
	#define DEBUG_PARSER(...)
#endif

void parse_cmd(char *cmd_param, instruction_desc_t *parsed_instr);
void operands_comments_extract(char *cmd, char *op_comm, char *operand, char *comment);
uint32_t operands_count(char *op_string);
uint32_t str_num_of_occurences(char *input_str, char ch);

#endif /* INSTR_PARSER_H_ */
