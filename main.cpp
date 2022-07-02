/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

// ７セグ出力先のピンを宣言
DigitalOut seven_seg[] = {
    DigitalOut(D2),
    DigitalOut(D4),
    DigitalOut(D6),
    DigitalOut(D7),
    DigitalOut(D8),
    DigitalOut(D3),
    DigitalOut(D5)
};

//　７セグの桁数指定のピンを宣言
DigitalOut four_digit[] = {
    DigitalOut(D12),
    DigitalOut(D11),
    DigitalOut(D10),
    DigitalOut(D9)
};

int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
    }
}

void show_number(int num)
{
    for ( int i = 0; i < 7; i++)
    {
        seven_seg[i] = 0;
    }
    switch (num) {
    case 0:
        seven_seg[0] = 1;
        seven_seg[1] = 1;
        seven_seg[2] = 1;
        seven_seg[3] = 1;
        seven_seg[4] = 1;
        seven_seg[5] = 1;
        break;
    case 1:
        seven_seg[1] = 1;
        seven_seg[2] = 1;
        break;
    case 2:
        seven_seg[0] = 1;
        seven_seg[1] = 1;
        seven_seg[3] = 1;
        seven_seg[4] = 1;
        seven_seg[6] = 1;
        break;
    case 3:
        seven_seg[0] = 1;
        seven_seg[1] = 1;
        seven_seg[2] = 1;
        seven_seg[3] = 1;
        seven_seg[6] = 1;
        break;
    case 4:
        seven_seg[1] = 1;
        seven_seg[2] = 1;
        seven_seg[5] = 1;
        seven_seg[6] = 1;
        break;
    case 5:
        seven_seg[0] = 1;
        seven_seg[2] = 1;
        seven_seg[3] = 1;
        seven_seg[5] = 1;
        seven_seg[6] = 1;
        break;
    case 6:
        seven_seg[0] = 1;
        seven_seg[2] = 1;
        seven_seg[3] = 1;
        seven_seg[4] = 1;
        seven_seg[5] = 1;
        seven_seg[6] = 1;
        break;
    case 7:
        seven_seg[0] = 1;
        seven_seg[1] = 1;
        seven_seg[2] = 1;
        break;
    case 8:
        seven_seg[0] = 1;
        seven_seg[1] = 1;
        seven_seg[2] = 1;
        seven_seg[3] = 1;
        seven_seg[4] = 1;
        seven_seg[5] = 1;
        seven_seg[6] = 1;
        break;
    case 9:
        seven_seg[0] = 1;
        seven_seg[1] = 1;
        seven_seg[2] = 1;
        seven_seg[3] = 1;
        seven_seg[5] = 1;
        seven_seg[6] = 1;
        break;
    default:
        printf("ほかの値です。\r\n");
    }
}