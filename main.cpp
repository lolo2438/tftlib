#include "mbed.h"
#include "pins.h"
#include "lcd.h"

//#include "SDFileSystem.h"

// main() runs in its own thread in the OS
int main()
{
    PinName LCD_DATA[8] = {LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7};

    RawSerial pc(USBTX, USBRX, 115200); // tx, rx, baud

    /* TODO:
        -> Bitmap read and print
     */
     /*   (x,y)
     (0,0)     (480,0)
        O------ x
        |
        |
        y
     (0,320)
     
      */
    lcd s(LCD_DATA, LCD_RST, LCD_CS, LCD_RS, LCD_WR, LCD_RD, 480, 320);

    s.cls();

    s.fillcircle(240, 160, 50, RED);
    s.string(140, 240, "Hello World!", BLACK);
    s.segment(32,58,0,90,BLUE);
}