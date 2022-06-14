/*
 * PWM_config.c
 *
 *  Created on: Mar 26, 2022
 *      Author: user
 */

#include "../../LIB/stdTypes.h"
#include "PWM_config.h"
#include "PWM_priv.h"

u8 PWM_u8PWMWaveNum = PWM_WAVE_NUM;

PWM_t PWM_AstrPWMConfig [PWM_WAVE_NUM] = {
		{TIMER2_ID,FAST_PWM,CLEAR_MODE,DISCONNECTED,7}
};

