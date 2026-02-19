/*
 * main.h
 *
 *  Created on: Feb 14, 2026
 *      Author: Admin
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stm32f1xx.h"
#include "task.h"
#include "list.h"
#include "queue.h"
#include "semphr.h"
//#include "port.h"

#include "stm32f1xx.h"
//task protypes
void Temperature_task(void *pvParameters);
void Voltage_task(void *pvParameters);
void Pot_task(void *pvParameters);
void switchtask(void *pvParameters);
void UART_task(void *pvParameters);


// Message structure

typedef struct{
	uint8_t id;  // here id ->1=> temp,  2=>voltage, 3=> pot , 4=> switch
	uint16_t value;
}sensor_message;


//function protypes
void init_clk(void);
void init_adc(void);
void init_switch(void);
void init_uart1(void);
uint8_t switch_read(void);
void UART_Transmit(char data);
void UART_SendString(char *str);
uint16_t adc_read(uint8_t channel);





#endif /* MAIN_H_ */
