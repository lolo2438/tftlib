#include "mbed.h"
#include "pins.h"
#include "ui.h"
#include "lcd.h"
#include "m_on.h"
#include "ui_bg.h"

// main() runs in its own thread in the OS
int main()
{
    PinName LCD_DATA[8] = {LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7};
    //115200
   // Serial pc(USBTX, USBRX, 9600); // tx, rx, baud

    /*   
    */
    //lcd s(LCD_DATA, LCD_RST, LCD_CS, LCD_RS, LCD_WR, LCD_RD, 480, 320);

   // s.fillrect(478,479,318,319,RED);
   // s.pixel(479,319,BLUE);

    //s.wrcolorbuf(0, 0, 480, 320, ui_bg);
  //  s.wrcolorbuf(0,0,70,34,m_on);

  ui u(LCD_DATA, LCD_RST, LCD_CS, LCD_RS, LCD_WR, LCD_RD);
  u.demo();
}