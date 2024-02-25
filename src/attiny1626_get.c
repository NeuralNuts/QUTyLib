#include <avr/io.h>
#include <stdio.h>
#include "string.h"

#define MAX_MESSAGE 255

char get_analog_comparator_type(int analog_comparator) {
    (register8_t)analog_comparator;

    struct AC_struct ac;
    char result_message[MAX_MESSAGE];

    if(analog_comparator == ac.CTRLA) strcpy(result_message, "[ANALOG_COMPARATOR_TYPE]: Control A");
    if(analog_comparator == ac.MUXCTRLA) strcpy(result_message, "[ANALOG_COMPARATOR_TYPE]: Mux Control A");
    if(analog_comparator == ac.DACREF) strcpy(result_message, "[ANALOG_COMPARATOR_TYPE]: Referance scale conrtol");
    if(analog_comparator == ac.INTCTRL) strcpy(result_message, "[ANALOG_COMPARATOR_TYPE]: Interrupt Control");
    if(analog_comparator == ac.STATUS) strcpy(result_message, "[ANALOG_COMPARATOR_TYPE]: Returns the analog comparator status");

    return result_message;
}