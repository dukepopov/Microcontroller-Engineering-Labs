// 7-segment, display only 1 digit
#include <MKL25Z4.H>
const uint32_t led_mask[] = {1UL << 0, 1UL << 6, 1UL << 12, 1UL << 16, 1UL << 17, 1UL << 3, 1UL << 11, 1UL << 13};	// 7 segment
const uint32_t led_ctrl_mask[] = {1UL << 7, 1UL << 4, 1UL << 5, 1UL << 10};	// digit selection

void LED_Config(void);
void LED_Display(int8_t x, int8_t y);
void LED_Clear(void);
void Delay(uint32_t nCount);

int main(void)
{
	int8_t i,j,k;
	SystemCoreClockUpdate(); // Optional- Setup SystemCoreClock variable
// Configure LED outputs
	LED_Config();
	#define LOOP_COUNT 0x1000
	while(1){
		// your code here		
		
		for (int i = 0; i <= 9; i++) {
			int k = 0;
			while(k<100) { 
				for(int j = 0; j <=4; j++) {
				
					LED_Display(i,j);
					Delay(LOOP_COUNT);
				}
			k++;
			}
			
		}
	
		//FPTC->PSOR = led_ctrl_mask[0] | led_ctrl_mask[1] | led_ctrl_mask[2];
		
		//FPTC->PSOR = led_mask[0] | led_mask[1] | led_mask[2] | led_mask[3] | led_mask[4] | led_mask[5]  ; 
		//Delay(LOOP_COUNT);
		
		//FPTC->PSOR = led_mask[1] | led_mask[2]; 
		//Delay(LOOP_COUNT);
		
		//FPTC->PCOR = led_mask[1] | led_mask[2];
		//FPTC->PSOR = 0xffffffff;
		//Delay(LOOP_COUNT);
		//FPTC->PCOR |= led_ctrl_mask[1];
		
		//Delay(LOOP_COUNT);
		
		//FPTC->PSOR = led_mask[3] | led_mask[4] | led_mask[0] | led_mask[1] | led_mask[6]; 
		
		//Delay(LOOP_COUNT);
		//FPTC->PCOR = led_mask[3] | led_mask[4] | led_mask[0] | led_mask[1] | led_mask[6];
		//Delay(LOOP_COUNT);
		//FPTC->PSOR |= led_ctrl_mask[1];
		//Delay(LOOP_COUNT);
		
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
	/* Enable Clock to Port C */
	// your code here
	SIM->SCGC5 |= (1UL << 11);

	/* configure Pin PTC0/3/4/5/6/7/10/11/12/13/16/17 as GPIO */
	PORTC->PCR[0] = (1UL << 8); /* Pin PTC0 is GPIO */
	PORTC->PCR[3] = (1UL << 8); /* Pin PTC0 is GPIO */
	PORTC->PCR[4] = (1UL << 8); /* Pin PTC0 is GPIO */
	PORTC->PCR[5] = (1UL << 8); /* Pin PTC0 is GPIO */
	PORTC->PCR[6] = (1UL << 8); /* Pin PTC0 is GPIO */
	PORTC->PCR[7] = (1UL << 8); /* Pin PTC0 is GPIO */
	PORTC->PCR[10] = (1UL << 8); /* Pin PTC0 is GPIO */
	PORTC->PCR[11] = (1UL << 8); /* Pin PTC0 is GPIO */
	PORTC->PCR[12] = (1UL << 8); /* Pin PTC0 is GPIO */
	PORTC->PCR[13] = (1UL << 8); /* Pin PTC0 is GPIO */
	PORTC->PCR[16] = (1UL << 8); /* Pin PTC0 is GPIO */
	PORTC->PCR[17] = (1UL << 8); /* Pin PTC0 is GPIO */
	// your code here

	/* Enable Pin PTC0/3/4/5/6/7/10/11/12/13/16/17 as output */
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

	

	
	// your code here

	return;
}


/*---------------------------------------------------------------------------
display number, x, in the yth digit. x=0-9, y=1-4
*---------------------------------------------------------------------------*/
void LED_Display(int8_t x, int8_t y)
{
	// your code here
	LED_Clear();
	switch(y) {
		case 1: FPTC->PCOR = led_ctrl_mask[0] ;break;
		case 2: FPTC->PCOR = led_ctrl_mask[1] ;break;
		case 3: FPTC->PCOR = led_ctrl_mask[2] ;break;
		case 4: FPTC->PCOR = led_ctrl_mask[3] ;break;
		default: break;
	}
	switch(x){
		case 0: FPTC->PSOR = led_mask[0] | led_mask[1] | led_mask[2] | led_mask[3] | led_mask[4] | led_mask[5]  ; break;
		case 1: FPTC->PSOR = led_mask[1] | led_mask[2]; break;
		case 2: FPTC->PSOR = led_mask[3] | led_mask[4] | led_mask[0] | led_mask[1] | led_mask[6]; break;
		case 3: FPTC->PSOR = led_mask[3] | led_mask[2] | led_mask[0] | led_mask[1] | led_mask[6]; break;
		case 4: FPTC->PSOR = led_mask[1] | led_mask[2] | led_mask[6] | led_mask[5]; break;
		case 5: FPTC->PSOR = led_mask[3] | led_mask[2] | led_mask[0] | led_mask[5] | led_mask[6]; break;
		case 6: FPTC->PSOR = led_mask[3] | led_mask[2] | led_mask[0] | led_mask[5] | led_mask[6] | led_mask[4]; break;
		case 7: FPTC->PSOR = led_mask[1] | led_mask[2] | led_mask[0]; break;
		case 8: FPTC->PSOR = led_mask[0] | led_mask[1] | led_mask[2] | led_mask[3] | led_mask[4] | led_mask[5] | led_mask[6]  ; break;
		case 9: FPTC->PSOR = led_mask[0] | led_mask[1] | led_mask[2] | led_mask[5] | led_mask[6]  ; break;
		default: break;
	}
	

	return;
}

/*---------------------------------------------------------------------------
Switch off LEDs
*---------------------------------------------------------------------------*/
void LED_Clear(void)
{
	FPTC->PCOR = (led_mask[0] |	led_mask[1] | led_mask[2] |	led_mask[3] |	led_mask[4] | led_mask[5] |	led_mask[6]  |	led_mask[7] ); /* clear all display */
	FPTC->PSOR = (led_ctrl_mask[0] | led_ctrl_mask[1] | led_ctrl_mask[2] | led_ctrl_mask[3]); /* disable all digits */
	return;
}

