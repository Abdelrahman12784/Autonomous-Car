/*
 * interrupt.h
 *
 *  Created on: Oct 16, 2021
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef MCAL_INTERRUPT_H_
#define MCAL_INTERRUPT_H_

#define ISR(vect_num) 		void vect_num (void)__attribute__((signal));\
							void vect_num (void)

#define VECT_INT0			__vector_1
#define VECT_INT1			__vector_2
#define VECT_INT2			__vector_3

#define VECT_TIMER2_CTC		__vector_4
#define VECT_TIMER2_OVF		__vector_5
#define VECT_TIMER1_ICU		__vector_6
#define VECT_TIMER1A_CTC	__vector_7
#define VECT_TIMER1B_CTC	__vector_8
#define VECT_TIMER1_OVF		__vector_9
#define VECT_TIMER0_CTC		__vector_10
#define VECT_TIMER0_OVF		__vector_11

#define VECT_ADC			__vector_16

/*for (i=0; i<660 ; i++)
	for (j=0;j<660;j++)
		asm("NOP");*/

#endif /* MCAL_INTERRUPT_H_ */
