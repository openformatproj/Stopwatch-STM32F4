/* Wrapper for MATLAB state machine
 * Last revision: 03-12-2016
 */

#ifndef ERT_MAIN_H
#define ERT_MAIN_H

#include "behavior.h"

extern RT_MODEL_WatchBehavior_T WatchBehavior_M_;
extern RT_MODEL_WatchBehavior_T *const WatchBehavior_M;
extern B_WatchBehavior_T WatchBehavior_B;
extern DW_WatchBehavior_T WatchBehavior_DW;
extern PrevZCX_WatchBehavior_T WatchBehavior_PrevZCX;

/* '<Root>/plus' */
extern boolean_T WatchBehavior_U_plus;

/* '<Root>/minus' */
extern boolean_T WatchBehavior_U_minus;

/* '<Root>/time' */
extern boolean_T WatchBehavior_U_time;

/* '<Root>/timeset' */
extern boolean_T WatchBehavior_U_timeset;

/* '<Root>/alarm' */
extern boolean_T WatchBehavior_U_alarm;

/* '<Root>/stopwatch' */
extern boolean_T WatchBehavior_U_stopwatch;

/* '<Root>/clock' */
extern boolean_T WatchBehavior_U_clock;

/* '<Root>/alarmSrv' */
extern boolean_T WatchBehavior_U_alarmSrv;

/* '<Root>/hours' */
extern uint8_T WatchBehavior_Y_hours;

/* '<Root>/minutes' */
extern uint8_T WatchBehavior_Y_minutes;

/* '<Root>/seconds' */
extern uint8_T WatchBehavior_Y_seconds;

/* '<Root>/tenths' */
extern uint8_T WatchBehavior_Y_tenths;

/* '<Root>/mode' */
extern uint8_T WatchBehavior_Y_mode;

/* '<Root>/sel' */
extern uint8_T WatchBehavior_Y_sel;

/* '<Root>/alarmDrv' */
extern boolean_T WatchBehavior_Y_alarmDrv;

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */

void rt_OneStep(RT_MODEL_WatchBehavior_T *const WatchBehavior_M);

#endif
