/*
 * main.cpp
 *
 *  Created on: 29-Oct-2014
 *      Author: Dhanish Vijayan
 *      Company: Elementz Engineers Guild Pvt Ltd
 *      Edited by : Moatasem Elsayed on 5/19
 */


//#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "main.h"
#include "ssd1306.h"
#include "com_def.h"
#include "bitmaps.h"


int main(void){
	_delay_ms(1000);
	DDRD=0xff;
	PORTD=0xff;
/* Initialize OLED Display */
	init_OLED();
	reset_display();

	while(1){

//		/*Draw image on Screen*/
		for(int i=0;i<sizeof(image_data_test);i++)     // show 128* 64 Logo
					SendChar(pgm_read_byte(image_data_test+i));
//		sendStrXY_test("Welcome",0,15,3);
//		sendcommand(0x2f);  /*Scroll on*/
		_delay_ms(4000);
//		sendcommand(0x2e);  /*Scroll off*/
//
//
		clear_display();

/* Draw text from font */
		sendStrXY("Moatasem",0,0);
		sendStrXY("Elsayed",2,0);
		sendStrXY("Pnjunction",4,0);
		sendStrXY("Welcome",6,0);

		_delay_ms(8000);
		clear_display();
	}
return 0;
}

