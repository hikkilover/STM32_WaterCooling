#include "test.h"

extern SYSTEM_MONITOR monitor;
void MONITOR_Test_Init(void)
{
	monitor.temperature = 30;
	monitor.fanMotorDutyRatio = 25;
	monitor.pumpMotorDutyRatio = 65;
	monitor.state = 0xAA;
}


extern TEMP_QUEUE temp_q;
void QUEUE_Test_Init(void)
{
	//���ɾ�ݲ�����
	for(int i =0; i<200;i++)
	{
		temp_q.temp[i] = i%20;
	}
	temp_q.head = 1;
	temp_q.rear = 0;
}


extern TEMP_QUEUE temp_q;
void QUEUE_reflash(uint16_t seed) 
{
	temp_q.head ++;
	if(temp_q.head==200) temp_q.head = 0;
	if(temp_q.rear==temp_q.head) temp_q.rear++;
	if(temp_q.rear==200) temp_q.rear = 0;
	temp_q.temp[temp_q.head] =seed;
}


//���������
//������̬���ߺ��ַ�
//�������ɫ�������Բο�
void MAIN_SURFACE_test(void)
{
	uint16_t i =1;
	uint16_t temp = 0;
	ADC1_Init();
	LCD_Init();
	MONITOR_Test_Init();
	QUEUE_Test_Init();
	SCREEN_frame_draw(0xBDF7);
	SCREEN_static_character_draw(0x2124);
	SCREEN_dynamic_character_reflash(BLUE);
	while(1)
	{
		//QUEUE_reflash(i%90);
		temp = TEMP_get();
		SCREEN_curve_reflash(GREEN);
		i++;
		if(i>=200) i = 1;
		Delay_Ms(100);
	}
}


//��ɫ���ԣ���Ч��
void COLOR_test(void)
{
	//��ɫ 
	LCD_Full_Circle(20, 20, 0x0365);
	LCD_Full_Circle(60, 20, 0x350A);//ǳ������
	//��ɫ
	LCD_Full_Circle(20, 60, 0xF1C4);
	LCD_Full_Circle(60, 60, 0xE0C3);//�ӽ�ԭ��ɫ
	//�߿�ɫ
	LCD_Full_Circle(20, 100, 0x2124);
	LCD_Full_Circle(60, 100, 0x8430);//��ɫ����
	LCD_Full_Circle(100, 100, 0xE71C);//��ɫ��ֱ���е�ǳ
	LCD_Full_Circle(20, 140, 0xF79E);
	LCD_Full_Circle(60, 140, 0xDEDB);
	LCD_Full_Circle(100, 140, 0xBDF7);
}


//������LED����
//���ܵļ�����һ���ƣ��м�ļ��ص�
void KEY_LED_test(void)
{
	uint8_t key = 0;
	KEY_Init();
	LED_Init();
	while(1)
	{
		key = KEY_Scan(0);
		if(key==1) LED1(ON);
		else if(key==2) LED2(ON);
		else if(key==3) LED3(ON);
		else if(key==4) LED4(ON);
		else if(key==5) 
			{
				LED1(OFF);
				LED2(OFF);
				LED3(OFF);
				LED4(OFF);
			}
		key = 0;
	}
}
