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

unsigned long powotsimulator::estimate_for_loop(QString statement){
    QString low_str, high_str, increment_str;
    unsigned long low = 0;
    unsigned long high = 0;
    unsigned long increment = 1;
    unsigned long result = 0;
    bool ok;
    bool less_than_and_eq = 0;
    bool greater_than_and_eq = 0;
    bool greater_than = 0;
    bool non_linear = 0;

    //qDebug()<<"****"<<statement;

    //--------------LOW-------------------
    low_str = statement.section(';', 0, 0);
    low_str = low_str.trimmed();
    remove_white_spaces(&low_str);
    low_str = low_str.section('=', 1, 1);
    low = low_str.toInt(&ok, 10);
    if(!ok){        
        low = process_arithmetic_operators_in_loops(&low_str);
        if(low == 0){
            err_message.display_error(LOOP_LOW_INVALID, &statement);
            return 1;
        }
    }
    //qDebug()<<"low = "<<low;
    //------------------------------------

    //--------------HIGH-------------------
    high_str = statement.section(';', 1, 1);
    high_str = high_str.trimmed();
    remove_white_spaces(&high_str);

    if(high_str.contains('<')){
        if(high_str.contains("<=")){
            high_str = high_str.section('=', 1, 1);
            less_than_and_eq = 1;
        }else {
            high_str = high_str.section('<', 1, 1);
        }
    }else if(high_str.contains('>')){
        if(high_str.contains(">=")){
            high_str = high_str.section('=', 1, 1);
            greater_than_and_eq = 1;
            greater_than = 1;
        }else{
            high_str = high_str.section('>', 1, 1);
            greater_than = 1;
        }
    }
    else{
        err_message.display_error(LOOP_WRONG_COND, &statement);
        return 1;
    }

    high = high_str.toInt(&ok, 10);
    if(!ok){
        high = process_arithmetic_operators_in_loops(&high_str);
        if(high == 0){
            err_message.display_error(LOOP_HIGH_INVALID, &statement);
            return 1;
        }
    }
    //qDebug()<<"high = "<<high;
    //-------------------------------------

    if(less_than_and_eq){
        high++;
    }

    if(greater_than_and_eq){
        low++;
    }

    //-------------INCR-------------------
    increment_str = statement.section(';', 2, 2);
    increment_str = increment_str.trimmed();
    remove_white_spaces(&increment_str);
    increment_str = increment_str.section(')', 0, -2);    
    increment = process_increments_in_loops(&increment_str, low, high, &non_linear, greater_than_and_eq);
    //qDebug()<<"increment: "<<increment;
    //------------------------------------

    if(non_linear){
        result = increment;
    }
    else{
        if(greater_than){
            result = (low - high)%increment;
            if(result){
                result = (low - high)/increment;
                result++;
            }
            else{
                result = (low - high)/increment;
            }
        }
        else{
            result = (high - low)%increment;
            if(result){
                result = (high - low)/increment;
                result++;
            }
            else{
                result = (high - low)/increment;
            }
        }
    }

    return result;
}

