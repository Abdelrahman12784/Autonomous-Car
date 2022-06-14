/*
 * PWM_prog.c
 *
 *  Created on: Mar 26, 2022
 *      Author: user
 */

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"
#include "PWM_config.h"
#include "PWM_priv.h"
#include "../interrupt.h"

extern u8 PWM_u8PWMWaveNum;

ES_t PWM_enuInit(PWM_t * Copy_pAstrPWMWaveConfig){
	ES_t Local_enuErrorState = ES_OK;
	if(Copy_pAstrPWMWaveConfig != NULL){
		for(u8 Local_u8Iter = 0; Local_u8Iter < PWM_u8PWMWaveNum; Local_u8Iter++){
			if(Copy_pAstrPWMWaveConfig[Local_u8Iter].Timer_Num == TIMER0_ID){
				if(Copy_pAstrPWMWaveConfig[Local_u8Iter].PWM_Mode == FAST_PWM){
					TCCR0 |= (0x48);
				}
				else if(Copy_pAstrPWMWaveConfig[Local_u8Iter].PWM_Mode == PHC_PWM){
					TCCR0 |=  (0x40);
					TCCR0 &= ~(0x08);
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrPWMWaveConfig[Local_u8Iter].Prescaler <= 5){
					TCCR0 |= Copy_pAstrPWMWaveConfig[Local_u8Iter].Prescaler;
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrPWMWaveConfig[Local_u8Iter].ComA_Mode <= 3){
					TCCR0 |= (Copy_pAstrPWMWaveConfig[Local_u8Iter].ComA_Mode<<4);
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
			}//end TIMER0_ID
			else if(Copy_pAstrPWMWaveConfig[Local_u8Iter].Timer_Num == TIMER1_ID){
				if(Copy_pAstrPWMWaveConfig[Local_u8Iter].PWM_Mode <= 15 &&
						Copy_pAstrPWMWaveConfig[Local_u8Iter].PWM_Mode != 0  &&
						Copy_pAstrPWMWaveConfig[Local_u8Iter].PWM_Mode != 4  &&
						Copy_pAstrPWMWaveConfig[Local_u8Iter].PWM_Mode != 12 &&
						Copy_pAstrPWMWaveConfig[Local_u8Iter].PWM_Mode != 13 ){
					TCCR1A |= ((Copy_pAstrPWMWaveConfig[Local_u8Iter].PWM_Mode) & (0x03));
					TCCR1B |= ((Copy_pAstrPWMWaveConfig[Local_u8Iter].PWM_Mode<<1) & (0x18));
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrPWMWaveConfig[Local_u8Iter].Prescaler <= 5){
					TCCR1B |= Copy_pAstrPWMWaveConfig[Local_u8Iter].Prescaler;
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrPWMWaveConfig[Local_u8Iter].ComA_Mode <= 3){
					TCCR1A |= (Copy_pAstrPWMWaveConfig[Local_u8Iter].ComA_Mode << 6);
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrPWMWaveConfig[Local_u8Iter].ComB_Mode <= 3){
					TCCR1A |= (Copy_pAstrPWMWaveConfig[Local_u8Iter].ComB_Mode << 4);
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
			}//end TIMER1_ID
			else if(Copy_pAstrPWMWaveConfig[Local_u8Iter].Timer_Num == TIMER2_ID){
				if(Copy_pAstrPWMWaveConfig[Local_u8Iter].PWM_Mode == FAST_PWM){
					TCCR2 |= (0x48);
				}
				else if(Copy_pAstrPWMWaveConfig[Local_u8Iter].PWM_Mode == PHC_PWM){
					TCCR2 |=  (0x40);
					TCCR2 &= ~(0x08);
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrPWMWaveConfig[Local_u8Iter].Prescaler <= 7){
					TCCR2 |= Copy_pAstrPWMWaveConfig[Local_u8Iter].Prescaler;
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrPWMWaveConfig[Local_u8Iter].ComA_Mode <= 3){
					TCCR2 |= (Copy_pAstrPWMWaveConfig[Local_u8Iter].ComA_Mode<<4);
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
			}//end TIMER2_ID
			else
				Local_enuErrorState = ES_OUT_OF_RANGE;
		}//end for loop
	}
	else
		Local_enuErrorState = ES_NULL_POINTER;
	return Local_enuErrorState;
}
ES_t PWM_enuSetPrescaler(PWM_t * Copy_pstrPWMWaveConfig, u8 Copy_u8Prescaler){
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pstrPWMWaveConfig != NULL){
		if(Copy_u8Prescaler <= 5){
			if(Copy_pstrPWMWaveConfig->Timer_Num == TIMER0_ID){
				TCCR0 &= ~(0x07);
				TCCR0 |= Copy_u8Prescaler;
				Local_enuErrorState = ES_OK;
			}
			else if(Copy_pstrPWMWaveConfig->Timer_Num == TIMER1_ID){
				TCCR1B &= ~(0x07);
				TCCR1B |= Copy_u8Prescaler;
				Local_enuErrorState = ES_OK;
			}
			else if(Copy_pstrPWMWaveConfig->Timer_Num == TIMER2_ID){
				TCCR2 &= ~(0x07);
				TCCR2 |= Copy_u8Prescaler;
				Local_enuErrorState = ES_OK;
			}
			else
				Local_enuErrorState = ES_OUT_OF_RANGE;
		}
	}
	else
		Local_enuErrorState = ES_NULL_POINTER;
	return Local_enuErrorState;
}

ES_t PWM_enuSetOutputCompare(u8 Copy_u8OCR, u16 Copy_u16OCValue){
	ES_t Local_enuErrorState = ES_OK;
	switch(Copy_u8OCR){
	case T0_OCR:
		OCR0 = ((u8)Copy_u16OCValue);
		break;
	case T1A_OCR:
		OCR1AH = (Copy_u16OCValue>>8);
		OCR1AL = ((u8)Copy_u16OCValue);
		break;
	case T1B_OCR:
		OCR1BH = (Copy_u16OCValue>>8);
		OCR1BL = ((u8)Copy_u16OCValue);
		break;
	case T2_OCR:
		OCR2 = ((u8)Copy_u16OCValue);
		break;
	default:
		Local_enuErrorState = ES_NOK;
	}
	return Local_enuErrorState;
}

ES_t PWM_enuSetOCRMode(u8 Copy_u8OCR ,u8 Copy_u8OCRMode){
	ES_t Local_enuErrorState = ES_OK;
	if(Copy_u8OCRMode <= 3){
		switch(Copy_u8OCR){
		case T0_OCR:
			TCCR0 |= (Copy_u8OCRMode << 4);
			break;
		case T1A_OCR:
			TCCR1A |= (Copy_u8OCRMode << 6);
			break;
		case T1B_OCR:
			TCCR1A |= (Copy_u8OCRMode << 4);
			break;
		case T2_OCR:
			TCCR2 |= (Copy_u8OCRMode << 4);
			break;
		default:
			Local_enuErrorState = ES_NOK;
		}
	}
	else
		Local_enuErrorState = ES_OUT_OF_RANGE;
	return Local_enuErrorState;
}

ES_t PWM_enuSetICR1(u16 Copy_u16ICR1){
	ICR1L = ((u8)Copy_u16ICR1);
	ICR1H = (Copy_u16ICR1>>8);
	return ES_OK;
}
