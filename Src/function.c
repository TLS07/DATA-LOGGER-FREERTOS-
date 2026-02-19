#include"main.h"
//adc channel sellection and data aquire

uint16_t adc_read(uint8_t channel)
{
	// only single conversion
	ADC1->SQR1&=~ADC_SQR1_L;

	//selecting the channel
	ADC1->SQR3=channel;

	//start adc conversion
	ADC1->CR2 |= ADC_CR2_SWSTART;

	//wait till end of conversion
	while (!(ADC1->SR & ADC_SR_EOC));

	//return the result
	return (uint16_t)ADC1->DR;
}

uint8_t switch_read(void)
{
	//switch  is actie low
    if (GPIOA->IDR & (1 << 3))
        return 0;   // Not pressed (pull-up keeps it HIGH)
    else
        return 1;   // Pressed (goes LOW)
}


void UART_Transmit(char data)
{
    while (!(USART2->SR & USART_SR_TXE));  // Wait until TX empty
    USART2->DR = data;
}


void UART_SendString(char *str)
{
    while (*str)
    {
        UART_Transmit(*str++);
    }
}

