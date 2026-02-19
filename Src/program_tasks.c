/*
 * program_tasks.c
 *
 */

#include "main.h"


/*
 * sensor_message structure example:
 * typedef struct
 * {
 *     uint8_t  id;
 *     uint16_t value;
 * } sensor_message;
 */

extern SemaphoreHandle_t xADCMutex;
extern QueueHandle_t     xSensorQueue;


// task to read the temperature senor reading from lm35
void Temperautre_task(void* pvParameters)
{
	/*
	 * LM35 10mv per °c
	 * ADC=>Voltage=>temp
	 * */

	sensor_message msg;
	uint16_t adc_value;
	uint16_t temperature;    //storing in valueX10;

	while(1)
	{
		//Take adc mutex
		xSemaphoreTake(xADCMutex,portMAX_DELAY);
		adc_value=adc_read(0);    // LM35 connected to channel one
		xSemaphoreGive(xADCMutex);

		//converting adc value->temprautre
		temperature=(adc_value*3300UL)/4095UL;

		msg.id=1;                  //temp id
		msg.value=temperature;


		//sending data to queue
		xQueueSend(xSensorQueue,&msg,portMAX_DELAY);
		vTaskDelay(pdMS_TO_TICKS(500));

	}
}


void VOltage_task(void *pvParameters)
{
	/*
	 * here using a voltage divder ciruit to measure voltage in the range
	 * of 0-25v  r1=1k, R2=150 ohm
	 * Current I when 25v applied
	 * I=25/(1k+150) =>21.7mA
	 * P=V*I =25*0.0217 =>0.54W for safe side we are taking 1W
	 *
	 * voltage multipier = 1150/150 = 7.667
	 * */
	sensor_message msg;
	uint16_t adc_value;
	uint16_t voltage;   //storing in value X100;
	while(1)
	{
		xSemaphoreTake(xADCMutex,portMAX_DELAY);
		adc_value=adc_read(1);         // volatge sensore connected to channel 1
		xSemaphoreGive(xADCMutex);

		voltage =(((uint32_t)adc_value*3300UL)*7667UL)/(4095*1000UL);

		msg.id=2;
		msg.value=voltage;
		xQueueSend(xSensorQueue,&msg,portMAX_DELAY);

		vTaskDelay(pdMS_TO_TICKS(500));

	}

}
xTaskCreate(Temperature_task,"TempTask",200,NULL,1,NULL);
xTaskCreate(Voltage_task,"VoltTask",200,NULL,1,NULL);
xTaskCreate(Pot_task,"PotTask",200,NULL,1,NULL);
xTaskCreate(switchtask,"switchTask", 200, NULL, 1, NULL);
xTaskCreate(UART_task,"UARTTask",200,NULL,2,NULL);
