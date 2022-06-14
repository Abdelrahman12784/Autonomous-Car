/*
 * EXTI_config.h
 *
 *  Created on: Feb 12, 2022
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

#define INT_NUM				1

typedef struct
{
	u8 senseLvl;
	u8 intMode;
	u8 intNum;
}EXTI_t;

#endif /* EXTI_CONFIG_H_ */
