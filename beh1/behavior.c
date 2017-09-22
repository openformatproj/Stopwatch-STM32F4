/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: WatchBehavior.c
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

#include "inc/beh1/behavior.h"
#include "inc/beh1/behavior_private.h"

/* Named constants for Chart: '<S1>/StateMachine' */
#define WatchBehavior_CALL_EVENT       (-1)
#define WatchBehavior_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define WatchBehavior_IN_active        ((uint8_T)1U)
#define WatchBehavior_IN_alarm         ((uint8_T)1U)
#define WatchBehavior_IN_armed         ((uint8_T)1U)
#define WatchBehavior_IN_disarmed      ((uint8_T)2U)
#define WatchBehavior_IN_hours         ((uint8_T)1U)
#define WatchBehavior_IN_minutes       ((uint8_T)2U)
#define WatchBehavior_IN_running       ((uint8_T)1U)
#define WatchBehavior_IN_set           ((uint8_T)1U)
#define WatchBehavior_IN_startup       ((uint8_T)2U)
#define WatchBehavior_IN_stopped       ((uint8_T)3U)
#define WatchBehavior_IN_stopwatch     ((uint8_T)2U)
#define WatchBehavior_IN_time          ((uint8_T)3U)
#define WatchBehavior_IN_timeset       ((uint8_T)4U)
#define WatchBehavior_IN_unset         ((uint8_T)2U)
#define WatchBehavior_event_alarm      (8)
#define WatchBehavior_event_arm        (2)
#define WatchBehavior_event_arm_p      (3)
#define WatchBehavior_event_clock      (10)
#define WatchBehavior_event_minus      (5)
#define WatchBehavior_event_plus       (4)
#define WatchBehavior_event_servedAlarm (11)
#define WatchBehavior_event_setAlarm   (0)
#define WatchBehavior_event_stopwatch  (9)
#define WatchBehavior_event_time       (6)
#define WatchBehavior_event_timeset    (7)
#define WatchBehavior_event_unsetAlarm (1)

/* Forward declaration for local functions */
static void WatchBehavior_hmstTick(real_T cmd, real_T sel, const uint8_T hmst[4],
  uint8_T HMST[4]);
static void WatchBehavior_hmstTick_k(real_T cmd, uint8_T sel, const uint8_T
  hmst[2], uint8_T HMST[2]);
static void WatchBehavior_broadcast_arm_n(uint8_T *WatchBehavior_Y_mode, uint8_T
  *WatchBehavior_Y_sel, boolean_T *WatchBehavior_Y_alarmDrv, B_WatchBehavior_T
  *WatchBehavior_B, DW_WatchBehavior_T *WatchBehavior_DW);
static boolean_T WatchBehavior_triggerAlarmCond(uint8_T *WatchBehavior_Y_mode,
  DW_WatchBehavior_T *WatchBehavior_DW);
static void WatchBehavior_alarmDrv(uint8_T *WatchBehavior_Y_mode, boolean_T
  *WatchBehavior_Y_alarmDrv, DW_WatchBehavior_T *WatchBehavior_DW);
static void WatchBehavior_modes_d(uint8_T *WatchBehavior_Y_mode, uint8_T
  *WatchBehavior_Y_sel, boolean_T *WatchBehavior_Y_alarmDrv, B_WatchBehavior_T
  *WatchBehavior_B, DW_WatchBehavior_T *WatchBehavior_DW);
static void WatchBehavior_hmstTick_k4(real_T cmd, uint8_T sel, const uint8_T
  hmst[4], uint8_T HMST[4]);
static void WatchBehavior_broadcast_arm(uint8_T *WatchBehavior_Y_sel,
  B_WatchBehavior_T *WatchBehavior_B, DW_WatchBehavior_T *WatchBehavior_DW);
static void WatchBehavior_modes(uint8_T *WatchBehavior_Y_sel, B_WatchBehavior_T *
  WatchBehavior_B, DW_WatchBehavior_T *WatchBehavior_DW);
static void WatchBehavior_exit_internal_operationModes(uint8_T
  *WatchBehavior_Y_mode, boolean_T *WatchBehavior_Y_alarmDrv, DW_WatchBehavior_T
  *WatchBehavior_DW);
static void WatchBehavior_operationModes(uint8_T *WatchBehavior_Y_mode, uint8_T *
  WatchBehavior_Y_sel, boolean_T *WatchBehavior_Y_alarmDrv, B_WatchBehavior_T
  *WatchBehavior_B, DW_WatchBehavior_T *WatchBehavior_DW);
static void WatchBehavior_chartstep_c1_WatchBehavior(uint8_T
  *WatchBehavior_Y_mode, uint8_T *WatchBehavior_Y_sel, boolean_T
  *WatchBehavior_Y_alarmDrv, B_WatchBehavior_T *WatchBehavior_B,
  DW_WatchBehavior_T *WatchBehavior_DW);

/*
 * Function for Chart: '<S1>/StateMachine'
 * function HMST = hmstTick(cmd,sel,hmst)
 * TICK Increment or decrement (tick) a time reference
 *    Tick a time reference in 'hmst' format ([1, 4]) by one. Step depends on
 *    the 'sel' value: if sel=1 hours are ticked, if sel=2 minutes are
 *    ticked, and so on. If hmst has less than 4 entries, algorithm pads it
 *    with zeros before executing but returns a value with the same size of
 *    input anyway.
 *    Usage: hmstTick(+1,sel,hmst) to increment, hmstTick(-1,sel,hmst) to
 *    decrement.
 *    Author: Alessandro Trifoglio
 *    Date: 19 November 2016
 *    Free domain
 */
static void WatchBehavior_hmstTick(real_T cmd, real_T sel, const uint8_T hmst[4],
  uint8_T HMST[4])
{
  int16_T b_HMST_idx_3;
  int16_T b_HMST_idx_2;
  int16_T b_HMST_idx_1;
  int16_T b_HMST_idx_0;

  /* 'hmstTick:16' sz = size(hmst); */
  /*  Size check */
  /* 'hmstTick:20' if (sz(2)>4 || ~isempty(sz(3:end))) */
  /*  Casting to double needed to solve some issues with uint8 format */
  /* 'hmstTick:26' hmstClass = class(hmst); */
  /* 'hmstTick:27' hmst = double(hmst); */
  /*  Pad with zeros if sz(2) is less than 4 */
  /* 'hmstTick:31' pad = zeros(sz(1),4-sz(2)); */
  /* 'hmstTick:32' hmst_padded = [hmst pad]; */
  /* 'hmstTick:34' HMST = hmst_padded; */
  b_HMST_idx_0 = hmst[0];
  b_HMST_idx_1 = hmst[1];
  b_HMST_idx_2 = hmst[2];
  b_HMST_idx_3 = hmst[3];

  /* 'hmstTick:36' if (cmd==+1) */
  if (cmd == 1.0) {
    /* 'hmstTick:38' if (sel==4) */
    if (sel == 4.0) {
      /* 'hmstTick:39' HMST(:,4) = mod(hmst_padded(:,4)+1,10); */
      b_HMST_idx_3 = (int16_T)((hmst[3] - (int32_T)floor(((real_T)hmst[3] + 1.0)
        / 10.0) * 10) + 1);

      /* 'hmstTick:40' if (hmst_padded(:,4)==9) */
      if (hmst[3] == 9) {
        /* 'hmstTick:41' sel=sel-1; */
        sel = 3.0;
      }
    }

    /* 'hmstTick:44' if (sel==3) */
    if (sel == 3.0) {
      /* 'hmstTick:45' HMST(:,3) = mod(hmst_padded(:,3)+1,60); */
      b_HMST_idx_2 = (int16_T)((hmst[2] - (int32_T)floor(((real_T)hmst[2] + 1.0)
        / 60.0) * 60) + 1);

      /* 'hmstTick:46' if (hmst_padded(:,3)==59) */
      if (hmst[2] == 59) {
        /* 'hmstTick:47' sel=sel-1; */
        sel = 2.0;
      }
    }

    /* 'hmstTick:50' if (sel==2) */
    if (sel == 2.0) {
      /* 'hmstTick:51' HMST(:,2) = mod(hmst_padded(:,2)+1,60); */
      b_HMST_idx_1 = (int16_T)((hmst[1] - (int32_T)floor(((real_T)hmst[1] + 1.0)
        / 60.0) * 60) + 1);

      /* 'hmstTick:52' if (hmst_padded(:,2)==59) */
      if (hmst[1] == 59) {
        /* 'hmstTick:53' sel=sel-1; */
        sel = 1.0;
      }
    }

    /* 'hmstTick:56' if (sel==1) */
    if (sel == 1.0) {
      /* 'hmstTick:57' HMST(:,1) = mod(hmst_padded(:,1)+1,24); */
      b_HMST_idx_0 = (int16_T)((hmst[0] - (int32_T)floor(((real_T)hmst[0] + 1.0)
        / 24.0) * 24) + 1);
    }
  } else {
    if (cmd == -1.0) {
      /* 'hmstTick:60' elseif (cmd==-1) */
      /* 'hmstTick:62' if (sel==4) */
      if (sel == 4.0) {
        /* 'hmstTick:63' HMST(:,4) = mod(hmst_padded(:,4)-1,10); */
        b_HMST_idx_3 = (int16_T)((hmst[3] - (int32_T)floor(((real_T)hmst[3] -
          1.0) / 10.0) * 10) - 1);

        /* 'hmstTick:64' if (hmst_padded(:,4)==0) */
        if (hmst[3] == 0) {
          /* 'hmstTick:65' sel=sel-1; */
          sel = 3.0;
        }
      }

      /* 'hmstTick:68' if (sel==3) */
      if (sel == 3.0) {
        /* 'hmstTick:69' HMST(:,3) = mod(hmst_padded(:,3)-1,60); */
        b_HMST_idx_2 = (int16_T)((hmst[2] - (int32_T)floor(((real_T)hmst[2] -
          1.0) / 60.0) * 60) - 1);

        /* 'hmstTick:70' if (hmst_padded(:,3)==0) */
        if (hmst[2] == 0) {
          /* 'hmstTick:71' sel=sel-1; */
          sel = 2.0;
        }
      }

      /* 'hmstTick:74' if (sel==2) */
      if (sel == 2.0) {
        /* 'hmstTick:75' HMST(:,2) = mod(hmst_padded(:,2)-1,60); */
        b_HMST_idx_1 = (int16_T)((hmst[1] - (int32_T)floor(((real_T)hmst[1] -
          1.0) / 60.0) * 60) - 1);

        /* 'hmstTick:76' if (hmst_padded(:,2)==0) */
        if (hmst[1] == 0) {
          /* 'hmstTick:77' sel=sel-1; */
          sel = 1.0;
        }
      }

      /* 'hmstTick:80' if (sel==1) */
      if (sel == 1.0) {
        /* 'hmstTick:81' HMST(:,1) = mod(hmst_padded(:,1)-1,24); */
        b_HMST_idx_0 = (int16_T)((hmst[0] - (int32_T)floor(((real_T)hmst[0] -
          1.0) / 24.0) * 24) - 1);
      }
    }
  }

  /*  Resize output */
  /* 'hmstTick:88' HMST = HMST(:,1:sz(2)); */
  /*  Recast output */
  /* 'hmstTick:92' HMST = cast(HMST,hmstClass); */
  if (b_HMST_idx_0 < 0) {
    b_HMST_idx_0 = 0;
  } else {
    if (b_HMST_idx_0 > 255) {
      b_HMST_idx_0 = 255;
    }
  }

  HMST[0] = (uint8_T)b_HMST_idx_0;
  if (b_HMST_idx_1 < 0) {
    b_HMST_idx_1 = 0;
  } else {
    if (b_HMST_idx_1 > 255) {
      b_HMST_idx_1 = 255;
    }
  }

  HMST[1] = (uint8_T)b_HMST_idx_1;
  if (b_HMST_idx_2 < 0) {
    b_HMST_idx_2 = 0;
  } else {
    if (b_HMST_idx_2 > 255) {
      b_HMST_idx_2 = 255;
    }
  }

  HMST[2] = (uint8_T)b_HMST_idx_2;
  if (b_HMST_idx_3 < 0) {
    b_HMST_idx_3 = 0;
  } else {
    if (b_HMST_idx_3 > 255) {
      b_HMST_idx_3 = 255;
    }
  }

  HMST[3] = (uint8_T)b_HMST_idx_3;
}

