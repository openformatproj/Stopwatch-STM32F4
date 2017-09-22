/*
 * Behavioral model of stopwatch. Handwritten using the SLIM pseudo-language (SLIM.h library)
 * Author: Alessandro Trifoglio
 */

#include "inc/beh2/behavior.h"
#include "inc/beh2/SLIM.h"

typedef enum tickMode {
	INCREMENT, DECREMENT
} tickMode;

typedef enum digitGroup {
	HOURS, MINUTES, SECONDS, TENTHS, NONE
} digitGroup;

/* ----------------------------------------------------------------------------- States ----------------------------------------------------------------------------- */

enum StateId {
	OPERATIONMODES, ALARMDRV, TIMEMODE, TIMESETMODE, ALARMMODE, STOPWATCHMODE, TIMESETMODEDISARMED, TIMESETMODEARMED, ALARMMODEDISARMED, ALARMMODEARMED, STOPWATCHMODESTARTUP, STOPWATCHMODESTOPPED, STOPWATCHMODERUNNING, UNSETMODE, SETMODE
};

State /*
*/	operationModes, alarmDrv, timeMode, timesetMode, alarmMode, stopwatchMode, timesetModeDisarmed, timesetModeArmed, alarmModeDisarmed, alarmModeArmed, stopwatchModeStartup, stopwatchModeStopped, stopwatchModeRunning, unsetMode, setMode;

/* ----------------------------------------------------------------------------- Events ----------------------------------------------------------------------------- */

enum Event {
	clock, alarmSrv, time, timeset, alarm, stopwatch, plus, minus, setAlarm, unsetAlarm
};

/* ----------------------------------------------------------------------------  Actions ---------------------------------------------------------------------------- */

/* Local variables */

unsigned int hmstTime[4] = {0, 0, 0, 0};
unsigned int hmstSet[2] = {0, 0};
unsigned int hmstAlarm[2] = {0, 0};
unsigned int hmstSw[4] = {0, 0, 0, 0};
boolean set = false;

/* Local functions */

boolean alarmReached () {
	return (hmstTime[HOURS]==hmstAlarm[HOURS] && hmstTime[MINUTES]==hmstAlarm[MINUTES] && hmstTime[SECONDS]==0 && hmstTime[TENTHS]==0);
}

unsigned int mod(const int a, const unsigned int b) {
	if (a==0) return 0;
	if (a>0) return a%b;
	if (a<0) {
		unsigned int rem = (-a)%b;
		if (rem!=0) return b - rem;
		else return 0;
	}
}

void hmstTick(const tickMode mode, digitGroup sel, unsigned int* hmst, unsigned int sz) {

	unsigned int hmst_padded[4] = {0, 0, 0, 0};

	unsigned int i;
	for (i=0; i<sz; i++) {
		hmst_padded[i] = hmst[i];
	}

	if (mode==INCREMENT) {

		if (sel==TENTHS) {
			hmst[TENTHS] = mod(hmst_padded[TENTHS]+1,10);
			if (hmst_padded[TENTHS]==9) {
				sel=sel-1;
			}
		}

		if (sel==SECONDS) {
			hmst[SECONDS] = mod(hmst_padded[SECONDS]+1,60);
			if (hmst_padded[SECONDS]==59) {
				sel=sel-1;
			}
		}

		if (sel==MINUTES) {
			hmst[MINUTES] = mod(hmst_padded[MINUTES]+1,60);
			if (hmst_padded[MINUTES]==59) {
				sel=sel-1;
			}
		}

		if (sel==HOURS) {
			hmst[HOURS] = mod(hmst_padded[HOURS]+1,24);
		}

	}

	else if (mode==DECREMENT) {

		if (sel==TENTHS) {
        	hmst[TENTHS] = mod(hmst_padded[TENTHS]-1,10);
            if (hmst_padded[TENTHS]==0) {
                sel=sel-1;
            }
        }

        if (sel==SECONDS) {
        	hmst[SECONDS] = mod(hmst_padded[SECONDS]-1,60);
            if (hmst_padded[SECONDS]==0) {
                sel=sel-1;
            }
        }

        if (sel==MINUTES) {
        	hmst[MINUTES] = mod(hmst_padded[MINUTES]-1,60);
            if (hmst_padded[MINUTES]==0) {
                sel=sel-1;
            }
        }

        if (sel==HOURS) {
        	hmst[HOURS] = mod(hmst_padded[HOURS]-1,24);
        }

	}

}

