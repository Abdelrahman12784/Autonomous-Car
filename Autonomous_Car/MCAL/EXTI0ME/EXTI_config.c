/*
 * EXTI_config.c
 *
 *  Created on: Feb 12, 2022
 *      Author: Ahmed El-Gaafrawy
 */
#include "../../LIB/stdTypes.h"
#include "EXTI_config.h"
#include "EXTI_priv.h"

u8 EXTI_u8IntNum = INT_NUM;

EXTI_t EXTI_AstrEXTIConfig [INT_NUM] = {
		{RISING , ENABLED , INT1_ID}//,  //int0
		//{},  //int1
};