/*
 * Function for Chart: '<S1>/StateMachine'
 * function HMST = hmstTick(cmd,sel,hmst)
 * TICK Increment or decrement (tick) a time reference
 *    Tick a time reference in 'hmst' format ([1, 4]) by one. Step depends on
 *    the 'sel' value: if sel=1 hours are ticked, if sel=2 minutes are
 *    ticked, and so on. If hmst has less than 4 entries, algorithm pads it
 *    with zeros before executing but returns a value with the same size of
 *    input anyway.
 *    Usage: hmstTick(+1,sel,hmst) to increment, hmstTick(-1,sel,hmst) to
 *    decrement.
 *    Author: Alessandro Trifoglio
 *    Date: 19 November 2016
 *    Free domain
 */
static void WatchBehavior_hmstTick_k(real_T cmd, uint8_T sel, const uint8_T
  hmst[2], uint8_T HMST[2])
{
  int16_T b_HMST_idx_1;
  int16_T b_HMST_idx_0;

  /* 'hmstTick:16' sz = size(hmst); */
  /*  Size check */
  /* 'hmstTick:20' if (sz(2)>4 || ~isempty(sz(3:end))) */
  /*  Casting to double needed to solve some issues with uint8 format */
  /* 'hmstTick:26' hmstClass = class(hmst); */
  /* 'hmstTick:27' hmst = double(hmst); */
  /*  Pad with zeros if sz(2) is less than 4 */
  /* 'hmstTick:31' pad = zeros(sz(1),4-sz(2)); */
  /* 'hmstTick:32' hmst_padded = [hmst pad]; */
  /* 'hmstTick:34' HMST = hmst_padded; */
  b_HMST_idx_0 = hmst[0];
  b_HMST_idx_1 = hmst[1];

  /* 'hmstTick:36' if (cmd==+1) */
  if (cmd == 1.0) {
    /* 'hmstTick:38' if (sel==4) */
    /* 'hmstTick:44' if (sel==3) */
    /* 'hmstTick:50' if (sel==2) */
    if (sel == 2) {
      /* 'hmstTick:51' HMST(:,2) = mod(hmst_padded(:,2)+1,60); */
      b_HMST_idx_1 = (int16_T)((hmst[1] - (int32_T)floor(((real_T)hmst[1] + 1.0)
        / 60.0) * 60) + 1);

      /* 'hmstTick:52' if (hmst_padded(:,2)==59) */
      if (hmst[1] == 59) {
        /* 'hmstTick:53' sel=sel-1; */
        sel = 1U;
      }
    }

    /* 'hmstTick:56' if (sel==1) */
    if (sel == 1) {
      /* 'hmstTick:57' HMST(:,1) = mod(hmst_padded(:,1)+1,24); */
      b_HMST_idx_0 = (int16_T)((hmst[0] - (int32_T)floor(((real_T)hmst[0] + 1.0)
        / 24.0) * 24) + 1);
    }
  } else {
    if (cmd == -1.0) {
      /* 'hmstTick:60' elseif (cmd==-1) */
      /* 'hmstTick:62' if (sel==4) */
      if (sel == 4) {
        /* 'hmstTick:63' HMST(:,4) = mod(hmst_padded(:,4)-1,10); */
        /* 'hmstTick:64' if (hmst_padded(:,4)==0) */
        /* 'hmstTick:65' sel=sel-1; */
        sel = 3U;
      }

      /* 'hmstTick:68' if (sel==3) */
      if (sel == 3) {
        /* 'hmstTick:69' HMST(:,3) = mod(hmst_padded(:,3)-1,60); */
        /* 'hmstTick:70' if (hmst_padded(:,3)==0) */
        /* 'hmstTick:71' sel=sel-1; */
        sel = 2U;
      }

      /* 'hmstTick:74' if (sel==2) */
      if (sel == 2) {
        /* 'hmstTick:75' HMST(:,2) = mod(hmst_padded(:,2)-1,60); */
        b_HMST_idx_1 = (int16_T)((hmst[1] - (int32_T)floor(((real_T)hmst[1] -
          1.0) / 60.0) * 60) - 1);

        /* 'hmstTick:76' if (hmst_padded(:,2)==0) */
        if (hmst[1] == 0) {
          /* 'hmstTick:77' sel=sel-1; */
          sel = 1U;
        }
      }

      /* 'hmstTick:80' if (sel==1) */
      if (sel == 1) {
        /* 'hmstTick:81' HMST(:,1) = mod(hmst_padded(:,1)-1,24); */
        b_HMST_idx_0 = (int16_T)((hmst[0] - (int32_T)floor(((real_T)hmst[0] -
          1.0) / 24.0) * 24) - 1);
      }
    }
  }

  /*  Resize output */
  /* 'hmstTick:88' HMST = HMST(:,1:sz(2)); */
  /*  Recast output */
  /* 'hmstTick:92' HMST = cast(HMST,hmstClass); */
  if (b_HMST_idx_0 < 0) {
    b_HMST_idx_0 = 0;
  } else {
    if (b_HMST_idx_0 > 255) {
      b_HMST_idx_0 = 255;
    }
  }

  HMST[0] = (uint8_T)b_HMST_idx_0;
  if (b_HMST_idx_1 < 0) {
    b_HMST_idx_1 = 0;
  } else {
    if (b_HMST_idx_1 > 255) {
      b_HMST_idx_1 = 255;
    }
  }

  HMST[1] = (uint8_T)b_HMST_idx_1;
}

/* Function for Chart: '<S1>/StateMachine' */
static void WatchBehavior_broadcast_arm_n(uint8_T *WatchBehavior_Y_mode, uint8_T
  *WatchBehavior_Y_sel, boolean_T *WatchBehavior_Y_alarmDrv, B_WatchBehavior_T
  *WatchBehavior_B, DW_WatchBehavior_T *WatchBehavior_DW)
{
  int32_T b_previousEvent;

  /* Event: '<S2>:193' */
  b_previousEvent = WatchBehavior_DW->sfEvent;
  WatchBehavior_DW->sfEvent = WatchBehavior_event_arm_p;
  if (WatchBehavior_DW->is_active_modes_b != 0U) {
    WatchBehavior_modes_d(WatchBehavior_Y_mode, WatchBehavior_Y_sel,
                          WatchBehavior_Y_alarmDrv, WatchBehavior_B,
                          WatchBehavior_DW);
  }

  WatchBehavior_DW->sfEvent = b_previousEvent;
}

/*
 * Function for Chart: '<S1>/StateMachine'
 * function cond = triggerAlarmCond
 * TRIGGERALARMCOND External alarm event is triggered when FSM is in 'time'
 *    mode and when current time is equal to alarm time (at zero seconds and
 *    zero tenths).
 */
static boolean_T WatchBehavior_triggerAlarmCond(uint8_T *WatchBehavior_Y_mode,
  DW_WatchBehavior_T *WatchBehavior_DW)
{
  boolean_T cond;
  boolean_T y;
  boolean_T x[4];
  int32_T k;
  boolean_T guard1 = false;
  boolean_T exitg1;

  /* MATLAB Function 'triggerAlarmCond': '<S2>:107' */
  /* '<S2>:107:8' cond = (Mode==uint8(0) && all(hmst==[hmstAlarm 0 0])); */
  guard1 = false;
  if (*WatchBehavior_Y_mode == 0) {
    x[0] = (WatchBehavior_DW->hmst[0] == WatchBehavior_DW->hmstAlarm[0]);
    x[1] = (WatchBehavior_DW->hmst[1] == WatchBehavior_DW->hmstAlarm[1]);
    x[2] = (WatchBehavior_DW->hmst[2] == 0);
    x[3] = (WatchBehavior_DW->hmst[3] == 0);
    y = true;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 4)) {
      if (!x[k]) {
        y = false;
        exitg1 = true;
      } else {
        k++;
      }
    }

    if (y) {
      cond = true;
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    cond = false;
  }

  return cond;
}

