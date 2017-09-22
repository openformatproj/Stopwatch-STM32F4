/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: WatchBehavior.h
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

#ifndef RTW_HEADER_WatchBehavior_h_
#define RTW_HEADER_WatchBehavior_h_
#ifndef WatchBehavior_COMMON_INCLUDES_
# define WatchBehavior_COMMON_INCLUDES_
#include "zero_crossing_types.h"
#endif                                 /* WatchBehavior_COMMON_INCLUDES_ */

#include "behavior_types.h"
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  uint8_T HMST[4];                     /* '<S1>/StateMachine' */
} B_WatchBehavior_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  int32_T sfEvent;                     /* '<S1>/StateMachine' */
  uint8_T is_c1_WatchBehavior;         /* '<S1>/StateMachine' */
  uint8_T is_operationModes;           /* '<S1>/StateMachine' */
  uint8_T is_active_operationModes;    /* '<S1>/StateMachine' */
  uint8_T is_modes;                    /* '<S1>/StateMachine' */
  uint8_T is_active_modes;             /* '<S1>/StateMachine' */
  uint8_T is_selection;                /* '<S1>/StateMachine' */
  uint8_T is_active_selection;         /* '<S1>/StateMachine' */
  uint8_T is_modes_g;                  /* '<S1>/StateMachine' */
  uint8_T was_modes;                   /* '<S1>/StateMachine' */
  uint8_T is_active_modes_b;           /* '<S1>/StateMachine' */
  uint8_T is_selection_m;              /* '<S1>/StateMachine' */
  uint8_T is_active_selection_n;       /* '<S1>/StateMachine' */
  uint8_T is_stopwatch;                /* '<S1>/StateMachine' */
  uint8_T is_alarmDrv;                 /* '<S1>/StateMachine' */
  uint8_T is_active_alarmDrv;          /* '<S1>/StateMachine' */
  uint8_T hmstAlarm[2];                /* '<S1>/StateMachine' */
  uint8_T hmst[4];                     /* '<S1>/StateMachine' */
  uint8_T hmstSet[2];                  /* '<S1>/StateMachine' */
  uint8_T hmstSw[4];                   /* '<S1>/StateMachine' */
  boolean_T set;                       /* '<S1>/StateMachine' */
} DW_WatchBehavior_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState StateMachine_Trig_ZCE[8]; /* '<S1>/StateMachine' */
} PrevZCX_WatchBehavior_T;

/* Real-time Model Data Structure */
struct tag_RTM_WatchBehavior_T {
  const char_T * volatile errorStatus;
  B_WatchBehavior_T *blockIO;
  PrevZCX_WatchBehavior_T *prevZCSigState;
  DW_WatchBehavior_T *dwork;
};

/* Model entry point functions */
extern void WatchBehavior_initialize(RT_MODEL_WatchBehavior_T *const
  WatchBehavior_M, boolean_T *WatchBehavior_U_plus, boolean_T
  *WatchBehavior_U_minus, boolean_T *WatchBehavior_U_time, boolean_T
  *WatchBehavior_U_timeset, boolean_T *WatchBehavior_U_alarm, boolean_T
  *WatchBehavior_U_stopwatch, boolean_T *WatchBehavior_U_clock, boolean_T
  *WatchBehavior_U_alarmSrv, uint8_T *WatchBehavior_Y_hours, uint8_T
  *WatchBehavior_Y_minutes, uint8_T *WatchBehavior_Y_seconds, uint8_T
  *WatchBehavior_Y_tenths, uint8_T *WatchBehavior_Y_mode, uint8_T
  *WatchBehavior_Y_sel, boolean_T *WatchBehavior_Y_alarmDrv);
extern void WatchBehavior_step(RT_MODEL_WatchBehavior_T *const WatchBehavior_M,
  boolean_T WatchBehavior_U_plus, boolean_T WatchBehavior_U_minus, boolean_T
  WatchBehavior_U_time, boolean_T WatchBehavior_U_timeset, boolean_T
  WatchBehavior_U_alarm, boolean_T WatchBehavior_U_stopwatch, boolean_T
  WatchBehavior_U_clock, boolean_T WatchBehavior_U_alarmSrv, uint8_T
  *WatchBehavior_Y_hours, uint8_T *WatchBehavior_Y_minutes, uint8_T
  *WatchBehavior_Y_seconds, uint8_T *WatchBehavior_Y_tenths, uint8_T
  *WatchBehavior_Y_mode, uint8_T *WatchBehavior_Y_sel, boolean_T
  *WatchBehavior_Y_alarmDrv);
extern void WatchBehavior_terminate(RT_MODEL_WatchBehavior_T *const
  WatchBehavior_M);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('MatlabWatch2016/WatchBehavior')    - opens subsystem MatlabWatch2016/WatchBehavior
 * hilite_system('MatlabWatch2016/WatchBehavior/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'MatlabWatch2016'
 * '<S1>'   : 'MatlabWatch2016/WatchBehavior'
 * '<S2>'   : 'MatlabWatch2016/WatchBehavior/StateMachine'
 */
#endif                                 /* RTW_HEADER_WatchBehavior_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
