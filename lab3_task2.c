// INPUT CONTROLLED LEDs
#include <MKL25Z4.H>
const uint32_t led_mask[] = {1UL << 18, 1UL << 19, 1UL << 1};
// LED #0, #1 are port B, LED #2 is port D
void LED_Config(void);
void LED_Set(void);
void LED_Clear(void);
__INLINE static void LED_On (uint32_t led);
__INLINE static void LED_Off (uint32_t led);
void Delay(uint32_t nCount);

#define MASK(x) (1UL << (x))

int main(void)
{
	SystemCoreClockUpdate(); // Optional- Setup SystemCoreClock variable
// Configure LED outputs
	LED_Config();
	#define LOOP_COUNT 0x400000
	while(1){
		// your code here
		if ((PTD->PDIR & MASK(0)) == MASK(0)){
		// switch is not pressed, then light LED 2
		LED_Clear();
		LED_On(1);
		} else {
		// switch is pressed, so light LED 1
		LED_Clear();
		}


	}
}

void Delay(uint32_t nCount)
{
	while(nCount--)
	{
	}
}

/*----------------------------------------------------------------------------
LED pin config
*----------------------------------------------------------------------------*/

void LED_Config(void)
{
	/* Enable Clock to Port B & D */
	// your code here

	/* configure Pin PTB18, PTB19 and PTD1 as GPIO */
	// your code here
		SIM->SCGC5 |= (1UL << 10) | (1UL << 12); /* Enable Clock to Port B & D */
	
	
		PORTB->PCR[18] = (1UL << 8); /* Pin PTB18 is GPIO */
		PORTB->PCR[19] = (1UL << 8); /* Pin PTB19 is GPIO */
		PORTD->PCR[1] = (1UL << 8); /* Pin PTD1 is GPIO */
	/* configure Pin PTD0, PTD2 and PTD5 as GPIO, enable pull-up resistor  */
	// your code here

		PORTD->PCR[0] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;
		PORTD->PCR[2] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;
		PORTD->PCR[5] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;
	
	/* enable PTB18/19 as Output */
	// your code here
		FPTB->PDDR = (led_mask[0] | led_mask[1] ); /* enable PTB18/19 as Output */

	/* enable PTD1 as Output */
	// your code here
		FPTD->PDDR = led_mask[2]; /* enable PTD1 as Output */
	/* enable PTD0,2,5 as Input */
	// your code here
	
	/* clear all outputs */
		
	// your code here

	return;
}

/*---------------------------------------------------------------------------
Switch on LEDs
*---------------------------------------------------------------------------*/
void LED_Set(void)
{
	LED_On(0);	// RED
	LED_On(1);	// GREEN
	LED_On(2);	// BLUE
	return;
}

/*---------------------------------------------------------------------------
Switch off LEDs
*---------------------------------------------------------------------------*/
void LED_Clear(void)
{
	LED_Off(0);
	LED_Off(1);
	LED_Off(2);
	return;
}

/*---------------------------------------------------------------------------
Switch on LED (just one)
*---------------------------------------------------------------------------*/
__INLINE static void LED_On (uint32_t led) {
if (led == 2) FPTD->PCOR = led_mask[led];
else FPTB->PCOR = led_mask[led];
}

/*---------------------------------------------------------------------------
Switch off LED (just one)
*---------------------------------------------------------------------------*/

__INLINE static void LED_Off (uint32_t led) {
if (led == 2) FPTD->PSOR = led_mask[led];
else FPTB->PSOR = led_mask[led];
}
