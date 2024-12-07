/*
 * UART.h
 *
 * Created on: Oct 29, 2024
 * Author: Isaiah Hendrick
 */

#ifndef HARDWARE_UART_DRIVER_H_
#define HARDWARE_UART_DRIVER_H_

/* Standard includes */
#include "driverlib.h"
#include <string.h>

/* Macros */
#define BUFFER_SIZE         2048
#define UART_CONSOLE        EUSCI_A0_BASE
#define UART_BLUETOOTH      EUSCI_A2_BASE

/* Function prototypes */
void UART_Init(uint32_t UART, eUSCI_UART_Config config);
void UART_WriteData(uint32_t UART, char * data);
uint32_t UART_ReadByte(uint32_t UART, uint8_t *Data, uint32_t Size);
int UART_ReadString(uint32_t UART, char *buffer, int size);
void trimBuffer(char *buffer);

#endif /* HARDWARE_UART_DRIVER_H_ */
