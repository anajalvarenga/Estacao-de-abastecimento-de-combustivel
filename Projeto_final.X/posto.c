#include <pic18f4520.h>
#include "posto.h"
#include "bits.h"
#include "keypad.h"
#include "lcd.h"
#include "stdio.h"
#include "ssd.h"
#include "delay.h"
#include "pwm.h"

unsigned int litro = 0;

void ledInicial() {
    PORTD = 0x01;
    tempo(250);
    PORTD = 0x03;
    tempo(250);
    PORTD = 0x07;
    tempo(250);
    PORTD = 0x0F;
    tempo(250);
    PORTD = 0x1F;
    tempo(250);
    PORTD = 0x3F;
    tempo(250);
    PORTD = 0x7F;
    tempo(250);
    PORTD = 0xFF;
    tempo(250);
    PORTD = 0x7F;
    tempo(250);
    PORTD = 0x3F;
    tempo(250);
    PORTD = 0x1F;
    tempo(250);
    PORTD = 0x0F;
    tempo(250);
    PORTD = 0x07;
    tempo(250);
    PORTD = 0x03;
    tempo(250);
    PORTD = 0x01;
    tempo(250);
    PORTD = 0x00;
    tempo(250);
}

void mensagemInicial() {
    char i, msgInicial[24] = "Bem-vindos Posto da Ana";

    ledInicial();

    lcdCommand(0x8F);
    for (i = 0; i < 23; i++) {
        lcdData(msgInicial[i]);
        lcdCommand(0x18);
        tempo(250);
    }
    tempo(250);
    lcdCommand(0x01);

    printf(" 1 - Gasolina\n 2 - Etanol\n 3 - Diesel\n 4 - G Adtivada");
}

void abastece(double valor, int indice) {
    float i;
    unsigned int preco = 0, litroTotal;
    char j, total[7] = "total:";

    lcdCommand(0x01);
    lcdCommand(0x80);
    for (j = 0; j < 6; j++) {
        lcdData(total[j]);
    }

    pwmSet1(32);
    
    while (bitTst(kpRead(), indice)) {
        preco = (unsigned int) (litro * valor);

        lcdCommand(0xC0);
        lcdData('R');
        lcdData('$');
        lcdData(((preco / 10000) % 10) + 48);
        lcdData(((preco / 1000) % 10) + 48);
        lcdData(((preco / 100) % 10) + 48);
        lcdData(((preco / 10) % 10) + 48);
        lcdData(',');
        lcdData(((preco / 1) % 10) + 48);
        lcdData(((preco * 10) % 10) + 48);

        litro++;
        ssdDigit((litro / 10) % 10, 3);
        ssdDigit((litro / 100) % 10, 2);
        ssdDigit((litro / 1000) % 10, 1);
        ssdDigit((litro / 10000) % 10, 0);

        for (i = 0; i < 180; i++);

        ssdUpdate();
        kpDebounce();
    }
    pwmSet1(0);
    
    litroTotal = litro;
    posAbastece(preco, litroTotal);
    
    litro = 0;
    ssdDigit((litro / 10) % 10, 3);
    ssdDigit((litro / 100) % 10, 2);
    ssdDigit((litro / 1000) % 10, 1);
    ssdDigit((litro / 10000) % 10, 0);
}

void posAbastece(unsigned int preco, unsigned int litroTotal) {
    char i, totalP[7] = "total:", totalL[8] = "litros:", continuar = 0;

    lcdCommand(0x01);
    for (i = 0; i < 6; i++) {
        lcdData(totalP[i]);
    }

    lcdCommand(0xC0);
    lcdData('R');
    lcdData('$');
    lcdData(((preco / 10000) % 10) + 48);
    lcdData(((preco / 1000) % 10) + 48);
    lcdData(((preco / 100) % 10) + 48);
    lcdData(((preco / 10) % 10) + 48);
    lcdData(',');
    lcdData(((preco / 1) % 10) + 48);
    lcdData(((preco * 10) % 10) + 48);

    lcdCommand(0x90);
    for (i = 0; i < 7; i++) {
        lcdData(totalL[i]);
    }

    lcdCommand(0xD0);
    lcdData(((litroTotal / 10000) % 10) + 48);
    lcdData(((litroTotal / 1000) % 10) + 48);
    lcdData(((litroTotal / 100) % 10) + 48);
    lcdData(((litroTotal / 10) % 10) + 48);

    segundo(10);

    lcdCommand(0x01);
    printf("Apos efetuar o  \npagamento     \n          \nPressione (*)   ");

    while (continuar == 0) {
        if (bitTst(kpRead(), 0)) {
            continuar = 1;
        }
        kpDebounce();
    }
    lcdCommand(0x01);
    lcdCommand(0x80);
    printf(" 1 - Gasolina\n 2 - Etanol\n 3 - Diesel\n 4 - G Adtivada");
}