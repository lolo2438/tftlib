#ifndef __LCD_H__
#define __LCD_H__

#include "hw.h"
#include "font.h"
#include "colors.h"

/*  Class: lcd
    inherits functions of hw

    Desc: Instantiate a lcd object with high level draw function
          to draw on the 3.5 inch lcd screen with the ILI9486 lcd driver.

    Spec: Color format is 16 bit RGB565
 */
class lcd : protected hw
{

public:
    lcd(PinName *lcd_data, PinName lcd_rst, PinName lcd_cs, PinName lcd_rs, PinName lcd_wr, PinName lcd_rd, unsigned short ScreenSize_X = 480, unsigned short ScreenSize_Y = 320);

    /* =============================================================== */
    /*  Function: lcd::pixel
        Desc: Draws a pixel at (x,y) of color color
     */
    void pixel(unsigned int x, unsigned int y, color_t color);

    /* =============================================================== */
     /* Function: lcd::hline
        Desc: Draws a horizontal line from (x1,y) to (x2,y) of color color
        Spec: Make sure x1 < x2
     */
    void hline(unsigned int x1, unsigned int x2,  unsigned int y, color_t color);

    /* Function: lcd::vline
        Desc: Draws a vertical line from (x,y1) to (x,y2) of color color
        Spec: Make sure y1 < y2
     */
    void vline(unsigned int x, unsigned int y1, unsigned int y2, color_t color);

    /* Function: lcd::segment
        Desc: Draws a segment from (x1,y1) to (x2,y2) of color color
     */
    void segment(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, color_t color);

    /* =============================================================== */
    /* Function: lcd::rect
        Desc: Draws a rectangle with (x1,y1), (x1,y2), (x2,y1), (x2,y2) as edge points
        Spec: Make sure x1 < x2 and y1 < y2
     */
    void rect(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, color_t color);

    /* Function: lcd::fillrect
        Desc: fills a rectangle with (x1,y1), (x1,y2), (x2,y1), (x2,y2) as edge points
        Spec: Make sure x1 < x2 and y1 < y2
     */
    void fillrect(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, color_t color);
    
    /* =============================================================== */
    /* Function: lcd::circle
        Desc: Draws a circle with (x0,y0) as center point and r as radius
     */
    void circle(unsigned int x0, unsigned int y0, unsigned int r, color_t color);

    /* Function: lcd::fillcircle
        Desc: fills a circle with (x0,y0) as center point and r as radius
     */
    void fillcircle(unsigned int x0, unsigned int y0, unsigned int r, color_t color);

    /* =============================================================== */

    void setfont(font dfont) { this->dfont = dfont; }

    void character(unsigned int x, unsigned int y, char c, color_t color);

    void string(unsigned int x, unsigned int y, const char *str, color_t color);

    void stringbuf(unsigned int x, unsigned int y, const char *str, const color_t *colorbuf);

    /* =============================================================== */
    
    unsigned int getXSize(void) { return xSize; };
    unsigned int getYSize(void) { return ySize; };

    void cls(void) { fillrect(0, getXSize(), 0,getYSize(), bgColor); }

    void setBgColor(unsigned short BgColor) { this->bgColor = BgColor; }

private:
  
    void window(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2);

    unsigned short xSize;
    unsigned short ySize;

    color_t bgColor;

    font dfont;
};

#endif