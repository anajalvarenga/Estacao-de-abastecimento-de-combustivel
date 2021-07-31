#include "delay.h"

void tempo(unsigned char ms){
    volatile unsigned char i, j, k;
    for(i = 0; i < ms; i++){
        for(j = 0; j < 41; j++){
            for(k = 0; k < 3; k++);
        }
    }
}

void segundo(unsigned char s){
    volatile unsigned char i;
    for(i = 0; i < s; i++){
        tempo(250);
        tempo(250);
        tempo(250);
        tempo(250);
    }
}