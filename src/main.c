//#include <avr/iotn1624.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "attiny1626_get.h"

#define BLINK_RAPID 5000000 * 2
#define BLINK_NORMAL 5000000 / 2

struct BinaryAlphabet {
    unsigned int A;
    unsigned int B;
    unsigned int C;
    unsigned int D;
    unsigned int E;
    unsigned int F;
    unsigned int G;
    unsigned int H;
    unsigned int I;
    unsigned int J;
    unsigned int K;
    unsigned int L;
    unsigned int M;
    unsigned int N;
    unsigned int O;
    unsigned int P;
    unsigned int Q;
    unsigned int R;
    unsigned int S;
    unsigned int T;
    unsigned int U;
    unsigned int V;
    unsigned int W;
    unsigned int X;
    unsigned int Y;
    unsigned int Z;

    unsigned int white_space;
};

void init_binary_alphabet(struct BinaryAlphabet *binary_alphabet) {
    binary_alphabet->A = 0b00000010;
    binary_alphabet->B = 0b10110000;
    binary_alphabet->C = 0b01000011;
    binary_alphabet->D = 0b01000100;
    binary_alphabet->E = 0b10010100;
    binary_alphabet->F = 0b01000110;
    binary_alphabet->G = 0b01000111;
    binary_alphabet->H = 0b10100010;
    binary_alphabet->I = 0b01001001;
    binary_alphabet->J = 0b01001010;
    binary_alphabet->K = 0b01001011;
    binary_alphabet->L = 0b00111100;
    binary_alphabet->M = 0b01001101;
    binary_alphabet->N = 0b01001110;
    binary_alphabet->O = 0b00001000;
    binary_alphabet->P = 0b01010000;
    binary_alphabet->Q = 0b01010001;
    binary_alphabet->R = 0b01010010;
    binary_alphabet->S = 0b01010011;
    binary_alphabet->T = 0b01010100;
    binary_alphabet->U = 0b01010101;
    binary_alphabet->V = 0b01010110;
    binary_alphabet->W = 0b01010111;
    binary_alphabet->X = 0b01011000;
    binary_alphabet->Y = 0b01011001;
    binary_alphabet->Z = 0b01011010;

    binary_alphabet->white_space = 0b11111111;
}


void start_blink(int pin_one, int pin_two, size_t duration) {
    //if(pin_one == NULL || pin_two == NULL) {
    //    exit(-1);
    //}
    //else {
        PORTB.OUTSET = pin_one;
        PORTB.DIRSET = (pin_two | pin_one);

        for(;;) {
            _delay_us(duration);

            PORTB.OUTTGL = pin_two;
        }
    //}
}

void spi_init(void) {
    // Disable global interrupts if necessary
    // cli();

    SPI0.CTRLB = SPI_SSD_bm;

    PORTB.DIRSET = PIN1_bm;
    PORTB.OUTSET = PIN1_bm;

    PORTA.DIRSET = PIN1_bm;

    PORTMUX.SPIROUTEA = PORTMUX_SPI0_ALT1_gc;
    PORTC.DIR |= (PIN0_bm | PIN2_bm); // Set SCK (PC0) and MOSI (PC2) as outputs

    SPI0.CTRLA = SPI_MASTER_bm | SPI_CLK2X_bm | SPI_PRESC_DIV4_gc | SPI_ENABLE_bm;
    // Master, double speed, /4 prescaler, MSB first, enable SPI

    // Enable global interrupts if previously disabled
    // sei();
}

void spi_write(uint8_t b){
    PORTA.OUTSET = PIN1_bm;
    SPI0.DATA = b; 

    while(!(SPI0.INTFLAGS & SPI_IF_bm)); // Wait for transmission to complete

    PORTA.OUTCLR = PIN1_bm;
}

void write_character_with_delay(uint8_t character, uint16_t delay) {
    for (uint16_t i = 0; i < delay; i++) {
        spi_write(character);
    }
}

void display_message(char *user_message, uint16_t delay_time) {
    struct BinaryAlphabet binary_alphabet;

    init_binary_alphabet(&binary_alphabet);

    //user_message = (char *)malloc(strlen(user_message) + 1);

    for(int i = 0; user_message[i] != '\0'; i++) {
        switch(user_message[i]) {
            case 'a':
                write_character_with_delay(0b00000010, delay_time);
                break;
            case 'b':
                write_character_with_delay(binary_alphabet.B, delay_time);
                break;
            case 'h':
                write_character_with_delay(binary_alphabet.H, delay_time);
                break;
            case 'e':
                write_character_with_delay(binary_alphabet.E, delay_time);
                break;
            case 'o':
                write_character_with_delay(binary_alphabet.O, delay_time);
             case 'l':
                write_character_with_delay(binary_alphabet.L, delay_time);
                break;
             case 'k':
                write_character_with_delay(0b10000000, delay_time);
                break;
            case ' ':
                write_character_with_delay(binary_alphabet.white_space, delay_time);
                break;
        }
    }
}

int main(void) {
    uint16_t delay = 65535 / 1;
    spi_init();
    for(;;){
        display_message("a", delay);

        //for (uint16_t i = 0; i < delay; i++){
            //           FABGCDE
        //    spi_write(0b11111111);// left - " "
        //    spi_write(0b00100010);// right - H
        //}
    }
}