/* Function for Chart: '<S1>/StateMachine' */
static void WatchBehavior_alarmDrv(uint8_T *WatchBehavior_Y_mode, boolean_T
  *WatchBehavior_Y_alarmDrv, DW_WatchBehavior_T *WatchBehavior_DW)
{
  boolean_T b_sf_internal_predicateOutput;

  /* During 'alarmDrv': '<S2>:90' */
  /* Alarm driver manages the trigger signal for the alarm. This signal is raised only after an alarm has been set by the user and an appropriate condition is met. Then, it is lowered back when either
     1. the user unsets the alarm
     2. a 'servedAlarm' signal is issued to the FSM
     setting and unsetting rules are described in the 'alarm' section. */
  switch (WatchBehavior_DW->is_alarmDrv) {
   case WatchBehavior_IN_set:
    /* During 'set': '<S2>:95' */
    /* '<S2>:97:1' sf_internal_predicateOutput = ... */
    /* '<S2>:97:1' unsetAlarm || servedAlarm; */
    if ((WatchBehavior_DW->sfEvent == WatchBehavior_event_unsetAlarm) ||
        (WatchBehavior_DW->sfEvent == WatchBehavior_event_servedAlarm)) {
      /* Transition: '<S2>:97' */
      WatchBehavior_DW->is_alarmDrv = WatchBehavior_IN_unset;

      /* Entry 'unset': '<S2>:93' */
      /* '<S2>:93:1' Alarm=false; */
      *WatchBehavior_Y_alarmDrv = false;
    } else {
      /* '<S2>:103:1' sf_internal_predicateOutput = ... */
      /* '<S2>:103:1' (clock) && (triggerAlarmCond); */
      if ((WatchBehavior_DW->sfEvent == WatchBehavior_event_clock) &&
          WatchBehavior_triggerAlarmCond(WatchBehavior_Y_mode, WatchBehavior_DW))
      {
        b_sf_internal_predicateOutput = true;
      } else {
        b_sf_internal_predicateOutput = false;
      }

      if (b_sf_internal_predicateOutput) {
        /* Transition: '<S2>:103' */
        /* '<S2>:103:1' Alarm=true; */
        *WatchBehavior_Y_alarmDrv = true;
      }
    }
    break;

   case WatchBehavior_IN_unset:
    /* During 'unset': '<S2>:93' */
    /* '<S2>:96:1' sf_internal_predicateOutput = ... */
    /* '<S2>:96:1' setAlarm; */
    if (WatchBehavior_DW->sfEvent == WatchBehavior_event_setAlarm) {
      /* Transition: '<S2>:96' */
      WatchBehavior_DW->is_alarmDrv = WatchBehavior_IN_set;
    }
    break;
  }
}

/* Function for Chart: '<S1>/StateMachine' */
static void WatchBehavior_modes_d(uint8_T *WatchBehavior_Y_mode, uint8_T
  *WatchBehavior_Y_sel, boolean_T *WatchBehavior_Y_alarmDrv, B_WatchBehavior_T
  *WatchBehavior_B, DW_WatchBehavior_T *WatchBehavior_DW)
{
  int32_T b_previousEvent;
  uint8_T tmp[2];
  uint8_T tmp_0[2];

  /* During 'modes': '<S2>:159' */
  /* '<S2>:159:1' sf_internal_predicateOutput = ... */
  /* '<S2>:159:1' plus; */
  if (WatchBehavior_DW->sfEvent == WatchBehavior_event_plus) {
    /* '<S2>:159:1' hmstAlarm=hmstTick(+1,Sel,hmstAlarm); */
    tmp_0[0] = WatchBehavior_DW->hmstAlarm[0];
    tmp_0[1] = WatchBehavior_DW->hmstAlarm[1];
    WatchBehavior_hmstTick_k(1.0, *WatchBehavior_Y_sel, tmp_0,
      WatchBehavior_DW->hmstAlarm);

    /* '<S2>:159:3' HMST=[hmstAlarm 0 0]; */
    WatchBehavior_B->HMST[0] = WatchBehavior_DW->hmstAlarm[0];
    WatchBehavior_B->HMST[1] = WatchBehavior_DW->hmstAlarm[1];
    WatchBehavior_B->HMST[2] = 0U;
    WatchBehavior_B->HMST[3] = 0U;

    /* '<S2>:159:3' arm; */
    WatchBehavior_broadcast_arm_n(WatchBehavior_Y_mode, WatchBehavior_Y_sel,
      WatchBehavior_Y_alarmDrv, WatchBehavior_B, WatchBehavior_DW);
  }

  /* '<S2>:159:2' sf_internal_predicateOutput = ... */
  /* '<S2>:159:2' minus; */
  if (WatchBehavior_DW->sfEvent == WatchBehavior_event_minus) {
    /* '<S2>:159:4' hmstAlarm=hmstTick(-1,Sel,hmstAlarm); */
    tmp[0] = WatchBehavior_DW->hmstAlarm[0];
    tmp[1] = WatchBehavior_DW->hmstAlarm[1];
    WatchBehavior_hmstTick_k(-1.0, *WatchBehavior_Y_sel, tmp,
      WatchBehavior_DW->hmstAlarm);

    /* '<S2>:159:6' HMST=[hmstAlarm 0 0]; */
    WatchBehavior_B->HMST[0] = WatchBehavior_DW->hmstAlarm[0];
    WatchBehavior_B->HMST[1] = WatchBehavior_DW->hmstAlarm[1];
    WatchBehavior_B->HMST[2] = 0U;
    WatchBehavior_B->HMST[3] = 0U;

    /* '<S2>:159:6' arm; */
    WatchBehavior_broadcast_arm_n(WatchBehavior_Y_mode, WatchBehavior_Y_sel,
      WatchBehavior_Y_alarmDrv, WatchBehavior_B, WatchBehavior_DW);
  }

  switch (WatchBehavior_DW->is_modes_g) {
   case WatchBehavior_IN_armed:
    /* During 'armed': '<S2>:158' */
    /* '<S2>:153:1' sf_internal_predicateOutput = ... */
    /* '<S2>:153:1' set==true; */
    if (WatchBehavior_DW->set) {
      /* Transition: '<S2>:153' */
      if (WatchBehavior_DW->is_modes_g == WatchBehavior_IN_armed) {
        /* Exit 'armed': '<S2>:158' */
        /* '<S2>:158:1' send(setAlarm,alarmDrv); */
        b_previousEvent = WatchBehavior_DW->sfEvent;
        WatchBehavior_DW->sfEvent = WatchBehavior_event_setAlarm;
        if (WatchBehavior_DW->is_active_alarmDrv != 0U) {
          WatchBehavior_alarmDrv(WatchBehavior_Y_mode, WatchBehavior_Y_alarmDrv,
            WatchBehavior_DW);
        }

        WatchBehavior_DW->sfEvent = b_previousEvent;

        /* '<S2>:158:1' set=true; */
        WatchBehavior_DW->set = true;
        WatchBehavior_DW->is_modes_g = WatchBehavior_IN_NO_ACTIVE_CHILD;
      }

      /* '<S2>:153:1' send(unsetAlarm,alarmDrv); */
      b_previousEvent = WatchBehavior_DW->sfEvent;
      WatchBehavior_DW->sfEvent = WatchBehavior_event_unsetAlarm;
      if (WatchBehavior_DW->is_active_alarmDrv != 0U) {
        WatchBehavior_alarmDrv(WatchBehavior_Y_mode, WatchBehavior_Y_alarmDrv,
          WatchBehavior_DW);
      }

      WatchBehavior_DW->sfEvent = b_previousEvent;
      if (WatchBehavior_DW->is_modes_g != WatchBehavior_IN_disarmed) {
        WatchBehavior_DW->is_modes_g = WatchBehavior_IN_disarmed;
        WatchBehavior_DW->was_modes = WatchBehavior_IN_disarmed;

        /* Entry 'disarmed': '<S2>:156' */
        /* '<S2>:156:1' HMST=[hmstAlarm 0 0]; */
        WatchBehavior_B->HMST[0] = WatchBehavior_DW->hmstAlarm[0];
        WatchBehavior_B->HMST[1] = WatchBehavior_DW->hmstAlarm[1];
        WatchBehavior_B->HMST[2] = 0U;
        WatchBehavior_B->HMST[3] = 0U;

        /* '<S2>:156:1' set=false; */
        WatchBehavior_DW->set = false;
      }
    }
    break;

   case WatchBehavior_IN_disarmed:
    /* During 'disarmed': '<S2>:156' */
    /* '<S2>:155:1' sf_internal_predicateOutput = ... */
    /* '<S2>:155:1' arm; */
    if (WatchBehavior_DW->sfEvent == WatchBehavior_event_arm_p) {
      /* Transition: '<S2>:155' */
      WatchBehavior_DW->is_modes_g = WatchBehavior_IN_armed;
      WatchBehavior_DW->was_modes = WatchBehavior_IN_armed;
    }
    break;
  }
}

/*
 * Function for Chart: '<S1>/StateMachine'
 * function HMST = hmstTick(cmd,sel,hmst)
 * TICK Increment or decrement (tick) a time reference
 *    Tick a time reference in 'hmst' format ([1, 4]) by one. Step depends on
 *    the 'sel' value: if sel=1 hours are ticked, if sel=2 minutes are
 *    ticked, and so on. If hmst has less than 4 entries, algorithm pads it
 *    with zeros before executing but returns a value with the same size of
 *    input anyway.
 *    Usage: hmstTick(+1,sel,hmst) to increment, hmstTick(-1,sel,hmst) to
 *    decrement.
 *    Author: Alessandro Trifoglio
 *    Date: 19 November 2016
 *    Free domain
 */
