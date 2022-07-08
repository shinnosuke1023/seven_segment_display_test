#include "mbed.h"

#define setting 0
#define counting 0


//Serial pc(USBTX, USBRX); // tx, rx

// ７セグ出力先のピンを宣言
DigitalOut seven_seg[] = {
    DigitalOut(D2),
    DigitalOut(D4),
    DigitalOut(D6),
    DigitalOut(D1), // D7 => D1
    DigitalOut(D0), // D8 => D0 マイコンピン仕様により電流不足のため
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

// ボタン入力制御用変数を宣言
int one_min_pressed = 0;
int ten_sec_pressed = 0;
int start_stop_pressed = 0;
int reset_pressed = 0;

// 時間用変数を宣言
int setting_time;
int remaining_time;
int minute;
int second;

// 各桁の数字用変数を宣言
int digits[] = {0, 0, 0, 0};

// 現在のモードを表す変数を宣言
int mode = setting;


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

void show_time(int time)
{
    second = time % 60;
    minute = (time - second) / 60;
    digits[1] = minute % 10;
    digits[0] = (minute - digits[1]) / 10;
    digits[3] = second % 10;
    digits[2] = (second - digits[3]) / 10;
    for (int i; i < 4;i++)
    {
        for ( int n = 0; n < 7; n++)
        {
            seven_seg[n] = 0;
        }
        specify_digit(i);
        show_number(digits[i]);
    }

}

void buzzer_ringing()
{
    for (int x;x<3;x++)
    {
        for(int y;y<4;y++)
        {
            Buzzer = 1;
            Buzzer = 0;
            wait(0.2);
        }
        wait(0.2);
    }
}

void module_test_loop()
{
    int value = 0;
    while (1)
    {
        wait(1);
        show_number(value);
        if (value == 9)
        {
            value = 0;
        }
        else
        {
            value += 1;
        }
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

void test_main_loop2()
{
    remaining_time = 0;
    while (1)
    {
        show_time(remaining_time);
        if(remaining_time == 5990)
        {
            remaining_time = 0;
        }
        else
        {
            remaining_time++;
        }
    }
}

int main()
{

    one_min.mode(PullUp);
    ten_sec.mode(PullUp);
    start_stop.mode(PullUp);
    reset.mode(PullUp);

    for ( int i = 0; i < 4; i++)
    {
        four_digit[i].output();
        four_digit[i].mode(PullDown);
    }

    test_main_loop2();
}
