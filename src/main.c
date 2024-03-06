#include "../include/attiny1626_display.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <unistd.h>

void tca_init() {
    PORTB.DIRSET = PIN0_bm;

    // Set waveform generation mode to single slope
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP1EN_bm;
    //TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_DSBOTTOM_gc | TCA_SINGLE_CMP1EN_bm;

    // Set period to control PWM frequency
    TCA0.SINGLE.PER = 1000;

    // Set duty cycle to 50% initially
    TCA0.SINGLE.CMP1 = 255;

    // Enable TCA0 overflow interrupt
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;

    // Enable TCA0
    TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm;
}

ISR(TCA0_OVF_vect) {
    // Your ISR code here

    PORTB.OUTTGL = PIN0_bm;

    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

int main() {
    cli();
    tca_init();
    sei();

    // Main program loop
    while(1) {
    }
    return 0;
}