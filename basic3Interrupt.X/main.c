/*
 * File:   main.c
 * Author: WHITELION
 *
 * Created on February 9, 2023, 2:50 PM
 */


#include <xc.h>
#include <avr/xmega.h>

void MainClkCtrl(void);
void main(void) {
    
    while(1)    {
        
    }
    
    return;
}

void MainClkCtrl(void)  {
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLA, CLKCTRL_CLKCTRL_OSC2OM_GC | CLKCTRL_CLKOUT_bm);
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLA, CLKCTRL_PDIV_6X_gc | CLKCTRL_PEN_bm);
}
