#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "stm32f1xx.h"

/* ============================================================
 * 1. Scheduler Behaviour
 * preemptive schduling enabled
 * ============================================================ */

#define configUSE_PREEMPTION                    1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
#define configUSE_TIME_SLICING                  1
#define configUSE_TICKLESS_IDLE                 0
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0

/* ============================================================
 * 2. Clock Configuration
 *    sysTick clock for timing
 *    rate is 1000hz
 * ============================================================ */

#define configCPU_CLOCK_HZ        ( SystemCoreClock )
#define configTICK_RATE_HZ        ( ( TickType_t )1000 )

/* ============================================================
 * 3. Memory Configuration (heap_4.c)
 * stm32f103c8t6 has 20KB ram in that we are using 10Kb for heap
 * ============================================================ */
#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configSUPPORT_STATIC_ALLOCATION         0
#define configTOTAL_HEAP_SIZE     ( ( size_t )( 10 * 1024 ) )
#define configMINIMAL_STACK_SIZE  ( ( uint16_t )128 )

/* ============================================================
 * 4. Task Configuration
 *  task priority from 0-4
 * ============================================================ */

#define configMAX_PRIORITIES                      5
#define configMAX_TASK_NAME_LEN                   16
#define configUSE_16_BIT_TICKS                    0
#define configIDLE_SHOULD_YIELD                   1

/* ============================================================
 * 5. Synchronisation Features
 *    enabling mutex semaphores
 * ============================================================ */

#define configUSE_MUTEXES                         1
#define configUSE_RECURSIVE_MUTEXES               1
#define configUSE_COUNTING_SEMAPHORES             1
#define configQUEUE_REGISTRY_SIZE                 8

/* ============================================================
 * 6. Error Checking
 *    check if memory allocated or not
 *    if fails vApplicationMallocFailedHook() is called
 * ============================================================ */

#define configCHECK_FOR_STACK_OVERFLOW            2
#define configUSE_MALLOC_FAILED_HOOK              1
#define configASSERT( x ) \
    if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/* ============================================================
 * 7. Software Timers
 * ============================================================ */

#define configUSE_TIMERS                          1
#define configTIMER_TASK_PRIORITY                 2
#define configTIMER_QUEUE_LENGTH                  10
#define configTIMER_TASK_STACK_DEPTH              128

/* ============================================================
 * 8. API Inclusion Control
 *    enabling the api
 * ============================================================ */

#define INCLUDE_vTaskPrioritySet                  1
#define INCLUDE_uxTaskPriorityGet                 1
#define INCLUDE_vTaskDelete                       1
#define INCLUDE_vTaskSuspend                      1
#define INCLUDE_vTaskDelay                        1
#define INCLUDE_vTaskDelayUntil                   1
#define INCLUDE_xTaskGetSchedulerState            1

/* ============================================================
 * 9. Cortex-M3 Interrupt Configuration
 * ============================================================ */

/* STM32F1 has 4 implemented priority bits
 * STM32F103 implements 4 priority bits.
 *  2^4 = 16 priority levels (0–15)
 *
 *  */
#ifdef __NVIC_PRIO_BITS
    #define configPRIO_BITS       __NVIC_PRIO_BITS
#else
    #define configPRIO_BITS       4
#endif

/* Lowest interrupt priority (numerically highest) */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         15

/* Highest interrupt priority allowed to call FreeRTOS API */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5

#define configKERNEL_INTERRUPT_PRIORITY \
    ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

#define configMAX_SYSCALL_INTERRUPT_PRIORITY \
    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* ============================================================
 * 10. Interrupt Handler Mapping
 * FreeRTOS uses 3 special exceptions:
    1)SVC → Starts first task
    2)PendSV → Performs context switch
    3)SysTick → Generates scheduler tick
 * ============================================================ */

#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

/* ============================================================
 * 11. Hook Function Prototypes (Required if Enabled)
 * ============================================================ */

void vApplicationMallocFailedHook(void);


#endif /* FREERTOS_CONFIG_H */
