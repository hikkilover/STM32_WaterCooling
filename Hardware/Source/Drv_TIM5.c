#include "Drv_TIM5.h"

/**
* @brief  TIM5初始化函数
* @param  无
* @retval 无
*/
void TIM5_Init(void)
{
	/*开启GPIOA、TIM5外设时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	/*配置GPIO管脚工作模式*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                  //复用推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                //最大工作频率：50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;                                        
	GPIO_Init(GPIOA,&GPIO_InitStructure);    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                            //浮空输入模式	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;                                        
	GPIO_Init(GPIOA,&GPIO_InitStructure);   
                               
	/*配置TIM5基本参数*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 8;                                     //预分频系数8，即计数时钟72MHz/(1+8)=8MHz
	TIM_TimeBaseInitStructure.TIM_Period = 16000;                                    //计数周期16000，即2ms
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;                  //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
	
	/*配置TIM5输出通道*/
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                                //输出通道为PWM1模式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                    //输出比较使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                         //输出极性低
	TIM_OC1Init(TIM5,&TIM_OCInitStructure);
	TIM_OC2Init(TIM5,&TIM_OCInitStructure);
	
	/*配置TIM5输入通道*/
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;                      //上升沿捕获
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;                  //直接映射到TI
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;                            //输入不分频
	TIM_ICInitStructure.TIM_ICFilter = 0x00;                                         //输入不滤波
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
	TIM_ICInit(TIM5,&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
	TIM_ICInit(TIM5,&TIM_ICInitStructure);
	
	/*使能预装载寄存器*/
	TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM5,TIM_OCPreload_Enable);
	
	/*设置初始脉宽*/
	TIM_SetCompare1(TIM5,0);
	TIM_SetCompare2(TIM5,0);
	
	/*开启TIM5*/
	TIM_Cmd(TIM5,ENABLE);
}
