/*
 * GIE_prog.c
 *
 *  Created on: Feb 12, 2022
 *      Author: Ahmed El-Gaafrawy
 */
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"

#include "GIE_priv.h"

ES_t GIE_enuInit(void){
	asm("CLI");
	return ES_OK;
}

ES_t GIE_enuEnable(void){
	//SREG |= (1<<I_BIT); //asm("SBI 0x-- , -");
	asm("SEI");
	return ES_OK;
}

ES_t GIE_enuDisable(void){
	asm("CLI");
	return ES_OK;
}
