#include "mbed.h"
#include "pins.h"
#include "ui.h"
#include "on.h"
#include "lcd.h"
//#include "SDFileSystem.h"

// main() runs in its own thread in the OS
int main()
{
    PinName LCD_DATA[8] = {LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7};
    //115200
    Serial pc(USBTX, USBRX, 9600); // tx, rx, baud

    /*   (x,y)
        (0,0)     (480,0)
        O------ x
        |
        |
        y
        (0,320)
    */
   // lcd s(LCD_DATA, LCD_RST, LCD_CS, LCD_RS, LCD_WR, LCD_RD, 480, 320);

   // s.wrcolorbuf(0, 480, 0, 320, on);
     ui u(LCD_DATA, LCD_RST, LCD_CS, LCD_RS, LCD_WR, LCD_RD);

    int i,j;
    for(i = 0; i < 100; i += 1){
        for(j = 0; j < BATTERY_COUNT; j += 1){
            u.draw_battery(j, i);
        }
    }

}