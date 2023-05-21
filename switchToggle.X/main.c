#include <avr/io.h>

int main (void)
{
    /* Configure SW0 as input */
    PORTC.DIRCLR = PIN7_bm;
    /* Configure LED0 pin as output */
    PORTC.DIRSET = PIN6_bm;
    /* Enable the internal pull-up for PC7 */
    PORTC.PIN7CTRL |= PORT_PULLUPEN_bm; 
    
    while (1)
    {
        /* Check the status of SW0 */
        /* 0: Pressed */
        if (!(PORTC.IN & (PIN7_bm)))
        {
            /* LED0 on */
            PORTC.OUTSET = PIN6_bm;
        }
        /* 1: Released */
        else
        {
            /* LED0 off */
            PORTC.OUTCLR = PIN6_bm;
        }
    }
}
