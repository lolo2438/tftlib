#include "mbed.h"
#include "pins.h"
#include "ui.h"
#include "RS485_Definitions.h"

//#define DEMO
//#define SPEED_TEST

#define BAUD_RATE 9600

void _draw(void);

RawSerial pc(USBTX, USBRX, BAUD_RATE); // tx, rx, baud

PinName LCD_DATA[8] = {LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7};
ui u(LCD_DATA, LCD_RST, LCD_CS, LCD_RS, LCD_WR, LCD_RD);

// main() runs in its own thread in the OS
int main()
{
#ifdef DEMO
    #ifdef SPEED_TEST
        #include "lcd.h"
        lcd s(LCD_DATA, LCD_RST, LCD_CS, LCD_RS, LCD_WR, LCD_RD);

        while(true){
            char id = pc.getc();
            int data = pc.getc();
        }

    #else
        u.demo();
    #endif
#else

    while(true){

        char id = pc.getc();
        char data = pc.getc();
        
        switch(id){
        // Power supply 
        case SLAVE_powersupply0:
            u.draw_battery(0, data - 'a');
            break;
        case SLAVE_powersupply1:
            u.draw_battery(1, data - 'a');
            break;
        case SLAVE_powersupply2:
            u.draw_battery(2, data - 'a');
            break;
        case SLAVE_powersupply3:
            u.draw_battery(3, data - 'a');
            break;
        
        // Motors
        case SLAVE_ESC_1:
            u.draw_motor(1, data - '0');
            break;
        case SLAVE_ESC_2:
            u.draw_motor(2, data - '0');
            break;
        case SLAVE_ESC_3:
            u.draw_motor(3, data - '0');
            break;
        case SLAVE_ESC_4:
            u.draw_motor(4, data - '0');
            break;
        case SLAVE_ESC_5:
            u.draw_motor(5, data - '0');
            break;
        case SLAVE_ESC_6:
            u.draw_motor(6, data - '0');
            break;
        case SLAVE_ESC_7:
            u.draw_motor(7, data - '0');
            break;
        case SLAVE_ESC_8:
            u.draw_motor(8, data - '0');
            break;

        // KillSwitch
        case SLAVE_killMission:
            u.draw_kswitch(data - '0');
            break;
        }
    }
#endif
}