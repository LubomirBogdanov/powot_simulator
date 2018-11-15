#include <stdint.h>
#include <stdbool.h>
#include "hw_memmap.h"

int main(void)
{
    uint8_t i, j, temp;
    uint8_t buff[10] = {35, 12, 10, 55, 31, 6, 8, 15, 44, 255};

    for(j = 0; j < 10; j++){
        for(i = 0; i < 10; i+=2){
            if(buff[i] < buff[i+1]){
                temp = buff[i];
                buff[i] = buff[i+1];
                buff[i+1] = temp;
            }
        }

        for(i = 1; i < 10; i+=2){
            if(buff[i] < buff[i+1]){
                temp = buff[i];
                buff[i] = buff[i+1];
                buff[i+1] = temp;
            }
        }
    }

	return 0;
}
