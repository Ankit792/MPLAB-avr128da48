/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <util/delay.h>

#define switchReleas 1
#define switchPress 0

/*
    Main application
*/
bool inc_dec_flag = true;
uint8_t switchCount=0;
uint16_t dutyCycle = 100;

uint8_t switchState = switchReleas;          //initial state of switch 1
uint8_t switchPrevState = switchReleas;     //previous state of switch 1 changes state from release to pressed

int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    
    TCA1.SINGLE.PER = 100;                
    
    /* Replace with your application code */
    while (1){
        switchPrevState = switchState;
        if (switch_GetValue() == switchPress) {               //whether the switch is currently pressed:0
                switchState = switchPress;
            } else {
            switchState = switchReleas;
            }
        
        if (switchState == switchPress && switchPrevState == switchReleas) {    // Switch was just pressed
            switchCount = 0;
        }
        
        if (switchState == switchPress) {     // Switch is being held down
            switchCount++;
            if (switchCount >= 10) {          // Increment/decrement duty cycle every 10th press
                switchCount = 0;
                if(inc_dec_flag == true) {
                    dutyCycle -= 10;
                    if (dutyCycle <= 0) {
                        dutyCycle = 0;
                        inc_dec_flag = false;
                    }
                } else {
                    dutyCycle += 10;
                    if (dutyCycle >= 100) {
                        dutyCycle = 100;
                        inc_dec_flag = true;
                    }
                }
                TCA1.SINGLE.CMP2 = dutyCycle;
            }
        }
        _delay_ms(10);                      // Delay for 10 milliseconds to avoid CPU hogging
    }     
}
/**
    End of File
*/