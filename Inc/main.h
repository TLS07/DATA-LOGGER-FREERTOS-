/*
 * main.h
 *
 *  Created on: Feb 14, 2026
 *      Author: Admin
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stm32f1xx.h"
#include "task.h"
#include "list.h"
#include "queue.h"
#include "semphr.h"

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







#endif /* MAIN_H_ */
