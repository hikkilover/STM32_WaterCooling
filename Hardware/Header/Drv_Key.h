#ifndef __DRV_KEY_H
#define __DRV_KEY_H	 

#include "main.h"

#define KEY_UP				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define KEY_DOWN		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)
#define KEY_LEFT			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define KEY_RIGHT		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)
#define KEY_CENTER		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)

#define KEY_UP_PRES			1
#define KEY_DOWN_PRES		2
#define KEY_LEFT_PRES		3
#define KEY_RIGHT_PRES		4
#define KEY_CENTER_PRES	5

void KEY_Init(void);//IO初始化
uint8_t KEY_Scan(uint8_t mode); 	//按键扫描函数					    
#endif