static void WatchBehavior_hmstTick_k4(real_T cmd, uint8_T sel, const uint8_T
  hmst[4], uint8_T HMST[4])
{
  int16_T b_HMST_idx_3;
  int16_T b_HMST_idx_2;
  int16_T b_HMST_idx_1;
  int16_T b_HMST_idx_0;

  /* 'hmstTick:16' sz = size(hmst); */
  /*  Size check */
  /* 'hmstTick:20' if (sz(2)>4 || ~isempty(sz(3:end))) */
  /*  Casting to double needed to solve some issues with uint8 format */
  /* 'hmstTick:26' hmstClass = class(hmst); */
  /* 'hmstTick:27' hmst = double(hmst); */
  /*  Pad with zeros if sz(2) is less than 4 */
  /* 'hmstTick:31' pad = zeros(sz(1),4-sz(2)); */
  /* 'hmstTick:32' hmst_padded = [hmst pad]; */
  /* 'hmstTick:34' HMST = hmst_padded; */
  b_HMST_idx_0 = hmst[0];
  b_HMST_idx_1 = hmst[1];
  b_HMST_idx_2 = hmst[2];
  b_HMST_idx_3 = hmst[3];

  /* 'hmstTick:36' if (cmd==+1) */
  if (cmd == 1.0) {
    /* 'hmstTick:38' if (sel==4) */
    if (sel == 4) {
      /* 'hmstTick:39' HMST(:,4) = mod(hmst_padded(:,4)+1,10); */
      b_HMST_idx_3 = (int16_T)((hmst[3] - (int32_T)floor(((real_T)hmst[3] + 1.0)
        / 10.0) * 10) + 1);

      /* 'hmstTick:40' if (hmst_padded(:,4)==9) */
      if (hmst[3] == 9) {
        /* 'hmstTick:41' sel=sel-1; */
        sel = 3U;
      }
    }

    /* 'hmstTick:44' if (sel==3) */
    if (sel == 3) {
      /* 'hmstTick:45' HMST(:,3) = mod(hmst_padded(:,3)+1,60); */
      b_HMST_idx_2 = (int16_T)((hmst[2] - (int32_T)floor(((real_T)hmst[2] + 1.0)
        / 60.0) * 60) + 1);

      /* 'hmstTick:46' if (hmst_padded(:,3)==59) */
      if (hmst[2] == 59) {
        /* 'hmstTick:47' sel=sel-1; */
        sel = 2U;
      }
    }

    /* 'hmstTick:50' if (sel==2) */
    if (sel == 2) {
      /* 'hmstTick:51' HMST(:,2) = mod(hmst_padded(:,2)+1,60); */
      b_HMST_idx_1 = (int16_T)((hmst[1] - (int32_T)floor(((real_T)hmst[1] + 1.0)
        / 60.0) * 60) + 1);

      /* 'hmstTick:52' if (hmst_padded(:,2)==59) */
      if (hmst[1] == 59) {
        /* 'hmstTick:53' sel=sel-1; */
        sel = 1U;
      }
    }

    /* 'hmstTick:56' if (sel==1) */
    if (sel == 1) {
      /* 'hmstTick:57' HMST(:,1) = mod(hmst_padded(:,1)+1,24); */
      b_HMST_idx_0 = (int16_T)((hmst[0] - (int32_T)floor(((real_T)hmst[0] + 1.0)
        / 24.0) * 24) + 1);
    }
  } else {
    if (cmd == -1.0) {
      /* 'hmstTick:60' elseif (cmd==-1) */
      /* 'hmstTick:62' if (sel==4) */
      if (sel == 4) {
        /* 'hmstTick:63' HMST(:,4) = mod(hmst_padded(:,4)-1,10); */
        b_HMST_idx_3 = (int16_T)((hmst[3] - (int32_T)floor(((real_T)hmst[3] -
          1.0) / 10.0) * 10) - 1);

        /* 'hmstTick:64' if (hmst_padded(:,4)==0) */
        if (hmst[3] == 0) {
          /* 'hmstTick:65' sel=sel-1; */
          sel = 3U;
        }
      }

      /* 'hmstTick:68' if (sel==3) */
      if (sel == 3) {
        /* 'hmstTick:69' HMST(:,3) = mod(hmst_padded(:,3)-1,60); */
        b_HMST_idx_2 = (int16_T)((hmst[2] - (int32_T)floor(((real_T)hmst[2] -
          1.0) / 60.0) * 60) - 1);

        /* 'hmstTick:70' if (hmst_padded(:,3)==0) */
        if (hmst[2] == 0) {
          /* 'hmstTick:71' sel=sel-1; */
          sel = 2U;
        }
      }

      /* 'hmstTick:74' if (sel==2) */
      if (sel == 2) {
        /* 'hmstTick:75' HMST(:,2) = mod(hmst_padded(:,2)-1,60); */
        b_HMST_idx_1 = (int16_T)((hmst[1] - (int32_T)floor(((real_T)hmst[1] -
          1.0) / 60.0) * 60) - 1);

        /* 'hmstTick:76' if (hmst_padded(:,2)==0) */
        if (hmst[1] == 0) {
          /* 'hmstTick:77' sel=sel-1; */
          sel = 1U;
        }
      }

      /* 'hmstTick:80' if (sel==1) */
      if (sel == 1) {
        /* 'hmstTick:81' HMST(:,1) = mod(hmst_padded(:,1)-1,24); */
        b_HMST_idx_0 = (int16_T)((hmst[0] - (int32_T)floor(((real_T)hmst[0] -
          1.0) / 24.0) * 24) - 1);
      }
    }
  }

  /*  Resize output */
  /* 'hmstTick:88' HMST = HMST(:,1:sz(2)); */
  /*  Recast output */
  /* 'hmstTick:92' HMST = cast(HMST,hmstClass); */
  if (b_HMST_idx_0 < 0) {
    b_HMST_idx_0 = 0;
  } else {
    if (b_HMST_idx_0 > 255) {
      b_HMST_idx_0 = 255;
    }
  }

  HMST[0] = (uint8_T)b_HMST_idx_0;
  if (b_HMST_idx_1 < 0) {
    b_HMST_idx_1 = 0;
  } else {
    if (b_HMST_idx_1 > 255) {
      b_HMST_idx_1 = 255;
    }
  }

  HMST[1] = (uint8_T)b_HMST_idx_1;
  if (b_HMST_idx_2 < 0) {
    b_HMST_idx_2 = 0;
  } else {
    if (b_HMST_idx_2 > 255) {
      b_HMST_idx_2 = 255;
    }
  }

  HMST[2] = (uint8_T)b_HMST_idx_2;
  if (b_HMST_idx_3 < 0) {
    b_HMST_idx_3 = 0;
  } else {
    if (b_HMST_idx_3 > 255) {
      b_HMST_idx_3 = 255;
    }
  }

  HMST[3] = (uint8_T)b_HMST_idx_3;
}

/* Function for Chart: '<S1>/StateMachine' */
static void WatchBehavior_broadcast_arm(uint8_T *WatchBehavior_Y_sel,
  B_WatchBehavior_T *WatchBehavior_B, DW_WatchBehavior_T *WatchBehavior_DW)
{
  int32_T b_previousEvent;

  /* Event: '<S2>:192' */
  b_previousEvent = WatchBehavior_DW->sfEvent;
  WatchBehavior_DW->sfEvent = WatchBehavior_event_arm;
  if (WatchBehavior_DW->is_active_modes != 0U) {
    WatchBehavior_modes(WatchBehavior_Y_sel, WatchBehavior_B, WatchBehavior_DW);
  }

  WatchBehavior_DW->sfEvent = b_previousEvent;
}

/* Function for Chart: '<S1>/StateMachine' */
static void WatchBehavior_modes(uint8_T *WatchBehavior_Y_sel, B_WatchBehavior_T *
  WatchBehavior_B, DW_WatchBehavior_T *WatchBehavior_DW)
{
  uint8_T tmp[2];
  uint8_T tmp_0[2];

  /* During 'modes': '<S2>:111' */
  /* '<S2>:111:1' sf_internal_predicateOutput = ... */
  /* '<S2>:111:1' plus; */
  if (WatchBehavior_DW->sfEvent == WatchBehavior_event_plus) {
    /* '<S2>:111:1' hmstSet=hmstTick(+1,Sel,hmstSet); */
    tmp_0[0] = WatchBehavior_DW->hmstSet[0];
    tmp_0[1] = WatchBehavior_DW->hmstSet[1];
    WatchBehavior_hmstTick_k(1.0, *WatchBehavior_Y_sel, tmp_0,
      WatchBehavior_DW->hmstSet);

    /* '<S2>:111:2' HMST=[hmstSet 0 0]; */
    WatchBehavior_B->HMST[0] = WatchBehavior_DW->hmstSet[0];
    WatchBehavior_B->HMST[1] = WatchBehavior_DW->hmstSet[1];
    WatchBehavior_B->HMST[2] = 0U;
    WatchBehavior_B->HMST[3] = 0U;

    /* '<S2>:111:3' arm; */
    WatchBehavior_broadcast_arm(WatchBehavior_Y_sel, WatchBehavior_B,
      WatchBehavior_DW);
  }

  /* '<S2>:111:1' sf_internal_predicateOutput = ... */
  /* '<S2>:111:1' minus; */
  if (WatchBehavior_DW->sfEvent == WatchBehavior_event_minus) {
    /* '<S2>:111:4' hmstSet=hmstTick(-1,Sel,hmstSet); */
    tmp[0] = WatchBehavior_DW->hmstSet[0];
    tmp[1] = WatchBehavior_DW->hmstSet[1];
    WatchBehavior_hmstTick_k(-1.0, *WatchBehavior_Y_sel, tmp,
      WatchBehavior_DW->hmstSet);

    /* '<S2>:111:6' HMST=[hmstSet 0 0]; */
    WatchBehavior_B->HMST[0] = WatchBehavior_DW->hmstSet[0];
    WatchBehavior_B->HMST[1] = WatchBehavior_DW->hmstSet[1];
    WatchBehavior_B->HMST[2] = 0U;
    WatchBehavior_B->HMST[3] = 0U;

    /* '<S2>:111:6' arm; */
    WatchBehavior_broadcast_arm(WatchBehavior_Y_sel, WatchBehavior_B,
      WatchBehavior_DW);
  }

  switch (WatchBehavior_DW->is_modes) {
   case WatchBehavior_IN_armed:
    /* During 'armed': '<S2>:42' */
    break;

   case WatchBehavior_IN_disarmed:
    /* During 'disarmed': '<S2>:35' */
    /* '<S2>:43:1' sf_internal_predicateOutput = ... */
    /* '<S2>:43:1' arm; */
    if (WatchBehavior_DW->sfEvent == WatchBehavior_event_arm) {
      /* Transition: '<S2>:43' */
      WatchBehavior_DW->is_modes = WatchBehavior_IN_armed;
    }
    break;
  }
}

