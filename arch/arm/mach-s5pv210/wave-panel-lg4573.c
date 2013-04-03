/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/lg4573.h>
#include <mach/gpio.h>
#include <mach/gpio-wave.h>
#include <linux/delay.h>

const unsigned short LG4573_SEQ_SETTING_TYPE_3[] = {
// 20111230
	0xC1,	 // Stand-by off
	0x100,

	0x11,   // Exit Sleep Mode

	0x36,
	0x100,

	0x3A,  
	0x170,  //24 bit interface

	0xB1,  //RGB interface setting
	0x110,  //VSYNC+HSYNC Rising edge HSYNC - active high VSYNC-active high DE-active high
	0x111,  // HBP -- 11, 10, 11, 13, 18, 1A, 14 Inc : L, Dec : R
	0x102,  // VBP -  3, 5, 7, 1C, 10, 0C  Inc : U, Dec : D


	0xB2,
	0x110,  //HYDYS panel, 480pexel
	0x1C8,  //800 pixels

	0xB3,
	0x100, // 0x01 : 1-Dot Inversion, 0x00 : Column Inversion

	0xB4,
	0x104,

	0xB5,
	0x105, // 5, 10, FF
	0x110,
	0x110,
	0x100,
	0x100,

	0xB6,
	0x101,  // overlaping
	0x101,
	0x102,
	0x140,
	0x102,
	0x100,

//Power controll
	0xC0,
	0x100,
	0x11F,

	0xC2,
	0x100,

	0xC3,	//Second Version LG4573
	0x103,
	0x104,
	0x105,	//0x103,	
	0x106,	//0x103,
	0x101,	//0x103,

	0xC4,
	0x102,
	0x123,
	0x116,	//0x10E,
	0x116,	//0x10E,
	0x102,
	0x17A,

	0xC5,
	0x177,	//0x174,

	0xC6,
	0x124,
	0x160,
	0x100,

//Gamma controll
	0xD0,  	// Gama Set_1
	0x100,	//0x142,
	0x101,	//0x113,
	0x166,	//0x141,
	0x126,	//0x116,
	0x100,	//0x107,
	0x100,	//0x103,
	0x166,	//0x161,
	0x131,	//0x116,
	0x103,	//0x103,

	0xD1,  // Gama Set_2
	0x100,	//0x142,
	0x101,	//0x113,
	0x166,	//0x141,
	0x126,	//0x116,
	0x100,	//0x107,
	0x100,	//0x103,
	0x166,	//0x161,
	0x131,	//0x116,
	0x103,	//0x103,

	0xD2,  // Gama Set_1
	0x100,	//0x142,
	0x101,	//0x113,
	0x166,	//0x141,
	0x126,	//0x116,
	0x100,	//0x107,
	0x100,	//0x103,
	0x166,	//0x161,
	0x131,	//0x116,
	0x103,	//0x103,

	0xD3,  // Gama Set_2
	0x100,	//0x142,
	0x101,	//0x113,
	0x166,	//0x141,
	0x126,	//0x116,
	0x100,	//0x107,
	0x100,	//0x103,
	0x166,	//0x161,
	0x131,	//0x116,
	0x103,	//0x103,

	0xD4,  // Gama Set_1
	0x100,	//0x142,
	0x101,	//0x113,
	0x166,	//0x141,
	0x126,	//0x116,
	0x100,	//0x107,
	0x100,	//0x103,
	0x166,	//0x161,
	0x131,	//0x116,
	0x103,	//0x103,

	0xD5,  // Gama Set_2
	0x100,	//0x142,
	0x101,	//0x113,
	0x166,	//0x141,
	0x126,	//0x116,
	0x100,	//0x107,
	0x100,	//0x103,
	0x166,	//0x161,
	0x131,	//0x116,
	0x103,	//0x103,
	
//	SLEEPMSEC, 100,

//	0x029, //Disp ON

       	ENDDEF, 0x0000 
};

