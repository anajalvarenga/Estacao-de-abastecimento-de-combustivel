# 1 "delay.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "delay.c" 2
# 1 "./delay.h" 1






void tempo(unsigned char ms);

void segundo(unsigned char s);
# 1 "delay.c" 2


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
