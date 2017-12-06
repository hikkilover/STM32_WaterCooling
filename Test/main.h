#ifndef __MAIN_H
#define __MAIN_H
	
#include <stdio.h>	
#include <stdarg.h>
	
#include "stm32f10x.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_fsmc.h"
#include "stm32f10x_adc.h"

#include "Drv_SysTick.h"
#include "Drv_USART1.h"
#include "Drv_LCD.h"
#include "Drv_ADC.h"
#include "Drv_Key.h"
#include "Drv_LED.h"
#include "Drv_Timer.h"

#include "test.h"


/*设置LCD驱动方式*/
//若要使用GPIO模拟时序驱动方式，注释此宏即可
typedef struct
{
	uint8_t temperature;
	uint8_t fanMotorDutyRatio;
	uint8_t pumpMotorDutyRatio;
	uint8_t state;
}SYSTEM_MONITOR;

typedef struct 
{
	uint8_t temp[200];
	uint8_t head;
	uint8_t rear;
}TEMP_QUEUE;

#define LCD_USE_FSMC

#endif /* __MAIN_H */
