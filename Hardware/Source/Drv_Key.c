#include "Drv_Key.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);     											//ʹ��PORTBʱ��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                             //�����Ƶ��50MHz
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;                             		 //��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;//TFT_LED��TFT_REST
	GPIO_Init(GPIOB,&GPIO_InitStructure);                   
} 


//����ץȡ����,���ذ���ֵ
//mode:0,��֧��������   1,֧�������� һ����˵����mode0
//0:û���κΰ�������,1,2,3,4,5:�а���
//ע��˺�������Ӧ���ȼ�, 1��5����ԽСԽ����
uint8_t KEY_Scan(uint8_t mode)
{	 
	static u8 key_up = 1;//�������ɿ���־
	if(mode) key_up = 1;  //֧������		  
	if(key_up&&(KEY_UP==0||KEY_DOWN==0||KEY_LEFT==0||KEY_RIGHT==0||KEY_CENTER==0))
	{
		Delay_Ms(10);//ȥ���� 
		key_up=0;
		if(KEY_UP==0) return KEY_UP_PRES;
		else if(KEY_DOWN==0) return KEY_DOWN_PRES;
		else if(KEY_LEFT==0) return KEY_LEFT_PRES;
		else if(KEY_RIGHT==0) return KEY_RIGHT_PRES;
		else if(KEY_CENTER==0) return KEY_CENTER_PRES;
	}
	else if(KEY_UP==1&&KEY_DOWN==1&&KEY_LEFT==1&&KEY_RIGHT==1&&KEY_CENTER==1)key_up=1; 	    
 	return 0;// �ް�������
}
