/* ###*B*###
* ERIKA Enterprise - a tiny RTOS for small microcontrollers
*
* Copyright (C) 2002-2013  Evidence Srl
*
* This file is part of ERIKA Enterprise.
*
* ERIKA Enterprise is free software; you can redistribute it
* and/or modify it under the terms of the GNU General Public License
* version 2 as published by the Free Software Foundation,
* (with a special exception described below).
*
* Linking this code statically or dynamically with other modules is
* making a combined work based on this code.  Thus, the terms and
* conditions of the GNU General Public License cover the whole
* combination.
*
* As a special exception, the copyright holders of this library give you
* permission to link this code with independent modules to produce an
* executable, regardless of the license terms of these independent
* modules, and to copy and distribute the resulting executable under
* terms of your choice, provided that you also meet, for each linked
* independent module, the terms and conditions of the license of that
* module.  An independent module is a module which is not derived from
* or based on this library.  If you modify this code, you may extend
* this exception to your version of the code, but you are not
* obligated to do so.  If you do not wish to do so, delete this
* exception statement from your version.
*
* ERIKA Enterprise is distributed in the hope that it will be
* useful, but WITHOUT ANY WARRANTY; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License version 2 for more details.
*
* You should have received a copy of the GNU General Public License
* version 2 along with ERIKA Enterprise; if not, write to the
* Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301 USA.
* ###*E*### */

#include "inc/alarm.h"
#include "inc/clock.h"
#include "inc/beh1/ert_main.h"

#include "ee.h"
#include "ee_irq.h"

#include "inc/interface/stm32f4_discovery_lcd.h"
#include "inc/interface/WidgetConfig.h"

/*
 * TASK LCD wake-up time (in milliseconds)
 */

#define LCDRATE 50

/*
 * 100 milliseconds (TASK Clock wake-up time)
 */

#define ONETENTH 100

/* --------------------------------------------- GLOBAL VARIABLES -------------------------------------------- */

unsigned int counter = 0; 						// Incremented every 100 ms and comprised between 0 and MAXCOUNT-1
boolean alarmSrv = false; 						// Used to signal when an alarm event is just terminated

/* -------------------------------------------------- TASKS -------------------------------------------------- */

/*
 * SysTick ISR2: count the interrupts, waking up expired alarms
 */

ISR2(systick_handler)
{
	CounterTick(myCounter);
}

/*
 * TASK Alarm: in charge of starting alarm events
 */

TASK(TaskAlarm)
{
  EventMaskType mask;
  boolean serving;
  while (true) {
    WaitEvent(EventAlarmOn);
    GetEvent(TaskAlarm, &mask);
    if (mask & EventAlarmOn) {
    	serving = true;
    	while (serving==true && launchAlarm(&counter)==true) {
    		GetEvent(TaskAlarm, &mask);
    		if (mask & EventAlarmOff) {
    			stopAlarm();
    			ClearEvent(EventAlarmOff);
    			serving = false;
    		}
    	}
    	if (serving==true) alarmSrv = true;
    	ClearEvent(EventAlarmOff);
    	ClearEvent(EventAlarmOn);
    }
  }
}

/*
 * TASK LCD: in charge of getting all touch events
 */

TASK(TaskLCD)
{
	unsigned int px, py;
	TPoint p;
	if (GetTouch_SC_Async(&px, &py)) {
		p.x = px;
		p.y = py;
		OnTouch(MyWatchScr, &p);
	}
}

/*
 * TASK Clock: in charge of updating the screen
 */

unsigned int hmst[4] = {0,0,0,0};				// Hours, minutes, seconds and tenths
unsigned int mode;								// Mode of operation: '0' for time, '1' for timeset, '2' for alarm, '3' for stopwatch
unsigned int sel;								// Selected digits: '0' for none, '1' for hours, '2' for minutes, '3' for seconds, '4' for tenths
boolean alarmDrv;

