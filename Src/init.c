
#include "main.h"
//system clock init
void init_clk(void)
{
	//step 1 choosing clock source
	RCC->CR|=RCC_CR_HSEON;    //choosing hse
	while(!(RCC->CR & RCC_CR_HSERDY));

	//step 2 configure flash prefetch and latency
	FLASH->ACR|=FLASH_ACR_PRFTBE|FLASH_ACR_LATENCY_2;

	//step 3 configurinh PLL
	RCC->CFGR|=RCC_CFGR_PLLSRC;            //hse as pll source
	RCC->CFGR&=~RCC_CFGR_PLLXTPRE_HSE;     //hse before pll not divided
	RCC->CFGR|=RCC_CFGR_PLLMULL9;         //pll multipiler

	// configuring speed of AHB,APB1,APB2
	RCC->CFGR|=RCC_CFGR_HPRE_DIV1;       //AHB =SYSCLK(72)
	RCC->CFGR|=RCC_CFGR_PPRE2_DIV1;      //APB2=72mhz
	RCC->CFGR|=RCC_CFGR_PPRE1_DIV2;      //APB1=36mhz


	//step 4 enable PLL and wait to get ready
	RCC->CR|=RCC_CR_PLLON;   //enable the PLL
	while(!(RCC->CR & RCC_CR_PLLRDY));


	//step 5 enabling the systems clock
	RCC->CFGR|=RCC_CFGR_SW_PLL;
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));
}


//adc1 setup for channel PA0 lm35, PA1 voltgae sensor , PA2 poteontmeter
void init_adc(void)
{
	//step 1 enable the clock
	RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;       //GPIOA clock enable
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;       //clk for ADC1 enbaled


	//step 2 setting the PA0,PA1,PA2 as input analog mode
	//PA0
	GPIOA->CRL&=~(GPIO_CRL_MODE0);    //input mode
	GPIOA->CRL&=~GPIO_CRL_CNF0;       // analog mode

	//PA1
	GPIOA->CRL&=~(GPIO_CRL_MODE1);    //input mode
	GPIOA->CRL&=~GPIO_CRL_CNF1;       // analog mode

	//PA2
	GPIOA->CRL&=~(GPIO_CRL_MODE2);    //input mode
	GPIOA->CRL&=~GPIO_CRL_CNF2;       // analog mode

	//step 3 power on adc
	ADC1->CR2|=ADC_CR2_ADON;          //ADON=1
	for(volatile int i=0;i<10000;i++) //intentionllay
		{
			;
		}

	// Start 4 calibration

	//reset clabiration
	ADC1->CR2 |= ADC_CR2_RSTCAL;
	while(ADC1->CR2 & ADC_CR2_RSTCAL);

	//again calibrate
	ADC1->CR2 |= ADC_CR2_CAL;
	while(ADC1->CR2 & ADC_CR2_CAL);

	//step 5 setting up sampling time of 55cycles for ch0,1,2
	ADC1->SMPR2&=~((0x7 << 0) | (0x7 << 3) | (0x7 << 6));
	ADC1->SMPR2|=((0x6 << 0) | (0x6 << 3) | (0x6 << 6));
}



