/*
 * EXTI_priv.h
 *
 *  Created on: Feb 12, 2022
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef MCAL_EXTI_EXTI_PRIV_H_
#define MCAL_EXTI_EXTI_PRIV_H_

#define LOW_LEVEL			58
#define ANY_LOGIC			74
#define RISING				12
#define FALLING				96

#define ENABLED				1
#define DISABLED			0

#define INT0_ID				0
#define INT1_ID				1
#define INT2_ID				2

#define GICR		*((volatile u8*)0x5B) /*General Interrupt Control Register (PIE)*/
#define GICR_INT0	6	/*INT0 PIE bit*/
#define GICR_INT1	7   /*INT1 PIE bit*/
#define GICR_INT2	5   /*INT2 PIE bit*/

#define MCUCR			*((volatile u8*)0x55) /*MCU Sense Control Register*/
#define MCUCR_ISC11		3		/*Interrupt 1 Sense Control bit 1*/
#define MCUCR_ISC10     2		/*Interrupt 1 Sense Control bit 0*/
#define MCUCR_ISC01     1		/*Interrupt 0 Sense Control bit 1*/
#define MCUCR_ISC00     0		/*Interrupt 0 Sense Control bit 0*/

#define MCUCSR			*((volatile u8*)0x54) /*MCU Sense Control Register*/
#define MCUCSR_ISC2     6	/*Interrupt 2 Sense Control*/


#endif /* MCAL_EXTI_EXTI_PRIV_H_ */
