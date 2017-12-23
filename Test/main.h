#ifndef __MAIN_H
#define __MAIN_H
	
#include <stdio.h>	
#include <stdarg.h>
#include <stdbool.h>
	
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

//c不支持bool型
//#define bool uint8_t
#define TRUE 1
#define FALSE 0


#define KP(x) (x.Kp*((float)x.Kp_strength)/100)
#define KI(x) (x.Ki*((float)x.Ki_strength)/100)
#define KD(x) (x.Kd*((float)x.Kd_strength)/100)
/*设置LCD驱动方式*/
//若要使用GPIO模拟时序驱动方式，注释此宏即可

//state的8个bit中bit7~bit2有用
//bit7 指示温度传感器工作状态
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

__packed typedef struct 
{
	float Kp;
	uint8_t Kp_strength;
	float Ki;
	uint8_t Ki_strength;
	float Kd;
	uint8_t Kd_strength;
}PID_CONTROLLER;


#define LCD_USE_FSMC

#endif /* __MAIN_H */
