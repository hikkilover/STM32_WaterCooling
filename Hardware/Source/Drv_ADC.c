
#include "Drv_ADC.h"

//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3																	   
void ADC1_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PC2 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //复位ADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				  
//获得ADC值
//ch:通道值 12
extern SYSTEM_MONITOR monitor;
u16 Get_ADC1_CH12(void)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, 12, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	
	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

u16 Get_ADC1_CH12_Average(u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_ADC1_CH12();
		Delay_Ms(5);
	}
	//ADC采样过程结束认为ADC在正常工作
	monitor.state |= 0x80;
	return temp_val/times;
} 	 

//这里队列操作的逻辑已经跑通
extern SYSTEM_MONITOR monitor;
extern TEMP_QUEUE temp_q;
uint16_t TEMP_get(void)
{
	uint16_t temp, adcValue;
	float tempFloat;
	adcValue = Get_ADC1_CH12_Average(10);
	tempFloat = (float)adcValue;
	tempFloat = (tempFloat * ADC_VREF * 1000.0f)/(4095.0f*LM35_SENSITIVITY*PREAMP_GAIN);
	temp = (uint16_t)tempFloat;
	//监视器中温度实时值更新
	monitor.temperature = temp;
	//温度记录队列更新
	temp_q.head ++;
	if(temp_q.head==200) temp_q.head = 0;
	if(temp_q.rear==temp_q.head) temp_q.rear++;
	if(temp_q.rear==200) temp_q.rear = 0;
	temp_q.temp[temp_q.head] = temp;
	return temp;
}
