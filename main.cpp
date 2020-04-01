#include "mbed.h"
#include "pins.h"
#include "colors.h"
#include "text.h"
#include "lcd.h"

// main() runs in its own thread in the OS
int main()
{
    PinName LCD_DATA[8] = {LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7};

    RawSerial pc(USBTX, USBRX, 115200); // tx, rx, baud

    /* TODO:
        -> Bitmap read and print
        -> Characters
     */
     /*   (x,y)
     (0,0)     (0,480)
        O------ y
        |
        |
        x
     (320,0)
     
      */
    lcd s(LCD_DATA, LCD_RST, LCD_CS, LCD_RS, LCD_WR, LCD_RD, 320, 480);

    while (true) {

        int x,y,i;

        s.fillcircle(160,240,30,0x001F);
    }
}

