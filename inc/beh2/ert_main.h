#ifndef ERT_MAIN_H
#define ERT_MAIN_H

#include "behavior.h"

void rt_Init (unsigned int* hmst, unsigned int* mode, unsigned int* sel, boolean* alarmDrv);
void rt_OneStep (const boolean plus, const boolean minus, const boolean time, const boolean timeset, const boolean alarm, const boolean stopwatch, const boolean clock, const boolean alarmSrv);

#endif /* ERT_MAIN_H */
