/*
 * UART.c
 *
 * Created on: Oct 29, 2024
 * Author: Isaiah Hendrick
 */

/* Custom includes */
#include "UART.h"

/* UART0 global variables */
uint8_t UART0_Buffer[BUFFER_SIZE];
uint16_t UART0_readIndex, UART0_writeIndex;

/* UART2 global variables */
uint8_t UART2_Buffer[BUFFER_SIZE];
uint16_t UART2_readIndex, UART2_writeIndex;

/* EUSCIAX UART interrupt handler prototypes */
void EUSCIA0_IRQHandler(void);
void EUSCIA2_IRQHandler(void);

/**
 * @brief Initializes the specified UART module with the provided configuration.
 *
 * This function sets up the specified UART module by configuring the GPIO pins,
 * initializing the module with the provided settings, enabling the module, and registering and
 * enabling the receive interrupt for the module. It handles UART modules EUSCI_A0_BASE and EUSCI_A2_BASE.
 *
 * @param UART The base address of the UART module (EUSCI_A0_BASE or EUSCI_A2_BASE)
 * @param config A structure containing the configuration settings for the UART module
 *
 * @return void
 */
void UART_Init(uint32_t UART, eUSCI_UART_Config config) {
    switch(UART)    {
        case EUSCI_A0_BASE:
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
            UART_initModule(UART, &config);
            UART_enableModule(UART);
            /* Register the Interrupt to the interrupt table and enable receive interrupt */
            UART_registerInterrupt(UART, EUSCIA0_IRQHandler);
            UART_enableInterrupt(UART, EUSCI_A_UART_RECEIVE_INTERRUPT);
            Interrupt_enableInterrupt(INT_EUSCIA0);
            break;
        case EUSCI_A2_BASE:
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
            UART_initModule(UART, &config);
            UART_enableModule(UART);
            /* Register the Interrupt to the interrupt table and enable receive interrupt */
            UART_registerInterrupt(UART, EUSCIA2_IRQHandler);
            UART_enableInterrupt(UART, EUSCI_A_UART_RECEIVE_INTERRUPT);
            Interrupt_enableInterrupt(INT_EUSCIA2);
            break;
        default:
            break;
    }
}

/**
 * @brief Writes data to a specified UART instance.
 *
 * This function transmits characters from the provided data array to the
 * specified UART instance until a null character is encountered, indicating the end of the string.
 *
 * @param UART The base address of the UART module
 * @param data A pointer to the character array containing the data to be transmitted
 *
 * @return void
 */
void UART_WriteData(uint32_t UART, char * data) {
    int i = 0;
    /* Transmit characters while a null character has not be reached */
    while(data[i] != '\0')  {
        UART_transmitData(UART, (uint8_t)data[i]);
        i++;
    }
}

/**
 * @brief Reads a byte (or specified number of bytes) from a UART buffer.
 *
 * This function reads a specified number of bytes from the UART buffer
 * corresponding to the specified UART module. It checks if data is available in the
 * buffer and retrieves it into the provided data array. The function handles UART
 * modules EUSCI_A0_BASE and EUSCI_A2_BASE.
 *
 * @param UART The base address of the UART module (EUSCI_A0_BASE or EUSCI_A2_BASE)
 * @param data A pointer to an array where the read data will be stored
 * @param size The number of bytes to read from the UART buffer
 *
 * @return The number of bytes actually read from the UART buffer
 */
uint32_t UART_ReadByte(uint32_t UART, uint8_t * data, uint32_t size)    {
    uint32_t i;
    int8_t c;

    switch(UART)    {
        case EUSCI_A0_BASE:
            for(i = 0; i < size; i++)   {
                /* Check if no data has been received by interrupt */
                if(UART0_readIndex == UART0_writeIndex)    {
                    return i;
                } else    {
                    /* Get a character from the buffer used by interrupt */
                    c = UART0_Buffer[UART0_readIndex];
                    Interrupt_disableMaster();
                    UART0_readIndex = (UART0_readIndex + 1) % BUFFER_SIZE;
                    Interrupt_enableMaster();

                    /* write character to new buffer */
                    data[i] = c;
                }
            }
            break;
        case EUSCI_A2_BASE:
            for(i = 0; i < size; i++)   {
                /* Check if no data has been received by interrupt */
                if(UART2_readIndex == UART2_writeIndex)    {
                    return i;
                } else  {
                    /* Get a character from the buffer used by interupt */
                    c = UART2_Buffer[UART2_readIndex];
                    Interrupt_disableMaster();
                    UART2_readIndex = (UART2_readIndex + 1) % BUFFER_SIZE;
                    Interrupt_enableMaster();

                    /* write character to new buffer */
                    data[i] = c;
                }
            }
            break;
        default:
            return 0;
    }
    return i;
}

