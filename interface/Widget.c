/*
 * Widget.c
 *
 *  Created on: 21/ott/2015
 *      Author: admim
 */

#include "inc/interface/Widget.h"

#include "inc/interface/WidgetConfig.h"
#include "inc/interface/debug.h"
#include "inc/interface/stm32f4_discovery_lcd.h"

unsigned char contains(Widget *w, TPoint *point){
	if	((point->x >= w->xl) && (point->x <= w->xl + w->xw) &&
		 (point->y >= w->yt) && (point->y <= w->yt + w->yh)) {
/*		debuginfo(5, point->x, point->y, 0);
		debuginfo(6, w->xl, w->yt, 0); */
		return 1;
	}
	else
		return 0;
}

unsigned char OnTouch(const Widget ws[], TPoint *press){
	unsigned char i, res;

	res = 0;
	for(i=0; i<NUMWIDGETS; i++) {
		if (ws[i].wt == BUTTONICON) {
			if(contains(&ws[i], press)) {
				setEvent(biconinfo(&ws[i])->onpress);
 			    res = 1;
 			}
		}
	}
	return res;
}

unsigned char DrawInit(Widget ws[])
{
	unsigned char i;
	for(i=0; i<NUMWIDGETS; i++) {
		DrawOff(&ws[i]);
	}
	return 1;
}

unsigned char DrawOn(Widget *w)
{
	char *imgptr = 0;

	switch (w->wt) {
	case BUTTONICON:
		imgptr = biconinfo(w)->iconp;
		break;
	case BACKGROUND:
	case IMAGE:
		imgptr = imginfo(w)->image;
		break;
	}
	if (imgptr != 0) {
		LCD_DrawPicture(w->xl, w->yt, w->xw, w->yh, imgptr);
		return 1;
	} else
		return 0;
}

unsigned char DrawOff(Widget *w)
{
	char *imgptr = 0;

	switch (w->wt) {
	case BUTTONICON:
		imgptr = biconinfo(w)->iconr;
		break;
	case BACKGROUND:
	case IMAGE:
		imgptr = imginfo(w)->image;
		break;
	}
	if (imgptr != 0) {
		LCD_DrawPicture(w->xl, w->yt, w->xw, w->yh, imgptr);
		return 1;
	}
		return 0;
}

unsigned char WPrint(Widget *w, char *s)
{
	if (w->wt == TEXT) {
		if (txtinfo(w)->bmode==COLOR) {
			LCD_SetTextColor(txtinfo(w)->bcolor);
			LCD_SetBackColor(txtinfo(w)->bcolor);
			LCD_DrawFullRect(w->xl, w->yt, w->xw, w->yh);
		}
		LCD_SetTextColor(txtinfo(w)->color);
		LCD_SetFont(txtinfo(w)->font);
		LCD_DisplayStringXY(w->xl, w->yt, s);
		return 1;
	} else
		return 0;
}

unsigned char WClear(Widget *w)
{
	char nullStr[1] = "\0";
	WPrint(w,nullStr);
}




