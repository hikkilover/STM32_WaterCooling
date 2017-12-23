#include "main.h"

SYSTEM_MONITOR monitor;
TEMP_QUEUE temp_q;
PID_CONTROLLER pid_controller;
uint16_t temp = 0;
uint8_t focus = 0;
//monitor�ĳ�ʼ��
void MONITOR_Init(void)
{
	monitor.temperature = 0;
	monitor.fanMotorDutyRatio = 0;
	monitor.pumpMotorDutyRatio = 0;
	monitor.state = 0x00;
}

//�¶ȶ��еĳ�ʼ��
void QUEUE_Init(void)
{
	for(int i =0; i<200;i++) temp_q.temp[i] = 0;
	//����д�� ��β��
	temp_q.head = 1;
	temp_q.rear = 0;
}

void CONTROLLER_Init(void)
{
	pid_controller.Kp = 10;
	pid_controller.Kp_strength = 20;
	pid_controller.Ki = 5;
	pid_controller.Ki_strength = 10;
	pid_controller.Kd = 0.1;
	pid_controller.Kd_strength = 0;
}


int main(void)
{
	//SysTick��ʱ����ʼ���������ṩ�����ʱ
	SysTick_Init();
	
	//USART1��ʼ����������ʽ���������
	USART1_Init(115200);
	printf("\r\n");
	//��ʼ�������ṹ��
	MONITOR_Init();
	QUEUE_Init();
	CONTROLLER_Init();
	UI_test();
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  ����ʧ�ܴ�����
  * @param  file: Դ�ļ���ָ��
  *         line: ����ʧ�����ڵ�����
  * @retval ��
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  while (1)
  {
		/*���������Ϣ*/
		printf("Assertion failed: file %s on line %d\r\n",file,line);
		Delay_Ms(1000);
  }
}
#endif
