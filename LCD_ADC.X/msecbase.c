/********************************************************
* msecbase - 1 msec pause routine						*
* The Internal oscillator is set to 4 Mhz and the		*
* internal instruction clock is 1/4 of the oscillator.	*
* This makes the internal instruction clock 1 Mhz or	*
* 1 usec per clock pulse.								*
* Using the 1:4 prescaler on the clock input to Timer0	* 
* slows the Timer0 count increment to 1 count/4 usec.	*
* Therefore 250 counts of the Timer0 would make a one	*
* millisecond delay (250 * 4 usec). But there are other	*
* instructions in the delay loop so using the MPLAB 	*
* stopwatch we find that we need Timer0 to overflow at 	*
* 243 clock ticks. Preset Timer0 to 13 (0D hex) to make	*
* Timer0 overflow at 243 clock ticks (256-13 = 243).	*
* This results in a 1.001 millisecond delay which is 	*
* close enough.											*
*********************************************************/
//#define _LEGACY_HEADERS //Added for compiler versions 9.81+
#include <pic.h>		// Include HITECH CC header file
//#include <xc.h>


void msecbase(void)
{
	OPTION_REG = 0b00000001;		//Set prescaler to TMRO 1:4
	TMR0 = 0xD;					//Preset TMRO to overflow on 250 counts
	while(!T0IF);				//Stay until TMRO overflow flag equals 1
	T0IF = 0;					//Clear the TMR0 overflow flag
}