unsigned long powotsimulator::process_arithmetic_operators_in_loops(QString *expression){
    QString temp_str;
    unsigned long temp_values;
    bool ok;
    unsigned long *arr_values;
    unsigned long occurences;
    unsigned long result = 0;
    unsigned long i;
    unsigned long subtract = 0;

    if(expression->contains('+')){
        occurences = expression->count('+');
        //qDebug()<<"occurences: "<<occurences;

        arr_values = new unsigned long[occurences+1];

        for(i = 0; i < occurences+1; i++){
            temp_str = expression->section('+', i, i);
            temp_values = temp_str.toInt(&ok, 10);
            if(!ok){
                err_message.display_error(LOOP_WRONG_EXPR);
                delete [] arr_values;
                return 0;
            }
            arr_values[i] = temp_values;
        }

        for(i = 0; i < occurences+1; i++){
            result += arr_values[i];
        }

        /*for(i = 0; i < occurences+1; i++){
            qDebug()<<"arr_values["<<i<<"] = "<<arr_values[i];
        }
        qDebug()<<"result = "<<result;
        */

        delete [] arr_values;

    }else if(expression->contains('-')){
        occurences = expression->count('-');

        arr_values = new unsigned long[occurences+1];

        for(i = 0; i < occurences+1; i++){
            temp_str = expression->section('-', i, i);
            temp_values = temp_str.toInt(&ok, 10);
            if(!ok){
                err_message.display_error(LOOP_WRONG_EXPR);
                delete [] arr_values;
                return 0;
            }
            arr_values[i] = temp_values;
        }

        for(i = 1; i < occurences+1; i++){
            subtract += arr_values[i];
        }
        result = arr_values[0] - subtract;

        /*for(i = 0; i < occurences+1; i++){
            qDebug()<<"arr_values["<<i<<"] = "<<arr_values[i];
        }
        qDebug()<<"result = "<<result;*/

        delete [] arr_values;

    }else if(expression->contains('*')){
        occurences = expression->count('*');

        arr_values = new unsigned long[occurences+1];

        for(i = 0; i < occurences+1; i++){
            temp_str = expression->section('*', i, i);
            temp_values = temp_str.toInt(&ok, 10);
            if(!ok){
                err_message.display_error(LOOP_WRONG_EXPR);
                delete [] arr_values;
                return 0;
            }
            arr_values[i] = temp_values;
        }

        result = 1;
        for(i = 0; i < occurences+1; i++){
            result *= arr_values[i];
        }

        /*for(i = 0; i < occurences+1; i++){
            qDebug()<<"arr_values["<<i<<"] = "<<arr_values[i];
        }
        qDebug()<<"result = "<<result;*/

        delete [] arr_values;
    }
    else if(expression->contains('/')){
        occurences = expression->count('/');

        arr_values = new unsigned long[occurences+1];

        for(i = 0; i < occurences+1; i++){
            temp_str = expression->section('/', i, i);
            temp_values = temp_str.toInt(&ok, 10);
            if(!ok){
                err_message.display_error(LOOP_WRONG_EXPR);
                delete [] arr_values;
                return 0;
            }
            arr_values[i] = temp_values;
        }

        for(i = 1; i < occurences+1; i++){
            arr_values[0] /= arr_values[i];
        }
        result = arr_values[0];

        /*for(i = 0; i < occurences+1; i++){
            qDebug()<<"arr_values["<<i<<"] = "<<arr_values[i];
        }
        qDebug()<<"result = "<<result;*/

        delete [] arr_values;
    }
    else{
        result = 0;
    }

    if(ok == 0){
        result = check_if_defined(expression);
    }

    return result;
}

unsigned long powotsimulator::process_increments_in_loops(QString *expression, unsigned long low, unsigned long high, bool *non_linear, bool greater_than_and_equal){
    bool ok = 0;
    unsigned long increment = 1;
    unsigned long power;

    if(expression->contains("++") || expression->contains("--")){
        increment = 1;
        ok = 1;
    }
    else if(expression->contains("+=") || expression->contains("-=")) {
        *expression = expression->section('=', 1, 2);
        increment = expression->toInt(&ok, 10);
    }
    else if(expression->contains('*')){

        *non_linear = 1;

        if(expression->contains("*=")){
            *expression = expression->section("*=", 1, 2);
            power = expression->toInt(&ok, 10);
            //Simulate the loop
            increment = 0;
            for(unsigned long i = low; i < high; i *= power){
                increment++;
            }
            //qDebug()<<"expression: "<<expression;
        }
    }
    else if(expression->contains('/')){

        *non_linear = 1;

        *expression = expression->section('/', 1, 2);
        power = expression->toInt(&ok, 10);
        //Simulate the loop
        //qDebug()<<"low: "<<low<<" high: "<<high<<" power: "<<power;
        increment = 0;
        if(greater_than_and_equal){
            for(unsigned long i = low; i >= high; i /= power){
               increment++;
            }
        }
        else{
            for(unsigned long i = low; i > high; i /= power){
               increment++;
            }
        }
    }

    return increment;
}

unsigned long powotsimulator::check_if_defined(QString *for_loop_cond){
    QString temp_str;
    unsigned long increment = 0;
    bool ok = 0;

    for(long i = 0; i < object_file_contents.size(); i++){
        if(object_file_contents.at(i).contains("#define")){
            temp_str = object_file_contents.at(i).section("#define", 1, 1);
            temp_str = temp_str.simplified();
            //qDebug()<<"temp_str "<<temp_str;

            if(temp_str.contains(*for_loop_cond)){
                temp_str = temp_str.section(' ', 1, 1);
                increment = temp_str.toInt(&ok, 10);
                //qDebug()<<"increment "<<increment;
            }
        }
    }

    if(ok == 0){
        increment = 0;
    }

    return increment;
}
