#  FreeRTOS Based Data Logger – STM32

## ⭐ Project Description

- This project is a FreeRTOS-based Data Logger implemented on an STM32(f103c8t6) microcontroller.

- The system collects data from multiple sensors and transmits the formatted sensor data to a PC/system via UART.

- Each sensor is handled by a dedicated FreeRTOS task. Since multiple sensors share the same ADC peripheral, a Mutex (Semaphore) is used to ensure safe ADC access. A Queue is used to transfer sensor data between tasks.

## ⭐ System Architecture
The system uses:
- FreeRTOS Tasks

- Queue (xSensorQueue) for inter-task communication

- Mutex (xADCMutex) for ADC protection

- UART for data transmission

- 12-bit ADC (0–4095 range)
### Data flow
```
Sensors → Individual Tasks → Queue → UART Task → PC
```
### Sensor Message Structure
```
typedef struct
{
    uint8_t  id;
    uint16_t value;
} sensor_message;
```

### Sensor ID Mapping
```
| Sensor             | ID |
| ------------------ | -- |
| Temperature (LM35) | 1  |
| Voltage Sensor     | 2  |
| Potentiometer      | 3  |
| Switch             | 4  |
```

## ⭐ FreeRTOS  Configuration
```
| Component             | Details   |
| --------------------- | --------- |
| Total Tasks           | 5         |
| UART Task Priority    | 2         |
| Sensor Tasks Priority | 1         |
| Queue Length          | 10        |
| Stack Size per Task   | 200 words |
| CPU Frequency         | 72 MHz    |
```
## ⭐ Task Description
### 1) Temperature Task (Temperature_task)
```
- Reads LM35 sensor via ADC Channel 0
- LM35 Output: 10mV per °C
- Converts ADC value to temperature
- Sends temperature data to queue
- Runs every 500 ms
```

### 2) Voltage Task (Voltage_task)
```
- Measures voltage (0–25V range)
- Uses voltage divider:
      R1 = 1kΩ
      R2 = 150Ω

- Scaling factor ≈ 7.667
- Converts ADC reading to actual voltage
- Sends data to queue
- Runs every 500 ms
```
### 3) Potentiometer Task (Pot_task)
```
- Reads potentiometer using ADC Channel 2
- Converts ADC value (0–4095) to percentage (0–100%)
- Sends data to queue
- Runs every 500 ms
```

### 4) Switch Task (switchtask)
```
- Reads digital switch (Active LOW)
      0 → Not Pressed
      1 → Pressed

- Sends switch status to queue
- Runs every 500 ms
```

### 5) UART Task (UART_task)
```
- Lowest priority task
- Waits indefinitely for messages from queue
- Identifies sensor using msg.id
- Formats data
- Sends data over UART
```

## ⭐ Synchronization Mechanisms
### ADC Mutex (xADCMutex)
 Since ,all use the same ADC peripheral
 ```
   Temperature sensor
   Voltage sensor
   Potentiometer
```
A Mutex is used to :
```
->Prevent concurrent ADC access
->Avoid corrupted readings
->Ensure thread safety
```

### Queue(xSensorQueue)
```
Size: 10 messages
Used for communication between sensor tasks and UART task
Decouples data collection from data transmission
```






  
  





   
