#include "Drv_LCD.h"

const uint8_t circle_r9[19] = {5, 9, 11, 13, 15, 17, 17, 19, 19, 19, 19, 19, 17, 17, 15, 13, 11, 9, 5};
/*8X16像素ASCII字符点阵数据*/
const uint8_t ascii_8X16[95][16] = 
{
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/
	{0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x08,0x08,0x00,0x00},/*"!",1*/
	{0x00,0x48,0x24,0x24,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*""",2*/
	{0x00,0x00,0x00,0x48,0x48,0x48,0x7E,0x24,0x24,0x24,0x7E,0x24,0x24,0x24,0x00,0x00},/*"#",3*/
	{0x00,0x00,0x10,0x3C,0x52,0x52,0x12,0x1C,0x30,0x50,0x50,0x52,0x52,0x3C,0x10,0x10},/*"$",4*/
	{0x00,0x00,0x00,0x22,0x25,0x15,0x15,0x0D,0x2A,0x58,0x54,0x54,0x52,0x22,0x00,0x00},/*"%",5*/
	{0x00,0x00,0x00,0x0C,0x12,0x12,0x12,0x0A,0x76,0x25,0x29,0x19,0x91,0x6E,0x00,0x00},/*"&",6*/
	{0x00,0x06,0x04,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",7*/
	{0x00,0x40,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x20,0x40,0x00},/*"(",8*/
	{0x00,0x02,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04,0x02,0x00},/*")",9*/
	{0x00,0x00,0x00,0x00,0x08,0x08,0x6B,0x1C,0x1C,0x6B,0x08,0x08,0x00,0x00,0x00,0x00},/*"*",10*/
	{0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x10,0xFE,0x10,0x10,0x10,0x00,0x00,0x00,0x00},/*"+",11*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x04,0x04,0x02},/*",",12*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"-",13*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x00,0x00},/*".",14*/
	{0x00,0x00,0x40,0x20,0x20,0x20,0x10,0x10,0x08,0x08,0x08,0x04,0x04,0x02,0x02,0x00},/*"/",15*/
	{0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00},/*"0",16*/
	{0x00,0x00,0x00,0x10,0x1C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00},/*"1",17*/
	{0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x40,0x20,0x10,0x08,0x04,0x42,0x7E,0x00,0x00},/*"2",18*/
	{0x00,0x00,0x00,0x3C,0x42,0x42,0x40,0x20,0x18,0x20,0x40,0x42,0x42,0x3C,0x00,0x00},/*"3",19*/
	{0x00,0x00,0x00,0x20,0x30,0x30,0x28,0x24,0x24,0x22,0xFE,0x20,0x20,0xF8,0x00,0x00},/*"4",20*/
	{0x00,0x00,0x00,0x7E,0x02,0x02,0x02,0x1E,0x22,0x40,0x40,0x42,0x22,0x1C,0x00,0x00},/*"5",21*/
	{0x00,0x00,0x00,0x18,0x24,0x02,0x02,0x3A,0x46,0x42,0x42,0x42,0x44,0x38,0x00,0x00},/*"6",22*/
	{0x00,0x00,0x00,0x7E,0x42,0x20,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x00,0x00},/*"7",23*/
	{0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00},/*"8",24*/
	{0x00,0x00,0x00,0x1C,0x22,0x42,0x42,0x42,0x62,0x5C,0x40,0x40,0x24,0x18,0x00,0x00},/*"9",25*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00},/*":",26*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08},/*";",27*/
	{0x00,0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x20,0x40,0x00,0x00},/*"<",28*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00},/*"=",29*/
	{0x00,0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x02,0x00,0x00},/*">",30*/
	{0x00,0x00,0x00,0x3C,0x42,0x42,0x46,0x20,0x10,0x10,0x10,0x00,0x18,0x18,0x00,0x00},/*"?",31*/
	{0x00,0x00,0x00,0x1C,0x22,0x5A,0x55,0x55,0x55,0x55,0x55,0x3A,0x42,0x3C,0x00,0x00},/*"@",32*/
	{0x00,0x00,0x00,0x08,0x08,0x18,0x14,0x14,0x24,0x3C,0x22,0x42,0x42,0xE7,0x00,0x00},/*"A",33*/
	{0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x1E,0x22,0x42,0x42,0x42,0x22,0x1F,0x00,0x00},/*"B",34*/
	{0x00,0x00,0x00,0x7C,0x42,0x42,0x01,0x01,0x01,0x01,0x01,0x42,0x22,0x1C,0x00,0x00},/*"C",35*/
	{0x00,0x00,0x00,0x1F,0x22,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1F,0x00,0x00},/*"D",36*/
	{0x00,0x00,0x00,0x3F,0x42,0x12,0x12,0x1E,0x12,0x12,0x02,0x42,0x42,0x3F,0x00,0x00},/*"E",37*/
	{0x00,0x00,0x00,0x3F,0x42,0x12,0x12,0x1E,0x12,0x12,0x02,0x02,0x02,0x07,0x00,0x00},/*"F",38*/
	{0x00,0x00,0x00,0x3C,0x22,0x22,0x01,0x01,0x01,0x71,0x21,0x22,0x22,0x1C,0x00,0x00},/*"G",39*/
	{0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x42,0xE7,0x00,0x00},/*"H",40*/
	{0x00,0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"I",41*/
	{0x00,0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x11,0x0F},/*"J",42*/
	{0x00,0x00,0x00,0x77,0x22,0x12,0x0A,0x0E,0x0A,0x12,0x12,0x22,0x22,0x77,0x00,0x00},/*"K",43*/
	{0x00,0x00,0x00,0x07,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x42,0x7F,0x00,0x00},/*"L",44*/
	{0x00,0x00,0x00,0x77,0x36,0x36,0x36,0x36,0x36,0x2A,0x2A,0x2A,0x2A,0x6B,0x00,0x00},/*"M",45*/
	{0x00,0x00,0x00,0xE3,0x46,0x46,0x4A,0x4A,0x52,0x52,0x52,0x62,0x62,0x47,0x00,0x00},/*"N",46*/
	{0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x1C,0x00,0x00},/*"O",47*/
	{0x00,0x00,0x00,0x3F,0x42,0x42,0x42,0x42,0x3E,0x02,0x02,0x02,0x02,0x07,0x00,0x00},/*"P",48*/
	{0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x4D,0x32,0x1C,0x60,0x00},/*"Q",49*/
	{0x00,0x00,0x00,0x3F,0x42,0x42,0x42,0x3E,0x12,0x12,0x22,0x22,0x42,0xC7,0x00,0x00},/*"R",50*/
	{0x00,0x00,0x00,0x7C,0x42,0x42,0x02,0x04,0x18,0x20,0x40,0x42,0x42,0x3E,0x00,0x00},/*"S",51*/
	{0x00,0x00,0x00,0x7F,0x49,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x1C,0x00,0x00},/*"T",52*/
	{0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00},/*"U",53*/
	{0x00,0x00,0x00,0xE7,0x42,0x42,0x22,0x24,0x24,0x14,0x14,0x18,0x08,0x08,0x00,0x00},/*"V",54*/
	{0x00,0x00,0x00,0x6B,0x2A,0x2A,0x2A,0x2A,0x2A,0x36,0x14,0x14,0x14,0x14,0x00,0x00},/*"W",55*/
	{0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x18,0x18,0x18,0x24,0x24,0x42,0xE7,0x00,0x00},/*"X",56*/
	{0x00,0x00,0x00,0x77,0x22,0x22,0x14,0x14,0x08,0x08,0x08,0x08,0x08,0x1C,0x00,0x00},/*"Y",57*/
	{0x00,0x00,0x00,0x7E,0x21,0x20,0x10,0x10,0x08,0x04,0x04,0x42,0x42,0x3F,0x00,0x00},/*"Z",58*/
	{0x00,0x78,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x78,0x00},/*"[",59*/
	{0x00,0x00,0x02,0x04,0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x20,0x20,0x20,0x40,0x40},/*"\",60*/
	{0x00,0x1E,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1E,0x00},/*"]",61*/
	{0x00,0x18,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"^",62*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},/*"_",63*/
	{0x00,0x06,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"`",64*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x30,0x2C,0x22,0x32,0x6C,0x00,0x00},/*"a",65*/
	{0x00,0x00,0x00,0x00,0x03,0x02,0x02,0x1A,0x26,0x42,0x42,0x42,0x26,0x1A,0x00,0x00},/*"b",66*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x02,0x02,0x02,0x44,0x38,0x00,0x00},/*"c",67*/
	{0x00,0x00,0x00,0x00,0x60,0x40,0x40,0x7C,0x42,0x42,0x42,0x42,0x62,0xDC,0x00,0x00},/*"d",68*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x42,0x7E,0x02,0x42,0x3C,0x00,0x00},/*"e",69*/
	{0x00,0x00,0x00,0x00,0x30,0x48,0x08,0x3E,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"f",70*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x22,0x22,0x1C,0x02,0x3C,0x42,0x42,0x3C},/*"g",71*/
	{0x00,0x00,0x00,0x00,0x03,0x02,0x02,0x3A,0x46,0x42,0x42,0x42,0x42,0xE7,0x00,0x00},/*"h",72*/
	{0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x0E,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"i",73*/
	{0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x38,0x20,0x20,0x20,0x20,0x20,0x20,0x22,0x1E},/*"j",74*/
	{0x00,0x00,0x00,0x00,0x03,0x02,0x02,0x72,0x12,0x0A,0x0E,0x12,0x22,0x77,0x00,0x00},/*"k",75*/
	{0x00,0x00,0x00,0x08,0x0E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"l",76*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x92,0x92,0x92,0x92,0x92,0xB7,0x00,0x00},/*"m",77*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3B,0x46,0x42,0x42,0x42,0x42,0xE7,0x00,0x00},/*"n",78*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00},/*"o",79*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1B,0x26,0x42,0x42,0x42,0x26,0x1A,0x02,0x07},/*"p",80*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x58,0x64,0x42,0x42,0x42,0x64,0x58,0x40,0xE0},/*"q",81*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x4C,0x04,0x04,0x04,0x04,0x1F,0x00,0x00},/*"r",82*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x42,0x02,0x3C,0x40,0x42,0x3E,0x00,0x00},/*"s",83*/
	{0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x3E,0x08,0x08,0x08,0x08,0x48,0x30,0x00,0x00},/*"t",84*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x63,0x42,0x42,0x42,0x42,0x62,0xDC,0x00,0x00},/*"u",85*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x22,0x22,0x14,0x14,0x08,0x08,0x00,0x00},/*"v",86*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDB,0x91,0x52,0x5A,0x2A,0x24,0x24,0x00,0x00},/*"w",87*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6E,0x24,0x18,0x18,0x18,0x24,0x76,0x00,0x00},/*"x",88*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x18,0x18,0x08,0x08,0x06},/*"y",89*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x22,0x10,0x08,0x08,0x44,0x7E,0x00,0x00},/*"z",90*/
	{0x00,0xC0,0x20,0x20,0x20,0x20,0x20,0x20,0x10,0x20,0x20,0x20,0x20,0x20,0xC0,0x00},/*"{",91*/
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},/*"|",92*/
	{0x00,0x03,0x04,0x04,0x04,0x04,0x04,0x04,0x08,0x04,0x04,0x04,0x04,0x04,0x03,0x00},/*"}",93*/
	{0x04,0x5A,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"~",94*/
};


/*全局变量*/
uint16_t point_color = BLACK;

/**
* @brief  LCD写寄存器函数
* @param  reg_addr:寄存器地址
*         reg_value:要写入的值
* @retval 无
*/
static inline void LCD_WriteReg(uint16_t reg_addr,uint16_t reg_value)
{
	LCD_WR_CMD(reg_addr);
	LCD_WR_DATA(reg_value);
}

#ifdef LCD_USE_FSMC

/**
* @brief  LCD读寄存器函数
* @param  reg_addr:寄存器地址
* @retval 从寄存器读出的值
*/
static inline uint16_t LCD_ReadReg(uint8_t reg_addr)
{
	LCD_WR_CMD(reg_addr);
	Delay_Us(5);
	return LCD_RD_DATA;
}

#endif /* LCD_USE_FSMC */

/**
* @brief  LCD初始化函数
* @param  无
* @retval 无
*/
void LCD_Init(void)
{
	#ifdef LCD_USE_FSMC
	
	/*开启GPIOD,GPIOE,FSMC外设时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);
	
	/*设置GPIO管脚工作模式*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                             //最大工作频率50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                              //通用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;                        //TFT_LED和TFT_REST
	GPIO_Init(GPIOD,&GPIO_InitStructure);                                         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                               //复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|  \
	                              GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7|  \
	                              GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|  \
	                              GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;            //TFT_DB2,TFT_DB3,TFT_RD,TFT_WR,TFT_CS,TFT_DB13,TFT_DB14,TFT_DB15,TFT_RS,TFT_DB0,TFT_DB1
	GPIO_Init(GPIOD,&GPIO_InitStructure);                                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|  \
	                              GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|  \
																GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;            //TFT_DB[4:12] 
  GPIO_Init(GPIOE,&GPIO_InitStructure);    
	                                                                              
	/*配置FSMC读时序参数*/                                                        
	FSMC_NORSRAMTimingInitTypeDef FSMC_ReadWriteTimingStructure;                  
	FSMC_ReadWriteTimingStructure.FSMC_AddressSetupTime = 1;                      //地址信号建立时间2个HCLK周期
	FSMC_ReadWriteTimingStructure.FSMC_AddressHoldTime = 0;
	FSMC_ReadWriteTimingStructure.FSMC_DataSetupTime = 15;                        //数据信号建立时间16个HCLK周期
	FSMC_ReadWriteTimingStructure.FSMC_BusTurnAroundDuration = 0;
	FSMC_ReadWriteTimingStructure.FSMC_CLKDivision = 0;
	FSMC_ReadWriteTimingStructure.FSMC_DataLatency = 0;
	FSMC_ReadWriteTimingStructure.FSMC_AccessMode = FSMC_AccessMode_A;            //异步访问模式A
	                                                                              
	/*配置FSMC写时序参数*/                                                        
	FSMC_NORSRAMTimingInitTypeDef FSMC_WriteTimingStructure;                      
	FSMC_WriteTimingStructure.FSMC_AddressSetupTime = 0;                          //地址信号建立时间1个HCLK周期
	FSMC_WriteTimingStructure.FSMC_AddressHoldTime = 0;
	FSMC_WriteTimingStructure.FSMC_DataSetupTime = 3;                             //数据信号建立时间4个HCLK周期
	FSMC_WriteTimingStructure.FSMC_BusTurnAroundDuration = 0;
	FSMC_WriteTimingStructure.FSMC_CLKDivision = 0;
	FSMC_WriteTimingStructure.FSMC_DataLatency = 0;
	FSMC_WriteTimingStructure.FSMC_AccessMode = FSMC_AccessMode_A;                //异步访问模式A
	                                                                              
	/*配置FSMC工作参数*/  
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMIintStructure;                            
	FSMC_NORSRAMIintStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;                    //LCD_CS连接到FSMC_NE1，因此这里选存储块1
	FSMC_NORSRAMIintStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;  //地址线与数据线不复用
	FSMC_NORSRAMIintStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;             //将LCD当作SRAM来处理
	FSMC_NORSRAMIintStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;    //数据线宽度16位
	FSMC_NORSRAMIintStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMIintStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMIintStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMIintStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMIintStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMIintStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;   //写操作使能
	FSMC_NORSRAMIintStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMIintStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;       //读写采用不同时序
	FSMC_NORSRAMIintStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMIintStructure.FSMC_ReadWriteTimingStruct = &FSMC_ReadWriteTimingStructure;
	FSMC_NORSRAMIintStructure.FSMC_WriteTimingStruct = &FSMC_WriteTimingStructure;
	FSMC_NORSRAMInit(&FSMC_NORSRAMIintStructure);
	
	/*使能BANK1的存储块1*/
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1,ENABLE);
	
	/*调用一次，防止警告，没有实际意义*/
	LCD_ReadReg(0x00);
	
	#else /* LCD_USE_FSMC */
	
	/*开启GPIOD,GPIOE,GPIOG外设时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	/*设置GPIO管脚工作模式*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                             //最大工作频率50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                              //通用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;                        //TFT_LED和TFT_REST
	GPIO_Init(GPIOD,&GPIO_InitStructure);                                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|  \
	                              GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7|  \
	                              GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|  \
	                              GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;           //TFT_DB2,TFT_DB3,TFT_RD,TFT_WR,TFT_CS,TFT_DB13,TFT_DB14,TFT_DB15,TFT_RS,TFT_DB0,TFT_DB1
	GPIO_Init(GPIOD,&GPIO_InitStructure);                                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|  \
	                              GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|  \
																GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;            //TFT_DB[4:12]
	GPIO_Init(GPIOE,&GPIO_InitStructure);                                                                            
	
	LCD_RD_HIGH;
	
	#endif /* LCD_USE_FSMC */
	
	/*复位LCD*/
	LCD_REST_HIGH;
	Delay_Ms(10);
	LCD_REST_LOW;
	Delay_Ms(10);
	LCD_REST_HIGH;
	
	/*LCD初始化序列*/
	LCD_WriteReg(0x11,0x001A);
	LCD_WriteReg(0x12,0x3121);
	LCD_WriteReg(0x13,0x006C);
	LCD_WriteReg(0x14,0x4249);
	LCD_WriteReg(0x10,0x0800);
	Delay_Ms(10);
	LCD_WriteReg(0x11,0x011A);
	Delay_Ms(10);
	LCD_WriteReg(0x11,0x031A);
	Delay_Ms(10);
	LCD_WriteReg(0x11,0x071A);
	Delay_Ms(10);
	LCD_WriteReg(0x11,0x0F1A);
	Delay_Ms(20);
	LCD_WriteReg(0x11,0x0F3A);
	Delay_Ms(30);
	LCD_WriteReg(0x01,0x011C);
	LCD_WriteReg(0x02,0x0100);
	LCD_WriteReg(0x03,0x1030);
	LCD_WriteReg(0x07,0x0000);
	LCD_WriteReg(0x08,0x0808);
	LCD_WriteReg(0x0B,0x1100);
	LCD_WriteReg(0x0C,0x0000);
	LCD_WriteReg(0x0F,0x1401);
	LCD_WriteReg(0x15,0x0000);
	LCD_WriteReg(0x20,0x0000);
	LCD_WriteReg(0x21,0x0000);
	LCD_WriteReg(0x38,0x00DB);
	LCD_WriteReg(0x39,0x0000);
	LCD_WriteReg(0x50,0x0001);
	LCD_WriteReg(0x51,0x020B);
	LCD_WriteReg(0x52,0x0805);
	LCD_WriteReg(0x53,0x0404);
	LCD_WriteReg(0x54,0x0C0C);
	LCD_WriteReg(0x55,0x000C);
	LCD_WriteReg(0x56,0x0101);
	LCD_WriteReg(0x57,0x0400);
	LCD_WriteReg(0x58,0x1108);
	LCD_WriteReg(0x59,0x050C);
	LCD_WriteReg(0x36,0x00AF);
	LCD_WriteReg(0x37,0x0000);
	LCD_WriteReg(0x38,0x00DB);
	LCD_WriteReg(0x39,0x0000);
	LCD_WriteReg(0x0F,0x0B01);
	LCD_WriteReg(0x07,0x0016);
	Delay_Ms(2);
	LCD_WriteReg(0x07,0x0017);
	LCD_WR_CMD(0x22);
	Delay_Ms(10);
	
	/*点亮背光*/
	LCD_LED_ON;
	
	/*清屏*/
	LCD_Clear(WHITE);
}

/**
* @brief  LCD显示窗口设置函数
* @param  x1,y1:窗口左上角坐标
*         x2,y2:窗口右下角坐标
* @retval 无
*/	
void LCD_Window(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2)
{
	LCD_WriteReg(0x37,x1);
	LCD_WriteReg(0x36,x2);
	LCD_WriteReg(0x39,y1);
	LCD_WriteReg(0x38,y2);
	
	LCD_WriteReg(0x20,x1);
	LCD_WriteReg(0x21,y1);
	
	LCD_WR_CMD(0x22);
}

/**
* @brief  LCD清屏函数
* @param  color:背景颜色
* @retval 无
*/
void LCD_Clear(uint16_t color)
{
	/*设置坐标*/
	LCD_Window(0,0,LCD_W-1,LCD_H-1);
	
	/*写入数据*/
	for(uint8_t i=0;i<LCD_W;i++)
		for(uint8_t j=0;j<LCD_H;j++)
			LCD_WR_DATA(color);
}

/**
* @brief  LCD绘制图片函数
* @param  drawBitmapStructure:一个LCD_DrawBitmapTypeDef类型的结构体指针
* @retval 无
*/
void LCD_DrawBitmap(LCD_DrawBitmapTypeDef *structure)
{
	/*检查参数合法性*/
	assert_param(structure->start_x < LCD_W || structure->start_y < LCD_H);
	assert_param(structure->start_x + structure->width <= LCD_W);
	assert_param(structure->start_y + structure->height <= LCD_H);
	
	/*设置坐标*/
	LCD_Window(structure->start_x,structure->start_y,structure->start_x+structure->width-1,structure->start_y+structure->height-1);
	
	/*写入数据*/
	for(uint16_t i = 0;i < (structure->height*structure->width/8);i++)
		for(uint8_t j = 0;j < 8;j++)
			(*(structure->pBitmapData + i)&(1<<j)) ? (LCD_WR_DATA(structure->color)) : (LCD_WR_DATA(WHITE));
}

/**
* @brief  LCD画点函数
* @param  x：点的横坐标
          y：点的纵坐标
          color：点的颜色
* @retval 无
*/
void LCD_DrawPoint(uint8_t x,uint8_t y)
{
	/*检查参数合法性*/
	assert_param(x < LCD_W || y < LCD_H);
	
	/*设置坐标*/
	LCD_Window(x,y,x,y);
	
	/*写入数据*/
	LCD_WR_DATA(point_color);
}

/**
* @brief  LCD显示字符函数
* @param  x：字符起始横坐标
          y：字符起始纵坐标
          color：字符的颜色
          ch：字符的ASCII码
* @retval 无
*/
void LCD_ShowChar(uint8_t x,uint8_t y,uint8_t ch)
{
	/*检查参数合法性*/
	assert_param(x < LCD_W-8 || y < LCD_H-16);
	
	uint8_t temp;
	
	/*设置窗口*/
	LCD_Window(x,y,x+7,y+15);
	
	/*写入数据*/
	for(uint8_t i = 0;i < 16;i++)
	{
		temp = ascii_8X16[ch-32][i];
		for(uint8_t j = 0;j < 8;j++)
		{
			if(temp & (1<<j))
			{
				LCD_WR_DATA(point_color);
			}
			else
			{
				LCD_WR_DATA(WHITE);
			}
		}
	}
}

uint8_t px = 0,py = 0;

/**
* @brief  设置格式化打印起始坐标函数
* @param  start_x:打印起始横坐标，范围0-167
*         start_y:打印起始纵坐标，范围0-212
* @retval 无
*/
void LCD_SetStart(uint8_t start_x,uint8_t start_y)
{
	/*检查参数合法性*/
	assert_param(start_x < LCD_W-8 || start_y < LCD_H-16);
	
	px = start_x;
	py = start_y;
}

/**
* @brief  LCD的格式化打印函数
* @param  与标准printf函数用法相同
* @retval 无
*/
#define CMD_BUFFER_LEN 128
void LCD_printf(char *fmt, ...)
{
	char buffer[CMD_BUFFER_LEN+1];
	uint8_t i = 0;
	
	va_list arg_ptr;
	va_start(arg_ptr,fmt);
	vsnprintf(buffer,CMD_BUFFER_LEN+1,fmt,arg_ptr);
	while((i < CMD_BUFFER_LEN) && buffer[i])
	{
		if(px > LCD_W-8)
		{
			px = 0;
			py += 16;
		}
		if(py > LCD_H-16)
		{
			px = 0;
			py = 0;
		}
		
		if(buffer[i] == '\n')
		{
			px = 0;
			py += 16;
			i++;
		}
		else if(buffer[i] == '\f')
		{
			px = 0;
			py = 0;
			i++;
		}
		else
		{
			LCD_ShowChar(px,py,buffer[i++]);
			px += 8;
		}
	}
	va_end(arg_ptr);
}


//边栏绘制
void SCREEN_frame_draw(uint16_t frame_color)
{
	LCD_Clear(WHITE);
	int h,w=0;
	//先绘制的是四周的边缘
	LCD_Window(0,0,SCREEN_WIDTH-1,SCREEN_HEIGHT-1);
	for(h=0;h<SCREEN_HEIGHT;h++)
	{
		for(w=0;w<SCREEN_WIDTH;w++)
		{
			if(PIXEL_IN_FRAME(h,w)) LCD_WR_DATA(frame_color);
			else LCD_WR_DATA(WHITE);
		}
	}
	//再绘制中间的横线
	LCD_Window(HORIZONTAL_MARGIN,MIDDLE_TOP,SCREEN_WIDTH-HORIZONTAL_MARGIN-1,MIDDLE_BOTTOM-1);
	for(h=0;h<MIDDLE_MARGIN_HEIGHT;h++)
	{
		for(w=0;w<(SCREEN_WIDTH-2*HORIZONTAL_MARGIN);w++)
		{
			LCD_WR_DATA(frame_color);
		}
	}
}


//绘制一个圆
void LCD_Full_Circle(uint16_t x0, uint16_t y0, uint16_t color)
{
	point_color = color;
	//圆的半径为9
	uint8_t areaSize = sizeof(circle_r9);
	uint8_t h,w;
	int8_t yOffset,xOffset;
	for(h = 0; h<areaSize; h++)
	{
		yOffset = - (areaSize-1)/2 + h;
		for(w = 0; w<circle_r9[h]; w++)
		{
			xOffset = - (circle_r9[h]-1)/2 + w;
			LCD_DrawPoint(x0+xOffset,y0+yOffset);
		}
	}
}


void SCREEN_static_character_draw(uint16_t font_color)
{
	point_color=font_color;
	uint8_t i = 0;
	//上半屏内字符
	LCD_SetStart(110, VERTICAL_MARGIN);
	LCD_printf("T Curve");
	LCD_SetStart(HORIZONTAL_MARGIN + 2,  CURVE_BOTTOM - 12);
	LCD_printf("0");
	LCD_SetStart(HORIZONTAL_MARGIN + 2,  CURVE_BOTTOM - 42);
	LCD_printf("30");
	LCD_SetStart(HORIZONTAL_MARGIN + 2,  CURVE_BOTTOM - 72);
	LCD_printf("60");
	LCD_SetStart(HORIZONTAL_MARGIN + 2,  CURVE_BOTTOM - 102);
	LCD_printf("90");
	//下半屏内字符
	LCD_SetStart(TABLE_CHARACTER_LEFT,TABLE_CHARACTER_TOP);
	LCD_printf("Temperature:     C");
	LCD_SetStart(TABLE_CHARACTER_LEFT,TABLE_CHARACTER_TOP+20);
	LCD_printf("Fan Motor:       %%");
	LCD_SetStart(TABLE_CHARACTER_LEFT,TABLE_CHARACTER_TOP+40);
	LCD_printf("Pump Motor:      %%");
	//考虑字符本身就占地方，余下的信息还是直接用色块显示
	for(i = 0; i<CIRCLE_NUMBER; i++)
	{
		LCD_Full_Circle(FIRST_CIRCLE_X0+CIRCLE_GAP*i, CIRCLE_Y0, BLUE);
	}
}

extern SYSTEM_MONITOR monitor;
void SCREEN_dynamic_character_reflash(uint16_t font_color)
{
	point_color=font_color;
	uint8_t i = 0;
	LCD_SetStart(TABLE_CHARACTER_LEFT+105,TABLE_CHARACTER_TOP);
	LCD_printf("%d",monitor.temperature);
	LCD_SetStart(TABLE_CHARACTER_LEFT+105,TABLE_CHARACTER_TOP+20);
	LCD_printf("%d",monitor.fanMotorDutyRatio);
	LCD_SetStart(TABLE_CHARACTER_LEFT+105,TABLE_CHARACTER_TOP+40);
	LCD_printf("%d",monitor.pumpMotorDutyRatio);
	//考虑字符本身就占地方，余下的信息还是直接用色块显示
	for(i = 0; i<CIRCLE_NUMBER; i++)
	{
		//绿色 有效
		if (monitor.state&(0x80>>i)) LCD_Full_Circle(FIRST_CIRCLE_X0+CIRCLE_GAP*i, CIRCLE_Y0, 0x350A);
		//红色 无效
		else LCD_Full_Circle(FIRST_CIRCLE_X0+CIRCLE_GAP*i, CIRCLE_Y0, 0xE0C3);
	}
}

extern TEMP_QUEUE temp_q;
void SCREEN_curve_reflash(uint16_t curve_color)
{
	uint16_t w = 0;
	uint16_t index,oldIndex = 0;
	//LCD_Window(HORIZONTAL_MARGIN,VERTICAL_MARGIN,SCREEN_WIDTH-HORIZONTAL_MARGIN-1,VERTICAL_MARGIN+CURVE_FIELD_HEIGHT-1);
	//w恰好是x轴的offset
	while(w<(SCREEN_WIDTH - HORIZONTAL_MARGIN - CURVE_LEFT))
	{
		//temp队列中的head指向最新的温度数据，最新的温度数据显示在屏幕左边
		if(temp_q.head>temp_q.rear)
		{
			if(w>=temp_q.head - temp_q.rear){break;}
			else{}
		}
		if(temp_q.head>=w) index = temp_q.head - w;
		else index = temp_q.head + 200 - w;
		oldIndex = index - 1;
		if(index == 0) oldIndex = 199; 
		//先擦除屏幕上此列的历史数据
		//注意用温度表示y轴偏移时用减而不用家，因为屏幕上越高的位置表示越高的温度而标号却越小
		point_color = WHITE;
		LCD_DrawPoint(CURVE_LEFT + w,CURVE_BOTTOM - temp_q.temp[oldIndex]);
		//color随温度平滑改变
		point_color = (RED-BLUE)*((float)(temp_q.temp[index]-20)/100)+BLUE;
		LCD_DrawPoint(CURVE_LEFT + w,CURVE_BOTTOM - temp_q.temp[index]);
		//ADD
		w++;
	}
}
