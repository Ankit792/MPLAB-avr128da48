/*
 * File:   main.c
 * Author: WHITELION
 *
 * Created on February 8, 2023, 4:42 PM
 */


#include <xc.h>
//#include <avr/ioavr128da48.h>

void main(void) {
    uint16_t counter = 0;
    
    PORTC.DIR = PIN6_bm;     // BM IS bitmask, using direction register to select pin
    
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;    // 21.5 -- waveform generation mode WGMODE
    TCA0.SINGLE.PER = 3333;                        // SET PERIOd REGISTER
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;      // OVERFLOW BM
    TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm;     // START TIMER WITH WNABLW BIT IN CTRLA REGISTER
    
    // using polling method
    
    while(1)
    {
        if(TCA0.SINGLE.INTFLAGS & TCA_SINGLE_OVF_bm)    {
            TCA0.SINGLE.INTFLAGS |= TCA_SINGLE_OVF_bm;   // to reset the ovf flag once it is overflowed so to write 1 to thos bit
            counter++;
        }
        if (counter >=1000)   {
            PORTC.OUTTGL = PIN6_bm;
            counter++;
        }
    }
    return;
}
