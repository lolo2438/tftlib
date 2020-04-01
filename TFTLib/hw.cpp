#include "hw.h"

hw::hw(PinName *lcd_data, PinName lcd_rst, PinName lcd_cs, PinName lcd_rs, PinName lcd_wr, PinName lcd_rd)
    : dbus(lcd_data[0],lcd_data[1],lcd_data[2],lcd_data[3],lcd_data[4],lcd_data[5],lcd_data[6],lcd_data[7]),
      rst(lcd_rst), cs(lcd_cs), rs(lcd_rs), wr(lcd_wr), rd(lcd_rd)
{

    dbus.mode(PullNone);
    dbus.output();

    rs = 1;
    wr = 1;
    rd = 1;
    
    cs = 0; // Select lcd
    
    // Reset
    rst = 0;
    wait_us(50000);
    rst = 1;
    wait_us(50000);
}

void hw::wr_cmd8(unsigned char cmd){

    rs = 0;

    dbus.write(cmd);
    
    wr = 0;
    wr = 1;
    
    rs = 1;
}  
    
void hw::wr_data8(unsigned char data){
   
    dbus.write(data); 
    wr = 0;
    wr = 1;

}

void hw::wr_data16(unsigned short data){

    dbus.write(((data >> 8) & 0xFF)); 
    wr = 0;
    wr = 1;

    dbus.write((data & 0xFF)); 
    wr = 0;
    wr = 1;

}

void hw::wr_data32(unsigned int data){
    
    dbus.write(((data >> 24) & 0xFF)); 
    wr = 0;
    wr = 1;

    dbus.write(((data >> 16) & 0xFF)); 
    wr = 0;
    wr = 1;

    dbus.write(((data >> 8) & 0xFF)); 
    wr = 0;
    wr = 1;

    dbus.write((data & 0xFF)); 
    wr = 0;
    wr = 1;
}

void hw::wr_gram(unsigned short color, unsigned int count){

    rs = 0;

    dbus.write(0x2C);
    
    wr = 0;
    wr = 1;
    
    rs = 1;

    while(count){

        dbus.write(((color >> 8) & 0xFF)); 
        wr = 0;
        wr = 1;

        dbus.write((color & 0xFF)); 
        wr = 0;
        wr = 1;

        count -= 1;
    }
}

void hw::wr_grambuf(unsigned short *colorbuf, unsigned int count){

    while(count){

        dbus.write((((*colorbuf) >> 8) & 0xFF)); 
        wr = 0;
        wr = 1;

        dbus.write(((*colorbuf) & 0xFF)); 
        wr = 0;
        wr = 1;

        colorbuf += 1;
        count -= 1;
    }
}


unsigned char hw::rd_data8(void){
    
    dbus.input();

    unsigned char data = 0;

    rd = 0;
    rd = 1;
    dbus.read(); //dummy
    
    rd = 0;
    rd = 1;

    data = dbus.read();
    
    dbus.output();

    return data;
}

unsigned short hw::rd_data16(void){

    dbus.input();

    unsigned short data = 0;
    
    rd = 0;
    rd = 1;
    dbus.read(); //dummy
    
    rd = 0;
    rd = 1;
    data |= ((dbus.read() & 0xFF) << 8);

    rd = 0;
    rd = 1;
    data |= (dbus.read() & 0xFF);

    dbus.output();

    return data;
}

unsigned int hw::rd_data32(void){

    dbus.input();

    unsigned int data = 0;
    
    rd = 0;
    rd = 1;
    dbus.read(); //dummy
    
    rd = 0;
    rd = 1;
    data |= ((dbus.read() & 0xFF) << 24);

    rd = 0;
    rd = 1;
    data |= ((dbus.read() & 0xFF) << 16);

    rd = 0;
    rd = 1;
    data |= ((dbus.read() & 0xFF) << 8);

    rd = 0;
    rd = 1;
    data |= (dbus.read() & 0xFF);

    dbus.output();

    return data;
}

void hw::rd_gram(unsigned short *colorbuf, unsigned int count){

    rs = 0;

    dbus.write(0x2E);
    
    wr = 0;
    wr = 1;
    
    rs = 1;

    dbus.input();

    rd = 0;
    rd = 1;
    dbus.read(); //dummy

    while(count){

        *colorbuf = 0;
        
        rd = 0;
        rd = 1;
        *colorbuf |= ((dbus.read() & 0xFF) << 8);
        
        rd = 0;
        rd = 1;
        *colorbuf |= (dbus.read() & 0xFF); 

        colorbuf += 1;
        count -= 1;
    }

    dbus.output();
}