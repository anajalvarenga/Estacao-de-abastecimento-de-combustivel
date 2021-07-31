#include "stdio.h"
#include "lcd.h"

void printf(char msg[60]){
    int i, linha = 1;
    lcdCommand(0x80);
    for(i = 0;i < 60;i++) {
        if(msg[i] == '\n'){
            i++;
             if(linha == 1){
                lcdCommand(0xC0);
                linha++;
             }else if(linha == 2){
                 lcdCommand(0x90);
                 linha++;
             }else if(linha == 3){
                 lcdCommand(0xD0);
                 linha++;
             }else{
                 lcdCommand(0xD0);
                 linha++;
             }
        }
        lcdData(msg[i]);
    }
}