void writeSelector (const digitGroup sel) {
	switch (sel) {
		case NONE:
			*Sel = 0;
			break;
		case HOURS:
			*Sel = 1;
			break;
		case MINUTES:
			*Sel = 2;
			break;
		case SECONDS:
			*Sel = 3;
			break;
		case TENTHS:
			*Sel = 4;
			break;
		default:
			break;
	}
}

digitGroup readSelector() {
	switch (*Sel) {
		case 0:
			return NONE;
			break;
		case 1:
			return HOURS;
			break;
		case 2:
			return MINUTES;
			break;
		case 3:
			return SECONDS;
			break;
		case 4:
			return TENTHS;
			break;
		default:
			break;
	}
}

/* Definitions */

void timeModeEntry () {
	*Mode = 0;
	writeSelector(NONE);
}

void timesetModeEntry () {
	*Mode = 1;
	writeSelector(MINUTES);
}

void alarmModeEntry () {
	*Mode = 2;
	writeSelector(MINUTES);
}

void stopwatchModeEntry () {
	*Mode = 3;
	writeSelector(NONE);
}

void timesetModeDisarmedEntry () {
	hmstSet[HOURS] = hmstTime[HOURS];
	hmstSet[MINUTES] = hmstTime[MINUTES];
	Hmst[HOURS] = hmstSet[HOURS];
	Hmst[MINUTES] = hmstSet[MINUTES];
	Hmst[SECONDS] = 0;
	Hmst[TENTHS] = 0;
}

void timesetModeArmedExit () {
	hmstTime[HOURS] = hmstSet[HOURS];
	hmstTime[MINUTES] = hmstSet[MINUTES];
	hmstTime[SECONDS] = 0;
	hmstTime[TENTHS] = 0;
}

void alarmModeDisarmedEntry () {
	Hmst[HOURS] = hmstAlarm[HOURS];
	Hmst[MINUTES] = hmstAlarm[MINUTES];
	Hmst[SECONDS] = 0;
	Hmst[TENTHS] = 0;
	set = false;
}

void alarmModeArmedExit () {
	set = true;
	SEND (setAlarm, &alarmDrv);
}

void stopwatchModeStartupEntry () {
	hmstSw[HOURS] = hmstTime[HOURS];
	hmstSw[MINUTES] = hmstTime[MINUTES];
	hmstSw[SECONDS] = hmstTime[SECONDS];
	hmstSw[TENTHS] = hmstTime[TENTHS];
	Hmst[HOURS] = hmstSw[HOURS];
	Hmst[MINUTES] = hmstSw[MINUTES];
	Hmst[SECONDS] = hmstSw[SECONDS];
	Hmst[TENTHS] = hmstSw[TENTHS];
}

void stopwatchModeStoppedEntry () {
	writeSelector(TENTHS);
}

void stopwatchModeRunningEntry () {
	writeSelector(NONE);
}

void unsetModeEntry () {
	*Alarm = false;
}

void timeIncr () {
	hmstTick (INCREMENT, TENTHS, hmstTime, 4);
}

void timeIncrShow () {
	timeIncr();
	Hmst[HOURS] = hmstTime[HOURS];
	Hmst[MINUTES] = hmstTime[MINUTES];
	Hmst[SECONDS] = hmstTime[SECONDS];
	Hmst[TENTHS] = hmstTime[TENTHS];
}

void timeSetIncr () {
	hmstTick (INCREMENT, readSelector(), hmstSet, 2);
	Hmst[HOURS] = hmstSet[HOURS];
	Hmst[MINUTES] = hmstSet[MINUTES];
	Hmst[SECONDS] = 0;
	Hmst[TENTHS] = 0;
}

void timeSetDecr () {
	hmstTick (DECREMENT, readSelector(), hmstSet, 2);
	Hmst[HOURS] = hmstSet[HOURS];
	Hmst[MINUTES] = hmstSet[MINUTES];
	Hmst[SECONDS] = 0;
	Hmst[TENTHS] = 0;
}

