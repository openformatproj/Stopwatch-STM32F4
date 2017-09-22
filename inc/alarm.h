/*
 * alarm.h
 *
 *  Created on: 17 gen 2017
 *      Author: Alessandro
 */

#ifndef INC_ALARM_H_
#define INC_ALARM_H_

#include "rt_types.h"

/*
 * Max value of counter
 */

#define MAXCOUNT 256

void stopAlarm (void);
boolean launchAlarm (unsigned int* counter);

#endif /* INC_ALARM_H_ */