const unsigned short LG4573_SEQ_SETTING_TYPE_0[] = {
// 20111230
	0x01,	 // sw reset
	SLEEPMSEC, 120,
	0xC1,	 // Stand-by off
	0x100,

	0x11,   // Exit Sleep Mode

	0x36,
	0x100,

	0x3A,  
	0x170,  //24 bit interface

	0xB1,  //RGB interface setting
	0x110,  //VSYNC+HSYNC Rising edge HSYNC - active high VSYNC-active high DE-active high
	0x111,  // HBP -- 11, 10, 11, 13, 18, 1A, 14 Inc : L, Dec : R
	0x102,  // VBP -  3, 5, 7, 1C, 10, 0C  Inc : U, Dec : D


	0xB2,
	0x110,  //HYDYS panel, 480pexel
	0x1C8,  //800 pixels

	0xB3,
	0x100, // 0x01 : 1-Dot Inversion, 0x00 : Column Inversion

	0xB4,
	0x104,

	0xB5,
	0x105, // 5, 10, FF
	0x110,
	0x110,
	0x100,
	0x100,

	0xB6,
	0x101,  // overlaping
	0x101,
	0x102,
	0x140,
	0x102,
	0x100,

//Power controll
	0xC0,
	0x100,
	0x11F,

	0xC2,
	0x100,

	0xC3,	
	0x103,
	0x104,
	0x103,	
	0x103,
	0x103,

	0xC4,
	0x102,
	0x123,
	0x10E,
	0x10E,
	0x102,
	0x17A,

	0xC5,
	0x174,

	0xC6,
	0x124,
	0x160,
	0x100,

//Gamma controll
	0xD0,  	// Gama Set_1
	0x142,
	0x113,
	0x141,
	0x116,
	0x107,
	0x103,
	0x161,
	0x116,
	0x103,

	0xD1,  	// Gama Set_1
	0x142,
	0x113,
	0x141,
	0x116,
	0x107,
	0x103,
	0x161,
	0x116,
	0x103,

	0xD2,  	// Gama Set_1
	0x142,
	0x113,
	0x141,
	0x116,
	0x107,
	0x103,
	0x161,
	0x116,
	0x103,

	0xD3,  	// Gama Set_1
	0x142,
	0x113,
	0x141,
	0x116,
	0x107,
	0x103,
	0x161,
	0x116,
	0x103,

	0xD4,  	// Gama Set_1
	0x142,
	0x113,
	0x141,
	0x116,
	0x107,
	0x103,
	0x161,
	0x116,
	0x103,

	0xD5,  	// Gama Set_1
	0x142,
	0x113,
	0x141,
	0x116,
	0x107,
	0x103,
	0x161,
	0x116,
	0x103,
            	
	SLEEPMSEC, 100,

	0x029, //Disp ON
	
	ENDDEF, 0x0000 
};


const unsigned short LG4573_SEQ_SLEEP_OFF[] = {
	0x11, 
	SLEEPMSEC, 200,
	0x29,
	SLEEPMSEC, 200,
	ENDDEF, 0x0000
};

const unsigned short LG4573_SEQ_SLEEP_ON[] = {
	0x10,            
	SLEEPMSEC, 200,
	0x28, 
	SLEEPMSEC, 200,
	ENDDEF, 0x0000
};

int get_lcdtype(void)
{
	int panel_id;

	panel_id = (gpio_get_value(GPIO_DIC_ID) << 1) | gpio_get_value(GPIO_OLED_ID);

	return panel_id;
}

struct s5p_lg4573_panel_data wave_lg4573_panel_data = {
	.seq_settings_type0 = LG4573_SEQ_SETTING_TYPE_0,
	/* TODO fix type1 and type2 tables */
	.seq_settings_type1 = LG4573_SEQ_SETTING_TYPE_0,
	.seq_settings_type2 = LG4573_SEQ_SETTING_TYPE_0,
	.seq_settings_type3 = LG4573_SEQ_SETTING_TYPE_3,
	.seq_standby_on = LG4573_SEQ_SLEEP_ON,
	.seq_standby_off = LG4573_SEQ_SLEEP_OFF,
	
	.get_lcdtype = &get_lcdtype,
};