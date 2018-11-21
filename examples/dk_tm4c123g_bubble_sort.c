#include <stdint.h>
#include <stdbool.h>
#include "hw_memmap.h"

int __attribute__((optimize("O0"))) main(void)
{
    volatile uint8_t i, j, temp;
    volatile uint8_t buff[10] = {35, 12, 10, 55, 31, 6, 8, 15, 44, 255};

    //Bubble sort
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if(buff[j] < buff[j+1]){
                temp = buff[j];
                buff[j] = buff[j+1];
                buff[j+1] = temp;
            }
        }
    }

    return 0;
}

