#include "../include/attiny1626_display.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <unistd.h>

void tca_init() {
    // Set buzzer pin (PA1) as output
    PORTB.DIR |= PIN0_bm;

    // Set waveform generation mode to single slope
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP1EN_bm;

    // Set period to control PWM frequency
    TCA0.SINGLE.PER = 100;

    // Set duty cycle to 50% initially
    TCA0.SINGLE.CMP1 = 200;

    // Enable TCA0 overflow interrupt
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;

    // Enable TCA0
    TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm;
}

void tcb_init(uint16_t period) {
    PORTB.DIRSET = PIN0_bm;

    TCB0.CTRLB = TCB_CNTMODE_INT_gc;   // Configure TCB0 in periodic interrupt mode
    TCB0.CCMP = period;                   // Set period to some value
    TCB0.INTCTRL = TCB_CAPT_bm;         // Invoke the CAPT ISR when the counter reaches CCMP
    TCB0.CTRLA = TCB_ENABLE_bm;         // Enable TCB0
}

ISR(TCB0_INT_vect) {
    // Your ISR code here
    // This function will be called each time TCB0 overflows

    PORTB.OUT = PIN0_bm; // Turn on the buzzer
    _delay_ms(200);
}

int main() {
    cli();
    tcb_init(1000);
    sei();

    // Main program loop
    while(1) {
    }
    return 0;
}