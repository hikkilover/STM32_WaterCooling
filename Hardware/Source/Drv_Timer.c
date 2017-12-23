#include "Drv_Timer.h"


//TIM3��ʼ������
//TIM3���������¶ȴ����������ж�
void TIM3_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}
//������
float Addtemp_error = 0;
float ideal_temp = 30;
extern uint16_t temp;
extern TEMP_QUEUE temp_q;
extern PID_CONTROLLER pid_controller;
extern SYSTEM_MONITOR monitor;
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	int motor_duty = 0;
	int temp_error;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx�����жϱ�־ 
		temp = TEMP_get();
	}
//	temp_error = (int)temp_q.temp[temp_q.head] - ideal_temp;

//	Addtemp_error = Addtemp_error + temp_error;
//	if(Addtemp_error>40) Addtemp_error = 40;
//	if(Addtemp_error<-30) Addtemp_error = -30;

//	
//	motor_duty = 	KP(pid_controller)*temp_error + KI(pid_controller)*Addtemp_error + 30;
//	
//	//����޷�
//	if(motor_duty>80) motor_duty = 80;
//	if(motor_duty<20) motor_duty = 20;
//	
//	TIM_SetCompare2(TIM5,(100-motor_duty)*160);
//	monitor.pumpMotorDutyRatio = motor_duty;
}

//timer5��ʼ��������������PWM�������
extern SYSTEM_MONITOR monitor;
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
	TIM_SetCompare1(TIM5,4000);
	TIM_SetCompare2(TIM5,0);
	
	/*����TIM5*/
	TIM_Cmd(TIM5,ENABLE);
	monitor.fanMotorDutyRatio =0;
	monitor.pumpMotorDutyRatio =0;
}
