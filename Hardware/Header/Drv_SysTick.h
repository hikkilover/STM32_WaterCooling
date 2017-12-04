#ifndef __DRV_SYSTICK_H
#define __DRV_SYSTICK_H

#include "main.h"

#define GET_SYSTIME_US systick*1000+(SysTick->LOAD-SysTick->VAL)*1000/SysTick->LOAD

extern volatile uint32_t systick;

void SysTick_Init(void);                        //SysTick��ʼ������
void Delay_Us(uint32_t n);                      //΢�뼶��ʱ����
void Delay_Ms(uint32_t n);                      //���뼶��ʱ����

#endif /* __DRV_SYSTICK_H */
