#include "../include/attiny1626_display.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main() {
    struct BinaryAlphabet binary_alphabet;

    uint8_t port5 = 0b00100000;

    PORTB.DIRSET = PIN0_bm;

    for(;;){
        PORTB.OUTTGL = PIN0_bm;

        _delay_ms(1000);
        //display_message("g", _1000_MILLISECOND_DELAY, binary_alphabet);
    }
}