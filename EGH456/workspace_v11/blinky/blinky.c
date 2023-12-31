//*****************************************************************************
//
// blinky.c - Simple example to blink the on-board LED.
//
// Copyright (c) 2013-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Blinky (blinky)</h1>
//!
//! A very simple example that blinks the on-board LED using direct register
//! access.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************
#include <stdint.h>
#include "inc/tm4c1294ncpdt.h"

int main(void)
{
    volatile uint32_t ui32Loop;

    // Enable the GPIO port that is used for the on-board LED.
    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R12 | SYSCTL_RCGCGPIO_R5;


    // Short delay to allow peripheral to enable
    for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++) { }

    // Enable GPIO pin for LED D2 (PN0)
    GPIO_PORTN_DIR_R = 0x03;
    GPIO_PORTF_AHB_DIR_R = 0X11;

    // Set the direction as output, and enable the GPIO pin for digital function.
    GPIO_PORTN_DEN_R = 0x03;
    GPIO_PORTF_AHB_DEN_R = 0X11;

    // Loop forever.
    while(1)
    {

        // Turn on the LED.
        GPIO_PORTN_DATA_R |= 0x01;
        GPIO_PORTN_DATA_R &= ~(0x02);
        GPIO_PORTF_AHB_DATA_R &= ~(0x01);
        GPIO_PORTF_AHB_DATA_R &= ~(0x10);

        // Delay for a bit.
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++) { }

        // Turn off the LED.
        GPIO_PORTN_DATA_R |= 0x02;
        GPIO_PORTN_DATA_R &= ~(0x01);
        GPIO_PORTF_AHB_DATA_R &= ~(0x01);
        GPIO_PORTF_AHB_DATA_R &= ~(0x10);

        // Delay for a bit.
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++) { }

        GPIO_PORTF_AHB_DATA_R |= 0x01;
        GPIO_PORTN_DATA_R &= ~(0x02);
        GPIO_PORTN_DATA_R &= ~(0x01);
        GPIO_PORTF_AHB_DATA_R &= ~(0x10);

        // Delay for a bit.
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++) { }

        GPIO_PORTF_AHB_DATA_R |= 0x10;
        GPIO_PORTN_DATA_R &= ~(0x02);
        GPIO_PORTF_AHB_DATA_R &= ~(0x01);
        GPIO_PORTN_DATA_R &= ~(0x01);

        // Delay for a bit.
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++) { }
    }
}
