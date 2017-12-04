#ifndef __DRV_LED_H
#define __DRV_LED_H	 
#include "main.h"

#define OFF Bit_RESET
#define ON Bit_SET

#define LED1(x) GPIO_WriteBit(GPIOC, GPIO_Pin_4, x) //D6
#define LED2(x) GPIO_WriteBit(GPIOC, GPIO_Pin_5, x) //D7
#define LED3(x) GPIO_WriteBit(GPIOB, GPIO_Pin_0, x)
#define LED4(x) GPIO_WriteBit(GPIOB, GPIO_Pin_1, x)

void LED_Init(void); //≥ı ºªØ
		 				    
#endif
