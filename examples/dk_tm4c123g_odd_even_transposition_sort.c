#include <stdint.h>
#include <stdbool.h>

int __attribute__((optimize("O0"))) main(void)
{
    uint8_t i, j, temp;
    uint8_t buff[10] = {35, 12, 10, 55, 31, 6, 8, 15, 44, 255};

    //Odd-even transposition sort
    for(j = 0; j < 5; j++){
        for(i = 1; i < 9; i+=2){
            if(buff[i] < buff[i+1]){
                temp = buff[i];
                buff[i] = buff[i+1];
                buff[i+1] = temp;
            }
        }

        for(i = 0; i < 9; i+=2){
            if(buff[i] < buff[i+1]){
                temp = buff[i];
                buff[i] = buff[i+1];
                buff[i+1] = temp;
            }
        }
    }

    return 0;
}

