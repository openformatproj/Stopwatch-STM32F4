#ifndef WATCH_BEHAVIOR_H
#define WATCH_BEHAVIOR_H

#include "../rt_types.h"

/* Output variables */

unsigned int* Hmst;
unsigned int* Mode;
unsigned int* Sel;
boolean* Alarm;

/* Init state machine */

void initSM ();

/* Dispatch events to state machine */

void dispatchSM (const unsigned int i);

#endif /* WATCH_BEHAVIOR_H */
