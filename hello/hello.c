#include <stdint.h>
#include <stdbool.h>

#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

#include "init.h"
#include "state.h"
#include "display.h"
#include "gassensor.h"
#include "watchdog.h"
#include "button_io.h"
#include "uart_io.h"
#include "data_logger.h"

/*tSchedulerTask g_psSchedulerTable[1];
uint32_t g_ui32SchedulerNumTasks = 1;*/

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

int main(void)
{
		_state_t* state = default_state();
	
		init(state);
	
		state->screen = FIRST_DISPLAY;

    // Sample AIN0 forever.  Display the value on the console.
    while(1)
    {
			IntMasterDisable();
			
			handle_buttons(state);
			
			IntMasterEnable();
    }
		
		free_state(state);
}
