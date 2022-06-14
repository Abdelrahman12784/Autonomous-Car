/*
 * TIMER_prog.c
 *
 *  Created on: Mar 18, 2022
 *      Author: user
 */
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"

#include "TIMER_config.h"
#include "TIMER_priv.h"

#include "../interrupt.h"

extern u8 Timer_u8TimerNum;

static void (*Timer_pfunISRFun[7]) (void*) = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};
static void *Timer_pvidISRParameter[7] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};

ES_t Timer_enuInit(Timer_t * Copy_pAstrTimerConfig){
	ES_t Local_enuErrorState = ES_OK;
	if(Copy_pAstrTimerConfig != NULL){
		for(u8 Local_u8Iter = 0; Local_u8Iter < Timer_u8TimerNum; Local_u8Iter++){
			if(Copy_pAstrTimerConfig[Local_u8Iter].Timer_Num == TIMER0_ID){
				if(Copy_pAstrTimerConfig[Local_u8Iter].Timer_Mode == NORMAL_MODE){
					TCCR0 &= ~(0x48);
				}
				else if(Copy_pAstrTimerConfig[Local_u8Iter].Timer_Mode == CTC_MODE){
					TCCR0 |=  (0x08);
					TCCR0 &= ~(0x40);
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrTimerConfig[Local_u8Iter].Prescaler <= 5){
					TCCR0 |= Copy_pAstrTimerConfig[Local_u8Iter].Prescaler;
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrTimerConfig[Local_u8Iter].ComA_Mode <= 3){
					TCCR0 |= (Copy_pAstrTimerConfig[Local_u8Iter].ComA_Mode<<4);
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrTimerConfig[Local_u8Iter].OF_INT_Mode == ENABLED){
					TIMSK |= 0x01;
				}
				else if(Copy_pAstrTimerConfig[Local_u8Iter].OF_INT_Mode == DISABLED){
					TIMSK &= ~(0x01);
				}
				else
					Local_enuErrorState = ES_NOK;
				if(Copy_pAstrTimerConfig[Local_u8Iter].CTCA_INT_Mode == ENABLED){
					TIMSK |= 0x02;
				}
				else if(Copy_pAstrTimerConfig[Local_u8Iter].CTCA_INT_Mode == DISABLED){
					TIMSK &= ~(0x02);
				}
				else
					Local_enuErrorState = ES_NOK;
			}//end TIMER0_ID
			else if(Copy_pAstrTimerConfig[Local_u8Iter].Timer_Num == TIMER1_ID){
				if(Copy_pAstrTimerConfig[Local_u8Iter].Timer_Mode == NORMAL_MODE){
					TCCR1A &= ~(0x03);
					TCCR1B &= ~(0x18);
				}
				else if(Copy_pAstrTimerConfig[Local_u8Iter].Timer_Mode == CTC_MODE || Copy_pAstrTimerConfig[Local_u8Iter].Timer_Mode == CTC_MODE_TOP_OCA){
					TCCR1A &= ~(0x03);
					TCCR1B &= ~(0x18);
					TCCR1B |=  (0x08);
				}
				else if(Copy_pAstrTimerConfig[Local_u8Iter].Timer_Mode == CTC_MODE_TOP_ICR){
					TCCR1A &= ~(0x03);
					TCCR1B |=  (0x18);
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrTimerConfig[Local_u8Iter].Prescaler <= 5){
					TCCR1B |= Copy_pAstrTimerConfig[Local_u8Iter].Prescaler;
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrTimerConfig[Local_u8Iter].ComA_Mode <= 3){
					TCCR1A |= (Copy_pAstrTimerConfig[Local_u8Iter].ComA_Mode << 6);
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrTimerConfig[Local_u8Iter].ComB_Mode <= 3){
					TCCR1A |= (Copy_pAstrTimerConfig[Local_u8Iter].ComB_Mode << 4);
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrTimerConfig[Local_u8Iter].OF_INT_Mode == ENABLED){
					TIMSK |= 0x04;
				}
				else if(Copy_pAstrTimerConfig[Local_u8Iter].OF_INT_Mode == DISABLED){
					TIMSK &= ~(0x04);
				}
				else
					Local_enuErrorState = ES_NOK;
				if(Copy_pAstrTimerConfig[Local_u8Iter].CTCA_INT_Mode == ENABLED){
					TIMSK |= 0x10;
				}
				else if(Copy_pAstrTimerConfig[Local_u8Iter].CTCA_INT_Mode == DISABLED){
					TIMSK &= ~(0x10);
				}
				else
					Local_enuErrorState = ES_NOK;
				if(Copy_pAstrTimerConfig[Local_u8Iter].CTCB_INT_Mode == ENABLED){
					TIMSK |= 0x08;
				}
				else if(Copy_pAstrTimerConfig[Local_u8Iter].CTCB_INT_Mode == DISABLED){
					TIMSK &= ~(0x08);
				}
				else
					Local_enuErrorState = ES_NOK;
			}//end TIMER1_ID
			else if(Copy_pAstrTimerConfig[Local_u8Iter].Timer_Num == TIMER2_ID){
				if(Copy_pAstrTimerConfig[Local_u8Iter].Timer_Mode == NORMAL_MODE){
					TCCR2 &= ~(0x48);
				}
				else if(Copy_pAstrTimerConfig[Local_u8Iter].Timer_Mode == CTC_MODE){
					TCCR2 |=  (0x08);
					TCCR2 &= ~(0x40);
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrTimerConfig[Local_u8Iter].Prescaler <= 7){
					TCCR2 |= Copy_pAstrTimerConfig[Local_u8Iter].Prescaler;
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrTimerConfig[Local_u8Iter].ComA_Mode <= 3){
					TCCR2 |= (Copy_pAstrTimerConfig[Local_u8Iter].ComA_Mode<<4);
				}
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;
				if(Copy_pAstrTimerConfig[Local_u8Iter].OF_INT_Mode == ENABLED){
					TIMSK |= 0x40;
				}
				else if(Copy_pAstrTimerConfig[Local_u8Iter].OF_INT_Mode == DISABLED){
					TIMSK &= ~(0x40);
				}
				else
					Local_enuErrorState = ES_NOK;
				if(Copy_pAstrTimerConfig[Local_u8Iter].CTCA_INT_Mode == ENABLED){
					TIMSK |= 0x80;
				}
				else if(Copy_pAstrTimerConfig[Local_u8Iter].CTCA_INT_Mode == DISABLED){
					TIMSK &= ~(0x80);
				}
				else
					Local_enuErrorState = ES_NOK;
			}//end TIMER2_ID
			else
				Local_enuErrorState = ES_OUT_OF_RANGE;
		}//end for loop
	}
	else
		Local_enuErrorState = ES_NULL_POINTER;
	return Local_enuErrorState;
}

