#include "../include/attiny1626_display.h"

int main() {
    struct BinaryAlphabet binary_alphabet;

    for(;;){
        display_message("g", _1000_MILLISECOND_DELAY, binary_alphabet);
    }
}