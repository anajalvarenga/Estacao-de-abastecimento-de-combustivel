# 1 "stdio.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "stdio.c" 2
# 1 "./stdio.h" 1



    void printf(char msg[60]);
# 1 "stdio.c" 2

# 1 "./lcd.h" 1
# 23 "./lcd.h"
 void lcdCommand(unsigned char cmd);
 void lcdData(unsigned char valor);
 void lcdInit(void);
# 2 "stdio.c" 2


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
