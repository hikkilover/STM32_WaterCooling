#include "main.h"

SYSTEM_MONITOR monitor;
TEMP_QUEUE temp_q;
PID_CONTROLLER pid_controller;
uint16_t temp = 0;
uint8_t focus = 0;
//monitor的初始化
void MONITOR_Init(void)
{
	monitor.temperature = 0;
	monitor.fanMotorDutyRatio = 0;
	monitor.pumpMotorDutyRatio = 0;
	monitor.state = 0x00;
}

//温度队列的初始化
void QUEUE_Init(void)
{
	for(int i =0; i<200;i++) temp_q.temp[i] = 0;
	//队首写入 队尾空
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
	//SysTick定时器初始化，用于提供软件延时
	SysTick_Init();
	
	//USART1初始化，用作格式化输入输出
	USART1_Init(115200);
	printf("\r\n");
	//初始化三个结构体
	MONITOR_Init();
	QUEUE_Init();
	CONTROLLER_Init();
	UI_test();
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  断言失败处理函数
  * @param  file: 源文件名指针
  *         line: 断言失败所在的行数
  * @retval 无
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  while (1)
  {
		/*报告错误信息*/
		printf("Assertion failed: file %s on line %d\r\n",file,line);
		Delay_Ms(1000);
  }
}
#endif
