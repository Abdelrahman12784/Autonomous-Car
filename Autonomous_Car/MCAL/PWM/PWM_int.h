/*
 * PWM_int.h
 *
 *  Created on: Mar 26, 2022
 *      Author: user
 */

#ifndef MCAL_PWM_PWM_INT_H_
#define MCAL_PWM_PWM_INT_H_

ES_t PWM_enuInit(PWM_t * Copy_pAstrPWMWaveConfig);

ES_t PWM_enuSetPrescaler(PWM_t * Copy_pstrPWMWaveConfig, u8 Copy_u8Prescaler);

ES_t PWM_enuSetOutputCompare(u8 Copy_u8OCR, u16 Copy_u16OCValue);// set OCR register

ES_t PWM_enuSetOCRMode(u8 Copy_u8OCR ,u8 Copy_u8OCRMode);

ES_t PWM_enuSetICR1(u16 Copy_u16ICR1);

#define DISCONNECTED		0

#define PHC_PWM				1
#define PHC_PWM_8BIT		1
#define PHC_PWM_9BIT		2
#define PHC_PWM_10BIT		3
#define FAST_PWM			3
#define FAST_PWM_8BIT		5
#define FAST_PWM_9BIT		6
#define FAST_PWM_10BIT		7
#define PHC_FC_PWM_TICR1 	8
#define PHC_FC_PWM_TOCR1A 	9
#define PHC_PWM_TICR1	 	10
#define PHC_PWM_TOCR1A 		11
#define FAST_PWM_TICR1	 	15
#define FAST_PWM_TOCR1A	 	16

#define CLEAR_MODE		2
#define SET_MODE		3

#define TIMER0_ID			75
#define TIMER1_ID			34
#define TIMER2_ID			88

#define T0_OCR			14
#define	T1A_OCR			23
#define	T1B_OCR			32
#define T2_OCR			41

#define PRE1			1
#define PRE8			2
#define PRE64			3
#define PRE256			4
#define PRE1024			5

#endif /* MCAL_PWM_PWM_INT_H_ */
