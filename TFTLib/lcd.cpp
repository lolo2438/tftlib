#include "lcd.h"

lcd::lcd(PinName *lcd_data, PinName lcd_rst, PinName lcd_cs, PinName lcd_rs, PinName lcd_wr, PinName lcd_rd, unsigned short ScreenSize_X, unsigned short ScreenSize_Y)
    : hw(lcd_data, lcd_rst, lcd_cs, lcd_rs, lcd_wr, lcd_rd), xSize(ScreenSize_X), ySize(ScreenSize_Y)
{

    xSize = ScreenSize_X;
    ySize = ScreenSize_Y;

    // Init Sequence    
    wr_cmd8(0xE0);        // Positive gamma control
    wr_data8(0x0F);
    wr_data8(0x18);
    wr_data8(0x15);
    wr_data8(0x09);
    wr_data8(0x0B);
    wr_data8(0x04);
    wr_data8(0x49);
    wr_data8(0x64);
    wr_data8(0x3D);
    wr_data8(0x08);
    wr_data8(0x15);
    wr_data8(0x06);
    wr_data8(0x12);
    wr_data8(0x07);
    wr_data8(0x00);

    wr_cmd8(0xE1);        // Negative gamma control
    wr_data8(0x0F);
    wr_data8(0x38);
    wr_data8(0x35);
    wr_data8(0x0a);
    wr_data8(0x0c);
    wr_data8(0x03);
    wr_data8(0x4A);
    wr_data8(0x42);
    wr_data8(0x36);
    wr_data8(0x04);
    wr_data8(0x0F);
    wr_data8(0x03);
    wr_data8(0x1F);
    wr_data8(0x1B);
    wr_data8(0x00);

    wr_cmd8(0x36);        // Memory Access Control
    wr_data8(0x08);       // BGR screen
    
    wr_cmd8(0x3A);        // Interface Pixel Format
    wr_data8(0x55);       // 16 bit/pixel for rgb and cpu interface
    
    wr_cmd8(0xB1);        // Frame Rate Control
    wr_data8(0xB0);       // 70 Hz
    wr_data8(0x10);       // 16 clocks/line
    
    wr_cmd8(0x20);        // Display inversion OFF

    wr_cmd8(0x11);        // Sleep Out
    wait_us(160000);

    wr_cmd8(0x53);        // Write ctrl display value
    wr_data8(0x24);       // BCTRL=1, BL=1
    
    wr_cmd8(0x51);        // Write display brightness value
    wr_data8(0xFF);       // Highest brightness

    wr_cmd8(0x29);        // Display on
}

void lcd::pixel(unsigned int x, unsigned int y, unsigned short color){

    wr_cmd8(0x2A);
    wr_data16(x);
    wr_data16(x);

    wr_cmd8(0x2B);
    wr_data16(y);
    wr_data16(y);

    wr_gram(color, 1);
}

void lcd::hline(unsigned int x1, unsigned int x2,  unsigned int y, unsigned short color){

    wr_cmd8(0x2A);
    wr_data16(x1 < x2 ? x1 : x2);
    wr_data16(x1 < x2 ? x2 : x1);

    wr_cmd8(0x2B);
    wr_data16(y);
    wr_data16(y);

    wr_gram(color, (x2 - x1) + 1);
}

void lcd::vline(unsigned int x, unsigned int y1, unsigned int y2, unsigned short color){

    wr_cmd8(0x2A);
    wr_data16(x);
    wr_data16(x);

    wr_cmd8(0x2B);
    wr_data16(y1 < y2 ? y1 : y2);
    wr_data16(y1 < y2 ? y2 : y1);

    wr_gram(color, (y2 - y1) + 1);
}

