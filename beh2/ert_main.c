#include "inc/beh2/ert_main.h"

#define NUM_EVENTS 8

typedef enum pinMode {
	RISING, FALLING, EITHER
} pinMode;

typedef struct EventPin {
	boolean value_; 								/* Previous value */
	boolean value; 									/* Current value */
	boolean triggered; 								/* Whether a valid transition has occurred */
	pinMode edge;
} EventPin;

EventPin queue[NUM_EVENTS];

void rt_Init (unsigned int* hmst, unsigned int* mode, unsigned int* sel, boolean* alarmDrv) {

	/* Store pointers */

	Hmst = hmst;
	Mode = mode;
	Sel = sel;
	Alarm = alarmDrv;

	/* Initialize queue */

	unsigned int i;
	for (i=0; i<NUM_EVENTS; i++) {
		queue[i].value_ = false;
		queue[i].triggered = false;
	}

	queue[0].edge = EITHER;
	queue[1].edge = RISING;
	queue[2].edge = RISING;
	queue[3].edge = RISING;
	queue[4].edge = RISING;
	queue[5].edge = RISING;
	queue[6].edge = RISING;
	queue[7].edge = RISING;

	/* Initialize state machine */

	initSM();

}

void rt_OneStep (const boolean plus, const boolean minus, const boolean time, const boolean timeset, const boolean alarm, const boolean stopwatch, const boolean clock, const boolean alarmSrv) {

	/* Incoming events are ordered by priority in the event queue; this is not
	 * fully compliant with Stateflow semantics, where event priority is defined
	 * "internally" and not "externally"
	 */

	queue[0].value = clock;
	queue[1].value = alarmSrv;
	queue[2].value = time;
	queue[3].value = timeset;
	queue[4].value = alarm;
	queue[5].value = stopwatch;
	queue[6].value = plus;
	queue[7].value = minus;

	/* Evaluate edge occurrences and dispatch occurred events to state machine,
	 * in the appropriate order
	 */

	unsigned int i;
	for (i=0; i<NUM_EVENTS; i++) {
		if (queue[i].edge==RISING || queue[i].edge==EITHER) {
			if (queue[i].value_==false && queue[i].value==true) queue[i].triggered = true;
		}
		if (queue[i].edge==FALLING || queue[i].edge==EITHER) {
			if (queue[i].value_==true && queue[i].value==false) queue[i].triggered = true;
		}
		if (queue[i].triggered) dispatchSM(i);
		queue[i].value_ = queue[i].value;
		queue[i].triggered = false;
	}

}
