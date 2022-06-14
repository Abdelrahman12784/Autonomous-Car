/*
 * EXTI_pro.c
 *
 *  Created on: Feb 12, 2022
 *      Author: Ahmed El-Gaafrawy
 */
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"

#include "EXTI_config.h"
#include "EXTI_priv.h"

static void (* EXTI_ApfunISRFun[3])(void*)= {NULL, NULL,NULL};
static void * EXTI_ApvidISRParameter[3] = {NULL, NULL,NULL};

extern u8 EXTI_u8IntNum;

ES_t EXTI_enuInit(EXTI_t * Copy_pAstrEXTIConfig){
	ES_t Local_enuErrorState = ES_NOK;
	if (Copy_pAstrEXTIConfig != NULL){
		for (u8 Local_u8EXTIter = 0; Local_u8EXTIter < EXTI_u8IntNum; Local_u8EXTIter++){
			if (Copy_pAstrEXTIConfig[Local_u8EXTIter].intNum == INT0_ID){
				MCUCR &=~(3<<0);
				switch (Copy_pAstrEXTIConfig[Local_u8EXTIter].senseLvl){
				case LOW_LEVEL: break;
				case ANY_LOGIC:
					MCUCR |=(1<<0);
					break;
				case FALLING:
					MCUCR |=(2<<0);
					break;
				case RISING:
					MCUCR |=(3<<0);
					break;
				default:
					Local_enuErrorState = ES_NOK;}
				if (Copy_pAstrEXTIConfig[Local_u8EXTIter].intMode == ENABLED)
					GICR |= (1<<GICR_INT0);
				else if (Copy_pAstrEXTIConfig[Local_u8EXTIter].intMode == DISABLED)
					GICR &=~(1<<GICR_INT0);
			}
			else if (Copy_pAstrEXTIConfig[Local_u8EXTIter].intNum == INT1_ID){
				MCUCR &=~(3<<2);
				switch (Copy_pAstrEXTIConfig[Local_u8EXTIter].senseLvl){
				case LOW_LEVEL: break;
				case ANY_LOGIC:
					MCUCR |=(1<<2);
					break;
				case FALLING:
					MCUCR |=(2<<2);
					break;
				case RISING:
					MCUCR |=(3<<2);
					break;
				default:
					Local_enuErrorState = ES_OUT_OF_RANGE;}
				if (Copy_pAstrEXTIConfig[Local_u8EXTIter].intMode == ENABLED)
					GICR |= (1<<GICR_INT1);
				else if (Copy_pAstrEXTIConfig[Local_u8EXTIter].intMode == DISABLED)
					GICR &=~(1<<GICR_INT1);
				else
					Local_enuErrorState = ES_OUT_OF_RANGE;}
			else if (Copy_pAstrEXTIConfig[Local_u8EXTIter].intNum == INT2_ID){
				MCUCSR &=~(1<<6);
				switch (Copy_pAstrEXTIConfig[Local_u8EXTIter].senseLvl){
				case FALLING:
					break;
				case RISING:
					MCUCSR |=(1<<6);
					break;
				default:
					Local_enuErrorState = ES_OUT_OF_RANGE;}
				if (Copy_pAstrEXTIConfig[Local_u8EXTIter].intMode == ENABLED)
					GICR |= (1<<GICR_INT2);
				else if (Copy_pAstrEXTIConfig[Local_u8EXTIter].intMode == DISABLED)
					GICR &=~(1<<GICR_INT2); }
			else // FOR intNum
				Local_enuErrorState = ES_OUT_OF_RANGE;
		}// End For Loop
	}// End IF ! NULL
	else
		Local_enuErrorState = ES_NULL_POINTER;
	return Local_enuErrorState;}

