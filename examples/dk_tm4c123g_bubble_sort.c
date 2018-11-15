#include <stdint.h>
#include <stdbool.h>
#include "hw_memmap.h"

int main(void)
{
    uint8_t i, j, temp;
    uint8_t buff[10] = {35, 12, 10, 55, 31, 6, 8, 15, 44, 255};

    for(i = 0; i < 10 - 1; i++){
        for(j = 0; j < 10 - i - 1; j++){
            if(buff[j] < buff[j+1]){
                temp = buff[j];
                buff[j] = buff[j+1];
                buff[j+1] = temp;
            }
        }
    }

	return 0;
}
