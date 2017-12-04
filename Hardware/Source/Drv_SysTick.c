#include "Drv_SysTick.h"

volatile uint32_t systick = 0;

/**
  * @brief  SysTick初始化函数
  * @param  无
  * @retval 无
  */
void SysTick_Init(void)
{
	RCC_ClocksTypeDef RCC_ClockStructure;
	RCC_GetClocksFreq(&RCC_ClockStructure);
	
	uint32_t cnts = (uint32_t)RCC_ClockStructure.HCLK_Frequency/8000;
	
	SysTick_Config(cnts);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

/**
  * @brief  微秒级延时函数
  * @param  要延时的微秒数
  * @retval 无
  */
void Delay_Us(uint32_t n)
{
	uint32_t now = GET_SYSTIME_US;
	while((GET_SYSTIME_US-now)<n);
}	

/**
  * @brief  毫秒级延时函数
  * @param  要延时的毫秒数
  * @retval 无
  */
void Delay_Ms(uint32_t n)
{
	while(n--)
		Delay_Us(1000);
}
