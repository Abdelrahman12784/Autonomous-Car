/*
 * Autonomous_Car_Config.h
 *
 *  Created on: Jun 9, 2022
 *      Author: user
 */

#ifndef APP_AUTONOMOUS_CAR_CONFIG_H_
#define APP_AUTONOMOUS_CAR_CONFIG_H_

typedef struct {
	u16 Counter;
	u8 state_EXTI;
	u8 TCNT_ULTR;
	u16 Counter_ULTR;
}ULTR_T;

void ICR_TIMER0(void * x);
void ICR_TIMER1(void * x);
void ICR_EXTI(void * x);
void Movement(u8 Movment_state);
u16 Ultrasonic(ULTR_T * ptr);

extern Timer_t Timer_AstrTimerConfig [TIMER_NUM];
extern PWM_t PWM_AstrPWMConfig [PWM_WAVE_NUM];
extern EXTI_t EXTI_AstrEXTIConfig [INT_NUM];

#define Minimum_Distance	30
#define Time_Of_Quarter_Cycle	280

#define PuzzerGroup			DIO_u8GROUP_C
#define PuzzerPin		    DIO_u8PIN5

//<--- ultrasonic configuration --->
#define TRIGERGROUP		    DIO_u8GROUP_C
#define TRIGERPIN		    DIO_u8PIN2
#define ECHOGROUP		    DIO_u8GROUP_D
#define ECHOPIN			    DIO_u8PIN3

//<--- Rc Car configuration --->
#define Moto1_Pin1		    DIO_u8PIN0
#define Moto1_Pin2		    DIO_u8PIN1
#define Moto2_Pin1		    DIO_u8PIN2
#define Moto2_Pin2		    DIO_u8PIN3
#define Moto1_Group1		DIO_u8GROUP_B
#define Moto1_Group2		DIO_u8GROUP_B
#define Moto2_Group1		DIO_u8GROUP_B
#define Moto2_Group2		DIO_u8GROUP_B

//<--- Movement States --->
#define Stop		0
#define Right		8
#define Left		1
#define Forward		9
#define Backward	6
#define TurnRound	5

//<--- Movement States --->
#define Right_Direction		4
#define Left_Direction		34
#define Forward_Direction	19

#endif /* APP_AUTONOMOUS_CAR_CONFIG_H_ */
