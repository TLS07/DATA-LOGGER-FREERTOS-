
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

	//step 5 setting adc clk
	RCC->CFGR &= ~RCC_CFGR_ADCPRE;
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;   // 72 / 6 = 12 MHz (VALID)

	//step 6 setting up sampling time of 55cycles for ch0,1,2
	ADC1->SMPR2&=~((0x7 << 0) | (0x7 << 3) | (0x7 << 6));
	ADC1->SMPR2|=((0x6 << 0) | (0x6 << 3) | (0x6 << 6));
}

//configuring PA3 as input pin
void init_switch(void)
{
    // step 1 Enable GPIOA clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // step 2 Clear MODE3 and CNF3 (4 bits total)
    GPIOA->CRL &= ~(0xF << (3 * 4));

    // step 3 Set CNF3 = 10 (input pull-up/pull-down)
    GPIOA->CRL |= (0x8 << (3 * 4));

    // step 4 Enable Pull-up (ODR bit = 1 → pull-up)
    GPIOA->ODR |= (1 << 3);
}

void init_uart1(void)
{
	// Step 1: Enable clocks
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;    // GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // USART1

	// Step 2: Configure PA9 (TX) as AF Push-Pull, 50MHz
	GPIOA->CRH &= ~(0xF << 4);      // Clear bits for PA9
	GPIOA->CRH |=  (0xB << 4);      // MODE=11 (50MHz), CNF=10 (AF PP)


	// Step 3: Set baud rate (9600 for 72MHz)
	USART1->BRR = (468 << 4) | 12;

	// Step 5: Enable TX, RX and USART
	USART1->CR1 |= USART_CR1_TE;  // Transmitter enable
	USART1->CR1 |= USART_CR1_UE;  // USART enable

}



