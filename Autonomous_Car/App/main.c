/*
 * main.c
 *
 *  Created on: Jun 9, 2022
 *      Author: user
 */

#include "../LIB/stdTypes.h"
#include "../LIB/errorState.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/TIMER/TIMER_config.h"
#include "../MCAL/TIMER/TIMER_int.h"
#include "../MCAL/EXTI0ME/EXTI_config.h"
#include "../MCAL/EXTI0ME/EXTI_int.h"
#include "../MCAL/PWM/PWM_config.h"
#include "../MCAL/PWM/PWM_int.h"
#include "../HAL/LCD/LCD_int.h"

#include <util/delay.h>
#include "Autonomous_Car_Config.h"

u16 Temp = 0;//<--- Distance of Right direction --->

int main(void){
	ULTR_T ultr = {0,0,0,0};
	LCD_enuInit();
	//	<--- Motors --->
	DIO_enuSetPinDirection(Moto1_Group1 ,Moto1_Pin1 ,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(Moto1_Group2 ,Moto1_Pin2 ,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(Moto2_Group1 ,Moto2_Pin1 ,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(Moto2_Group2 ,Moto2_Pin2 ,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(PuzzerGroup,PuzzerPin,DIO_u8OUTPUT);
	DIO_enuSetPinValue(PuzzerGroup,PuzzerPin,DIO_u8HIGH);
	_delay_ms(100);
	DIO_enuSetPinValue(PuzzerGroup,PuzzerPin,DIO_u8LOW);
	//	<--- Timer And EXTI For UltraSonic --->
	Timer_enuInit(Timer_AstrTimerConfig);
	Timer_enuCallBack(T0_OVF_INT,ICR_TIMER0,&ultr);
	Timer_enuCallBack(T1A_CTC_INT,ICR_TIMER1,&ultr);
	Timer_enuSetOutputCompare(T1A_OCR,160);
	DIO_enuSetPinDirection(TRIGERGROUP,TRIGERPIN,DIO_u8OUTPUT);
	DIO_enuSetPinValue(TRIGERGROUP,TRIGERPIN,DIO_u8LOW);
	_delay_ms(500);
	EXTI_enuInit(EXTI_AstrEXTIConfig);
	EXTI_enuCallBack(EXTI_AstrEXTIConfig,ICR_EXTI,&ultr);
	DIO_enuSetPinDirection(ECHOGROUP,ECHOPIN,DIO_u8INPUT);
	DIO_enuSetPinValue(ECHOGROUP,ECHOPIN,DIO_u8FLOAT);
	//	<--- PWM For Servo --->
	PWM_enuInit(PWM_AstrPWMConfig);
	DIO_enuSetPinDirection(DIO_u8GROUP_D,DIO_u8PIN7,DIO_u8OUTPUT);
	PWM_enuSetOutputCompare(T2_OCR,Forward_Direction);
	_delay_ms(400);
	GIE_enuEnable();
	while(1){
		u16 Distance = Ultrasonic(&ultr);
		if(Distance > Minimum_Distance){
			Movement(Forward);
		}
		while(Distance > Minimum_Distance){
			Distance = Ultrasonic(&ultr);
		}
		Movement(Stop);
		PWM_enuSetOutputCompare(T2_OCR,Right_Direction);
		_delay_ms(100);
		Distance = Ultrasonic(&ultr);
		PWM_enuSetOutputCompare(T2_OCR,Left_Direction);
		_delay_ms(200);
		Temp = Ultrasonic(&ultr);
		PWM_enuSetOutputCompare(T2_OCR,Forward_Direction);
		if(Distance > Minimum_Distance || Temp > Minimum_Distance){
			if(Distance >= Temp){
				Movement(Right);
				_delay_ms(Time_Of_Quarter_Cycle);
				Movement(Stop);
			}
			else if(Distance < Temp){
				Movement(Left);
				_delay_ms(Time_Of_Quarter_Cycle);
				Movement(Stop);
			}
		}
		else{
			DIO_enuSetPinValue(PuzzerGroup,PuzzerPin,DIO_u8HIGH);
			_delay_ms(100);
			DIO_enuSetPinValue(PuzzerGroup,PuzzerPin,DIO_u8LOW);
			Movement(TurnRound);
			_delay_ms(300);
			Movement(Stop);
		}
	}
}

u16 Ultrasonic(ULTR_T * ptr){
	u16 Distance = 0;
	while(Distance == 0 || Distance > 400){
		DIO_enuSetPinValue(TRIGERGROUP,TRIGERPIN,DIO_u8HIGH);
		Timer_enuSetPrescaler((Timer_AstrTimerConfig + 1),PRE1);
		Timer_enuSetTCNT((Timer_AstrTimerConfig + 1),0);
		ptr->state_EXTI = 0;
		while(!(ptr->state_EXTI == 2));
		EXTI_enuSetSenseLvl(EXTI_AstrEXTIConfig,RISING);
		s32 time = (((ptr->Counter_ULTR * 256ul)+ptr->TCNT_ULTR)*1000ul) / 16000ul;
		Distance = (((time * 34)/1000) / 2);
	}
	return Distance;
}

void ICR_EXTI(void * x){
	ULTR_T *ptr = x;
	if(ptr->state_EXTI == 0){
		ptr->Counter = 0;
		Timer_enuSetTCNT(Timer_AstrTimerConfig,0);
		EXTI_enuSetSenseLvl(EXTI_AstrEXTIConfig,FALLING);
		ptr->state_EXTI = 1;
	}
	else if(ptr->state_EXTI == 1){
		Timer_enuReadTCNT(Timer_AstrTimerConfig,&ptr->TCNT_ULTR);
		ptr->Counter_ULTR = ptr->Counter;
		ptr->state_EXTI = 2;
	}
}

void ICR_TIMER0(void * x){
	ULTR_T *ptr = x;
	ptr->Counter++;
}

void ICR_TIMER1(void * x){
	DIO_enuSetPinValue(TRIGERGROUP,TRIGERPIN,DIO_u8LOW);
	Timer_enuSetPrescaler((Timer_AstrTimerConfig + 1),0);
}
void Movement(u8 Movment_state){
	if(Movment_state == Stop){
		DIO_enuSetPinValue(Moto1_Group1 ,Moto1_Pin1 ,DIO_u8LOW);
		DIO_enuSetPinValue(Moto1_Group2 ,Moto1_Pin2 ,DIO_u8LOW);
		DIO_enuSetPinValue(Moto2_Group1 ,Moto2_Pin1 ,DIO_u8LOW);
		DIO_enuSetPinValue(Moto2_Group2 ,Moto2_Pin2 ,DIO_u8LOW);
		LCD_enuWriteCommand(0x80);
		LCD_enuSendString("         ");
		LCD_enuWriteCommand(0x80);
		LCD_enuSendString("Stop");
	}
	else{
		LCD_enuWriteCommand(0x80);
		LCD_enuSendString("         ");
		LCD_enuWriteCommand(0x80);
		if(Movment_state == Forward)
			LCD_enuSendString("Forward");
		else if(Movment_state == Right)
			LCD_enuSendString("Right");
		else if(Movment_state == Left)
			LCD_enuSendString("Left");
		else if(Movment_state == Backward)
			LCD_enuSendString("Backward");
		else if(Movment_state == TurnRound)
			LCD_enuSendString("TurnRound");
		DIO_enuSetPinValue(Moto1_Group1 ,Moto1_Pin1 ,((Movment_state>>0) & 1));
		DIO_enuSetPinValue(Moto1_Group2 ,Moto1_Pin2 ,((Movment_state>>1) & 1));
		DIO_enuSetPinValue(Moto2_Group1 ,Moto2_Pin1 ,((Movment_state>>2) & 1));
		DIO_enuSetPinValue(Moto2_Group2 ,Moto2_Pin2 ,((Movment_state>>3) & 1));
	}
}