void timeAlarmIncr () {
	hmstTick (INCREMENT, readSelector(), hmstAlarm, 2);
	Hmst[HOURS] = hmstAlarm[HOURS];
	Hmst[MINUTES] = hmstAlarm[MINUTES];
	Hmst[SECONDS] = 0;
	Hmst[TENTHS] = 0;
}

void timeAlarmDecr () {
	hmstTick (DECREMENT, readSelector(), hmstAlarm, 2);
	Hmst[HOURS] = hmstAlarm[HOURS];
	Hmst[MINUTES] = hmstAlarm[MINUTES];
	Hmst[SECONDS] = 0;
	Hmst[TENTHS] = 0;
}

void switchSel () {
	if (readSelector()==MINUTES) writeSelector(HOURS);
	else if (readSelector()==HOURS) writeSelector(MINUTES);
}

void timeStopwatchZero () {
	hmstSw[HOURS] = 0;
	hmstSw[MINUTES] = 0;
	hmstSw[SECONDS] = 0;
	hmstSw[TENTHS] = 0;
	Hmst[HOURS] = hmstSw[HOURS];
	Hmst[MINUTES] = hmstSw[MINUTES];
	Hmst[SECONDS] = hmstSw[SECONDS];
	Hmst[TENTHS] = hmstSw[TENTHS];
}

void timeStopwatchIncr () {
	hmstTick (INCREMENT, readSelector(), hmstSw, 4);
	Hmst[HOURS] = hmstSw[HOURS];
	Hmst[MINUTES] = hmstSw[MINUTES];
	Hmst[SECONDS] = hmstSw[SECONDS];
	Hmst[TENTHS] = hmstSw[TENTHS];
}

void timeStopwatchDecr () {
	hmstTick (DECREMENT, readSelector(), hmstSw, 4);
	Hmst[HOURS] = hmstSw[HOURS];
	Hmst[MINUTES] = hmstSw[MINUTES];
	Hmst[SECONDS] = hmstSw[SECONDS];
	Hmst[TENTHS] = hmstSw[TENTHS];
}

void timeStopwatchStepIncr () {
	hmstTick (INCREMENT, TENTHS, hmstSw, 4);
	Hmst[HOURS] = hmstSw[HOURS];
	Hmst[MINUTES] = hmstSw[MINUTES];
	Hmst[SECONDS] = hmstSw[SECONDS];
	Hmst[TENTHS] = hmstSw[TENTHS];
}

void triggerAlarm () {
	*Alarm = true;
}

void dismissAlarm () {
	SEND (unsetAlarm, &alarmDrv);
}

/* ------------------------- Init state machine: fill states' attributes and force each of them to its initial state (only not leaf states) ------------------------- */

