#include "../include/attiny1626_display.h"

int main() {
    struct BinaryAlphabet binary_alphabet;

    for(;;){
        display_message("hello", _500_MILLISECOND_DELAY, binary_alphabet);
    }
}