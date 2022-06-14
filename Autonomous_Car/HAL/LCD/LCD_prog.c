/*
 * LCD_prog.c
 *
 *  Created on: Feb 4, 2022
 *      Author: Ahmed El-Gaafrawy
 */
//libraries
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"

// lower layers
#include "../../MCAL/DIO/DIO_int.h"

// own libraries
#include "LCD_config.h"
#include "LCD_priv.h"

#include <util/delay.h>


ES_t LCD_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	_delay_ms(32);

	DIO_enuSetPinDirection(EN_GRP , RS_PIN , DIO_u8OUTPUT);
	DIO_enuSetPinDirection(RW_GRP , RW_PIN , DIO_u8OUTPUT);
	DIO_enuSetPinDirection(EN_GRP , EN_PIN , DIO_u8OUTPUT);

	DIO_enuSetPinDirection(D7_GRP , D7_PIN , DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D6_GRP , D6_PIN , DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D5_GRP , D5_PIN , DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D4_GRP , D4_PIN , DIO_u8OUTPUT);

#if LCD_u8MODE == EIGHT_BIT
	DIO_enuSetPinDirection(D3_GRP , D3_PIN , DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D2_GRP , D2_PIN , DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D1_GRP , D1_PIN , DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D0_GRP , D0_PIN , DIO_u8OUTPUT);

	DIO_enuSetPinValue(RS_GRP , RS_PIN , DIO_u8LOW );
	LCD_enuWriteNLatch(0x38);

#elif LCD_u8MODE == FOUR_BIT

	DIO_enuSetPinValue(RS_GRP , RS_PIN , DIO_u8LOW );

	DIO_enuSetPinValue(D7_GRP , D7_PIN , DIO_u8LOW );
	DIO_enuSetPinValue(D6_GRP , D6_PIN , DIO_u8LOW );
	DIO_enuSetPinValue(D5_GRP , D5_PIN , DIO_u8HIGH);
	DIO_enuSetPinValue(D4_GRP , D4_PIN , DIO_u8LOW );

	DIO_enuSetPinValue(EN_GRP , EN_PIN , DIO_u8HIGH);
	_delay_ms(5);
	DIO_enuSetPinValue(EN_GRP , EN_PIN , DIO_u8LOW);
	//difference speed bt. atmega & lcd
	_delay_ms(32);

	LCD_enuWriteNLatch(0x28);
#else
#error "LCD Mode has a wrong configuration"
#endif

	//Display control
	DIO_enuSetPinValue(RS_GRP , RS_PIN , DIO_u8LOW );
	LCD_enuWriteNLatch(0x0f);

	//Display Clear
	DIO_enuSetPinValue(RS_GRP , RS_PIN , DIO_u8LOW );
	LCD_enuWriteNLatch(0x01);

	//Entry Set
	DIO_enuSetPinValue(RS_GRP , RS_PIN , DIO_u8LOW );
	LCD_enuWriteNLatch(0x06);


	return Local_enuErrorState;
}

ES_t LCD_enuWriteData(u8 Copy_u8Data )
{
	ES_t Local_enuErrorState = ES_NOK;

	DIO_enuSetPinValue(RS_GRP , RS_PIN , DIO_u8HIGH );
	LCD_enuWriteNLatch(Copy_u8Data);

	return Local_enuErrorState;
}

ES_t LCD_enuWriteCommand(u8 Copy_u8Command )
{
	ES_t Local_enuErrorState = ES_NOK;

	DIO_enuSetPinValue(RS_GRP , RS_PIN , DIO_u8LOW );
	LCD_enuWriteNLatch(Copy_u8Command);

	return Local_enuErrorState;
}

ES_t LCD_enuSendString(const char * Copy_pcString)
{
	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_pcString != NULL) //(void*)0
	{
		//Null terminator = '\0' , 0x00, 0
		while (*Copy_pcString)
		{
			DIO_enuSetPinValue(RS_GRP , RS_PIN , DIO_u8HIGH );
			LCD_enuWriteNLatch(*Copy_pcString++);
		}
		Local_enuErrorState =ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}



