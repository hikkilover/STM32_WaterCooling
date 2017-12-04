#include "Drv_Key.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);     											//使能PORTB时钟
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                             //最大工作频率50MHz
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;                             		 //上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;//TFT_LED和TFT_REST
	GPIO_Init(GPIOB,&GPIO_InitStructure);                   
} 


//按键抓取函数,返回按键值
//mode:0,不支持连续按   1,支持连续按 一般来说就用mode0
//0:没有任何按键按下,1,2,3,4,5:有按键
//注意此函数有响应优先级, 1到5数字越小越优先
uint8_t KEY_Scan(uint8_t mode)
{	 
	static u8 key_up = 1;//按键按松开标志
	if(mode) key_up = 1;  //支持连按		  
	if(key_up&&(KEY_UP==0||KEY_DOWN==0||KEY_LEFT==0||KEY_RIGHT==0||KEY_CENTER==0))
	{
		Delay_Ms(10);//去抖动 
		key_up=0;
		if(KEY_UP==0) return KEY_UP_PRES;
		else if(KEY_DOWN==0) return KEY_DOWN_PRES;
		else if(KEY_LEFT==0) return KEY_LEFT_PRES;
		else if(KEY_RIGHT==0) return KEY_RIGHT_PRES;
		else if(KEY_CENTER==0) return KEY_CENTER_PRES;
	}
	else if(KEY_UP==1&&KEY_DOWN==1&&KEY_LEFT==1&&KEY_RIGHT==1&&KEY_CENTER==1)key_up=1; 	    
 	return 0;// 无按键按下
}
