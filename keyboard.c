#include <MKL25Z4.H>
#include "keyboard.h"
#include "LED.h"

void Delay(uint32_t nCount)
{
    while(nCount--)
    {
    }
}

/* Pin initialization for the keyboard */
void init(void) {
    /* Enable clock for Port D and A */
    SIM->SCGC5 |= (1UL << 9) | (1UL << 10);

    /* Select GPIO and enable pull-up resistors and interrupts on falling edges for pins connected to columns */
    // Configuring pins connected to columns on the keyboard
    PORTA->PCR[1] = (1UL << 8); /* Pin PTA1 is GPIO */
    PORTA->PCR[2] = (1UL << 8); /* Pin PTA2 is GPIO */
    PORTA->PCR[4] = (1UL << 8); /* Pin PTA4 is GPIO */
    PORTA->PCR[5] = (1UL << 8); /* Pin PTA5 is GPIO */
    PORTD->PCR[0] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
    PORTD->PCR[2] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
    PORTD->PCR[5] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);

    /* Pins for RGB LEDs initialization */
    // Add code here if needed

    /* Set relevant port D pins to inputs */
    // Set pins connected to rows on the keyboard as inputs
    FPTD->PDDR &= ~MASK(2) | ~MASK(0)| ~MASK(5);

    /* Set relevant port A pins to outputs */
    // Set pins connected to digit selection on the 7-segment display as outputs
    FPTA->PDDR |= MASK(1) | MASK(2) | MASK(4)| MASK(5) ;
    FPTA->PCOR |= MASK(1) | MASK(2) | MASK(4)| MASK(5) ; // Clearing outputs initially

    /* Enable Interrupts */
    // Set the priority and enable interrupts for PORTD
    NVIC_SetPriority(PORTD_IRQn, 128); // 0, 64, 128, or 192
    NVIC_ClearPendingIRQ(PORTD_IRQn); 
    NVIC_EnableIRQ(PORTD_IRQn);
}

void PORTD_IRQHandler(void) {  
    // Clear pending interrupts
    LED_Clear();

    if ((PORTD->ISFR & MASK(0)) == MASK(0)){
        // If interrupt triggered by key in column 1
        FPTA->PDDR &= ~(MASK(1) | MASK(2) | MASK(4) | MASK(5)) ; // Set relevant pins as inputs
        if ((PTA->PDIR & MASK(5)) == MASK(5)){
            LED_Display(2,1); // Display '2' on the 7-segment display
        }
        else if ((PTA->PDIR & MASK(4)) == MASK(4)){
            LED_Display(5,1); // Display '5' on the 7-segment display
        } 
        else if ((PTA->PDIR & MASK(2)) == MASK(2)){
            LED_Display(8,1); // Display '8' on the 7-segment display
        } 
        else if ((PTA->PDIR & MASK(1)) == MASK(1)){
            LED_Display(0,1); // Display '0' on the 7-segment display   
        } 
        else {
            return;
        }
    }
    else if ((PORTD->ISFR & MASK(2)) == MASK(2)){
        // If interrupt triggered by key in column 2
        FPTA->PDDR &= ~(MASK(1) | MASK(2) | MASK(4) | MASK(5)) ; // Set relevant pins as inputs
        if ((PTA->PDIR & MASK(5)) == MASK(5)){
            LED_Display(3,1); // Display '3' on the 7-segment display
        }
        else if ((PTA->PDIR & MASK(4)) == MASK(4)){
            LED_Display(6,1); // Display '6' on the 7-segment display
        } 
        else if ((PTA->PDIR & MASK(2)) == MASK(2)){
            LED_Display(9,1); // Display '9' on the 7-segment display
        } 
        else if ((PTA->PDIR & MASK(1)) == MASK(1)){
            LED_Display(hash,1); // Display '#' on the 7-segment display
        } 
        else {
            return;
        }
    } 
    else if ((PORTD->ISFR & MASK(5)) == MASK(5)){
        // If interrupt triggered by key in column 3
        FPTA->PDDR &= ~(MASK(1) | MASK(2) | MASK(4) | MASK(5)) ; // Set relevant pins as inputs
        if ((PTA->PDIR & MASK(5)) == MASK(5)){
            LED_Display(1,1); // Display '1' on the 7-segment display
        }
        else if ((PTA->PDIR & MASK(4)) == MASK(4)){
            LED_Display(4,1); // Display '4' on the 7-segment display
        } 
        else if ((PTA->PDIR & MASK(2)) == MASK(2)){
            LED_Display(7,1); // Display '7' on the 7-segment display
        } 
        else if ((PTA->PDIR & MASK(1)) == MASK(1)){
            LED_Display(asterisk,1); // Display '*' on the 7-segment display
        } 
        else {
            return;
        }
    }
    else {
        LED_Clear();
    }
    
    FPTA->PDDR |= MASK(1) | MASK(2) | MASK(4)| MASK(5) ; // Set pins back as outputs
    NVIC_ClearPendingIRQ(PORTD_IRQn);
    
    // Clear status flags 
    PORTD->ISFR = 0xffffffff;
}
