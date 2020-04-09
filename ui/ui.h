#ifndef __UI_H__
#define __UI_H__

#include "lcd.h"

#define BATTERY_COUNT 4
#define MOTOR_COUNT 8

class ui {

public:
    ui(PinName *lcd_data, PinName lcd_rst, PinName lcd_cs, PinName lcd_rs, PinName lcd_wr, PinName lcd_rd, unsigned short ScreenSize_X = 480, unsigned short ScreenSize_Y = 320);

    void draw_battery(int battery_nb, int voltage);

    void draw_motor(int motor_nb, bool motor_status);

    void draw_kswitch(bool kswitch_state);

private:

    lcd s;
    int battery_state[BATTERY_COUNT];
    bool motor_state[MOTOR_COUNT];
};

#endif