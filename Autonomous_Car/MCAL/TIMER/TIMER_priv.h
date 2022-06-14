/*
 * TIMER_priv.h
 *
 *  Created on: Feb 26, 2022
 *      Author: user
 */

#ifndef MCAL_TIMER_TIMER_PRIV_H_
#define MCAL_TIMER_TIMER_PRIV_H_

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

#endif /* MCAL_TIMER_TIMER_PRIV_H_ */
