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
#include <stdio.h>
#include <string.h>
#define len 8

void executeCommand(char *command);
void sendString(const char *str);


/*takes the received string as argument and check its value and sets the LED state accordingly*/
void executeCommand(char *command)
{
    if(strcmp(command, "1") == 0)
    {
        IO_PC6_SetLow();
//        sendString("OK, LED ON.\r\n");
    }
    else if (strcmp(command, "0") == 0)
    {
        IO_PC6_SetHigh();
//        sendString("OK, LED OFF.\r\n");
    } 
    else 
    {
        sendString("Type ON/OFF to control the LED.\r\n");
    }
}

/*sends a string of character to USART*/
void sendString(const char *str)
{
    for(size_t i = 0; i < strlen(str); i++)
    {
        USART1_Write(str[i]);
    }
}

/*command-- continously read character from UART and stores them in the command array
 reads character from USART  using usart_read() 
 */
void main(void)
{
    char command[len];
/**index variable is used to keep track of next position in the command array where character is stored*/
    uint8_t index = 0;
    uint8_t c;
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();

    /* Replace with your application code */
    sendString("Type ON/OFF to control the LED.\r\n");
    
    while (1){
        c = USART1_Read();
/**if character is not \n,\r, it is added to character array called command using command[index++]=c
 Here \n is line feed 0xOA and \r is carriage return 0xOD
 */
        if(c != '\n' && c != '\r')
        {
            command[index++] = c;
            if(index > len)
            {
                index = 0;
            }
        }  
        if(c == '\n')
        {
            command[index] = '\0';
            index = 0;
            executeCommand(command);
        }          
    }
}