void lcd::segment(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, unsigned short color){

    /* Algorithme: Brensnham line algorithme
       https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
     */

    int sx = x1 < x2 ? 1 : -1;
    int dx = (x2 - x1) * sx;
    
    int sy = y1 < y2 ? -1 : 1;
    int dy = (y2 - y1) * sy;
    
    int e = dx + dy;
    int e2;
    
    while((x1 != x2) && (y1 != y2)){
        pixel(x1, y1, color);

        e2 = e + e;
        if(e2 >= dy){
            e += dy;
            x1 += sx;
        }

        if(e2 <= dx){
            e += dx;
            y1 -= sy;
        }
    }

    pixel(x2,y2,color);
}

void lcd::rect(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, unsigned short color){

    hline(x1, x2, y1, color);
    hline(x1, x2, y2, color);
    
    vline(x1, y1, y2, color);
    vline(x2, y1, y2, color);
}
    
void lcd::fillrect(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, unsigned short color){

    wr_cmd8(0x2A);
    wr_data16(x1 < x2 ? x1 : x2);
    wr_data16(x1 < x2 ? x2 : x1);

    wr_cmd8(0x2B);
    wr_data16(y1 < y2 ? y1 : y2);
    wr_data16(y1 < y2 ? y2 : y1);
    
    wr_gram(color, (((x2 - x1) + 1) * ((y2 - y1) + 1)));
}
    
void lcd::circle(unsigned int x0, unsigned int y0, unsigned int r, unsigned short color){
    
    /*
    Algorithme: Cercle d'andres
    https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_de_cercle_d%27Andres
        Plus lent mais résoud le problème de bresenham
    */
    /*
    int x = 0;
    int y = r;
    int d = r - 1;

    int x_2;
    int y_2;

    while(x <= y){
        pixel(x0 + x, y0 + y, color);
        pixel(x0 + y, y0 + x, color);
        
        pixel(x0 - x, y0 + y, color);
        pixel(x0 - y, y0 + x, color);
        
        pixel(x0 + x, y0 - y, color);
        pixel(x0 + y, y0 - x, color);
        
        pixel(x0 - x, y0 - y, color);
        pixel(x0 - y, y0 - x, color);
        
        x_2 = (x + x);
        y_2 = (y + y);

        if(d >= x_2){
            d = d - x_2 - 1;
            x = x + 1;
        }
        else if(d < ((r + r) - y_2)){
            d = d + y_2 - 1;
            y = y - 1;
        }   
        else{
            d = d + y_2 - x_2 - 2;
            y = y - 1;
            x = x + 1;
        }   
    }
    */

    /* 
    Autre algorithme: cercle de bresenham
    https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_d%27arc_de_cercle_de_Bresenham
    */
    int x = 0;
    int y = r;
    int m = 5 - 4*y;

    while(x <= y){

        pixel(x0 + x, y0 + y, color);
        pixel(x0 + y, y0 + x, color);
        
        pixel(x0 - x, y0 + y, color);
        pixel(x0 - y, y0 + x, color);
        
        pixel(x0 + x, y0 - y, color);
        pixel(x0 + y, y0 - x, color);
        
        pixel(x0 - x, y0 - y, color);
        pixel(x0 - y, y0 - x, color);

        if(m > 0){
            y = y - 1;
            m = m - 8*y;
        }
        
        x = x + 1;
        m = m + 8*x + 4;
    }
}

void lcd::fillcircle(unsigned int x0, unsigned int y0, unsigned int r, unsigned short color){

    int x = 0;
    int y = r;
    int m = 5 - 4*y;

    while(x <= y){

        vline((x0 + x), (y0 - y), (y0 + y), color);
        vline((x0 - x), (y0 - y), (y0 + y), color);
        vline((x0 + y), (y0 - x), (y0 + x), color);
        vline((x0 - y), (y0 - x), (y0 + x), color);

        hline((x0 - x), (x0 + x), (y0 + y), color);
        hline((x0 - x), (x0 + x), (y0 - y), color);
        hline((x0 - y), (x0 + y), (y0 + x), color);
        hline((x0 - y), (x0 + y), (y0 - x), color);        

        if(m > 0){
            y = y - 1;
            m = m - 8*y;
        }

        x = x + 1;
        m = m + 8*x + 4;
    }
}