/**
 * @brief Reads a string from the UART buffer until an escape character is received.
 *
 * This function reads characters from the specified UART buffer and stores them in the
 * provided buffer until an escape character (ASCII 27) is encountered. It handles newline characters,
 * backspaces, and ensures that the buffer is null-terminated.
 *
 * @param UART The base address of the UART module
 * @param buffer A pointer to the character array where the read string will be stored
 * @param size The size of the buffer
 *
 * @return The number of characters read, or size + 1 if the buffer is full
 */
int UART_ReadString(uint32_t UART, char * buffer, int size) {
    char c = 0;
    uint32_t i = 0;

    /* While an escpae character is not received */
    while(c != 27)  {
        if(UART_ReadByte(UART, (uint8_t*)&c, 1) != 0)   {
           // check for newline character
            if(c == '\n' || c == '\r')   {
               if(i + 3 > size) {
                   return size + 1;
               }

               buffer[i++] = '\r';
               buffer[i++] = '\n';
               buffer[i++] = 0;

               return i;
           // check for backspace
           } else if(c == 127 || c == 8) {
               i--;
               buffer[i] = 0;
           // else add character to buffer
           } else {
               if(i < size) {
                   buffer[i++] = c;
               } else {
                   return size + 1;
               }
           }
        }
    }
    return 0;
}


/**
 * @brief Trims the RX/TX buffer of trailing \r or \n characters.
 *
 * This function removes trailing carriage return (\r) and newline (\n) characters from
 * the provided buffer. It iterates from the end of the buffer and replaces these characters with
 * null terminators until none are left at the end of the string.
 *
 * @param buffer A pointer to the character array (buffer) to be trimmed.
 *
 * @return void
 */
void trimBuffer(char *buffer) {
    int len = strlen(buffer);

    // Trim trailing \r and \n characters
    while (len > 0 && (buffer[len - 1] == '\r' || buffer[len - 1] == '\n')) {
        buffer[len - 1] = '\0';
        len--;
    }
}


/**
 * @brief EUSCIA0 UART Handler for Serial Console (via USB).
 *
 * This interrupt handler function is for the EUSCIA0 UART module. It processes the received data
 * by reading the UART status, clearing the interrupt flag, and storing the received character
 * into the UART buffer. It also echoes the received character back to be viewed during typing.
 *
 * @param void
 *
 * @return void
 */
void EUSCIA0_IRQHandler(void)   {
    uint8_t c;
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A0_BASE);    // get interrupt status

    UART_clearInterruptFlag(EUSCI_A0_BASE, status);                     // clear interrupt flag
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)    {
        c = UART_receiveData(EUSCI_A0_BASE);                // get char from console
        UART0_Buffer[UART0_writeIndex] = c;                       // add to UART buffer
        UART0_writeIndex = (UART0_writeIndex + 1) % BUFFER_SIZE;        // increment buffer
        UART_transmitData(EUSCI_A0_BASE, c);
    }
}

/**
 * @brief EUSCIA2 UART Handler for HC05 Bluetooth Breakout Module.
 *
 * This interrupt handler function is for the EUSCIA2 UART module. It processes the received data
 * by reading the UART status, clearing the interrupt flag, and storing the received character
 * into the UART buffer.
 *
 * @param void
 *
 * @return void
 */
void EUSCIA2_IRQHandler(void)   {
    uint8_t c;
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A2_BASE);    // get interrupt status

    UART_clearInterruptFlag(EUSCI_A2_BASE, status);                     // clear interrupt flag
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT) {
        c = UART_receiveData(EUSCI_A2_BASE);                // get character from bluetooth RX
        UART2_Buffer[UART2_writeIndex] = c;                       // add to UART buffer
        UART2_writeIndex = (UART2_writeIndex + 1) % BUFFER_SIZE;        // increment buffer
    }
}

