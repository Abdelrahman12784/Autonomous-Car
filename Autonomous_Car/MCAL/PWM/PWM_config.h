/*
 * PWM_config.h
 *
 *  Created on: Mar 26, 2022
 *      Author: user
 */

#ifndef MCAL_PWM_PWM_CONFIG_H_
#define MCAL_PWM_PWM_CONFIG_H_

#define PWM_WAVE_NUM		1

typedef struct {
	u8 Timer_Num;
	u8 PWM_Mode;
	u8 ComA_Mode;
	u8 ComB_Mode;
	u8 Prescaler;
}PWM_t;

#endif /* MCAL_PWM_PWM_CONFIG_H_ */
