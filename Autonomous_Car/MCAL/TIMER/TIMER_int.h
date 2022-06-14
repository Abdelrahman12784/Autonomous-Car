/*
 * TIMER_int.h
 *
 *  Created on: Mar 17, 2022
 *      Author: user
 */

#ifndef MCAL_TIMER_TIMER_INT_H_
#define MCAL_TIMER_TIMER_INT_H_

ES_t Timer_enuInit(Timer_t * Copy_pAstrTimerConfig);

ES_t Timer_enuSetPrescaler(Timer_t *Copy_pstrTimerConfig, u8 Copy_u8Preload);

ES_t Timer_enuSetOutputCompare(u8 Copy_u8OCR, u16 Copy_u16OCValue);// set OCR register

ES_t Timer_enuCallBack(u8 Copy_u8TimerType, void (*Copy_pfunAppFun)(void*),void *Copy_pvidAppParameter);

ES_t Timer_enuReadTCNT(Timer_t *Copy_pstrTimerConfig, u16 *Copy_pu16Value);

ES_t Timer_enuSetTCNT(Timer_t *Copy_pstrTimerConfig, u16 Copy_u16Value);

ES_t Timer_enuEnableINT(u8 Copy_u8INT);

ES_t Timer_enuDisableINT(u8 Copy_u8INT);

ES_t Timer_enuSetOCRMode(u8 Copy_u8OCR ,u8 Copy_u8OCRMode);

#define NORMAL_MODE			0	// Overflow Mode Or OC Pin Disconnected Mode
#define CTC_MODE			2
#define CTC_MODE_TOP_OCA	4
#define CTC_MODE_TOP_ICR	12

#define DISCONNECTED		0

#define TIMER0_ID			75
#define TIMER1_ID			34
#define TIMER2_ID			88

#define ENABLED				1
#define DISABLED			0

#define PRE1			1
#define PRE8			2
#define PRE64			3
#define PRE256			4
#define PRE1024			5

#define TOGGLE_MODE		1
#define CLEAR_MODE		2
#define SET_MODE		3

#define T0_OVF_INT		0
#define T0_CTC_INT		1
#define	T1_OVF_INT		2
#define	T1B_CTC_INT		3
#define	T1A_CTC_INT		4
#define	T2_OVF_INT		6
#define	T2_CTC_INT		7

#define T0_OCR			14
#define	T1A_OCR			23
#define	T1B_OCR			32
#define T2_OCR			41

#endif /* MCAL_TIMER_TIMER_INT_H_ */
