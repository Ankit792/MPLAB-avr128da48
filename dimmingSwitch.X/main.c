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

/*
    Main application
*/
bool inc_dec_flag = true;
uint8_t switchCount=0;
uint16_t dutyCycle = 100;

int main(void)
{

    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    
    TCA1.SINGLE.PER = 100;                //TCA1.SINGLE.CMP2 = 0xfff;
    /* Replace with your application code */
    while (1){
        if (switch_GetValue() == 0) {                   // 0: Pressed
            _delay_ms(200);
            switchCount = (switchCount + 1);
                
            if(inc_dec_flag == true)
                dutyCycle = dutyCycle-10 ;
            if(inc_dec_flag == false)
                dutyCycle = dutyCycle+10 ;
            if(dutyCycle <= 0)
                inc_dec_flag = false;
            if(dutyCycle >= 100)
                inc_dec_flag = true;
            TCA1.SINGLE.CMP2 = dutyCycle;
        }
    }     
}
/**
    End of File
*/