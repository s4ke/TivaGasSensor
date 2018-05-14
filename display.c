#include <cstdio>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grlib/grlib.h"
#include "display.h"
#include "util.h"
#include "conversion.h"

#include "drivers/cfal96x64x16.h"


static void display_screen(_state_t* state);
static void display_screen_ppm(_state_t* state);
static void display_screen_pct(_state_t* state);
static void blank_screen(tContext* sContext);
static void printToScreen(tContext* sContext, char* str);

void display_init(_state_t* state) {
	tContext* sContext = &state->context;

	//
	// Initialize the display driver.
	//
	CFAL96x64x16Init();

	//
	// Initialize the graphics context.
	//
	GrContextInit(sContext, &g_sCFAL96x64x16);
}

void display_render(_state_t* state) {
	switch(state->screen) {
	case DISPLAY_SCREEN:
		display_screen(state);
		break;
	case DISPLAY_PPM_SCREEN:
		display_screen_ppm(state);
		break;
	case DISPLAY_PCT_SCREEN:
		display_screen_pct(state);
		break;
	default:
		blank_screen(&state->context);
	}
}

static void display_screen(_state_t* state) {
	char str[32];
	_float_t floatVoltage = util_to_adc_voltage(state->sensor_data->max_val);
	_uint32_t preComma = (int) floatVoltage;
	_uint32_t postComma = ((int) (floatVoltage * 100)) - (preComma * 100);
	sprintf(str, "AIN0 = %d.%d", preComma, postComma);
	printToScreen(&state->context, str);
}

static void display_screen_ppm(_state_t* state) {
	char str[32];
	_float_t floatVoltage = util_to_adc_voltage(state->sensor_data->max_val);
	_float_t float_ppm = conversion_voltage_to_ppm(floatVoltage);

	_uint32_t preComma = (int) float_ppm;
	_uint32_t postComma = ((int) (float_ppm * 100)) - (preComma * 100);
	sprintf(str, "ppm = %d.%d", preComma, postComma);
	printToScreen(&state->context, str);
}

static void display_screen_pct(_state_t* state) {
	char str[32];
	_float_t floatVoltage = util_to_adc_voltage(state->sensor_data->max_val);
	_float_t float_ppm = conversion_voltage_to_pct(floatVoltage);

	_uint32_t preComma = (int) float_ppm;
	_uint32_t postComma = ((int) (float_ppm * 100)) - (preComma * 100);
	sprintf(str, "pct = %d.%d%%", preComma, postComma);
	printToScreen(&state->context, str);
}




static void blank_screen(tContext* sContext) {
	tRectangle sRect;

	//draw black rectangle -> clear the screen
	sRect.i16XMin = 0;
	sRect.i16YMin = 0;
	sRect.i16XMax = GrContextDpyWidthGet(sContext) - 1;
	sRect.i16YMax = GrContextDpyHeightGet(sContext) - 1;
	GrContextForegroundSet(sContext, ClrBlack);
	GrRectFill(sContext, &sRect);
}

static void printToScreen(tContext* sContext, char* str) {
	tRectangle sRect;

	//draw black rectangle -> clear the screen
	sRect.i16XMin = 0;
	sRect.i16YMin = 0;
	sRect.i16XMax = GrContextDpyWidthGet(sContext) - 1;
	sRect.i16YMax = GrContextDpyHeightGet(sContext) - 1;
	GrContextForegroundSet(sContext, ClrBlack);
	GrRectFill(sContext, &sRect);
	//GrFlush(sContext);

	// Fill the top 24 rows of the screen with blue to create the banner.
	sRect.i16XMin = 0;
	sRect.i16YMin = 0;
	sRect.i16XMax = GrContextDpyWidthGet(sContext) - 1;
	sRect.i16YMax = 23;
	GrContextForegroundSet(sContext, ClrDarkBlue);
	GrRectFill(sContext, &sRect);

	// Put a white box around the banner.
	GrContextForegroundSet(sContext, ClrWhite);
	GrRectDraw(sContext, &sRect);

	// Put the application name in the middle of the banner.
	GrContextFontSet(sContext, g_psFontCm12);
	GrStringDrawCentered(sContext, "Gasometer", -1,
	                     GrContextDpyWidthGet(sContext) / 2, 10, 0);

	// Say hello using the Computer Modern 40 point font.
	GrContextFontSet(sContext, g_psFontCm12 /*g_psFontFixed6x8*/);
	GrStringDrawCentered(sContext, str, -1,
	                     GrContextDpyWidthGet(sContext) / 2,
	                     ((GrContextDpyHeightGet(sContext) - 24) / 2) + 24,
	                     0);

	// Flush any cached drawing operations.
	GrFlush(sContext);
}
