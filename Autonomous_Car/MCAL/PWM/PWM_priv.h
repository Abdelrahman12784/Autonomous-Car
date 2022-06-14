/*
 * PWM_priv.h
 *
 *  Created on: Mar 26, 2022
 *      Author: user
 */

#ifndef MCAL_PWM_PWM_PRIV_H_
#define MCAL_PWM_PWM_PRIV_H_

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

#define TIMSK			*((volatile u8*)0x59)
#define TIFR			*((volatile u8*)0x58)

#define TCCR0			*((volatile u8*)0x53)
#define TCNT0			*((volatile u8*)0x52)
#define OCR0			*((volatile u8*)0x5C)

#define TCCR1A          *((volatile u8*)0x4F)
#define TCCR1B          *((volatile u8*)0x4E)
#define TCNT1H          *((volatile u8*)0x4D)
#define TCNT1L          *((volatile u8*)0x4C)
#define OCR1AH          *((volatile u8*)0x4B)
#define OCR1AL          *((volatile u8*)0x4A)
#define OCR1BH          *((volatile u8*)0x49)
#define OCR1BL          *((volatile u8*)0x48)
#define ICR1H			*((volatile u8*)0x47)
#define ICR1L           *((volatile u8*)0x46)

#define TCCR2			*((volatile u8*)0x45)
#define TCNT2			*((volatile u8*)0x44)
#define OCR2			*((volatile u8*)0x43)

#endif /* MCAL_PWM_PWM_PRIV_H_ */