ES_t Timer_enuSetPrescaler(Timer_t *Copy_pstrTimerConfig, u8 Copy_u8Preload){
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pstrTimerConfig != NULL){
		if(Copy_u8Preload <= 5){
			if(Copy_pstrTimerConfig->Timer_Num == TIMER0_ID){
				TCCR0 &= ~(0x07);
				TCCR0 |= Copy_u8Preload;
				Local_enuErrorState = ES_OK;
			}
			else if(Copy_pstrTimerConfig->Timer_Num == TIMER1_ID){
				TCCR1B &= ~(0x07);
				TCCR1B |= Copy_u8Preload;
				Local_enuErrorState = ES_OK;
			}
			else if(Copy_pstrTimerConfig->Timer_Num == TIMER2_ID){
				TCCR2 &= ~(0x07);
				TCCR2 |= Copy_u8Preload;
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

ES_t Timer_enuSetOutputCompare(u8 Copy_u8OCR, u16 Copy_u16OCValue){
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

ES_t Timer_enuReadTCNT(Timer_t *Copy_pstrTimerConfig, u16 *Copy_u16Value){
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pstrTimerConfig != NULL){
		if(Copy_pstrTimerConfig->Timer_Num == TIMER0_ID){
			*Copy_u16Value = TCNT0;
			Local_enuErrorState = ES_OK;
		}
		else if(Copy_pstrTimerConfig->Timer_Num == TIMER1_ID){
			*Copy_u16Value = TCNT1L;
			*Copy_u16Value = (((u16)TCNT1H)<<8);
			Local_enuErrorState = ES_OK;
		}
		else if(Copy_pstrTimerConfig->Timer_Num == TIMER2_ID){
			*Copy_u16Value = TCNT2;
			Local_enuErrorState = ES_OK;
		}
		else
			Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	else
		Local_enuErrorState = ES_NULL_POINTER;
	return Local_enuErrorState;
}

ES_t Timer_enuSetTCNT(Timer_t *Copy_pstrTimerConfig, u16 Copy_u16Value){
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pstrTimerConfig != NULL){
		if(Copy_pstrTimerConfig->Timer_Num == TIMER0_ID){
			TCNT0 = ((u8)Copy_u16Value);
			Local_enuErrorState = ES_OK;
		}
		else if(Copy_pstrTimerConfig->Timer_Num == TIMER1_ID){
			TCNT1H = (Copy_u16Value>>8);
			TCNT1L = ((u8)Copy_u16Value);
			Local_enuErrorState = ES_OK;
		}
		else if(Copy_pstrTimerConfig->Timer_Num == TIMER2_ID){
			TCNT2 = ((u8)Copy_u16Value);
			Local_enuErrorState = ES_OK;
		}
		else
			Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	else
		Local_enuErrorState = ES_NULL_POINTER;
	return Local_enuErrorState;
}

ES_t Timer_enuEnableINT(u8 Copy_u8INT){
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_u8INT <= 7 && Copy_u8INT != 5){
		TIMSK |= (1<<Copy_u8INT);
	}
	else
		Local_enuErrorState = ES_NOK;
	return Local_enuErrorState;
}

ES_t Timer_enuDisableINT(u8 Copy_u8INT){
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_u8INT <= 7 && Copy_u8INT != 5){
		TIMSK &= ~(1<<Copy_u8INT);
	}
	else
		Local_enuErrorState = ES_NOK;
	return Local_enuErrorState;
}

ES_t Timer_enuSetOCRMode(u8 Copy_u8OCR ,u8 Copy_u8OCRMode){
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

ES_t Timer_enuCallBack(u8 Copy_u8TimerType, void (*Copy_pfunAppFun)(void*),void *Copy_pvidAppParameter){
	ES_t Local_enuErrorState = ES_OK;
	if(Copy_pfunAppFun != NULL && Copy_pvidAppParameter != NULL){
		if(Copy_u8TimerType <= 4){
			Timer_pfunISRFun[Copy_u8TimerType] = Copy_pfunAppFun;
			Timer_pvidISRParameter[Copy_u8TimerType] = Copy_pvidAppParameter;
		}
		else if(Copy_u8TimerType > 4 && Copy_u8TimerType <= 7){
			Copy_u8TimerType--;
			Timer_pfunISRFun[Copy_u8TimerType] = Copy_pfunAppFun;
			Timer_pvidISRParameter[Copy_u8TimerType] = Copy_pvidAppParameter;
		}
		else
			Local_enuErrorState = ES_NOK;
	}
	else
		Local_enuErrorState = ES_NULL_POINTER;
	return Local_enuErrorState;
}

ISR(VECT_TIMER0_OVF){
	if(Timer_pfunISRFun[0] != NULL && Timer_pvidISRParameter[0] != NULL){
		Timer_pfunISRFun[0](Timer_pvidISRParameter[0]);
	}
}

ISR(VECT_TIMER0_CTC){
	if(Timer_pfunISRFun[1] != NULL && Timer_pvidISRParameter[1] != NULL){
		Timer_pfunISRFun[1](Timer_pvidISRParameter[1]);
	}
}

ISR(VECT_TIMER1_OVF){
	if(Timer_pfunISRFun[2] != NULL && Timer_pvidISRParameter[2] != NULL){
		Timer_pfunISRFun[2](Timer_pvidISRParameter[2]);
	}
}

ISR(VECT_TIMER1B_CTC){
	if(Timer_pfunISRFun[3] != NULL && Timer_pvidISRParameter[3] != NULL){
		Timer_pfunISRFun[3](Timer_pvidISRParameter[3]);
	}
}

ISR(VECT_TIMER1A_CTC){
	if(Timer_pfunISRFun[4] != NULL && Timer_pvidISRParameter[4] != NULL){
		Timer_pfunISRFun[4](Timer_pvidISRParameter[4]);
	}
}

ISR(VECT_TIMER2_OVF){
	if(Timer_pfunISRFun[5] != NULL && Timer_pvidISRParameter[5] != NULL){
		Timer_pfunISRFun[5](Timer_pvidISRParameter[5]);
	}
}

ISR(VECT_TIMER2_CTC){
	if(Timer_pfunISRFun[6] != NULL && Timer_pvidISRParameter[6] != NULL){
		Timer_pfunISRFun[6](Timer_pvidISRParameter[6]);
	}
}