/* Function for Chart: '<S1>/StateMachine' */
static void WatchBehavior_exit_internal_operationModes(uint8_T
  *WatchBehavior_Y_mode, boolean_T *WatchBehavior_Y_alarmDrv, DW_WatchBehavior_T
  *WatchBehavior_DW)
{
  int32_T b_previousEvent;

  /* Exit Internal 'operationModes': '<S2>:22' */
  switch (WatchBehavior_DW->is_operationModes) {
   case WatchBehavior_IN_alarm:
    /* Exit Internal 'alarm': '<S2>:30' */
    /* Exit Internal 'selection': '<S2>:142' */
    WatchBehavior_DW->is_selection_m = WatchBehavior_IN_NO_ACTIVE_CHILD;
    WatchBehavior_DW->is_active_selection_n = 0U;

    /* Exit Internal 'modes': '<S2>:159' */
    if (WatchBehavior_DW->is_modes_g == WatchBehavior_IN_armed) {
      /* Exit 'armed': '<S2>:158' */
      /* '<S2>:158:1' send(setAlarm,alarmDrv); */
      b_previousEvent = WatchBehavior_DW->sfEvent;
      WatchBehavior_DW->sfEvent = WatchBehavior_event_setAlarm;
      if (WatchBehavior_DW->is_active_alarmDrv != 0U) {
        WatchBehavior_alarmDrv(WatchBehavior_Y_mode, WatchBehavior_Y_alarmDrv,
          WatchBehavior_DW);
      }

      WatchBehavior_DW->sfEvent = b_previousEvent;

      /* '<S2>:158:1' set=true; */
      WatchBehavior_DW->set = true;
      WatchBehavior_DW->is_modes_g = WatchBehavior_IN_NO_ACTIVE_CHILD;
    } else {
      WatchBehavior_DW->is_modes_g = WatchBehavior_IN_NO_ACTIVE_CHILD;
    }

    WatchBehavior_DW->is_active_modes_b = 0U;
    WatchBehavior_DW->is_operationModes = WatchBehavior_IN_NO_ACTIVE_CHILD;
    break;

   case WatchBehavior_IN_timeset:
    /* Exit Internal 'timeset': '<S2>:29' */
    /* Exit Internal 'selection': '<S2>:114' */
    WatchBehavior_DW->is_selection = WatchBehavior_IN_NO_ACTIVE_CHILD;
    WatchBehavior_DW->is_active_selection = 0U;

    /* Exit Internal 'modes': '<S2>:111' */
    if (WatchBehavior_DW->is_modes == WatchBehavior_IN_armed) {
      /* Exit 'armed': '<S2>:42' */
      /* '<S2>:42:1' hmst=[hmstSet 0 0]; */
      WatchBehavior_DW->hmst[0] = WatchBehavior_DW->hmstSet[0];
      WatchBehavior_DW->hmst[1] = WatchBehavior_DW->hmstSet[1];
      WatchBehavior_DW->hmst[2] = 0U;
      WatchBehavior_DW->hmst[3] = 0U;
      WatchBehavior_DW->is_modes = WatchBehavior_IN_NO_ACTIVE_CHILD;
    } else {
      WatchBehavior_DW->is_modes = WatchBehavior_IN_NO_ACTIVE_CHILD;
    }

    WatchBehavior_DW->is_active_modes = 0U;
    WatchBehavior_DW->is_operationModes = WatchBehavior_IN_NO_ACTIVE_CHILD;
    break;

   default:
    /* Exit Internal 'stopwatch': '<S2>:31' */
    WatchBehavior_DW->is_stopwatch = WatchBehavior_IN_NO_ACTIVE_CHILD;
    WatchBehavior_DW->is_operationModes = WatchBehavior_IN_NO_ACTIVE_CHILD;
    break;
  }
}

