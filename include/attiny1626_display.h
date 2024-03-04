#ifndef ATTINY1626_DISPLAY_H
#define ATTINY1626_DISPLAY_H

#define BLINK_RAPID 5000000 * 2
#define BLINK_NORMAL 5000000 / 2

#define _1000_MILLISECOND_DELAY 32767 * 2
#define _500_MILLISECOND_DELAY 32767
#define _250_MILLISECOND_DELAY 16383
#define _50_MILLISECOND_DELAY 3276

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

void display_message(char *user_message, int delay_time, struct BinaryAlphabet binary_alphabet);

#endif