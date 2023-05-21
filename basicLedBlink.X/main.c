/*
 * File:   main.c
 * Author: WHITELION
 *
 * Created on February 9, 2023, 11:18 AM
 */

#define F_CPU 4000000UL
#include <xc.h>
//#include <avr/ioavr128da48.h>
#include <util/delay.h>

void main(void) {
    
    PORTC_DIR = PIN6_bm;          //portc_dir is direction register
    
    while(1)
    {
     PORTC_OUTTGL = PIN6_bm;
     
     _delay_ms(1000);
    }
    
    return;
}
