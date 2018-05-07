#include "init.h"

#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"

#include "grlib/grlib.h"
#include "drivers/cfal96x64x16.h"
#include "drivers/buttons.h"

#include "inc/hw_memmap.h"

#include "watchdog.h"
#include "uart_io.h"
#include "button_io.h"
#include "sensortimer.h"
#include "global.h"

void init(_state_t* state){
		global_init(state);
	
		tContext* sContext = &state->context;
		
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
    // Initialize the display driver.
    //
    CFAL96x64x16Init();
		
		//
    // Initialize the graphics context.
    //
    GrContextInit(sContext, &g_sCFAL96x64x16);
		
		//
    // Set the clocking to run at 20 MHz (200 MHz / 10) using the PLL.  When
    // using the ADC, you must either use the PLL or supply a 16 MHz clock
    // source.
    // TODO: The SYSCTL_XTAL_ value must be changed to match the value of the
    // crystal on your board.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
									 
		//
    // The ADC0 peripheral must be enabled for use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    //
    // For this example ADC0 is used with AIN0 on port E7.
    // The actual port and pins used may be different on your part, consult
    // the data sheet for more information.  GPIO port E needs to be enabled
    // so these pins can be used.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    //
    // Select the analog ADC function for these pins.
    // Consult the data sheet to see which functions are allocated per pin.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_7);

    //
    // Enable sample sequence 3 with a processor signal trigger.  Sequence 3
    // will do a single sample when the processor sends a signal to start the
    // conversion.  Each ADC module has 4 programmable sequences, sequence 0
    // to sequence 3.  This example is arbitrarily using sequence 3.
    //
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);

    //
    // Configure step 0 on sequence 3.  Sample channel 0 (ADC_CTL_CH0) in
    // single-ended mode (default) and configure the interrupt flag
    // (ADC_CTL_IE) to be set when the sample is done.  Tell the ADC logic
    // that this is the last conversion on sequence 3 (ADC_CTL_END).  Sequence
    // 3 has only one programmable step.  Sequence 1 and 2 have 4 steps, and
    // sequence 0 has 8 programmable steps.  Since we are only doing a single
    // conversion using sequence 3 we will only configure step 0.  For more
    // information on the ADC sequences and steps, reference the datasheet.
    //
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE |
                             ADC_CTL_END);

    //
    // Since sample sequence 3 is now configured, it must be enabled.
    //
    ADCSequenceEnable(ADC0_BASE, 3);

    //
    // Clear the interrupt status flag.  This is done to make sure the
    // interrupt flag is cleared before we sample.
    //
    ADCIntClear(ADC0_BASE, 3);
		
		init_watchdog();
		
		buttons_init();
		
		uart_init();
		
		sensortimer_init();
		
		/*
		g_psSchedulerTable[0] = (tSchedulerTask) {
			.pfnFunction = (tSchedulerFunction) &read_data, 
			.pvParam = state,
			.bActive = true,
			.ui32FrequencyTicks = 100
		};
		*/
		
		/*g_psSchedulerTable[0] = (tSchedulerTask) {
			.pfnFunction = (tSchedulerFunction) &display,
			.pvParam = state,
			.bActive = true,
			.ui32FrequencyTicks = 15
		};*/
		
		//SchedulerSysTickIntHandler();
		//SchedulerInit(30);
}
