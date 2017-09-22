/*
 * touch.h
 *
 *  Created on: 20/ott/2015
 *      Author: admim
 */

#ifndef TOUCH_H_
#define TOUCH_H_

#include "stm32f4xx.h"

typedef struct{
	int16_t x;
	int16_t y;
} TPoint;

typedef struct{
    /*scale factor for x direction*/
    float    xScale;
    /*scale factor for x direction*/
    float    yScale;
    /*Offset in x direction*/
    int  xOffset;
    /*Offset in y direction*/
    int  yOffset;
} TCal;

/* Public functions ---------------------------------------------------------*/
unsigned char  Lcd_Touch_Calibration();
unsigned char  GetTouch_SC_Async(unsigned int *xs, unsigned int *ys);
unsigned char  GetTouch_SC_Sync(unsigned int *xs, unsigned int *ys);
unsigned char  GetTouch_TC_Async(int *xs, int *ys);
unsigned char  GetTouch_TC_Sync(int *xs, int *ys);
void InitTouch(float xs, float ys, int16_t xo, int16_t yo);

#endif /* TOUCH_H_ */
