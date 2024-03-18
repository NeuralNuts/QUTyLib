// ATTINY1626 lib
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

// std lib
#include <stdio.h>
#include <unistd.h>

// My files
#include "../include/attiny1626_display.h"

#define FREQ_BASE 90000 * 9 
#define FREQ_BASE_2 50000 * 2
#define DELAY_BASE 30
#define DELAY_BASE_HALF 60 / 4

struct Note {
    float freq;
    int duration;
};

struct Note notes[] = {};

#define NUM_PWM_CHANNELS 2 // Number of PWM channels to use

void non_const_delay(uint16_t duration) {
    for(uint16_t i = 0; i < duration; i++) {
        _delay_ms(1);
    }
}

void tca_init(uint16_t freq, uint16_t duration) {
    PORTMUX.TCAROUTEA |= PORTMUX_TCA00_bm;
    PORTB.DIRSET = PIN0_bm;

    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc;
    TCA0.SINGLE.CTRLB |= TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP1EN_bm;
    TCA0.SINGLE.PER = freq;
    TCA0.SINGLE.CMP1 = TCA0.SINGLE.PER / 2;
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;

    non_const_delay(duration);
}

void tcb_init(uint16_t freq, uint16_t duration) {
    TCB0.CTRLA = TCB_CLKSEL_DIV1_gc; 
    TCB0.CCMP = freq / 2; 
    TCB0.CTRLB = TCB_CCMPEN_bm | TCB_CNTMODE_PWM8_gc;

    non_const_delay(duration);
}

ISR(TCA0_OVF_vect) {
    PORTB.OUTTGL = PIN0_bm;
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

void play_note(uint16_t channel, uint16_t freq, uint16_t duration) {
    switch (channel) {
        case 0:
            tca_init(freq, duration);
            break;
        case 1:
            tcb_init(freq, duration);
            break;
    }
}

int main() {
    sei();

    while(1) {
        int num_notes = sizeof(notes) / sizeof(notes[0]);

        for (int i = 0; i < num_notes; i++) {
            //play_note(0, midi_notes[i].freq, midi_notes[i].duration);
        }
    }

    return 0;
}