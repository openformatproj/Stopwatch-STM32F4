/*
 * clock.c
 *
 *  Created on: 17 gen 2017
 *      Author: Alessandro Trifoglio
 */

#include "inc/clock.h"

#include "inc/rt_types.h"
#include "inc/interface/WidgetConfig.h"
#include "inc/interface/stm32f4_discovery_lcd.h"

char tstr[3];														// Buffer containing digits to display

/* Draw the background */

void DrawBackground ()
{
	DrawInit(MyWatchScr);
	LCD_SetTextColor(Black);
	LCD_SetBackColor(Black);
	LCD_DrawFullRect(28, 62, 200, 56);
	DrawOn(&MyWatchScr[BTIME]);
	WPrint(&MyWatchScr[SEP1STR], ":");
	WPrint(&MyWatchScr[SEP2STR], ":");
	//WPrint(&MyWatchScr[SEP3STR], ".");
}

/* Decode an integer format into a vector of digits */

void strencode2digit (unsigned int digit)
{
	tstr[2]=0;
	tstr[0]=digit/10+'0';
	tstr[1]=digit%10+'0';
}

void strencode1digit (unsigned int digit)
{
	tstr[1]=0;
	tstr[0]=digit%10+'0';
}

/* Update digits on the screen according to the new values (and the new mode) */

void UpdateDigitsOnScreen (unsigned int blink, unsigned int sel, unsigned int* hmst_, unsigned int* hmst, unsigned int mode_, unsigned int mode)
{

	static boolean clearedDigit[4] = {false,false,false,false};
	int digitToClear = (blink==0)*sel;
	int digitToReprint = (blink==(BLINK-1)/2)*sel;

	/* Update hours and minutes anyway */
	if (digitToClear==1) {
		WClear(&MyWatchScr[HRSSTR]);
		clearedDigit[0] = true;
	} else
	if (hmst[0]!=hmst_[0] || digitToReprint==1 || (clearedDigit[0] && sel!=1)) {
		strencode2digit(hmst[0]);
		WPrint(&MyWatchScr[HRSSTR], tstr);
		clearedDigit[0] = false;
	}

	if (digitToClear==2) {
		WClear(&MyWatchScr[MINSTR]);
		clearedDigit[1] = true;
	} else
	if (hmst[1]!=hmst_[1] || digitToReprint==2 || (clearedDigit[1] && sel!=2)) {
		strencode2digit(hmst[1]);
		WPrint(&MyWatchScr[MINSTR], tstr);
		clearedDigit[1] = false;
	}
	/* Update the other digits according to particular mode transitions */
	if ((mode_==1 || mode_==2) && (mode==0 || mode==3)) { 			// If previous mode is 'timeset' or 'alarm' and the new one is 'time' or 'stopwatch'
		WPrint(&MyWatchScr[SEP2STR], ":");
		strencode2digit(hmst[2]);
		WPrint(&MyWatchScr[SECSTR], tstr);
		if (mode==3) {
			WPrint(&MyWatchScr[SEP3STR], ".");
			strencode1digit(hmst[3]);
			WPrint(&MyWatchScr[TTSSTR], tstr);
		}
	} else
	if ((mode_==0 || mode_==3) && (mode==1 || mode==2)) { 			// If previous mode is 'time' or 'stopwatch' and the new one is 'timeset' or 'alarm'
		if (mode_==3) {
			WClear(&MyWatchScr[TTSSTR]);
			WClear(&MyWatchScr[SEP3STR]);
		}
		WClear(&MyWatchScr[SECSTR]);
		WClear(&MyWatchScr[SEP2STR]);
	} else
	if (mode_==0 && mode==3) { 										// If previous mode is 'time' and the new one is 'stopwatch'
		if (hmst[2]!=hmst_[2]) {
			strencode2digit(hmst[2]);
			WPrint(&MyWatchScr[SECSTR], tstr);
		}
		WPrint(&MyWatchScr[SEP3STR], ".");
		strencode1digit(hmst[3]);
		WPrint(&MyWatchScr[TTSSTR], tstr);
	} else
	if (mode_==3 && mode==0) { 										// If previous mode is 'stopwatch' and the new one is 'time'
		WClear(&MyWatchScr[TTSSTR]);
		WClear(&MyWatchScr[SEP3STR]);
		if (hmst[2]!=hmst_[2]) {
			strencode2digit(hmst[2]);
			WPrint(&MyWatchScr[SECSTR], tstr);
		}
	} else
	if (mode_==mode) { 												// If previous mode and new mode are the same
		if (mode==0 || mode==3) {
			if (digitToClear==3) {
				WClear(&MyWatchScr[SECSTR]);
				clearedDigit[2] = true;
			} else
			if (hmst[2]!=hmst_[2] || digitToReprint==3 || (clearedDigit[2] && sel!=3)) {
				strencode2digit(hmst[2]);
				WPrint(&MyWatchScr[SECSTR], tstr);
				clearedDigit[2] = false;
			}
		}
		if (mode==3) {
			if (digitToClear==4) {
				WClear(&MyWatchScr[TTSSTR]);
				clearedDigit[3] = true;
			} else
			if (hmst[3]!=hmst_[3] || digitToReprint==4 || (clearedDigit[3] && sel!=4)) {
				strencode1digit(hmst[3]);
				WPrint(&MyWatchScr[TTSSTR], tstr);
				clearedDigit[3] = false;
			}
		}
	}

}

/* Update button icons on the screen according to the new mode of operation */

void UpdateIconsOnScreen (unsigned int mode_, unsigned int mode)
{
	switch(mode_) {
		case 0:
			DrawOff(&MyWatchScr[BTIME]);
			break;
		case 1:
			DrawOff(&MyWatchScr[BTIMESET]);
			break;
		case 2:
			DrawOff(&MyWatchScr[BALARM]);
			break;
		case 3:
			DrawOff(&MyWatchScr[BSWATCH]);
			break;
	}
	switch(mode) {
		case 0:
			DrawOn(&MyWatchScr[BTIME]);
			break;
		case 1:
			DrawOn(&MyWatchScr[BTIMESET]);
			break;
		case 2:
			DrawOn(&MyWatchScr[BALARM]);
			break;
		case 3:
			DrawOn(&MyWatchScr[BSWATCH]);
			break;
	}
}
