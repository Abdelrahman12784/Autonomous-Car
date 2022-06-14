/*
 * TIMER_config.c
 *
 *  Created on: Mar 18, 2022
 *      Author: user
 */
#include "../../LIB/stdTypes.h"
#include "TIMER_config.h"
#include "TIMER_priv.h"

u8 Timer_u8TimerNum = TIMER_NUM;

Timer_t Timer_AstrTimerConfig [TIMER_NUM] = {
		{TIMER0_ID,NORMAL_MODE,DISABLED,DISCONNECTED,PRE1,ENABLED,DISABLED,DISABLED},
		{TIMER1_ID,CTC_MODE_TOP_OCA,DISABLED,DISABLED,0,DISABLED,ENABLED,DISABLED}
};

