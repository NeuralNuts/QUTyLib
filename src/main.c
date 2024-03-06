#include "../include/attiny1626_display.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <unistd.h>

void tca_init(uint16_t freq) {
    PORTMUX.TCAROUTEA = PORTMUX_TCA00_bm;

    PORTB.DIRSET = PIN0_bm;

    //  WGM set to single slope
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP1EN_bm;
    //TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_DSBOTTOM_gc | TCA_SINGLE_CMP1EN_bm;

    // period to control PWM frequency
    TCA0.SINGLE.PER = freq;

    // Set duty cycle initially
    TCA0.SINGLE.CMP1 = 1000;

    // Enable TCA0 overflow interrupt
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;

    // Enable TCA0
    TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm;
}

ISR(TCA0_OVF_vect) {
    PORTB.OUTTGL = PIN0_bm;

    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

#define FREQ_BASE 90000 * 9 
#define FREQ_BASE_2 50000 * 2
#define DELAY_BASE 30
#define DELAY_BASE_HALF 60 / 4

void note(uint16_t freq, uint16_t duration) {
    PORTB.OUTCLR = PIN0_bm; // Toggle the output pin connected to the buzzer

    tca_init(freq); // Initialize TCA for the given frequency

    for (uint16_t i = 0; i < duration; i++) {
        _delay_ms(1); // Delay for 1 millisecond
    }


    // Turn off the note
    TCA0.SINGLE.CTRLA = 0; // Disable TCA
    PORTB.OUTSET = PIN0_bm; // Set the pin high
}

// Play the melody
void compose() {
     // Si Si Si Si Si
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);

    // Re Si Si Si Si Si
    note(FREQ_BASE / 233, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);

    // Si Si Si Si Si
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);

    // Si Si Si Si Si
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);

    // Si Si Si Si Si
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);

    // Si Si Si Si Si Si Si Si Si Si Si
    note(FREQ_BASE / 247, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);

    // Mi Mi Mi Mi Mi Mi Mi
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);

    // Re Re Re Re Re Re Re
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);

    // La La Si Si Si Si Si Si Si Si Si Si
    note(FREQ_BASE / 440, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 440, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);

    // Mi Mi Si Si Si Si Si Si Si Si Si Si
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);

    // Mi Mi
    note(FREQ_BASE / 330, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);

    // Si Si Si Si Si Si Si Si Si Si Si
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);

    // Mi Mi Mi Mi Mi Mi Mi
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);

    // Re Re Re Re Re Re Re
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);

    // La Si Si Si Si Si Si Si Si Si Si Si Si
    note(FREQ_BASE / 440, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);

    // Mi Mi Si Si Si Si Si Si Si Si Si Si
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 494, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);

    // Mi Mi
    note(FREQ_BASE / 330, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);

    // Si Si Si Si Si Si Si Si Si Si Si
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 247, DELAY_BASE * 2);
    _delay_ms(DELAY_BASE);

    // Mi Mi Mi Mi Mi Mi Mi
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 330, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);

    // Re Re Re Re Re Re Re
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
    note(FREQ_BASE / 294, DELAY_BASE * 4);
    _delay_ms(DELAY_BASE);
}

int main() {
    cli();
    sei();

    struct BinaryAlphabet ba;

    while(1) {
        compose();
    }

    return 0;
}