static ES_t LCD_enuWriteNLatch( u8 Copy_u8Byte)
{
	ES_t Local_enuErrorState = ES_NOK;

#if LCD_u8MODE == EIGHT_BIT

	DIO_enuSetPinValue(EN_GRP , EN_PIN , DIO_u8LOW);
	DIO_enuSetPinValue(RW_GRP , RW_PIN , DIO_u8LOW);

	//data
	DIO_enuSetPinValue(D7_GRP , D7_PIN , ((Copy_u8Byte>>7)&1) );
	DIO_enuSetPinValue(D6_GRP , D6_PIN , ((Copy_u8Byte>>6)&1) );
	DIO_enuSetPinValue(D5_GRP , D5_PIN , ((Copy_u8Byte>>5)&1) );
	DIO_enuSetPinValue(D4_GRP , D4_PIN , ((Copy_u8Byte>>4)&1) );
	DIO_enuSetPinValue(D3_GRP , D3_PIN , ((Copy_u8Byte>>3)&1) );
	DIO_enuSetPinValue(D2_GRP , D2_PIN , ((Copy_u8Byte>>2)&1) );
	DIO_enuSetPinValue(D1_GRP , D1_PIN , ((Copy_u8Byte>>1)&1) );
	DIO_enuSetPinValue(D0_GRP , D0_PIN , ((Copy_u8Byte>>0)&1) );


	DIO_enuSetPinValue(EN_GRP , EN_PIN , DIO_u8HIGH);
	_delay_ms(5);
	DIO_enuSetPinValue(EN_GRP , EN_PIN , DIO_u8LOW);

	//difference speed bt. atmega & lcd
	_delay_ms(32);

#elif LCD_u8MODE == FOUR_BIT

	DIO_enuSetPinValue(EN_GRP , EN_PIN , DIO_u8LOW);
	DIO_enuSetPinValue(RW_GRP , RW_PIN , DIO_u8LOW);

	//data
	DIO_enuSetPinValue(D7_GRP , D7_PIN , ((Copy_u8Byte>>7)&1) );
	DIO_enuSetPinValue(D6_GRP , D6_PIN , ((Copy_u8Byte>>6)&1) );
	DIO_enuSetPinValue(D5_GRP , D5_PIN , ((Copy_u8Byte>>5)&1) );
	DIO_enuSetPinValue(D4_GRP , D4_PIN , ((Copy_u8Byte>>4)&1) );

	DIO_enuSetPinValue(EN_GRP , EN_PIN , DIO_u8HIGH);
	_delay_ms(5);
	DIO_enuSetPinValue(EN_GRP , EN_PIN , DIO_u8LOW);
	//difference speed bt. atmega & lcd
	_delay_ms(20);

	DIO_enuSetPinValue(D7_GRP , D7_PIN , ((Copy_u8Byte>>3)&1) );
	DIO_enuSetPinValue(D6_GRP , D6_PIN , ((Copy_u8Byte>>2)&1) );
	DIO_enuSetPinValue(D5_GRP , D5_PIN , ((Copy_u8Byte>>1)&1) );
	DIO_enuSetPinValue(D4_GRP , D4_PIN , ((Copy_u8Byte>>0)&1) );


	DIO_enuSetPinValue(EN_GRP , EN_PIN , DIO_u8HIGH);
	_delay_ms(5);
	DIO_enuSetPinValue(EN_GRP , EN_PIN , DIO_u8LOW);

	//difference speed bt. atmega & lcd
	_delay_ms(32);
#else
#error "LCD Mode has a wrong configuration"
#endif
	return Local_enuErrorState;
}

ES_t LCD_enuWriteIntegerNum(s32 Copy_s32Num)
{
	ES_t Local_enuErrorState = ES_NOK;

	s32 Local_s32Reverse=0;
	u8 Local_u8Remainder=0 , Local_u8NumDigit=0;

	if(Copy_s32Num <0)
	{
		DIO_enuSetPinValue(RS_GRP , RS_PIN , DIO_u8HIGH);
		LCD_enuWriteNLatch('-');
		Copy_s32Num *= -1 ;
	}
	while (Copy_s32Num)
	{
		Local_u8Remainder = Copy_s32Num % 10;
		Local_s32Reverse = Local_s32Reverse * 10 + Local_u8Remainder;
		Copy_s32Num /=10;
		Local_u8NumDigit ++;
	}

	while (Local_u8NumDigit)
	{
		Local_u8Remainder = Local_s32Reverse % 10;
		DIO_enuSetPinValue(RS_GRP , RS_PIN , DIO_u8HIGH);
		LCD_enuWriteNLatch(Local_u8Remainder + '0');
		Local_s32Reverse /= 10;
		Local_u8NumDigit --;
	}

	return Local_enuErrorState;
}
