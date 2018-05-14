#include "init.h"

#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"

#include "grlib/grlib.h"
#include "drivers/buttons.h"

#include "inc/hw_memmap.h"

#include "watchdog.h"
#include "uart_io.h"
#include "button_io.h"
#include "sensortimer.h"
#include "display.h"
#include "global.h"

void init(_state_t* state){
	global_init(state);

	// Enable the FPU
	ROM_FPUEnable();

	//
	// Enable lazy stacking for interrupt handlers.  This allows floating-point
	// instructions to be used within interrupt handlers, but at the expense of
	// extra stack usage.
	//
	ROM_FPULazyStackingEnable();

	//
	// Set the clocking to run directly from the crystal.
	//
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
	                   SYSCTL_OSC_MAIN);

	// enable systick for scheduler
	ROM_SysTickEnable();


	//
	// Set the clocking to run at 20 MHz (200 MHz / 10) using the PLL.  When
	// using the ADC, you must either use the PLL or supply a 16 MHz clock
	// source.
	// TODO: The SYSCTL_XTAL_ value must be changed to match the value of the
	// crystal on your board.
	//
	SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
	               SYSCTL_XTAL_16MHZ);

	gassensor_init();

	display_init(state);

	watchdog_init();

	button_io_init();

	uart_io_init();

	sensortimer_init();
}
