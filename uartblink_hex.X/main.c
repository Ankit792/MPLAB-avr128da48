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

/**This code should work as expected, it's a simple program that reads characters from USART1, 
 * and once it receives a newline character '\n', it interprets the command contained in the buffer 
 * and executes it. The only supported commands are "0" and "1", and they control the state of the 
 * PC6 IO pin on the microcontroller. If any other characters are received, they will be ignored.*/

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <stdlib.h>

#define len 8

void executeCommand(char *command);

void executeCommand(char *command)
{
        if(command[1] == 0x01)
    {
        IO_PC6_SetLow();
    }
        else if (command[1] == 0x00)
    {
        IO_PC6_SetHigh();
    }
}

/*
    Main application
*/
 
int main(void)
{
    char command[len];
    uint8_t index = 0;    //integer index to keep track of the position in the command array
    uint8_t c;          //to store the characters read from the USART1 interface
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();

    while (1){
/*In each iteration, it reads a character from the USART1 interface 
 * by calling the USART1_Read function and stores it in the c variable.*/
    c = USART1_Read();
   
/*If the character is not a newline or a carriage return, the character is added
 *to the command array and the index variable is incremented. If the index is greater than 20, the index is reset to 0.*/
        
/*The first if statement checks if the character c is not a newline or a carriage 
 * return character. If this is true, the character c is added to the command array and the 
 * index is incremented. The if statement inside this block of code checks if the 
 * index has exceeded the length len of the command array, and if it has, it sets the index back to 0.
 */    
    if(c != '\n' && c != '\r')
        {
            command[index++] = c;
            if(index > len)
            {
                index = 0;
            }
        }  

/*The second if statement checks if the character c is a newline character. If this is true, 
 * the code adds a null terminator ('\0') to the end of the command array, resets the index to 0, and calls 
 * the executeCommand function with the command array as its argument. This function is likely 
 * responsible for processing the received command and performing some action based on its contents.
 */    
        if(c == '\n' )
        {
            command[index] = '\0';
            index = 0;
            executeCommand(command);
        }
    }
}
