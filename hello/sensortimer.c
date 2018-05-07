#include "sensortimer.h"

#include "stdint.h"
#include "stdbool.h"

#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/rom.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"

#include "stdtypes.h"
#include "gassensor.h"
#include "data_logger.h"
#include "display.h"
#include "global.h"
#include "watchdog.h"


void SensorTimerHandler(void) {

	//
	// Clear the timer interrupt.
	//
	ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	ROM_IntMasterDisable();

	_uint32_t old_max = g_state->sensor_data->maxVal;

	read_data((_sensor_data_t*) g_state->sensor_data);
	log_data((_sensor_data_t*) g_state->sensor_data);

	if(old_max != g_state->sensor_data->maxVal) {
		display((_state_t*) g_state);
	}

	ping_watchdog();

	ROM_IntMasterEnable();
}

void sensortimer_init () {
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	
	//
	// Enable processor interrupts.
	//
	ROM_IntMasterEnable();

	//
	// Configure the two 32-bit periodic timer.
	//
	ROM_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
	ROM_TimerLoadSet(TIMER0_BASE, TIMER_A, ROM_SysCtlClockGet() / 12);

	//
	// Setup the interrupts for the timer timeout.
	//
	ROM_IntEnable(INT_TIMER0A);
	ROM_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	//
	// Enable the timer.
	//
	ROM_TimerEnable(TIMER0_BASE, TIMER_A);
}

