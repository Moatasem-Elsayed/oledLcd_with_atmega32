/*
 * ssd1306.c
 *
 *  Created on: 05-May-2015
 *      Author: root
 *       *      Edited by : Moatasem Elsayed on 5/19
 */

#include<avr/io.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "ssd1306.h"
#include "i2c_dev.h"
#include "font.h"

void sendcommand(unsigned char com){
	i2c_write(0x80,com);
}

void SendChar(unsigned char data){
	i2c_write(0x40,data);
}



//==========================================================//
// Turns display on.
void displayOn(void)
{
	sendcommand(0xaf);        //display on
}

//==========================================================//
// Turns display off.
void displayOff(void)
{
	sendcommand(0xae);		//display off
}

//==========================================================//
// Set the cursor position in a 16 COL * 8 ROW map.
void setXY(unsigned char row,unsigned char col)
{
	sendcommand(0xb0+row);                //set page address
	sendcommand(0x00+(8*col&0x0f));       //set low col address //lower nibble
	sendcommand(0x10+((8*col>>4)&0x0f));  //set high col address//higher nibble
}


//==========================================================//
// Prints a string in coordinates X Y, being multiples of 8.
// This means we have 16 COLS (0-15) and 8 ROWS (0-7).
void sendStrXY( char *string, int X, int Y)
{
	setXY(X,Y);
	unsigned char i=0;
	while(*string)
	{
		for(i=0;i<8;i++)
		{
			SendChar(pgm_read_byte(myFont1[*string-0x20]+i));
		}
		*string++;
	}
}
void sendStrXY_test( char *string, int x, int yl,int yh)
{
	sendcommand(0xb0+x);                //set page address
	sendcommand(0x00+yl);       //set low col address //
	sendcommand(0x10+yh);  //set high col address
	unsigned char i=0;
	while(*string)
	{
		for(i=0;i<8;i++)
		{
			SendChar(pgm_read_byte(myFont1[*string-0x20]+i));
		}
		*string++;
	}
}


//==========================================================//
// Inits oled and draws logo at startup
void init_OLED(void)
{
	InitI2C();
	sendcommand(SSD1306_DISPLAYOFF);                    // 0xAE
	sendcommand(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
	sendcommand(0x80);                 // the suggested ratio 0x80
	sendcommand(SSD1306_SETMULTIPLEX);                  // 0xA8
	sendcommand(0x3F);
	sendcommand(SSD1306_SETDISPLAYOFFSET);              // 0xD3
	sendcommand(0x0);                                   // no offset
	sendcommand(SSD1306_SETSTARTLINE);// | 0x0);        // line #0
	sendcommand(SSD1306_CHARGEPUMP);                    // 0x8D
	sendcommand(0x14);  // using internal VCC
	sendcommand(SSD1306_MEMORYMODE);                    // 0x20
	sendcommand(0x00);          // 0x00 horizontal addressing
	sendcommand(SSD1306_SEGREMAP | 0x1); // rotate screen 180
	sendcommand(SSD1306_COMSCANDEC); // rotate screen 180
	sendcommand(SSD1306_SETCOMPINS);                    // 0xDA
	sendcommand(0x12);
	sendcommand(SSD1306_SETCONTRAST);                   // 0x81
	sendcommand(0xCF);
	sendcommand(SSD1306_SETPRECHARGE);                  // 0xd9
	sendcommand(0xF1);
	sendcommand(SSD1306_SETVCOMDETECT);                 // 0xDB
	sendcommand(0x40);
	sendcommand(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
	sendcommand(SSD1306_NORMALDISPLAY);                 // 0xA6
	sendcommand(SSD1306_DISPLAYON);                     //switch on OLED
}

//==========================================================//
// Clears the display by sendind 0 to all the screen map.
void clear_display(void)
{
	unsigned char i,k;
	for(k=0;k<8;k++)
	{
		setXY(k,0);
		{
			for(i=0;i<128;i++)     //clear all COL
			{
				SendChar(0);         //clear all COL
				//delay(10);
			}
		}
	}
}


//==========================================================//
// Resets display depending on the actual mode.
void reset_display(void)
{
	displayOff();
	clear_display();


	displayOn();
}

