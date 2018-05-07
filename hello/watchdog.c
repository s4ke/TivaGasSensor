#include "watchdog.h"

#include "driverlib/rom.h"
#include "driverlib/watchdog.h"
#include "driverlib/sysctl.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"

volatile _watchdog_info_t _watchdog_info;

void init_watchdog(void) {
	_watchdog_info._reset = false;
	_watchdog_info._timer = 0;
	
	//
  // Enable the peripherals used by this example.
	//
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);

	//
	// Enable processor interrupts.
	//
	ROM_IntMasterEnable();

	//
	// Set GPIO PG2 as an output.  This drives an LED on the board that will
	// toggle when a watchdog interrupt is processed.
	//
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PIN_2);
	ROM_GPIOPinWrite(GPIO_PORTG_BASE, GPIO_PIN_2, 0);

	//
	// Enable the watchdog interrupt.
	//
	ROM_IntEnable(INT_WATCHDOG);

	//
	// Set the period of the watchdog timer.
	//
	ROM_WatchdogReloadSet(WATCHDOG0_BASE, ROM_SysCtlClockGet());

	//
	// Enable reset generation from the watchdog timer.
	//
	ROM_WatchdogResetEnable(WATCHDOG0_BASE);

	//
	// Enable the watchdog timer.
	//
	ROM_WatchdogEnable(WATCHDOG0_BASE);
}

void WatchdogIntHandler(void) {
    //
    // If we have been told to stop feeding the watchdog, return immediately
    // without clearing the interrupt.  This will cause the system to reset
    // next time the watchdog interrupt fires.
    //
    if(_watchdog_info._reset) {
			return;
    }
		
		if(_watchdog_info._timer > 5) {
			return;
		}

		++_watchdog_info._timer;
		
    //
    // Clear the watchdog interrupt.
    //
    ROM_WatchdogIntClear(WATCHDOG0_BASE);

    //
    // Invert the GPIO PF3 value.
    //
    ROM_GPIOPinWrite(GPIO_PORTG_BASE, GPIO_PIN_2,
                     (ROM_GPIOPinRead(GPIO_PORTG_BASE, GPIO_PIN_2) ^
                                     GPIO_PIN_2));
}
