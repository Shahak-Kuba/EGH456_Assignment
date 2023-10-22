//*****************************************************************************
//
// watchdog.c - Watchdog timer example.
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
#include <stdio.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/watchdog.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "drivers/buttons.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/ustdlib.h"

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Watchdog (watchdog)</h1>
//!
//! This example application demonstrates the use of the watchdog as a simple
//! heartbeat for the system.  If the watchdog is not periodically fed, it will
//! reset the system.  Each time the watchdog is fed, the LED is inverted so
//! that it is easy to see that it is being fed, which occurs once every
//! second.  To stop the watchdog being fed and, hence, cause a system reset,
//! press the SW1 button.
//
//*****************************************************************************
#define WATCHDOG_FREQ 3
#define PRESSED 1
#define UNPRESSED 0
//****************************************************************************
//
// System clock rate in Hz.
//
//****************************************************************************
uint32_t g_ui32SysClock;

volatile uint32_t counter = 0;
volatile uint8_t bState = UNPRESSED;

//*****************************************************************************
//
// Flag to tell the watchdog interrupt handler whether or not to clear the
// interrupt (feed the watchdog).
//
//*****************************************************************************
volatile bool g_bFeedWatchdog = true;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
//
// The interrupt handler for the watchdog.  This feeds the dog (so that the
// processor does not get reset) and winks the LED connected to GPIO B3.
//
//*****************************************************************************

void
WatchdogIntHandler(void)
{
    counter++;
    //
    // If we have been told to stop feeding the watchdog, return immediately
    // without clearing the interrupt.  This will cause the system to reset
    // next time the watchdog interrupt fires.
    //
    if((counter >= 5 * WATCHDOG_FREQ))
    {

        UARTprintf("\n 5 seconds passed");
        UARTprintf("\n system rebooting\n");
        counter = 0;
        return;
    }

    //
    // Clear the watchdog interrupt.
    //
    ROM_WatchdogIntClear(WATCHDOG0_BASE);

    //
    // Invert the GPIO PN0 value.
    //
    ROM_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0,
                     (ROM_GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_0) ^
                                     GPIO_PIN_0));


}

//*****************************************************************************
//
// This function is called when the SW1 button is pressed.
//
//*****************************************************************************
static int32_t
SW1ButtonPressed(void)
{
    //
    // Set the flag that tells the interrupt handler not to clear the
    // watchdog interrupt.
    //
    g_bFeedWatchdog = false;
    counter = 0;
    UARTprintf("\n counter reset");
    bState = PRESSED;

    return(0);
}

void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, g_ui32SysClock);
}

//*****************************************************************************
//
// This example demonstrates the use of the watchdog timer.
//
//*****************************************************************************
int
main(void)
{
    //
    // Set the clocking to run directly from the crystal at 120MHz.
    //
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                             SYSCTL_OSC_MAIN |
                                             SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_480), 120000000);
    //
    // Initialize the buttons driver.
    //
    ButtonsInit();

    //
    // Initialize the UART and write status.
    //
    ConfigureUART();
    UARTprintf("\n program started \n");

    //
    // Enable the peripherals used by this example.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

    //
    // Enable processor interrupts.
    //
    ROM_IntMasterEnable();

    //
    // Set GPIO PN0 as an output.  This drives an LED on the board that will
    // toggle when a watchdog interrupt is processed.
    //
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    ROM_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);

    //
    // Enable the watchdog interrupt.
    //
    ROM_IntEnable(INT_WATCHDOG);

    //
    // Set the period of the watchdog timer to 1 second.
    //
    ROM_WatchdogReloadSet(WATCHDOG0_BASE, g_ui32SysClock / WATCHDOG_FREQ); // watchdog timer updates at 3Hz

    //
    // Enable reset generation from the watchdog timer.
    //
    ROM_WatchdogResetEnable(WATCHDOG0_BASE);

    //
    // Enable the watchdog timer.
    //
    ROM_WatchdogEnable(WATCHDOG0_BASE);

    //
    // Loop forever while the LED winks as watchdog interrupts are handled.
    //

    uint8_t SW1_prevState = 0;
    while(1)
    {
        //
        // Poll for the select button pressed
        //
        uint8_t ui8Buttons = ButtonsPoll(0, 0);
        uint8_t SW1_state = (ui8Buttons & USR_SW1);

        if ((SW1_state != SW1_prevState) && SW1_state) {
            SW1ButtonPressed();
        }

        SW1_prevState = SW1_state;
    }
}
