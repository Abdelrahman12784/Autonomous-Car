/*
 * EXTI_int.h
 *
 *  Created on: Feb 12, 2022
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef EXTI_INT_H_
#define EXTI_INT_H_

ES_t EXTI_enuInit(EXTI_t * Copy_pAstrEXTIConfig);

ES_t EXTI_enuSetSenseLvl(EXTI_t * Copy_pstrEXTIConfig, u8 Copy_u8SenseLvl);

ES_t EXTI_enuEnableINT(EXTI_t * Copy_pstrEXTIConfig);

ES_t EXTI_enuDisableINT(EXTI_t * Copy_pstrEXTIConfig);

ES_t EXTI_enuCallBack(EXTI_t * Copy_pstrEXTIConfig, void (*Copy_pfunAppFun)(void*), void * Copy_pvidAppParameter);

#define LOW_LEVEL			58
#define ANY_LOGIC			74
#define RISING				12
#define FALLING				96

#define ENABLED				1
#define DISABLED			0

#define INT0_ID				75
#define INT1_ID				34
#define INT2_ID				76

#endif /* EXTI_INT_H_ */