/* Function for Chart: '<S1>/StateMachine' */
static void WatchBehavior_operationModes(uint8_T *WatchBehavior_Y_mode, uint8_T *
  WatchBehavior_Y_sel, boolean_T *WatchBehavior_Y_alarmDrv, B_WatchBehavior_T
  *WatchBehavior_B, DW_WatchBehavior_T *WatchBehavior_DW)
{
  uint8_T tmp[4];
  uint8_T tmp_0[4];

  /* During 'operationModes': '<S2>:22' */
  /* Operation modes are:
     1. [active.operationModes.time time] mode
     2. [active.operationModes.timeset time set] mode
     3. [active.operationModes.alarm alarm] mode
     4. [active.operationModes.stopwatch stopwatch] mode
     each of them is entered when the associated icon from STM32F4 display is selected.
   */
  /* '<S2>:22:1' sf_internal_predicateOutput = ... */
  /* '<S2>:22:1' clock; */
  if (WatchBehavior_DW->sfEvent == WatchBehavior_event_clock) {
    /* '<S2>:22:1' hmst=hmstTick(+1,4,hmst); */
    tmp_0[0] = WatchBehavior_DW->hmst[0];
    tmp_0[1] = WatchBehavior_DW->hmst[1];
    tmp_0[2] = WatchBehavior_DW->hmst[2];
    tmp_0[3] = WatchBehavior_DW->hmst[3];
    WatchBehavior_hmstTick(1.0, 4.0, tmp_0, WatchBehavior_DW->hmst);
  }

  /* '<S2>:27:1' sf_internal_predicateOutput = ... */
  /* '<S2>:27:1' (time) && (Mode~=uint8(0)); */
  if ((WatchBehavior_DW->sfEvent == WatchBehavior_event_time) &&
      (*WatchBehavior_Y_mode != 0)) {
    /* Transition: '<S2>:27' */
    WatchBehavior_exit_internal_operationModes(WatchBehavior_Y_mode,
      WatchBehavior_Y_alarmDrv, WatchBehavior_DW);
    if (WatchBehavior_DW->is_operationModes != WatchBehavior_IN_time) {
      WatchBehavior_DW->is_operationModes = WatchBehavior_IN_time;

      /* Entry 'time': '<S2>:13' */
      /* '<S2>:13:1' Mode=uint8(0); */
      *WatchBehavior_Y_mode = 0U;

      /* '<S2>:13:1' Sel=uint8(0); */
      *WatchBehavior_Y_sel = 0U;
    }
  } else {
    /* '<S2>:33:1' sf_internal_predicateOutput = ... */
    /* '<S2>:33:1' (timeset) && (Mode~=uint8(1)); */
    if ((WatchBehavior_DW->sfEvent == WatchBehavior_event_timeset) &&
        (*WatchBehavior_Y_mode != 1)) {
      /* Transition: '<S2>:33' */
      WatchBehavior_exit_internal_operationModes(WatchBehavior_Y_mode,
        WatchBehavior_Y_alarmDrv, WatchBehavior_DW);
      if (WatchBehavior_DW->is_operationModes != WatchBehavior_IN_timeset) {
        WatchBehavior_DW->is_operationModes = WatchBehavior_IN_timeset;

        /* Entry 'timeset': '<S2>:29' */
        /* '<S2>:29:1' Mode=uint8(1); */
        *WatchBehavior_Y_mode = 1U;
      }

      /* Entry Internal 'timeset': '<S2>:29' */
      WatchBehavior_DW->is_active_modes = 1U;

      /* Entry Internal 'modes': '<S2>:111' */
      /* Transition: '<S2>:36' */
      if (WatchBehavior_DW->is_modes != WatchBehavior_IN_disarmed) {
        WatchBehavior_DW->is_modes = WatchBehavior_IN_disarmed;

        /* Entry 'disarmed': '<S2>:35' */
        /* '<S2>:35:1' hmstSet=hmst(1,1:2); */
        /* '<S2>:35:1' HMST=[hmstSet 0 0]; */
        WatchBehavior_DW->hmstSet[0] = WatchBehavior_DW->hmst[0];
        WatchBehavior_B->HMST[0] = WatchBehavior_DW->hmstSet[0];
        WatchBehavior_DW->hmstSet[1] = WatchBehavior_DW->hmst[1];
        WatchBehavior_B->HMST[1] = WatchBehavior_DW->hmstSet[1];
        WatchBehavior_B->HMST[2] = 0U;
        WatchBehavior_B->HMST[3] = 0U;
      }

      WatchBehavior_DW->is_active_selection = 1U;

      /* Entry Internal 'selection': '<S2>:114' */
      /* Transition: '<S2>:116' */
      if (WatchBehavior_DW->is_selection != WatchBehavior_IN_minutes) {
        WatchBehavior_DW->is_selection = WatchBehavior_IN_minutes;

        /* Entry 'minutes': '<S2>:117' */
        /* '<S2>:117:1' Sel=uint8(2); */
        *WatchBehavior_Y_sel = 2U;
      }
    } else {
      /* '<S2>:32:1' sf_internal_predicateOutput = ... */
      /* '<S2>:32:1' (alarm) && (Mode~=uint8(2)); */
      if ((WatchBehavior_DW->sfEvent == WatchBehavior_event_alarm) &&
          (*WatchBehavior_Y_mode != 2)) {
        /* Transition: '<S2>:32' */
        WatchBehavior_exit_internal_operationModes(WatchBehavior_Y_mode,
          WatchBehavior_Y_alarmDrv, WatchBehavior_DW);
        if (WatchBehavior_DW->is_operationModes != WatchBehavior_IN_alarm) {
          WatchBehavior_DW->is_operationModes = WatchBehavior_IN_alarm;

          /* Entry 'alarm': '<S2>:30' */
          /* '<S2>:30:1' Mode=uint8(2); */
          *WatchBehavior_Y_mode = 2U;
        }

        /* Entry Internal 'alarm': '<S2>:30' */
        WatchBehavior_DW->is_active_modes_b = 1U;

        /* Entry Internal 'modes': '<S2>:159' */
        switch (WatchBehavior_DW->was_modes) {
         case WatchBehavior_IN_armed:
          WatchBehavior_DW->is_modes_g = WatchBehavior_IN_armed;
          WatchBehavior_DW->was_modes = WatchBehavior_IN_armed;
          break;

         case WatchBehavior_IN_disarmed:
          if (WatchBehavior_DW->is_modes_g != WatchBehavior_IN_disarmed) {
            WatchBehavior_DW->is_modes_g = WatchBehavior_IN_disarmed;
            WatchBehavior_DW->was_modes = WatchBehavior_IN_disarmed;

            /* Entry 'disarmed': '<S2>:156' */
            /* '<S2>:156:1' HMST=[hmstAlarm 0 0]; */
            WatchBehavior_B->HMST[0] = WatchBehavior_DW->hmstAlarm[0];
            WatchBehavior_B->HMST[1] = WatchBehavior_DW->hmstAlarm[1];
            WatchBehavior_B->HMST[2] = 0U;
            WatchBehavior_B->HMST[3] = 0U;

            /* '<S2>:156:1' set=false; */
            WatchBehavior_DW->set = false;
          }
          break;

         default:
          /* Transition: '<S2>:154' */
          if (WatchBehavior_DW->is_modes_g != WatchBehavior_IN_disarmed) {
            WatchBehavior_DW->is_modes_g = WatchBehavior_IN_disarmed;
            WatchBehavior_DW->was_modes = WatchBehavior_IN_disarmed;

            /* Entry 'disarmed': '<S2>:156' */
            /* '<S2>:156:1' HMST=[hmstAlarm 0 0]; */
            WatchBehavior_B->HMST[0] = WatchBehavior_DW->hmstAlarm[0];
            WatchBehavior_B->HMST[1] = WatchBehavior_DW->hmstAlarm[1];
            WatchBehavior_B->HMST[2] = 0U;
            WatchBehavior_B->HMST[3] = 0U;

            /* '<S2>:156:1' set=false; */
            WatchBehavior_DW->set = false;
          }
          break;
        }

        WatchBehavior_DW->is_active_selection_n = 1U;

        /* Entry Internal 'selection': '<S2>:142' */
        /* Transition: '<S2>:147' */
        if (WatchBehavior_DW->is_selection_m != WatchBehavior_IN_minutes) {
          WatchBehavior_DW->is_selection_m = WatchBehavior_IN_minutes;

          /* Entry 'minutes': '<S2>:152' */
          /* '<S2>:152:1' Sel=uint8(2); */
          *WatchBehavior_Y_sel = 2U;
        }
      } else {
        /* '<S2>:34:1' sf_internal_predicateOutput = ... */
        /* '<S2>:34:1' (stopwatch) && (Mode~=uint8(3)); */
        if ((WatchBehavior_DW->sfEvent == WatchBehavior_event_stopwatch) &&
            (*WatchBehavior_Y_mode != 3)) {
          /* Transition: '<S2>:34' */
          WatchBehavior_exit_internal_operationModes(WatchBehavior_Y_mode,
            WatchBehavior_Y_alarmDrv, WatchBehavior_DW);
          if (WatchBehavior_DW->is_operationModes != WatchBehavior_IN_stopwatch)
          {
            WatchBehavior_DW->is_operationModes = WatchBehavior_IN_stopwatch;

            /* Entry 'stopwatch': '<S2>:31' */
            /* '<S2>:31:1' Mode=uint8(3); */
            *WatchBehavior_Y_mode = 3U;
          }

          /* Entry Internal 'stopwatch': '<S2>:31' */
          /* Transition: '<S2>:173' */
          if (WatchBehavior_DW->is_stopwatch != WatchBehavior_IN_startup) {
            WatchBehavior_DW->is_stopwatch = WatchBehavior_IN_startup;

            /* Entry 'startup': '<S2>:174' */
            /* '<S2>:174:1' Sel=uint8(0); */
            *WatchBehavior_Y_sel = 0U;

            /* '<S2>:174:1' hmstSw=hmst; */
            /* '<S2>:174:1' HMST=hmstSw; */
            WatchBehavior_DW->hmstSw[0] = WatchBehavior_DW->hmst[0];
            WatchBehavior_B->HMST[0] = WatchBehavior_DW->hmstSw[0];
            WatchBehavior_DW->hmstSw[1] = WatchBehavior_DW->hmst[1];
            WatchBehavior_B->HMST[1] = WatchBehavior_DW->hmstSw[1];
            WatchBehavior_DW->hmstSw[2] = WatchBehavior_DW->hmst[2];
            WatchBehavior_B->HMST[2] = WatchBehavior_DW->hmstSw[2];
            WatchBehavior_DW->hmstSw[3] = WatchBehavior_DW->hmst[3];
            WatchBehavior_B->HMST[3] = WatchBehavior_DW->hmstSw[3];
          }
        } else {
          switch (WatchBehavior_DW->is_operationModes) {
           case WatchBehavior_IN_alarm:
            /* During 'alarm': '<S2>:30' */
            if (WatchBehavior_DW->is_active_modes_b != 0U) {
              WatchBehavior_modes_d(WatchBehavior_Y_mode, WatchBehavior_Y_sel,
                                    WatchBehavior_Y_alarmDrv, WatchBehavior_B,
                                    WatchBehavior_DW);
            }

            if (WatchBehavior_DW->is_active_selection_n != 0U) {
              /* During 'selection': '<S2>:142' */
              switch (WatchBehavior_DW->is_selection_m) {
               case WatchBehavior_IN_hours:
                /* During 'hours': '<S2>:150' */
                /* '<S2>:139:1' sf_internal_predicateOutput = ... */
                /* '<S2>:139:1' alarm; */
                if (WatchBehavior_DW->sfEvent == WatchBehavior_event_alarm) {
                  /* Transition: '<S2>:139' */
                  WatchBehavior_DW->is_selection_m = WatchBehavior_IN_minutes;

                  /* Entry 'minutes': '<S2>:152' */
                  /* '<S2>:152:1' Sel=uint8(2); */
                  *WatchBehavior_Y_sel = 2U;
                }
                break;

               case WatchBehavior_IN_minutes:
                /* During 'minutes': '<S2>:152' */
                /* '<S2>:151:1' sf_internal_predicateOutput = ... */
                /* '<S2>:151:1' alarm; */
                if (WatchBehavior_DW->sfEvent == WatchBehavior_event_alarm) {
                  /* Transition: '<S2>:151' */
                  WatchBehavior_DW->is_selection_m = WatchBehavior_IN_hours;

                  /* Entry 'hours': '<S2>:150' */
                  /* '<S2>:150:1' Sel=uint8(1); */
                  *WatchBehavior_Y_sel = 1U;
                }
                break;
              }
            }
            break;

           case WatchBehavior_IN_stopwatch:
            /* During 'stopwatch': '<S2>:31' */
            switch (WatchBehavior_DW->is_stopwatch) {
             case WatchBehavior_IN_running:
              /* During 'running': '<S2>:184' */
              /* '<S2>:186:1' sf_internal_predicateOutput = ... */
              /* '<S2>:186:1' stopwatch; */
              switch (WatchBehavior_DW->sfEvent) {
               case WatchBehavior_event_stopwatch:
                /* Transition: '<S2>:186' */
                WatchBehavior_DW->is_stopwatch = WatchBehavior_IN_stopped;

                /* Entry 'stopped': '<S2>:183' */
                /* '<S2>:183:1' Sel=uint8(4); */
                *WatchBehavior_Y_sel = 4U;
                break;

               case WatchBehavior_event_clock:
                /* '<S2>:184:1' sf_internal_predicateOutput = ... */
                /* '<S2>:184:1' clock; */
                /* '<S2>:184:1' hmstSw=hmstTick(+1,4,hmstSw); */
                tmp[0] = WatchBehavior_DW->hmstSw[0];
                tmp[1] = WatchBehavior_DW->hmstSw[1];
                tmp[2] = WatchBehavior_DW->hmstSw[2];
                tmp[3] = WatchBehavior_DW->hmstSw[3];
                WatchBehavior_hmstTick(1.0, 4.0, tmp, WatchBehavior_DW->hmstSw);

                /* '<S2>:184:3' HMST=hmstSw; */
                WatchBehavior_B->HMST[0] = WatchBehavior_DW->hmstSw[0];
                WatchBehavior_B->HMST[1] = WatchBehavior_DW->hmstSw[1];
                WatchBehavior_B->HMST[2] = WatchBehavior_DW->hmstSw[2];
                WatchBehavior_B->HMST[3] = WatchBehavior_DW->hmstSw[3];
                break;
              }
              break;

             case WatchBehavior_IN_startup:
              /* During 'startup': '<S2>:174' */
              /* '<S2>:182:1' sf_internal_predicateOutput = ... */
              /* '<S2>:182:1' stopwatch; */
              if (WatchBehavior_DW->sfEvent == WatchBehavior_event_stopwatch) {
                /* Transition: '<S2>:182' */
                /* '<S2>:182:1' hmstSw=uint8([0 0 0 0]); */
                /* '<S2>:182:1' HMST=hmstSw; */
                WatchBehavior_DW->hmstSw[0] = 0U;
                WatchBehavior_B->HMST[0] = WatchBehavior_DW->hmstSw[0];
                WatchBehavior_DW->hmstSw[1] = 0U;
                WatchBehavior_B->HMST[1] = WatchBehavior_DW->hmstSw[1];
                WatchBehavior_DW->hmstSw[2] = 0U;
                WatchBehavior_B->HMST[2] = WatchBehavior_DW->hmstSw[2];
                WatchBehavior_DW->hmstSw[3] = 0U;
                WatchBehavior_B->HMST[3] = WatchBehavior_DW->hmstSw[3];
                WatchBehavior_DW->is_stopwatch = WatchBehavior_IN_stopped;

                /* Entry 'stopped': '<S2>:183' */
                /* '<S2>:183:1' Sel=uint8(4); */
                *WatchBehavior_Y_sel = 4U;
              }
              break;

             case WatchBehavior_IN_stopped:
              /* During 'stopped': '<S2>:183' */
              /* '<S2>:185:1' sf_internal_predicateOutput = ... */
              /* '<S2>:185:1' stopwatch; */
              switch (WatchBehavior_DW->sfEvent) {
               case WatchBehavior_event_stopwatch:
                /* Transition: '<S2>:185' */
                WatchBehavior_DW->is_stopwatch = WatchBehavior_IN_running;

                /* Entry 'running': '<S2>:184' */
                /* '<S2>:184:1' Sel=uint8(0); */
                *WatchBehavior_Y_sel = 0U;
                break;

               case WatchBehavior_event_plus:
                /* '<S2>:189:1' sf_internal_predicateOutput = ... */
                /* '<S2>:189:1' plus; */
                /* Transition: '<S2>:189' */
                /* '<S2>:189:1' hmstSw=hmstTick(+1,Sel,hmstSw); */
                tmp[0] = WatchBehavior_DW->hmstSw[0];
                tmp[1] = WatchBehavior_DW->hmstSw[1];
                tmp[2] = WatchBehavior_DW->hmstSw[2];
                tmp[3] = WatchBehavior_DW->hmstSw[3];
                WatchBehavior_hmstTick_k4(1.0, *WatchBehavior_Y_sel, tmp,
                  WatchBehavior_DW->hmstSw);

                /* '<S2>:189:1' HMST=hmstSw; */
                WatchBehavior_B->HMST[0] = WatchBehavior_DW->hmstSw[0];
                WatchBehavior_B->HMST[1] = WatchBehavior_DW->hmstSw[1];
                WatchBehavior_B->HMST[2] = WatchBehavior_DW->hmstSw[2];
                WatchBehavior_B->HMST[3] = WatchBehavior_DW->hmstSw[3];
                break;

               case WatchBehavior_event_minus:
                /* '<S2>:188:1' sf_internal_predicateOutput = ... */
                /* '<S2>:188:1' minus; */
                /* Transition: '<S2>:188' */
                /* '<S2>:188:1' hmstSw=hmstTick(-1,Sel,hmstSw); */
                tmp[0] = WatchBehavior_DW->hmstSw[0];
                tmp[1] = WatchBehavior_DW->hmstSw[1];
                tmp[2] = WatchBehavior_DW->hmstSw[2];
                tmp[3] = WatchBehavior_DW->hmstSw[3];
                WatchBehavior_hmstTick_k4(-1.0, *WatchBehavior_Y_sel, tmp,
                  WatchBehavior_DW->hmstSw);

                /* '<S2>:188:1' HMST=hmstSw; */
                WatchBehavior_B->HMST[0] = WatchBehavior_DW->hmstSw[0];
                WatchBehavior_B->HMST[1] = WatchBehavior_DW->hmstSw[1];
                WatchBehavior_B->HMST[2] = WatchBehavior_DW->hmstSw[2];
                WatchBehavior_B->HMST[3] = WatchBehavior_DW->hmstSw[3];
                break;
              }
              break;
            }
            break;

           case WatchBehavior_IN_time:
            /* During 'time': '<S2>:13' */
            /* '<S2>:13:1' sf_internal_predicateOutput = ... */
            /* '<S2>:13:1' clock; */
            if (WatchBehavior_DW->sfEvent == WatchBehavior_event_clock) {
              /* '<S2>:13:3' HMST=hmst; */
              WatchBehavior_B->HMST[0] = WatchBehavior_DW->hmst[0];
              WatchBehavior_B->HMST[1] = WatchBehavior_DW->hmst[1];
              WatchBehavior_B->HMST[2] = WatchBehavior_DW->hmst[2];
              WatchBehavior_B->HMST[3] = WatchBehavior_DW->hmst[3];
            }
            break;

           case WatchBehavior_IN_timeset:
            /* During 'timeset': '<S2>:29' */
            if (WatchBehavior_DW->is_active_modes != 0U) {
              WatchBehavior_modes(WatchBehavior_Y_sel, WatchBehavior_B,
                                  WatchBehavior_DW);
            }

            if (WatchBehavior_DW->is_active_selection != 0U) {
              /* During 'selection': '<S2>:114' */
              switch (WatchBehavior_DW->is_selection) {
               case WatchBehavior_IN_hours:
                /* During 'hours': '<S2>:119' */
                /* '<S2>:121:1' sf_internal_predicateOutput = ... */
                /* '<S2>:121:1' timeset; */
                if (WatchBehavior_DW->sfEvent == WatchBehavior_event_timeset) {
                  /* Transition: '<S2>:121' */
                  WatchBehavior_DW->is_selection = WatchBehavior_IN_minutes;

                  /* Entry 'minutes': '<S2>:117' */
                  /* '<S2>:117:1' Sel=uint8(2); */
                  *WatchBehavior_Y_sel = 2U;
                }
                break;

               case WatchBehavior_IN_minutes:
                /* During 'minutes': '<S2>:117' */
                /* '<S2>:120:1' sf_internal_predicateOutput = ... */
                /* '<S2>:120:1' timeset; */
                if (WatchBehavior_DW->sfEvent == WatchBehavior_event_timeset) {
                  /* Transition: '<S2>:120' */
                  WatchBehavior_DW->is_selection = WatchBehavior_IN_hours;

                  /* Entry 'hours': '<S2>:119' */
                  /* '<S2>:119:1' Sel=uint8(1); */
                  *WatchBehavior_Y_sel = 1U;
                }
                break;
              }
            }
            break;
          }
        }
      }
    }
  }
}

