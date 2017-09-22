/*
 * Event.h
 *
 *  Created on: 22/ott/2015
 *      Author: admim
 */

#ifndef EVENT_H_
#define EVENT_H_

typedef unsigned char Event;

typedef unsigned char Events;
extern Events evts;

#define setEvent(Event) (evts |= Event)
#define clearEvent(Event) (evts &= !Event)
#define clearEvents() (evts = 0)
#define IsEvent(Event) ((unsigned char)(evts & Event))

#endif /* EVENT_H_ */
