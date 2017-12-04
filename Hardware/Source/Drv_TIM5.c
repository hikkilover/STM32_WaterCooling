#include "Drv_TIM5.h"

/**
* @brief  TIM5��ʼ������
* @param  ��
* @retval ��
*/
void TIM5_Init(void)
{
	/*����GPIOA��TIM5����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	/*����GPIO�ܽŹ���ģʽ*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                  //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                //�����Ƶ�ʣ�50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;                                        
	GPIO_Init(GPIOA,&GPIO_InitStructure);    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                            //��������ģʽ	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;                                        
	GPIO_Init(GPIOA,&GPIO_InitStructure);   
                               
	/*����TIM5��������*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 8;                                     //Ԥ��Ƶϵ��8��������ʱ��72MHz/(1+8)=8MHz
	TIM_TimeBaseInitStructure.TIM_Period = 16000;                                    //��������16000����2ms
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;                  //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
	
	/*����TIM5���ͨ��*/
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                                //���ͨ��ΪPWM1ģʽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                    //����Ƚ�ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                         //������Ե�
	TIM_OC1Init(TIM5,&TIM_OCInitStructure);
	TIM_OC2Init(TIM5,&TIM_OCInitStructure);
	
	/*����TIM5����ͨ��*/
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;                      //�����ز���
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;                  //ֱ��ӳ�䵽TI
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;                            //���벻��Ƶ
	TIM_ICInitStructure.TIM_ICFilter = 0x00;                                         //���벻�˲�
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
	TIM_ICInit(TIM5,&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
	TIM_ICInit(TIM5,&TIM_ICInitStructure);
	
	/*ʹ��Ԥװ�ؼĴ���*/
	TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM5,TIM_OCPreload_Enable);
	
	/*���ó�ʼ����*/
	TIM_SetCompare1(TIM5,0);
	TIM_SetCompare2(TIM5,0);
	
	/*����TIM5*/
	TIM_Cmd(TIM5,ENABLE);
}
