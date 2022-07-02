/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms


DigitalOut seven_segment[] = {
    DigitalOut(D2),
    DigitalOut(D4),
    DigitalOut(D6),
    DigitalOut(D7),
    DigitalOut(D8),
    DigitalOut(D3),
    DigitalOut(D5),
    
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
