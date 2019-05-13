/*
 *	LCD interface example
 *	Uses routines from delay.c
 *	This code will interface to a standard LCD controller
 *	like the Hitachi HD44780. It uses it in 4 bit mode, with
 *	the hardware connected as follows (the standard 14 pin 
 *	LCD connector is used):
 *	
 *	PORTC bits 0-3 are connected to the LCD data bits 4-7 (high nibble)
 *	PORTA bit 2 is connected to LCD RS input (register select)
 *  RW input (read/write) connected to ground
 *	PORTA bit 1 is connected to the LCD EN bit (enable)
 *	
 *	
 */
#define _LEGACY_HEADERS //Added for compiler versions 9.81+
#include	<htc.h>
#include	"lcd.h"

void pause( unsigned short usvalue );		//Establish pause routine function

#define	LCD_RS RA2
#define	LCD_RW RA4
#define LCD_EN RA1

#define LCD_DATA	PORTC

#define	LCD_STROBE()	((LCD_EN = 1),(LCD_EN=0))

/* write a byte to the LCD in 4 bit mode */

void
lcd_write(unsigned char c)
{
	pause (1);
	LCD_DATA = ( ( c >> 4 ) & 0x0F );
	LCD_STROBE();
	LCD_DATA = ( c & 0x0F );
	LCD_STROBE();
	
}

/*
 * 	Clear and home the LCD
 */

void
lcd_clear(void)
{
	LCD_RS = 0;
	lcd_write(0x1);
	pause (2);
}

/* write a string of chars to the LCD */

void
lcd_puts(const char * s)
{
	LCD_RS = 1;	// write characters
	while(*s)
		lcd_write(*s++);
}

/* write one character to the LCD */

void
lcd_putch(char c)
{
	LCD_RS = 1;	// write characters
	lcd_write( c );
}


/*
 * Go to the specified position
 */

void
lcd_goto(unsigned char pos)
{
	LCD_RS = 0;
	lcd_write(pos);
}
	
/* initialize the LCD - put into 4 bit mode */
void
lcd_init()
{
	char init_value;

	//ANSEL = 0;			// Disable analog pins on PORTA
	
	init_value = 0x3;
	TRISA=0;
	TRISC=0;
	LCD_RS = 0;
	LCD_EN = 0;
	LCD_RW = 0;
	
	pause (15);				// wait 15mSec after power applied,
	LCD_DATA	 = init_value;
	LCD_STROBE();
	pause(10);
	LCD_STROBE();
	pause(10);
	LCD_STROBE();
	pause(10);
	LCD_DATA = 2;	// Four bit mode
	LCD_STROBE();
	
	lcd_write(0x28); // Set interface length
//	lcd_write(0xC); // Display On, Cursor Off, Blink Off
	lcd_write(0xF); // Display On, Cursor On, Cursor Blink
	lcd_clear();	// Clear screen
	lcd_write(0x6); // Set entry Mode
}