void initSM () {

	operationModes.id = OPERATIONMODES;
	operationModes.parent = NULL;
	operationModes.isLeaf = false;
	operationModes.hasHistory = false;
	operationModes.entryAction = &voidAction;
	operationModes.exitAction = &voidAction;
	operationModes.action_o = &voidAction;
	operationModes.state_o = &timeMode;

	alarmDrv.id = ALARMDRV;
	alarmDrv.parent = NULL;
	alarmDrv.isLeaf = false;
	alarmDrv.hasHistory = false;
	alarmDrv.entryAction = &voidAction;
	alarmDrv.exitAction = &voidAction;
	alarmDrv.action_o = &voidAction;
	alarmDrv.state_o = &unsetMode;

	timeMode.id = TIMEMODE;
	timeMode.parent = &operationModes;
	timeMode.isLeaf = true;
	timeMode.hasHistory = false;
	timeMode.entryAction = &timeModeEntry;
	timeMode.exitAction = &voidAction;
	timeMode.action_o = NULL;
	timeMode.state_o = NULL;

	timesetMode.id = TIMESETMODE;
	timesetMode.parent = &operationModes;
	timesetMode.isLeaf = false;
	timesetMode.hasHistory = false;
	timesetMode.entryAction = &timesetModeEntry;
	timesetMode.exitAction = &voidAction;
	timesetMode.action_o = &voidAction;
	timesetMode.state_o = &timesetModeDisarmed;

	alarmMode.id = ALARMMODE;
	alarmMode.parent = &operationModes;
	alarmMode.isLeaf = false;
	alarmMode.hasHistory = true;
	alarmMode.entryAction = &alarmModeEntry;
	alarmMode.exitAction = &voidAction;
	alarmMode.action_o = &voidAction;
	alarmMode.state_o = &alarmModeDisarmed;

	stopwatchMode.id = STOPWATCHMODE;
	stopwatchMode.parent = &operationModes;
	stopwatchMode.isLeaf = false;
	stopwatchMode.hasHistory = false;
	stopwatchMode.entryAction = &stopwatchModeEntry;
	stopwatchMode.exitAction = &voidAction;
	stopwatchMode.action_o = &voidAction;
	stopwatchMode.state_o = &stopwatchModeStartup;

	timesetModeDisarmed.id = TIMESETMODEDISARMED;
	timesetModeDisarmed.parent = &timesetMode;
	timesetModeDisarmed.isLeaf = true;
	timesetModeDisarmed.hasHistory = false;
	timesetModeDisarmed.entryAction = &timesetModeDisarmedEntry;
	timesetModeDisarmed.exitAction = &voidAction;
	timesetModeDisarmed.action_o = NULL;
	timesetModeDisarmed.state_o = NULL;

	timesetModeArmed.id = TIMESETMODEARMED;
	timesetModeArmed.parent = &timesetMode;
	timesetModeArmed.isLeaf = true;
	timesetModeArmed.hasHistory = false;
	timesetModeArmed.entryAction = &voidAction;
	timesetModeArmed.exitAction = &timesetModeArmedExit;
	timesetModeArmed.action_o = NULL;
	timesetModeArmed.state_o = NULL;

	alarmModeDisarmed.id = ALARMMODEDISARMED;
	alarmModeDisarmed.parent = &alarmMode;
	alarmModeDisarmed.isLeaf = true;
	alarmModeDisarmed.hasHistory = false;
	alarmModeDisarmed.entryAction = &alarmModeDisarmedEntry;
	alarmModeDisarmed.exitAction = &voidAction;
	alarmModeDisarmed.action_o = NULL;
	alarmModeDisarmed.state_o = NULL;

	alarmModeArmed.id = ALARMMODEARMED;
	alarmModeArmed.parent = &alarmMode;
	alarmModeArmed.isLeaf = true;
	alarmModeArmed.hasHistory = false;
	alarmModeArmed.entryAction = &voidAction;
	alarmModeArmed.exitAction = &alarmModeArmedExit;
	alarmModeArmed.action_o = NULL;
	alarmModeArmed.state_o = NULL;

	stopwatchModeStartup.id = STOPWATCHMODESTARTUP;
	stopwatchModeStartup.parent = &stopwatchMode;
	stopwatchModeStartup.isLeaf = true;
	stopwatchModeStartup.hasHistory = false;
	stopwatchModeStartup.entryAction = &stopwatchModeStartupEntry;
	stopwatchModeStartup.exitAction = &voidAction;
	stopwatchModeStartup.action_o = NULL;
	stopwatchModeStartup.state_o = NULL;

	stopwatchModeStopped.id = STOPWATCHMODESTOPPED;
	stopwatchModeStopped.parent = &stopwatchMode;
	stopwatchModeStopped.isLeaf = true;
	stopwatchModeStopped.hasHistory = false;
	stopwatchModeStopped.entryAction = &stopwatchModeStoppedEntry;
	stopwatchModeStopped.exitAction = &voidAction;
	stopwatchModeStopped.action_o = NULL;
	stopwatchModeStopped.state_o = NULL;

	stopwatchModeRunning.id = STOPWATCHMODERUNNING;
	stopwatchModeRunning.parent = &stopwatchMode;
	stopwatchModeRunning.isLeaf = true;
	stopwatchModeRunning.hasHistory = false;
	stopwatchModeRunning.entryAction = &stopwatchModeRunningEntry;
	stopwatchModeRunning.exitAction = &voidAction;
	stopwatchModeRunning.action_o = NULL;
	stopwatchModeRunning.state_o = NULL;

	unsetMode.id = UNSETMODE;
	unsetMode.parent = &alarmDrv;
	unsetMode.isLeaf = true;
	unsetMode.hasHistory = false;
	unsetMode.entryAction = &unsetModeEntry;
	unsetMode.exitAction = &voidAction;
	unsetMode.action_o = NULL;
	unsetMode.state_o = NULL;

	setMode.id = SETMODE;
	setMode.parent = &alarmDrv;
	setMode.isLeaf = true;
	setMode.hasHistory = false;
	setMode.entryAction = &voidAction;
	setMode.exitAction = &voidAction;
	setMode.action_o = NULL;
	setMode.state_o = NULL;

	init (&operationModes);
	init (&alarmDrv);
	init (&timesetMode);
	init (&alarmMode);
	init (&stopwatchMode);

}

