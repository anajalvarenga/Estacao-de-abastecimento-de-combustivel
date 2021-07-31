#include <pic18f4520.h>
#include "config.h"
#include "bits.h"
#include "ssd.h"
#include "keypad.h"
#include "delay.h"
#include "posto.h"
#include "lcd.h"
#include "pwm.h"

void main(void) {
    float i = 0;
    unsigned int tecla, temp;

    TRISD = 0x00;
    PORTD = 0x00;
    
    lcdInit();
    mensagemInicial();
    
    ssdInit();
    kpInit();
    pwmInit();

    for (;;) {
        ssdUpdate();
        kpDebounce();
        tecla = kpRead();

        if (bitTst(tecla, 3)) { //1 - Gasolina
            abastece(6.108, 3);
        }
        if (bitTst(tecla, 7)) { //2 - Etanol
            abastece(4.324, 7);
        }
        if (bitTst(tecla, 11)) { //3 - Diesel
            abastece(4.718, 11);
        }
        if (bitTst(tecla, 2)) { //4 - Gasolina Adtivada
            abastece(6.195, 2);
        }
        for (i = 0; i < 100; i++);
    }
}
