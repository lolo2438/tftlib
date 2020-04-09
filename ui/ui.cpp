#include "ui.h"

#include "bat_0_5.h"
#include "bat_1_5.h"
#include "bat_2_5.h"
#include "bat_3_5.h"
#include "bat_4_5.h"
#include "bat_5_5.h"

#include "kswitch_off.h"
#include "kswitch_on.h"

#include "m_off.h"
#include "m_on.h"

#include "ui_bg.h"

#include "colors.h"

#define MAX_VOLTAGE 100
#define MIN_VOLTAGE 10

ui::ui(PinName *lcd_data, PinName lcd_rst, PinName lcd_cs, PinName lcd_rs, PinName lcd_wr, PinName lcd_rd, unsigned short ScreenSize_X, unsigned short ScreenSize_Y)
    :s(lcd_data, lcd_rst, lcd_cs, lcd_rs, lcd_wr, lcd_rd, ScreenSize_X, ScreenSize_Y), battery_state{-1}, motor_state{1}
{
    s.setBgColor(0x738E);   //Grayish
    s.wrcolorbuf(0, ScreenSize_X, 0, ScreenSize_Y, ui_bg);
}

void ui::draw_battery(int battery_nb, int voltage){
   
    const int treshold[5] = { 90, 70, 50, 30, 10 };

    const unsigned int battery_x_pos = 20;
    const unsigned int battery_y_pos[4] = {112, 166, 227, 278};
    const unsigned int battery_x_size = 65;
    const unsigned int battery_y_size = 25;

    const unsigned int voltage_x_pos = 137;
    const unsigned int voltage_y_pos[4] = {118, 172, 231, 284};

    const color_t *battery_img[6] = { bat_0_5, bat_1_5, bat_2_5, bat_3_5, bat_4_5, bat_5_5 };

    int b_state;

    // Get the state of the battery
    if     (voltage > treshold[0]) b_state = 5;
    else if(voltage > treshold[1]) b_state = 4;
    else if(voltage > treshold[2]) b_state = 3;
    else if(voltage > treshold[3]) b_state = 2;
    else if(voltage > treshold[4]) b_state = 1;
    else                           b_state = 0;

    // Only redraw when needed
    if(b_state != battery_state[battery_nb]){
        battery_state[battery_nb] = b_state;
        //TODO: Faire en sorte que couleur blanc: OXFFFF ne soit pas écris, peut etre ajouter un flag// changer false a true
        s.wrcolorbuf(battery_x_pos, battery_x_pos + battery_x_size, battery_y_pos[battery_nb], 
                     battery_y_pos[battery_nb] + battery_y_size, battery_img[b_state], false);
    }

    // TODO: Convert voltage to a string
    char str[3];    // Attention au null terminator!! max value 99\0
    sprintf(str,"%d", voltage);
    s.string(voltage_x_pos, voltage_y_pos[battery_nb], str, BLACK);
}


void ui::draw_motor(int motor_nb, bool motor_status){

    const color_t *motor_img[2] = {m_off, m_on};
    
    const unsigned int motor_x_pos[2] = { 0, 1 }; // [0] -> moteurs paires, [1] -> moteurs impaires
    const unsigned int motor_y_pos[4] = { 0, 1, 2, 3 }; // 1 et 2 on le meme, 3 et 4 ont le meme...

    const unsigned int motor_x_size = 70;
    const unsigned int motor_y_size = 34;

    bool xindex = motor_nb % 2; // 1,3,5,7 ont le meme index, 2,4,6,8 ont le meme index
    int yindex = motor_nb - (motor_nb / 2); // 1,2 ; 3,4 ; 5,6 ; 7,8 ; ont le meme index

    if(motor_state[motor_nb - 1] != motor_status){
        motor_state[motor_nb - 1] = motor_status;
        s.wrcolorbuf(motor_x_pos[xindex], motor_x_pos[xindex] + motor_x_size, motor_y_pos[yindex], 
                     motor_y_pos[yindex] + motor_y_size, motor_img[motor_status], false);
    }
}

void ui::draw_kswitch(bool kswitch_state){

}