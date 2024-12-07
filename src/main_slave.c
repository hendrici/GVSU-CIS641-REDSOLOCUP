/*
 * -------------------------------------------
 *    MSP432 DriverLib - v3_21_00_05 
 * -------------------------------------------
 *
 * --COPYRIGHT--,BSD,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/****************************************************************************** */

/* Standard includes */
#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>

/* Custom includes */
#include "UART.h"
#include "CS_Driver.h"

/* Macros */
#define MAIN_BUFFER_SIZE 256

/* Data Buffer to hold Console and Bluetooth data */
char Buffer[MAIN_BUFFER_SIZE];

/* main function */
int main(void)
{
    WDT_A_holdTimer();      // stop watchdog timer

    CS_Init_48MHz();        // manipulate system clocks

    eUSCI_UART_Config config;
    config.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;
    config.clockPrescalar = 312*4;                                    // calculated 3MHz divided by 9600 baud rate
    config.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
    config.parity = EUSCI_A_UART_LSB_FIRST;
    config.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
    config.uartMode = EUSCI_A_UART_MODE;
    UART_Init(UART_CONSOLE, config);                                  // initialize UART console instance

    config.clockPrescalar = 78*4;                                     // calculated 3MHz divided by 38400 baud rate
    UART_Init(UART_BLUETOOTH, config);                                // initialize UART bluetooth instance

    Interrupt_enableMaster();

    UART_WriteData(UART_CONSOLE, "\x1b[31m");                         // color formatting escape code

    /* ASCII art for startup visual */
    UART_WriteData(UART_CONSOLE, "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\r\n");
    UART_WriteData(UART_CONSOLE, ": ______   _______ ______     _______ _______ ___     _______    _______ __   __ _______ :\r\n");
    UART_WriteData(UART_CONSOLE, ":|    _ | |       |      |   |       |       |   |   |       |  |       |  | |  |       |:\r\n");
    UART_WriteData(UART_CONSOLE, ":|   | || |    ___|  _    |  |  _____|   _   |   |   |   _   |  |       |  | |  |    _  |:\r\n");
    UART_WriteData(UART_CONSOLE, ":|   |_||_|   |___| | |   |  | |_____|  | |  |   |   |  | |  |  |       |  |_|  |   |_| |:\r\n");
    UART_WriteData(UART_CONSOLE, ":|    __  |    ___| |_|   |  |_____  |  |_|  |   |___|  |_|  |  |      _|       |    ___|:\r\n");
    UART_WriteData(UART_CONSOLE, ":|   |  | |   |___|       |   _____| |       |       |       |  |     |_|       |   |    :\r\n");
    UART_WriteData(UART_CONSOLE, ":|___|  |_|_______|______|   |_______|_______|_______|_______|  |_______|_______|___|    :\r\n");
    UART_WriteData(UART_CONSOLE, "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\r\n\n");

    UART_WriteData(UART_CONSOLE, "\x1b[36C  .::::::::::::::.\r\n"
                             "\x1b[36C  .=***+++******=.\r\n"
                             "\x1b[36C   :*###########-\r\n"
                             "\x1b[36C   .*##########*:\r\n"
                             "\x1b[36C   .+##########*.\r\n"
                             "\x1b[36C    -##########*.\r\n"
                             "\x1b[36C    :##########+.\r\n"
                             "\x1b[36C    .*#########-\r\n"
                             "\x1b[36C    .+#########.\r\n"
                             "\x1b[36C     -#########.\r\n"
                             "\x1b[36C     .=++**+++-\r\n");

    UART_WriteData(UART_CONSOLE, "\x1b[37m\nCIS 641 Final Project --- Welcome User #2!\r\n\n");     // print welcome message

    while (1) {
        // User #1 sends a message
        UART_WriteData(UART_CONSOLE, "\x1b[36m\rUser #2: \x1b[37m");
        UART_ReadString(UART_BLUETOOTH, Buffer, MAIN_BUFFER_SIZE);
        trimBuffer(Buffer);

        if (strlen(Buffer) > 0) {
            UART_WriteData(UART_CONSOLE, "\x1b[31m\rUser #1: \x1b[37m");
            UART_WriteData(UART_CONSOLE, Buffer);
            UART_WriteData(UART_CONSOLE, "\r\n");

            // User #2 sends a message
            UART_WriteData(UART_CONSOLE, "\x1b[36m\rUser #2: \x1b[37m");
            UART_ReadString(UART_CONSOLE, Buffer, MAIN_BUFFER_SIZE);
            UART_WriteData(UART_BLUETOOTH, Buffer);
        }
    }


}



