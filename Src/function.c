#include"main.h"
extern SemaphoreHandle_t xSwitchSemaphore;

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

void EXTI3_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken= pdFALSE;
	if(EXTI->PR &(1<<3))
	{
		EXTI->PR =(1<<3); //clear the pending bit
		xSemaphoreGiveFromISR(xSwitchSemaphore,&xHigherPriorityTaskWoken);

		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}

}

