/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
 *
 * Code generated for Simulink model 'WatchBehavior'.
 *
 * Model version                  : 1.354
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Sun Jan 29 22:20:58 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
/*
 * ert_main.c has been divided into two separate files: this one and ert_main.h. These files contain the interface
 * of behavioral model; the other files have not been modified
 */

#include "inc/beh1/ert_main.h"                                                       /* Model's header file (wrapper) */

RT_MODEL_WatchBehavior_T WatchBehavior_M_;
RT_MODEL_WatchBehavior_T *const WatchBehavior_M = &WatchBehavior_M_;            /* Real-time model */
B_WatchBehavior_T WatchBehavior_B;                                              /* Observable signals */
DW_WatchBehavior_T WatchBehavior_DW;                                            /* Observable states */
PrevZCX_WatchBehavior_T WatchBehavior_PrevZCX;                                  /* Triggered events */

/* '<Root>/plus' */
boolean_T WatchBehavior_U_plus;

/* '<Root>/minus' */
boolean_T WatchBehavior_U_minus;

/* '<Root>/time' */
boolean_T WatchBehavior_U_time;

/* '<Root>/timeset' */
boolean_T WatchBehavior_U_timeset;

/* '<Root>/alarm' */
boolean_T WatchBehavior_U_alarm;

/* '<Root>/stopwatch' */
boolean_T WatchBehavior_U_stopwatch;

/* '<Root>/clock' */
boolean_T WatchBehavior_U_clock;

/* '<Root>/alarmSrv' */
boolean_T WatchBehavior_U_alarmSrv;

/* '<Root>/hours' */
uint8_T WatchBehavior_Y_hours;

/* '<Root>/minutes' */
uint8_T WatchBehavior_Y_minutes;

/* '<Root>/seconds' */
uint8_T WatchBehavior_Y_seconds;

/* '<Root>/tenths' */
uint8_T WatchBehavior_Y_tenths;

/* '<Root>/mode' */
uint8_T WatchBehavior_Y_mode;

/* '<Root>/sel' */
uint8_T WatchBehavior_Y_sel;

/* '<Root>/alarmDrv' */
boolean_T WatchBehavior_Y_alarmDrv;

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

void rt_OneStep(RT_MODEL_WatchBehavior_T *const WatchBehavior_M)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(WatchBehavior_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  WatchBehavior_step(WatchBehavior_M, WatchBehavior_U_plus,
                     WatchBehavior_U_minus, WatchBehavior_U_time,
                     WatchBehavior_U_timeset, WatchBehavior_U_alarm,
                     WatchBehavior_U_stopwatch, WatchBehavior_U_clock,
                     WatchBehavior_U_alarmSrv, &WatchBehavior_Y_hours,
                     &WatchBehavior_Y_minutes, &WatchBehavior_Y_seconds,
                     &WatchBehavior_Y_tenths, &WatchBehavior_Y_mode,
                     &WatchBehavior_Y_sel, &WatchBehavior_Y_alarmDrv);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
