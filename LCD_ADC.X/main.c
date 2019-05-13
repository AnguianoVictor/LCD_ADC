/*
 * File:   main.c
 * Author: Victor Manuel Ramírez Anguiano
 * Descripcion: Este programa lee 4 entradas analogicas y las muestra en una pantalla LCD 16x2
 * Created on 8 de mayo de 2019, 07:24 PM
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


#include <xc.h>
#include <stdio.h>
#include "lcd.h"
#include "msecbase.h"
#include "pause.h"

float read;
unsigned char buffer[20];

void main(void) {
    //Activacion de puertos analogicos RA5,RE0,RE1,RE2
    ANSEL = 0xF0;
    ANSELH = 0x00;
    ADCON1 = 0b10000000;
    
    TRISA = 0b00000000;
    TRISB = 0b00000100;
    TRISE = 0b00000111;
    
    lcd_init();		
    lcd_clear();	
    
    while(1)
    {
        ADCON0 = 0b00100001;			// Sample Time
        GO_DONE = 1;				// Start A/D conversion on AN0
        pause(1);
        while(GO_DONE == 1); 	// Wait for conversion to complete
        read = (ADRESH << 8)|ADRESL;
        read = (read*5.0)/1023;
        lcd_goto(0x80);             //0x80 INICIO + 0x00 CURSOR
        sprintf(buffer,"V1=%.3f",read);
        lcd_puts(buffer);
        pause(50);	

        ADCON0 = 0b00010101;	
        GO_DONE = 1;				// Start A/D conversion on AN0
        pause(1);
        while(GO_DONE == 1); 	// Wait for conversion to complete
        read = (ADRESH << 8)|ADRESL;
        read = (read*5.0)/1023;
        lcd_goto(0x89);                 //0x80 INICIO + 0x09 CURSOR
        sprintf(buffer,"V2=%.3f",read);
        lcd_puts(buffer);
        pause(50);	
        
        ADCON0 = 0b00011001;	
        GO_DONE = 1;				// Start A/D conversion on AN0
        pause(1);
        while(GO_DONE == 1); 	// Wait for conversion to complete
        read = (ADRESH << 8)|ADRESL;
        read = (read*5.0)/1023;
        lcd_goto(0xC0);             //0xC0 INICIO + 0x00 CURSOR
        sprintf(buffer,"V3=%.3f",read);
        lcd_puts(buffer);
        pause(50);
        
        ADCON0 = 0b00011101;
        GO_DONE = 1;				// Start A/D conversion on AN0
        pause(1);
        while(GO_DONE == 1); 	// Wait for conversion to complete
        read = (ADRESH << 8)|ADRESL;
        read = (read*5.0)/1023;
        lcd_goto(0xC9);             //0xC0 INICIO + 0x0 CURSOR
        sprintf(buffer,"V4=%.3f",read);
        lcd_puts(buffer);
        pause(50);
    }
    return;
}