ES_t EXTI_enuSetSenseLvl(EXTI_t * Copy_pstrEXTIConfig, u8 Copy_u8SenseLvl){
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pstrEXTIConfig != NULL){
		if(Copy_pstrEXTIConfig->intNum == INT0_ID){
			MCUCR &= ~(3<<0);
			switch(Copy_u8SenseLvl){
			case LOW_LEVEL:
				break;
			case ANY_LOGIC:
				MCUCR |= (1<<0); break;
			case FALLING:
				MCUCR |= (2<<0); break;
			case RISING:
				MCUCR |= (3<<0); break;
			default:
				Local_enuErrorState = ES_NOK;}}
		else if(Copy_pstrEXTIConfig->intNum == INT1_ID){
			MCUCR &= ~(3<<2);
			switch(Copy_u8SenseLvl){
			case LOW_LEVEL:
				break;
			case ANY_LOGIC:
				MCUCR |= (1<<2); break;
			case FALLING:
				MCUCR |= (2<<2); break;
			case RISING:
				MCUCR |= (3<<2); break;
			default:
				Local_enuErrorState = ES_NOK;}}
		else if(Copy_pstrEXTIConfig->intNum == INT2_ID){
			switch(Copy_u8SenseLvl){
			case FALLING:
				MCUCSR &= ~(1<<6); break;
			case RISING:
				MCUCSR |= (1<<6); break;
			default:
				Local_enuErrorState = ES_NOK;}
		}
		else
			Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	else
		Local_enuErrorState = ES_NULL_POINTER;
	return Local_enuErrorState;}

ES_t EXTI_enuEnableINT(EXTI_t * Copy_pstrEXTIConfig){
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pstrEXTIConfig != NULL){
		switch(Copy_pstrEXTIConfig->intNum){
		case(INT0_ID):
				GICR |= (1<<GICR_INT0); break;
		case(INT1_ID):
				GICR |= (1<<GICR_INT1); break;
		case(INT2_ID):
				GICR |= (1<<GICR_INT2); break;
		default:
			Local_enuErrorState = ES_NOK;}
	}
	else
		Local_enuErrorState = ES_NULL_POINTER;
	return Local_enuErrorState;
}

ES_t EXTI_enuDisableINT(EXTI_t * Copy_pstrEXTIConfig){
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pstrEXTIConfig != NULL){
		switch(Copy_pstrEXTIConfig->intNum){
		case(INT0_ID):
				GICR &= ~(1<<GICR_INT0); break;
		case(INT1_ID):
				GICR &= ~(1<<GICR_INT1); break;
		case(INT2_ID):
				GICR &= ~(1<<GICR_INT2); break;
		default:
			Local_enuErrorState = ES_NOK;}
	}
	else
		Local_enuErrorState = ES_NULL_POINTER;
	return Local_enuErrorState;
}

ES_t EXTI_enuCallBack(EXTI_t * Copy_pstrEXTIConfig, void (*Copy_pfunAppFun)(void*), void * Copy_pvidAppParameter)
{
	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_pstrEXTIConfig != NULL && Copy_pfunAppFun != NULL)
	{
		EXTI_ApfunISRFun[ Copy_pstrEXTIConfig->intNum ] = Copy_pfunAppFun;
		EXTI_ApvidISRParameter [ Copy_pstrEXTIConfig->intNum ] = Copy_pvidAppParameter;
	}

	return Local_enuErrorState;
}

void __vector_1 (void)__attribute__((signal));
void __vector_2 (void)__attribute__((signal));
void __vector_3 (void)__attribute__((signal));

void __vector_1 (void)
{
	if (EXTI_ApfunISRFun[0] != NULL)
	{
		EXTI_ApfunISRFun[0] ( EXTI_ApvidISRParameter[0] );
	}
}

void __vector_2 (void)
{
	if (EXTI_ApfunISRFun[1] != NULL)
	{
		EXTI_ApfunISRFun[1] ( EXTI_ApvidISRParameter[1] );
	}
}

void __vector_3 (void)
{
	if (EXTI_ApfunISRFun[2] != NULL)
	{
		EXTI_ApfunISRFun[2] ( EXTI_ApvidISRParameter[2] );
	}
}
