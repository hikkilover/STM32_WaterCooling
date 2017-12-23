#include "Drv_Timer.h"


//TIM3初始化函数
//TIM3用来触发温度传感器采样中断
void TIM3_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}
//误差积分
float Addtemp_error = 0;
float ideal_temp = 30;
extern uint16_t temp;
extern TEMP_QUEUE temp_q;
extern PID_CONTROLLER pid_controller;
extern SYSTEM_MONITOR monitor;
void TIM3_IRQHandler(void)   //TIM3中断
{
	int motor_duty = 0;
	int temp_error;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx更新中断标志 
		temp = TEMP_get();
	}
//	temp_error = (int)temp_q.temp[temp_q.head] - ideal_temp;

//	Addtemp_error = Addtemp_error + temp_error;
//	if(Addtemp_error>40) Addtemp_error = 40;
//	if(Addtemp_error<-30) Addtemp_error = -30;

//	
//	motor_duty = 	KP(pid_controller)*temp_error + KI(pid_controller)*Addtemp_error + 30;
//	
//	//输出限幅
//	if(motor_duty>80) motor_duty = 80;
//	if(motor_duty<20) motor_duty = 20;
//	
//	TIM_SetCompare2(TIM5,(100-motor_duty)*160);
//	monitor.pumpMotorDutyRatio = motor_duty;
}

//timer5初始化函数，用来做PWM波的输出
extern SYSTEM_MONITOR monitor;
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
	TIM_SetCompare1(TIM5,4000);
	TIM_SetCompare2(TIM5,0);
	
	/*开启TIM5*/
	TIM_Cmd(TIM5,ENABLE);
	monitor.fanMotorDutyRatio =0;
	monitor.pumpMotorDutyRatio =0;
}
