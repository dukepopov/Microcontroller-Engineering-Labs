// traffic light
#include <MKL25Z4.H>
const uint32_t led_mask[] = {1UL << 18, 1UL << 19, 1UL << 1};
// LED #0, #1 are port B, LED #2 is port D
void LED_Config(void);
void LED_Set(void);
void LED_Clear(void);
__INLINE static void LED_On (uint32_t led);
__INLINE static void LED_Off (uint32_t led);
void Delay(uint32_t nCount);

int main(void)
{
	int8_t i;
	SystemCoreClockUpdate(); // Optional- Setup SystemCoreClock variable
// Configure LED outputs
	LED_Config();
	#define LOOP_COUNT 0x200000
	#define LOOP_COUNT1 0x400000
	while(1){
		// your code here
		Delay(LOOP_COUNT);
		LED_On(1);
		Delay(3 * LOOP_COUNT1);
		LED_Off(1);
		
		int i; 
		for (i=0; i<=4; i++) {
				Delay(LOOP_COUNT);
				LED_Set();
				Delay(LOOP_COUNT);
				LED_Clear();
		}
		
		Delay(LOOP_COUNT);
		LED_On(0);
		Delay(3 * LOOP_COUNT1);
		LED_Off(0);
		
		Delay(LOOP_COUNT);
		LED_Set();
		Delay(2 * LOOP_COUNT1);
		LED_Clear();
	
		
		

	};
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
		SIM->SCGC5 |= (1UL << 10) | (1UL << 12); /* Enable Clock to Port B & D */
		PORTB->PCR[18] = (1UL << 8); /* Pin PTB18 is GPIO */
		PORTB->PCR[19] = (1UL << 8); /* Pin PTB19 is GPIO */
		PORTD->PCR[1] = (1UL << 8); /* Pin PTD1 is GPIO */
		FPTB->PDOR = (led_mask[0] | led_mask[1] ); /* switch Red/Green LED off */
		FPTB->PDDR = (led_mask[0] | led_mask[1] ); /* enable PTB18/19 as Output */
		FPTD->PDOR = led_mask[2]; /* switch Blue LED off */
		FPTD->PDDR = led_mask[2]; /* enable PTD1 as Output */
		return;

	return;
}

/*---------------------------------------------------------------------------
Switch on all LEDs
*---------------------------------------------------------------------------*/
void LED_Set(void)
{
	LED_On(0);	// RED
	LED_On(1);	// GREEN
	
	return;
}

/*---------------------------------------------------------------------------
Switch off all LEDs
*---------------------------------------------------------------------------*/
void LED_Clear(void)
{
	LED_Off(0);
	LED_Off(1);
	
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
