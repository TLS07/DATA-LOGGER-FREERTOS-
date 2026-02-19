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
void Temperature_task(void* pvParameters)
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


void Voltage_task(void *pvParameters)
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

void Pot_task(void *pvParameters)
{
	/*
	     * Potentiometer reading:
	     * ADC value 0-4095 → 0-100%
	     */


	sensor_message msg;
	uint16_t adc_value;
    uint8_t pot_percent;  // 0-100%

    while(1)
    {
    	xSemaphoreTake(xADCMutex,portMAX_DELAY);
    	adc_value=adc_read(2);     //pot connected to chnnel 2
    	xSemaphoreGive(xADCMutex);

    	//converting ADC value to percentage
    	pot_percent=(adc_value*100UL)/4095UL;

    	msg.id=3;
    	msg.value=pot_percent;

    	//send data to queue
    	xQueueSend(xSensorQueue,&msg,portMAX_DELAY);

    	vTaskDelay(pdMS_TO_TICKS(500));
    }

}


void switchtask(void *pvParameters)
{
    /*
     * Switch reading:
     * Active low switch on PA3
     * 0 -> Not pressed
     * 1 -> Pressed
     */

    sensor_message msg;
    uint8_t switch_state;

    while(1)
    {
        // Read the switch
        switch_state = switch_read();  // function returns 0 or 1

        msg.id = 4;            // Switch ID
        msg.value = switch_state;

        // Send to queue
        xQueueSend(xSensorQueue, &msg, portMAX_DELAY);

        // Delay
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void UART_task(void *pvParameters)
{
	sensor_message msg;
	char buffer[50];

	while(1)
	{
		//wait indefenitely until a message is  available in queue
		if(xQueueReceive(xSensorQueue,&msg,portMAX_DELAY)==pdTRUE)
		{
			switch(msg.id)
			{
			case 1:  //temperature
				 sprintf(buffer, "Temperature: %u.%u C\r\n",msg.value / 10, msg.value % 10);
				 break;

			case 2:  // voltage
				sprintf(buffer, "Voltage: %u.%02u V\r\n",msg.value / 100, msg.value % 100);
				break;

			case 3: //pot
				 sprintf(buffer, "Potentiometer: %u %%\r\n", msg.value);
				 break;

			 case 4: // Switch status
				 if(msg.value)
					 sprintf(buffer, "Switch: ON\r\n");
				 else
					 sprintf(buffer, "Switch: OFF\r\n");
				 break;
			}
		}
		// Send formatted string over UART
		UART_SendString(buffer);
	}
}



