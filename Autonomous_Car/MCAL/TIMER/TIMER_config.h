/*
 * TIMER_config.h
 *
 *  Created on: Mar 18, 2022
 *      Author: user
 */

#ifndef MCAL_TIMER_TIMER_CONFIG_H_
#define MCAL_TIMER_TIMER_CONFIG_H_

#define TIMER_NUM		2

typedef struct {
	u8 Timer_Num;
	u8 Timer_Mode;
	u8 ComA_Mode;
	u8 ComB_Mode;
	u8 Prescaler;
	u8 OF_INT_Mode;
	u8 CTCA_INT_Mode;
	u8 CTCB_INT_Mode;
}Timer_t;

#endif /* MCAL_TIMER_TIMER_CONFIG_H_ */
