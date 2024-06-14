#include <MKL25Z4.H>
#include "LED.h"

// Array to store masks for each segment of the 7-segment display
const uint32_t led_mask[] = {1UL << 0, 1UL << 6, 1UL << 12, 1UL << 16, 1UL << 17, 1UL << 3, 1UL << 11, 1UL << 13};    // 7 segment
// Array to store masks for digit selection lines
const uint32_t led_ctrl_mask[] = {1UL << 7, 1UL << 4, 1UL << 5, 1UL << 10};    // digit selection

/*----------------------------------------------------------------------------
LED pin configuration
*----------------------------------------------------------------------------*/
void LED_Clear(void);
void LED_Config(void)
{
    // Enable Clock to Port C
    SIM->SCGC5 |= (1UL << 11);

    // Configure Pin PTC0/3/4/5/6/7/10/11/12/13/16/17 as GPIO for 7-segment display
    PORTC->PCR[0] = (1UL << 8); /* Pin PTC0 is GPIO */
    PORTC->PCR[3] = (1UL << 8); /* Pin PTC3 is GPIO */
    PORTC->PCR[4] = (1UL << 8); /* Pin PTC4 is GPIO */
    PORTC->PCR[5] = (1UL << 8); /* Pin PTC5 is GPIO */
    PORTC->PCR[6] = (1UL << 8); /* Pin PTC6 is GPIO */
    PORTC->PCR[7] = (1UL << 8); /* Pin PTC7 is GPIO */
    PORTC->PCR[10] = (1UL << 8); /* Pin PTC10 is GPIO */
    PORTC->PCR[11] = (1UL << 8); /* Pin PTC11 is GPIO */
    PORTC->PCR[12] = (1UL << 8); /* Pin PTC12 is GPIO */
    PORTC->PCR[13] = (1UL << 8); /* Pin PTC13 is GPIO */
    PORTC->PCR[16] = (1UL << 8); /* Pin PTC16 is GPIO */
    PORTC->PCR[17] = (1UL << 8); /* Pin PTC17 is GPIO */

    // Enable Pin PTC0/3/4/5/6/7/10/11/12/13/16/17 as output for 7-segment display
    FPTC->PDDR |= (led_mask[0]); /* enable  as Output */
    FPTC->PDDR |= (led_mask[1]); /* enable  as Output */
    FPTC->PDDR |= (led_mask[2]); /* enable  as Output */
    FPTC->PDDR |= (led_mask[3]); /* enable  as Output */
    FPTC->PDDR |= (led_mask[4]); /* enable  as Output */
    FPTC->PDDR |= (led_mask[5]); /* enable  as Output */
    FPTC->PDDR |= (led_mask[6]); /* enable  as Output */
    FPTC->PDDR |= (led_mask[7]); /* enable  as Output */
    FPTC->PDDR |= (led_ctrl_mask[0]); /* enable  as Output */
    FPTC->PDDR |= (led_ctrl_mask[1]); /* enable  as Output */
    FPTC->PDDR |= (led_ctrl_mask[2]); /* enable  as Output */
    FPTC->PDDR |= (led_ctrl_mask[3]); /* enable  as Output */

    return;
}


/*---------------------------------------------------------------------------
Display number x in the yth digit. x=0-9, y=1-4
*---------------------------------------------------------------------------*/
void LED_Display(int8_t x, int8_t y)
{
    // Clear all LEDs and disable all digits
    LED_Clear();
    
    // Enable the selected digit
    switch(y) {
        case 1: FPTC->PCOR = led_ctrl_mask[0]; break;
        case 2: FPTC->PCOR = led_ctrl_mask[1]; break;
        case 3: FPTC->PCOR = led_ctrl_mask[2]; break;
        case 4: FPTC->PCOR = led_ctrl_mask[3]; break;
        default: break;
    }
    
    // Display the corresponding number or character on the selected digit
    switch(x){
        case 0: FPTC->PSOR = led_mask[0] | led_mask[1] | led_mask[2] | led_mask[3] | led_mask[4] | led_mask[5]; break;  // Display '0'
        case 1: FPTC->PSOR = led_mask[1] | led_mask[2]; break;  // Display '1'
        case 2: FPTC->PSOR = led_mask[3] | led_mask[4] | led_mask[0] | led_mask[1] | led_mask[6]; break;  // Display '2'
        case 3: FPTC->PSOR = led_mask[3] | led_mask[2] | led_mask[0] | led_mask[1] | led_mask[6]; break;  // Display '3'
        case 4: FPTC->PSOR = led_mask[1] | led_mask[2] | led_mask[6] | led_mask[5]; break;  // Display '4'
        case 5: FPTC->PSOR = led_mask[3] | led_mask[2] | led_mask[0] | led_mask[5] | led_mask[6]; break;  // Display '5'
        case 6: FPTC->PSOR = led_mask[3] | led_mask[2] | led_mask[0] | led_mask[5] | led_mask[6] | led_mask[4]; break;  // Display '6'
        case 7: FPTC->PSOR = led_mask[1] | led_mask[2] | led_mask[0]; break;  // Display '7'
        case 8: FPTC->PSOR = led_mask[0] | led_mask[1] | led_mask[2] | led_mask[3] | led_mask[4] | led_mask[5] | led_mask[6]; break;  // Display '8'
        case 9: FPTC->PSOR = led_mask[0] | led_mask[1] | led_mask[2] | led_mask[5] | led_mask[6]; break;  // Display '9'
        case hash: FPTC->PSOR = led_mask[3] | led_mask[4] | led_mask[5] | led_mask[6]; break;  // Display '#'
        case asterisk: FPTC->PSOR = led_mask[1] | led_mask[2] | led_mask[4] | led_mask[5] | led_mask[6]; break;  // Display '*'
        default: break;
    }
    
    return;
}

/*---------------------------------------------------------------------------
Switch off LEDs
*---------------------------------------------------------------------------*/
void LED_Clear(void)
{
    // Clear all LED segments and disable all digits
    FPTC->PCOR = (led_mask[0] | led_mask[1] | led_mask[2] | led_mask[3] | led_mask[4] | led_mask[5] | led_mask[6] | led_mask[7]);
    FPTC->PSOR = (led_ctrl_mask[0] | led_ctrl_mask[1] | led_ctrl_mask[2] | led_ctrl_mask[3]);
    
    return;
}