TASK(TaskClock)
{

	static boolean button[6] = {false,false,false,false,false,false}; 		// Pressed buttons

	static boolean tick = false; 											// 100 ms clock
	static unsigned int blink = 1; 											// Used for the blinking feature

	static unsigned int hmst_[4] = {61,61,61,10};							// Current time
	static unsigned int mode_ = 0;											// Current mode of operation
	static boolean alarmDrv_ = false;										// Current value of alarmDrv

	tick = !tick; 															// Clock generation at 100 ms
	counter = (counter+1)%MAXCOUNT;
	blink = (blink+1)%BLINK;												// Selected digit blinks when this variable reaches zero

	/* Gather button events */
	if (IsEvent(TIMEMODE)) button[0]=true;
	if (IsEvent(TIMESETMODE)) button[1]=true;
	if (IsEvent(ALARMMODE)) button[2]=true;
	if (IsEvent(SWATCHMODE)) button[3]=true;
	if (IsEvent(PLUS)) button[4]=true;
	if (IsEvent(MINUS)) button[5]=true;

	/* Link the variables to behavioral model (MATLAB R2016b) */

	/* '<Root>/plus' */
	WatchBehavior_U_plus = button[4];

	/* '<Root>/minus' */
	WatchBehavior_U_minus = button[5];

	/* '<Root>/time' */
	WatchBehavior_U_time = button[0];

	/* '<Root>/timeset' */
	WatchBehavior_U_timeset = button[1];

	/* '<Root>/alarm' */
	WatchBehavior_U_alarm = button[2];

	/* '<Root>/stopwatch' */
	WatchBehavior_U_stopwatch = button[3];

	/* '<Root>/clock' */
	WatchBehavior_U_clock = tick;

	/* '<Root>/alarmSrv' */
	WatchBehavior_U_alarmSrv = alarmSrv;

	/*
	 * Step the SM
	 */

	rt_OneStep(WatchBehavior_M);

	/*
	 * -------------------
	 */

	/* '<Root>/hours' */
	hmst[0] = WatchBehavior_Y_hours;

	/* '<Root>/minutes' */
	hmst[1] = WatchBehavior_Y_minutes;

	/* '<Root>/seconds' */
	hmst[2] = WatchBehavior_Y_seconds;

	/* '<Root>/tenths' */
	hmst[3] = WatchBehavior_Y_tenths;

	/* '<Root>/mode' */
	mode = WatchBehavior_Y_mode;

	/* '<Root>/sel' */
	sel = WatchBehavior_Y_sel;

	/* '<Root>/alarmDrv' */
	alarmDrv = WatchBehavior_Y_alarmDrv;

	/*
	 * Alarm manager: launch alarm, reset internal state after an alarm has been served or dismiss the running alarm
	 */

	if (alarmDrv==true && alarmDrv_==false) SetEvent(TaskAlarm, EventAlarmOn);
	if (alarmDrv==false && alarmDrv_==true) {
		if (alarmSrv==true) alarmSrv = false;
		else SetEvent(TaskAlarm, EventAlarmOff);
	}
	alarmDrv_ = alarmDrv;

	/*
	 * Clear events for the next cycle
	 */

	clearEvent(TIMEMODE);
	clearEvent(TIMESETMODE);
	clearEvent(ALARMMODE);
	clearEvent(SWATCHMODE);
	clearEvent(PLUS);
	clearEvent(MINUS);
	for (unsigned int i=0; i<6; i++) button[i]=false;

	/*
	 * Update the screen according to new outputs and mode of operation
	 */

	UpdateDigitsOnScreen(blink, sel, hmst_, hmst, mode_, mode);

	for (unsigned int i=0; i<4; i++)
		hmst_[i]=hmst[i]; 						// Update current time

	if (mode!=mode_) {
		UpdateIconsOnScreen(mode_, mode);
		mode_ = mode; 							// Update current mode
	}

}

/*
 * MAIN TASK
 */

int main(void)
{

	SystemInit();

	/*
	 * Initializes Erika related stuffs
	 */
	EE_system_init();

	/*
	 * Initialize systick
	 */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();

	/*
	 * GPIOD Periph clock enable
	 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/*
	 * Configure led pins in output pushpull mode
	 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/*
	 * Initializes LCD and touchscreen
	 */
	IOE_Config();

	/*
	 * Initialize the LCD
	 */
	STM32f4_Discovery_LCD_Init();

	/*
	 * Automatic calibration
	 */
	//InitTouch(-0.09, 0.0656, -335, 10); 			// Manual calibration. x-axis (first and third parameter) are usually more problematic
	LCD_Clear(White);
	LCD_SetFont(&Font8x12);
	Lcd_Touch_Calibration();

	/*
	 * Draw the background
	 */
	DrawBackground();

	/*
	 * ------------------------------ State Machine initialization (MATLAB R2016b) ------------------------------
	 */

	/* Pack model data into RTM */
  	WatchBehavior_M->blockIO = &WatchBehavior_B;
  	WatchBehavior_M->dwork = &WatchBehavior_DW;
  	WatchBehavior_M->prevZCSigState = &WatchBehavior_PrevZCX;

  	/* Initialize model */
  	WatchBehavior_initialize(WatchBehavior_M, &WatchBehavior_U_plus,
    &WatchBehavior_U_minus, &WatchBehavior_U_time, &WatchBehavior_U_timeset,
    &WatchBehavior_U_alarm, &WatchBehavior_U_stopwatch, &WatchBehavior_U_clock,
    &WatchBehavior_U_alarmSrv, &WatchBehavior_Y_hours, &WatchBehavior_Y_minutes,
    &WatchBehavior_Y_seconds, &WatchBehavior_Y_tenths, &WatchBehavior_Y_mode,
    &WatchBehavior_Y_sel, &WatchBehavior_Y_alarmDrv);

    /*
	 * ----------------------------------------------------------------------------------------------------------
	 */

  	/*
  	 * Explicitly activate TASK Alarm
  	 */
  	ActivateTask(TaskAlarm);

	/*
	 * Program cyclic alarms which will fire after an initial offset,
	 * and after that periodically
	 */
	SetRelAlarm(AlarmTaskLCD, 10, LCDRATE);
	SetRelAlarm(AlarmTaskClock, 10, ONETENTH);

	/*
	 * Forever loop: background activities (if any) should go here
	 */
	while (rtmGetErrorStatus(WatchBehavior_M) == (NULL)) {
    	/*  Perform other application tasks here */
  	}

	/* Disable rt_OneStep() here */

	/*
	 * Terminate model
	 */
	WatchBehavior_terminate(WatchBehavior_M);
  	return 0;

  	/*
  	 * -------------------------------------------------------------------------------------------------------
  	 */
	
}