/* Dispatch service (state machine description) in SLIM pseudo-language
 * Model:

	START_SM
		START_HIERARCHICAL (STATE_UP1)
			START_STATE (STATE_1)
				WHEN (event_1) IF (x==0) UPDATE_TO (&state_2, EXTERNAL, &act_1)
				WHEN (event_2) ALWAYS UPDATE_TO (&state_3, EXTERNAL, &act_2)
			END_STATE
			START_STATE (STATE_2)
				WHEN (event_1) ALWAYS UPDATE_TO (&state_4, EXTERNAL, &act_3)
			END_STATE
		END_HIERARCHICAL;
		START_HIERARCHICAL (STATE_UP2)
			START_STATE (STATE_7)
				WHEN (event_1) IF (x<0) UPDATE_TO (&state_8, EXTERNAL, &act_7)
				WHEN (event_2) ALWAYS UPDATE_TO (&state_9, EXTERNAL, &act_8)
			END_STATE
			START_STATE (STATE_8)
				WHEN (event_1) ALWAYS UPDATE_TO (&state_9, EXTERNAL, &act_9)
			END_STATE
		END_HIERARCHICAL;
	END_SM

 */

START_SM
	START_HIERARCHICAL (OPERATIONMODES)
		START_STATE (TIMEMODE)
			WHEN (clock) ALWAYS UPDATE_TO (&timeMode, INTERNAL, &timeIncrShow)
			WHEN (timeset) ALWAYS UPDATE_TO (&timesetMode, EXTERNAL, &voidAction)
			WHEN (alarm) ALWAYS UPDATE_TO (&alarmMode, EXTERNAL, &voidAction)
			WHEN (stopwatch) ALWAYS UPDATE_TO (&stopwatchMode, EXTERNAL, &voidAction)
		END_STATE
		START_STATE (TIMESETMODE)
			WHEN (clock) ALWAYS UPDATE_TO (&timesetMode, INTERNAL, &timeIncr)
			WHEN (time) ALWAYS UPDATE_TO (&timeMode, EXTERNAL, &voidAction)
			WHEN (alarm) ALWAYS UPDATE_TO (&alarmMode, EXTERNAL, &voidAction)
			WHEN (stopwatch) ALWAYS UPDATE_TO (&stopwatchMode, EXTERNAL, &voidAction)
		END_STATE
		START_STATE (ALARMMODE)
			WHEN (clock) ALWAYS UPDATE_TO (&alarmMode, INTERNAL, &timeIncr)
			WHEN (time) ALWAYS UPDATE_TO (&timeMode, EXTERNAL, &voidAction)
			WHEN (timeset) ALWAYS UPDATE_TO (&timesetMode, EXTERNAL, &voidAction)
			WHEN (stopwatch) ALWAYS UPDATE_TO (&stopwatchMode, EXTERNAL, &voidAction)
		END_STATE
		START_STATE (STOPWATCHMODE)
			WHEN (clock) ALWAYS UPDATE_TO (&stopwatchMode, INTERNAL, &timeIncr)
			WHEN (time) ALWAYS UPDATE_TO (&timeMode, EXTERNAL, &voidAction)
			WHEN (timeset) ALWAYS UPDATE_TO (&timesetMode, EXTERNAL, &voidAction)
			WHEN (alarm) ALWAYS UPDATE_TO (&alarmMode, EXTERNAL, &voidAction)
		END_STATE
	END_HIERARCHICAL
	START_HIERARCHICAL (ALARMDRV)
		START_STATE (UNSETMODE)
			WHEN (setAlarm) ALWAYS UPDATE_TO (&setMode, EXTERNAL, &voidAction)
		END_STATE
		START_STATE (SETMODE)
			WHEN (unsetAlarm) ALWAYS UPDATE_TO (&unsetMode, EXTERNAL, &voidAction)
			WHEN (clock) IF(*Mode==0 && alarmReached()) UPDATE_TO (&setMode, INTERNAL, &triggerAlarm)
		END_STATE
	END_HIERARCHICAL
	START_HIERARCHICAL (TIMESETMODE)
		START_STATE (TIMESETMODEDISARMED)
			WHEN (plus) ALWAYS UPDATE_TO (&timesetModeArmed, EXTERNAL, &timeSetIncr)
			WHEN (minus) ALWAYS UPDATE_TO (&timesetModeArmed, EXTERNAL, &timeSetDecr)
			WHEN (timeset) ALWAYS UPDATE_TO (&timesetModeDisarmed, INTERNAL, &switchSel)
		END_STATE
		START_STATE (TIMESETMODEARMED)
			WHEN (plus) ALWAYS UPDATE_TO (&timesetModeArmed, INTERNAL, &timeSetIncr)
			WHEN (minus) ALWAYS UPDATE_TO (&timesetModeArmed, INTERNAL, &timeSetDecr)
			WHEN (timeset) ALWAYS UPDATE_TO (&timesetModeArmed, INTERNAL, &switchSel)
		END_STATE
	END_HIERARCHICAL
	START_HIERARCHICAL (ALARMMODE)
		START_STATE (ALARMMODEDISARMED)
			WHEN (plus) ALWAYS UPDATE_TO (&alarmModeArmed, EXTERNAL, &timeAlarmIncr)
			WHEN (minus) ALWAYS UPDATE_TO (&alarmModeArmed, EXTERNAL, &timeAlarmDecr)
			WHEN (alarm) ALWAYS UPDATE_TO (&alarmModeDisarmed, INTERNAL, &switchSel)
		END_STATE
		START_STATE (ALARMMODEARMED)
			WHEN (plus) ALWAYS UPDATE_TO (&alarmModeArmed, INTERNAL, &timeAlarmIncr)
			WHEN (minus) ALWAYS UPDATE_TO (&alarmModeArmed, INTERNAL, &timeAlarmDecr)
			WHEN (alarm) ALWAYS UPDATE_TO (&alarmModeArmed, INTERNAL, &switchSel)
			WHEN (clock) IF (set) UPDATE_TO (&alarmModeDisarmed, EXTERNAL, &dismissAlarm)
		END_STATE
	END_HIERARCHICAL
	START_HIERARCHICAL (STOPWATCHMODE)
		START_STATE (STOPWATCHMODESTARTUP)
			WHEN (stopwatch) ALWAYS UPDATE_TO (&stopwatchModeStopped, EXTERNAL, &timeStopwatchZero)
		END_STATE
		START_STATE (STOPWATCHMODESTOPPED)
			WHEN (plus) ALWAYS UPDATE_TO (&stopwatchModeStopped, INTERNAL, &timeStopwatchIncr)
			WHEN (minus) ALWAYS UPDATE_TO (&stopwatchModeStopped, INTERNAL, &timeStopwatchDecr)
			WHEN (stopwatch) ALWAYS UPDATE_TO (&stopwatchModeRunning, EXTERNAL, &voidAction)
		END_STATE
		START_STATE (STOPWATCHMODERUNNING)
			WHEN (clock) ALWAYS UPDATE_TO (&stopwatchModeRunning, INTERNAL, &timeStopwatchStepIncr)
			WHEN (stopwatch) ALWAYS UPDATE_TO (&stopwatchModeStopped, EXTERNAL, &voidAction)
		END_STATE
	END_HIERARCHICAL
END_SM

/* ---------------------------------------------------------------- Dispatch events to state machine ---------------------------------------------------------------- */

void dispatchSM (const unsigned int i) {

	dispatch (&operationModes, i);
	dispatch (&alarmDrv, i);
	
}