/* Function for Chart: '<S1>/StateMachine' */
static void WatchBehavior_chartstep_c1_WatchBehavior(uint8_T
  *WatchBehavior_Y_mode, uint8_T *WatchBehavior_Y_sel, boolean_T
  *WatchBehavior_Y_alarmDrv, B_WatchBehavior_T *WatchBehavior_B,
  DW_WatchBehavior_T *WatchBehavior_DW)
{
  /* During: WatchBehavior/StateMachine */
  /* At startup, state machine directly goes in the [active active] state. */
  if (WatchBehavior_DW->is_c1_WatchBehavior == WatchBehavior_IN_active) {
    /* During 'active': '<S2>:91' */
    /* This state has 4 [active.operationModes operation modes] and an [active.alarmDrv alarm driver]. */
    if (WatchBehavior_DW->is_active_operationModes != 0U) {
      WatchBehavior_operationModes(WatchBehavior_Y_mode, WatchBehavior_Y_sel,
        WatchBehavior_Y_alarmDrv, WatchBehavior_B, WatchBehavior_DW);
    }

    if (WatchBehavior_DW->is_active_alarmDrv != 0U) {
      WatchBehavior_alarmDrv(WatchBehavior_Y_mode, WatchBehavior_Y_alarmDrv,
        WatchBehavior_DW);
    }
  }
}

