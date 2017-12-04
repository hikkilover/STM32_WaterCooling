#ifndef __DRV_ADC_H
#define __DRV_ADC_H

#include "main.h"
#define LM35_SENSITIVITY 10.0f                    //传感器灵敏度，单位：毫伏每摄氏度                         
#define PREAMP_GAIN      3.0f                     //前置放大增益：3倍
#define ADC_VREF         3.3f                     //ADC参考电压：3.3V   

void ADC1_Init(void);
u16 Get_ADC1_CH12(void);
u16 Get_ADC1_CH12_Average(u8 times);
uint16_t TEMP_get(void);


#endif /* __DRV_ADC_H*/
