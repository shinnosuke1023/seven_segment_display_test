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
DigitalInOut four_digit[] = {
    DigitalInOut(D12),
    DigitalInOut(D11),
    DigitalInOut(D10),
    DigitalInOut(D9)
};

// ボタン用のピンを宣言
DigitalIn one_min(A0);
DigitalIn ten_sec(A1);
DigitalIn start_stop(A2);
DigitalIn reset(A3);


// 電子ブザーのFET用出力を宣言
DigitalInOut Buzzer(A7);

int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    one_min.mode(PullUp);
    ten_sec.mode(PullUp);
    start_stop.mode(PullUp);
    reset.mode(PullUp);

    for ( int i = 0; i < 4; i++)
    {
        four_digit[i].output();
        four_digit[i].mode(PullDown);
    }

    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
    }
}

void specify_digit(int num)
{
    for ( int i = 0; i < 4; i++)
    {
        four_digit[i] = 0;
    }
    four_digit[num] = 1;
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

void test_main_loop()
{
    int value = 0;
    int digit = 1;
    int one_min_val;
    int ten_sec_val;
    int start_stop_val;
    int reset_val;
    while (1)
    {
        one_min_val = one_min;
        ten_sec_val = ten_sec;
        start_stop_val = start_stop;
        reset_val = reset;
        if (one_min_val == 1)
        {
            if (value == 0)
            {
                value = 9;
            }
            else
            {
                value -= 1;
            }
        }
        if (ten_sec_val == 1)
        {
            if (value == 9)
            {
                value = 0;
            }
            else
            {
                value += 1;
            }
        }
        if (start_stop_val == 1)
        {
            if (digit == 1)
            {
                digit = 4;
            }
            else 
            {
                digit -= 1;
            }
        }
        if (reset_val == 1)
        {
            if (digit == 4)
            {
                digit = 1;
            }
            else
            {
                digit += 1;
            }
        }
        specify_digit(digit);
        show_number(value);
    }
        

}