/* Model step function */
void WatchBehavior_step(RT_MODEL_WatchBehavior_T *const WatchBehavior_M,
  boolean_T WatchBehavior_U_plus, boolean_T WatchBehavior_U_minus, boolean_T
  WatchBehavior_U_time, boolean_T WatchBehavior_U_timeset, boolean_T
  WatchBehavior_U_alarm, boolean_T WatchBehavior_U_stopwatch, boolean_T
  WatchBehavior_U_clock, boolean_T WatchBehavior_U_alarmSrv, uint8_T
  *WatchBehavior_Y_hours, uint8_T *WatchBehavior_Y_minutes, uint8_T
  *WatchBehavior_Y_seconds, uint8_T *WatchBehavior_Y_tenths, uint8_T
  *WatchBehavior_Y_mode, uint8_T *WatchBehavior_Y_sel, boolean_T
  *WatchBehavior_Y_alarmDrv)
{
  B_WatchBehavior_T *WatchBehavior_B = ((B_WatchBehavior_T *)
    WatchBehavior_M->blockIO);
  DW_WatchBehavior_T *WatchBehavior_DW = ((DW_WatchBehavior_T *)
    WatchBehavior_M->dwork);
  PrevZCX_WatchBehavior_T *WatchBehavior_PrevZCX = ((PrevZCX_WatchBehavior_T *)
    WatchBehavior_M->prevZCSigState);
  boolean_T zcEvent[8];
  boolean_T tmp;
  int32_T i;
  int8_T rtb_inputevents_idx_1;
  int8_T rtb_inputevents_idx_2;
  int8_T rtb_inputevents_idx_3;
  int8_T rtb_inputevents_idx_4;
  int8_T rtb_inputevents_idx_5;
  int8_T rtb_inputevents_idx_6;
  int8_T rtb_inputevents_idx_7;

  /* Chart: '<S1>/StateMachine' incorporates:
   *  TriggerPort: '<S2>/input events'
   */
  /* Inport: '<Root>/plus' */
  zcEvent[0] = (((WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[0] == POS_ZCSIG)
                 != (int32_T)WatchBehavior_U_plus) &&
                (WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[0] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/minus' */
  zcEvent[1] = (((WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[1] == POS_ZCSIG)
                 != (int32_T)WatchBehavior_U_minus) &&
                (WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[1] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/time' */
  zcEvent[2] = (((WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[2] == POS_ZCSIG)
                 != (int32_T)WatchBehavior_U_time) &&
                (WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[2] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/timeset' */
  zcEvent[3] = (((WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[3] == POS_ZCSIG)
                 != (int32_T)WatchBehavior_U_timeset) &&
                (WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[3] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/alarm' */
  zcEvent[4] = (((WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[4] == POS_ZCSIG)
                 != (int32_T)WatchBehavior_U_alarm) &&
                (WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[4] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/stopwatch' */
  zcEvent[5] = (((WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[5] == POS_ZCSIG)
                 != (int32_T)WatchBehavior_U_stopwatch) &&
                (WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[5] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/clock' */
  zcEvent[6] = (((WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[6] == POS_ZCSIG)
                 != (int32_T)WatchBehavior_U_clock) &&
                (WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[6] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/alarmSrv' */
  zcEvent[7] = (((WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[7] == POS_ZCSIG)
                 != (int32_T)WatchBehavior_U_alarmSrv) &&
                (WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[7] !=
                 UNINITIALIZED_ZCSIG));
  tmp = false;
  for (i = 0; i < 8; i++) {
    tmp = (tmp || zcEvent[i]);
  }

  if (tmp) {
    /* Inport: '<Root>/minus' */
    rtb_inputevents_idx_1 = (int8_T)(zcEvent[1] ? WatchBehavior_U_minus ?
      RISING_ZCEVENT : FALLING_ZCEVENT : NO_ZCEVENT);

    /* Inport: '<Root>/time' */
    rtb_inputevents_idx_2 = (int8_T)(zcEvent[2] ? WatchBehavior_U_time ?
      RISING_ZCEVENT : FALLING_ZCEVENT : NO_ZCEVENT);

    /* Inport: '<Root>/timeset' */
    rtb_inputevents_idx_3 = (int8_T)(zcEvent[3] ? WatchBehavior_U_timeset ?
      RISING_ZCEVENT : FALLING_ZCEVENT : NO_ZCEVENT);

    /* Inport: '<Root>/alarm' */
    rtb_inputevents_idx_4 = (int8_T)(zcEvent[4] ? WatchBehavior_U_alarm ?
      RISING_ZCEVENT : FALLING_ZCEVENT : NO_ZCEVENT);

    /* Inport: '<Root>/stopwatch' */
    rtb_inputevents_idx_5 = (int8_T)(zcEvent[5] ? WatchBehavior_U_stopwatch ?
      RISING_ZCEVENT : FALLING_ZCEVENT : NO_ZCEVENT);

    /* Inport: '<Root>/clock' */
    rtb_inputevents_idx_6 = (int8_T)(zcEvent[6] ? WatchBehavior_U_clock ?
      RISING_ZCEVENT : FALLING_ZCEVENT : NO_ZCEVENT);

    /* Inport: '<Root>/alarmSrv' */
    rtb_inputevents_idx_7 = (int8_T)(zcEvent[7] ? WatchBehavior_U_alarmSrv ?
      RISING_ZCEVENT : FALLING_ZCEVENT : NO_ZCEVENT);

    /* Inport: '<Root>/plus' */
    /* Gateway: WatchBehavior/StateMachine */
    if ((int8_T)(zcEvent[0] ? WatchBehavior_U_plus ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      /* Event: '<S2>:1' */
      WatchBehavior_DW->sfEvent = WatchBehavior_event_plus;
      WatchBehavior_chartstep_c1_WatchBehavior(WatchBehavior_Y_mode,
        WatchBehavior_Y_sel, WatchBehavior_Y_alarmDrv, WatchBehavior_B,
        WatchBehavior_DW);
    }

    if (rtb_inputevents_idx_1 == 1) {
      /* Event: '<S2>:2' */
      WatchBehavior_DW->sfEvent = WatchBehavior_event_minus;
      WatchBehavior_chartstep_c1_WatchBehavior(WatchBehavior_Y_mode,
        WatchBehavior_Y_sel, WatchBehavior_Y_alarmDrv, WatchBehavior_B,
        WatchBehavior_DW);
    }

    if (rtb_inputevents_idx_2 == 1) {
      /* Event: '<S2>:3' */
      WatchBehavior_DW->sfEvent = WatchBehavior_event_time;
      WatchBehavior_chartstep_c1_WatchBehavior(WatchBehavior_Y_mode,
        WatchBehavior_Y_sel, WatchBehavior_Y_alarmDrv, WatchBehavior_B,
        WatchBehavior_DW);
    }

    if (rtb_inputevents_idx_3 == 1) {
      /* Event: '<S2>:4' */
      WatchBehavior_DW->sfEvent = WatchBehavior_event_timeset;
      WatchBehavior_chartstep_c1_WatchBehavior(WatchBehavior_Y_mode,
        WatchBehavior_Y_sel, WatchBehavior_Y_alarmDrv, WatchBehavior_B,
        WatchBehavior_DW);
    }

    if (rtb_inputevents_idx_4 == 1) {
      /* Event: '<S2>:5' */
      WatchBehavior_DW->sfEvent = WatchBehavior_event_alarm;
      WatchBehavior_chartstep_c1_WatchBehavior(WatchBehavior_Y_mode,
        WatchBehavior_Y_sel, WatchBehavior_Y_alarmDrv, WatchBehavior_B,
        WatchBehavior_DW);
    }

    if (rtb_inputevents_idx_5 == 1) {
      /* Event: '<S2>:6' */
      WatchBehavior_DW->sfEvent = WatchBehavior_event_stopwatch;
      WatchBehavior_chartstep_c1_WatchBehavior(WatchBehavior_Y_mode,
        WatchBehavior_Y_sel, WatchBehavior_Y_alarmDrv, WatchBehavior_B,
        WatchBehavior_DW);
    }

    if (rtb_inputevents_idx_6 != 0) {
      /* Event: '<S2>:7' */
      WatchBehavior_DW->sfEvent = WatchBehavior_event_clock;
      WatchBehavior_chartstep_c1_WatchBehavior(WatchBehavior_Y_mode,
        WatchBehavior_Y_sel, WatchBehavior_Y_alarmDrv, WatchBehavior_B,
        WatchBehavior_DW);
    }

    if (rtb_inputevents_idx_7 == 1) {
      /* Event: '<S2>:194' */
      WatchBehavior_DW->sfEvent = WatchBehavior_event_servedAlarm;
      WatchBehavior_chartstep_c1_WatchBehavior(WatchBehavior_Y_mode,
        WatchBehavior_Y_sel, WatchBehavior_Y_alarmDrv, WatchBehavior_B,
        WatchBehavior_DW);
    }
  }

  /* Inport: '<Root>/plus' */
  WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[0] = WatchBehavior_U_plus;

  /* Inport: '<Root>/minus' */
  WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[1] = WatchBehavior_U_minus;

  /* Inport: '<Root>/time' */
  WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[2] = WatchBehavior_U_time;

  /* Inport: '<Root>/timeset' */
  WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[3] = WatchBehavior_U_timeset;

  /* Inport: '<Root>/alarm' */
  WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[4] = WatchBehavior_U_alarm;

  /* Inport: '<Root>/stopwatch' */
  WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[5] = WatchBehavior_U_stopwatch;

  /* Inport: '<Root>/clock' */
  WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[6] = WatchBehavior_U_clock;

  /* Inport: '<Root>/alarmSrv' */
  WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[7] = WatchBehavior_U_alarmSrv;

  /* Outport: '<Root>/hours' */
  *WatchBehavior_Y_hours = WatchBehavior_B->HMST[0];

  /* Outport: '<Root>/minutes' */
  *WatchBehavior_Y_minutes = WatchBehavior_B->HMST[1];

  /* Outport: '<Root>/seconds' */
  *WatchBehavior_Y_seconds = WatchBehavior_B->HMST[2];

  /* Outport: '<Root>/tenths' */
  *WatchBehavior_Y_tenths = WatchBehavior_B->HMST[3];
}

/* Model initialize function */
void WatchBehavior_initialize(RT_MODEL_WatchBehavior_T *const WatchBehavior_M,
  boolean_T *WatchBehavior_U_plus, boolean_T *WatchBehavior_U_minus, boolean_T
  *WatchBehavior_U_time, boolean_T *WatchBehavior_U_timeset, boolean_T
  *WatchBehavior_U_alarm, boolean_T *WatchBehavior_U_stopwatch, boolean_T
  *WatchBehavior_U_clock, boolean_T *WatchBehavior_U_alarmSrv, uint8_T
  *WatchBehavior_Y_hours, uint8_T *WatchBehavior_Y_minutes, uint8_T
  *WatchBehavior_Y_seconds, uint8_T *WatchBehavior_Y_tenths, uint8_T
  *WatchBehavior_Y_mode, uint8_T *WatchBehavior_Y_sel, boolean_T
  *WatchBehavior_Y_alarmDrv)
{
  DW_WatchBehavior_T *WatchBehavior_DW = ((DW_WatchBehavior_T *)
    WatchBehavior_M->dwork);
  PrevZCX_WatchBehavior_T *WatchBehavior_PrevZCX = ((PrevZCX_WatchBehavior_T *)
    WatchBehavior_M->prevZCSigState);
  B_WatchBehavior_T *WatchBehavior_B = ((B_WatchBehavior_T *)
    WatchBehavior_M->blockIO);

  /* Registration code */

  /* block I/O */
  (void) memset(((void *) WatchBehavior_B), 0,
                sizeof(B_WatchBehavior_T));

  /* states (dwork) */
  (void) memset((void *)WatchBehavior_DW, 0,
                sizeof(DW_WatchBehavior_T));

  /* external inputs */
  *WatchBehavior_U_plus = false;
  *WatchBehavior_U_minus = false;
  *WatchBehavior_U_time = false;
  *WatchBehavior_U_timeset = false;
  *WatchBehavior_U_alarm = false;
  *WatchBehavior_U_stopwatch = false;
  *WatchBehavior_U_clock = false;
  *WatchBehavior_U_alarmSrv = false;

  /* external outputs */
  (*WatchBehavior_Y_hours) = 0U;
  (*WatchBehavior_Y_minutes) = 0U;
  (*WatchBehavior_Y_seconds) = 0U;
  (*WatchBehavior_Y_tenths) = 0U;
  (*WatchBehavior_Y_mode) = 0U;
  (*WatchBehavior_Y_sel) = 0U;
  (*WatchBehavior_Y_alarmDrv) = false;

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      WatchBehavior_PrevZCX->StateMachine_Trig_ZCE[i] = UNINITIALIZED_ZCSIG;
    }

    /* SystemInitialize for Chart: '<S1>/StateMachine' */
    WatchBehavior_DW->is_active_alarmDrv = 0U;
    WatchBehavior_DW->is_alarmDrv = WatchBehavior_IN_NO_ACTIVE_CHILD;
    WatchBehavior_DW->is_active_operationModes = 0U;
    WatchBehavior_DW->is_operationModes = WatchBehavior_IN_NO_ACTIVE_CHILD;
    WatchBehavior_DW->is_active_modes_b = 0U;
    WatchBehavior_DW->is_modes_g = WatchBehavior_IN_NO_ACTIVE_CHILD;
    WatchBehavior_DW->was_modes = WatchBehavior_IN_NO_ACTIVE_CHILD;
    WatchBehavior_DW->is_active_selection_n = 0U;
    WatchBehavior_DW->is_selection_m = WatchBehavior_IN_NO_ACTIVE_CHILD;
    WatchBehavior_DW->is_stopwatch = WatchBehavior_IN_NO_ACTIVE_CHILD;
    WatchBehavior_DW->is_active_modes = 0U;
    WatchBehavior_DW->is_modes = WatchBehavior_IN_NO_ACTIVE_CHILD;
    WatchBehavior_DW->is_active_selection = 0U;
    WatchBehavior_DW->is_selection = WatchBehavior_IN_NO_ACTIVE_CHILD;
    WatchBehavior_DW->is_c1_WatchBehavior = WatchBehavior_IN_NO_ACTIVE_CHILD;
    WatchBehavior_DW->sfEvent = WatchBehavior_CALL_EVENT;

    /* Entry: WatchBehavior/StateMachine */
    /* Entry Internal: WatchBehavior/StateMachine */
    /* Transition: '<S2>:25' */
    if (WatchBehavior_DW->is_c1_WatchBehavior != WatchBehavior_IN_active) {
      WatchBehavior_DW->is_c1_WatchBehavior = WatchBehavior_IN_active;

      /* Entry 'active': '<S2>:91' */
      /* '<S2>:91:1' hmst=uint8([0 0 0 0]); */
      WatchBehavior_DW->hmst[0] = 0U;
      WatchBehavior_DW->hmst[1] = 0U;
      WatchBehavior_DW->hmst[2] = 0U;
      WatchBehavior_DW->hmst[3] = 0U;

      /* '<S2>:91:1' hmstAlarm=uint8([0 0]); */
      WatchBehavior_DW->hmstAlarm[0] = 0U;
      WatchBehavior_DW->hmstAlarm[1] = 0U;
    }

    /* Entry Internal 'active': '<S2>:91' */
    WatchBehavior_DW->is_active_operationModes = 1U;

    /* Entry Internal 'operationModes': '<S2>:22' */
    /* Transition: '<S2>:28' */
    if (WatchBehavior_DW->is_operationModes != WatchBehavior_IN_time) {
      WatchBehavior_DW->is_operationModes = WatchBehavior_IN_time;

      /* SystemInitialize for Outport: '<Root>/mode' */
      /* Entry 'time': '<S2>:13' */
      /* '<S2>:13:1' Mode=uint8(0); */
      *WatchBehavior_Y_mode = 0U;

      /* SystemInitialize for Outport: '<Root>/sel' */
      /* '<S2>:13:1' Sel=uint8(0); */
      *WatchBehavior_Y_sel = 0U;
    }

    WatchBehavior_DW->is_active_alarmDrv = 1U;

    /* Entry Internal 'alarmDrv': '<S2>:90' */
    /* Transition: '<S2>:94' */
    if (WatchBehavior_DW->is_alarmDrv != WatchBehavior_IN_unset) {
      WatchBehavior_DW->is_alarmDrv = WatchBehavior_IN_unset;

      /* SystemInitialize for Outport: '<Root>/alarmDrv' */
      /* Entry 'unset': '<S2>:93' */
      /* '<S2>:93:1' Alarm=false; */
      *WatchBehavior_Y_alarmDrv = false;
    }

    /* End of SystemInitialize for Chart: '<S1>/StateMachine' */
  }
}

/* Model terminate function */
void WatchBehavior_terminate(RT_MODEL_WatchBehavior_T *const WatchBehavior_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(WatchBehavior_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
