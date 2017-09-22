/*
 * alarm.c
 *
 *  Created on: 17 gen 2017
 *      Author: Alessandro Trifoglio
 */

#include "inc/alarm.h"

#include "inc/interface/WidgetConfig.h"

#define MAXBEATS 30

unsigned int toReset = 0;
unsigned int i = 0;

/*
 * LEDs are switched on-off according to these time intervals. Values are comprised between 0 (no wait time before switching a LED)
 * and 100*(MAXCOUNT-1) (maximum wait time before toggling LED) and are expressed in milliseconds
 */

unsigned int beats[MAXBEATS] = {
100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100
};

void stopAlarm (void) {

	if (toReset==1) {
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		toReset = 0;
	}
	i = 0;

}

boolean launchAlarm (unsigned int* counter) {

	static unsigned int lastCounter;

	if (i==0) {
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		lastCounter = *counter;
		toReset = (toReset-1)%2;
		i++;
		return 1;
	} else if (i<=MAXBEATS) {
		while ((*counter-lastCounter)%MAXCOUNT<(beats[i-1]/100));
		switch (toReset) {
			case (1):
				GPIO_ResetBits(GPIOD, GPIO_Pin_12);
				break;
			case (0):
				GPIO_SetBits(GPIOD, GPIO_Pin_12);
				break;
			default:
				break;
		}
		lastCounter = *counter;
		toReset = (toReset-1)%2;
		i++;
		return true;
	} else {
		stopAlarm();
		return false;
	}

}
