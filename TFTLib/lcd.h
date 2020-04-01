#ifndef __LCD_H__
#define __LCD_H__

#include "hw.h"

class lcd : protected hw
{

public:
    lcd(PinName *lcd_data, PinName lcd_rst, PinName lcd_cs, PinName lcd_rs, PinName lcd_wr, PinName lcd_rd, unsigned short ScreenSize_X, unsigned short ScreenSize_Y);

    void pixel(unsigned int x, unsigned int y, unsigned short color);

    void hline(unsigned int x1, unsigned int x2,  unsigned int y, unsigned short color);
    void vline(unsigned int x, unsigned int y1, unsigned int y2, unsigned short color);
    void segment(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, unsigned short color);

    void rect(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, unsigned short color);
    void fillrect(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, unsigned short color);
    
    void circle(unsigned int x0, unsigned int y0, unsigned int r, unsigned short color);
    void fillcircle(unsigned int x0, unsigned int y0, unsigned int r, unsigned short color);

private:
  
    unsigned short xSize;
    unsigned short ySize;

};

#endif