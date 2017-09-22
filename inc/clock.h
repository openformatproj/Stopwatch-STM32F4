/*
 * clock.h
 *
 *  Created on: 17 gen 2017
 *      Author: Alessandro
 */

#ifndef INC_CLOCK_H_
#define INC_CLOCK_H_

/*
 * Quantity linearly proportional to the period of blinking:
 * for instance, if BLINK=5 period of blinking is one half
 * second
 */
#define BLINK 5

void DrawBackground (void);

void UpdateDigitsOnScreen (unsigned int blink, unsigned int sel, unsigned int* hmst_, unsigned int* hmst, unsigned int mode_, unsigned int mode);
void UpdateIconsOnScreen (unsigned int mode_, unsigned int mode);

#endif /* INC_CLOCK_H_ */
