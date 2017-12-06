/*
	* TFT_LED --> PD12
	* TFT_REST --> PD11
	*	TFT_CS --> FSMC_NE1(PD7)
	*	TFT_DB0 --> FSMC_D0(PD14)
	*	TFT_DB1 --> FSMC_D1(PD15)
	*	TFT_DB2 --> FSMC_D2(PD0)
	*	TFT_DB3 --> FSMC_D3(PD1)
	*	TFT_DB4 --> FSMC_D4(PE7)
	*	TFT_DB5 --> FSMC_D5(PE8)
	*	TFT_DB6 --> FSMC_D6(PE9)
	*	TFT_DB7 --> FSMC_D7(PE10)
	*	TFT_DB8 --> FSMC_D8(PE11)
	*	TFT_DB9 --> FSMC_D9(PE12)
	*	TFT_DB10 --> FSMC_D10(PE13)
	*	TFT_DB11 --> FSMC_D11(PE14)
	*	TFT_DB12 --> FSMC_D12(PE15)
	*	TFT_DB13 --> FSMC_D13(PD8)
	*	TFT_DB14 --> FSMC_D14(PD9)
	*	TFT_DB15 --> FSMC_D15(PD10)
	*	TFT_RS --> FSMC_A18(PD13)
	*	TFT_RD --> FSMC_NOE(PD4)
	*	TFT_WR --> FSMC_NWE(PD5)
	*
	*	本库支持FSMC驱动和软件模拟8080并口驱动
	* 使用FSMC驱动请添加宏定义“#define LCD_USE_FSMC"，否则使用软件模拟8080并口驱动
	* FSMC驱动效率最高，但FSMC会与TIM4_CH2(PB7)管脚发生冲突，以至于该管脚不能用于输出PWM信号
	* 如需使用TIM4_CH2(PB7)输出PWM信号，请选择软件模拟8080并口驱动LCD
	*
	* 使用本库需要实现毫秒级延时函数 "void Delay_Ms(uint32_t nms)"
 */ 
	
#ifndef __DRV_LCD_H
#define __DRV_LCD_H
	
#include "main.h"
	
#define LCD_W 176          //LCD宽度176像素
#define LCD_H 220          //LCD高度220像素

typedef struct
{
	uint8_t *pBitmapData;
	uint8_t start_x;
	uint8_t start_y;
	uint8_t width;
	uint8_t height;
	uint16_t color;
}LCD_DrawBitmapTypeDef;

#define LCD_REST_HIGH      GPIOD->BSRR = 1<<11
#define LCD_REST_LOW       GPIOD->BSRR = 1<<27
#define LCD_LED_ON         GPIOD->BSRR = 1<<12
#define LCD_LED_OFF        GPIOD->BSRR = 1<<28
	
#ifdef LCD_USE_FSMC
	
typedef struct
{
	__IO uint16_t CR;        //虚拟的LCD“指令寄存器”
	__IO uint16_t DR;        //虚拟的LCD“数据寄存器”
}LCD_TypeDef;

/*LCD的地址（根据硬件连接确定）*/
#define LCD_BASE           (uint32_t)(0x60000000|0x0007FFFE)
#define LCD                ((LCD_TypeDef *) LCD_BASE)

/*FSMC方式实现LCD读写时序*/
#define LCD_WR_CMD(value)  LCD->CR = (value)
#define LCD_WR_DATA(value) LCD->DR = (value)
#define LCD_RD_DATA        LCD->DR					

#else /* LCD_USE_FSMC */

#define LCD_CS_HIGH        GPIOD->BSRR = 1<<7
#define LCD_CS_LOW         GPIOD->BSRR = 1<<23
#define LCD_RS_HIGH        GPIOD->BSRR = 1<<13
#define LCD_RS_LOW         GPIOD->BSRR = 1<<29
#define LCD_RD_HIGH        GPIOD->BSRR = 1<<4
#define LCD_RD_LOW         GPIOD->BSRR = 1<<20
#define LCD_WR_HIGH        GPIOD->BSRR = 1<<5
#define LCD_WR_LOW         GPIOD->BSRR = 1<<21

/*软件模拟8080并口方式实现LCD写时序*/
#define LCD_DATA_OUT(data) {                     \
													 GPIOD->ODR &= 0x38FC; \
                           GPIOD->ODR |= ((data&0x000C)>>2)|((data&0xE000)>>5)|((data&0x0003)<<14);  \
													 GPIOE->ODR &= 0x007F; \
													 GPIOE->ODR |= (data&0x1FF0)<<3; \
                           }

#define LCD_WR_CMD(value)  {                     \
	                         LCD_RS_LOW;           \
                           LCD_CS_LOW;           \
													 LCD_DATA_OUT(value);  \
													 LCD_WR_LOW;           \
													 LCD_WR_HIGH;          \
													 LCD_CS_HIGH;          \
                           }
													 
#define LCD_WR_DATA(value) {                     \
	                         LCD_RS_HIGH;          \
                           LCD_CS_LOW;           \
                           LCD_DATA_OUT(value);  \
                           LCD_WR_LOW;           \
                           LCD_WR_HIGH;          \
                           LCD_CS_HIGH;          \
                           }

#endif /* LCD_USE_FSMC */

/*预定义颜色*/
//颜色格式RGB565，也可参照色值表自行定义
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	   0x001F  
#define RED           	 0xF800
#define GREEN         	 0x07E0
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 
#define GRAY  			     0X8430 

													 
													 
#define SCREEN_HEIGHT 220
#define SCREEN_WIDTH 176

#define VERTICAL_MARGIN 5
#define HORIZONTAL_MARGIN 4

#define MIDDLE_MARGIN_HEIGHT 3
#define MIDDLE_TOP VERTICAL_MARGIN+CURVE_FIELD_HEIGHT-1
#define MIDDLE_BOTTOM MIDDLE_TOP+MIDDLE_MARGIN_HEIGHT

#define CURVE_FIELD_HEIGHT 120
#define CURVE_BOTTOM_MARGIN 5
#define CURVE_BOTTOM MIDDLE_TOP - CURVE_BOTTOM_MARGIN
#define CURVE_LEFT_LABLE 20
#define CURVE_LEFT HORIZONTAL_MARGIN + CURVE_LEFT_LABLE


//#define TABLE_FIELD_HEIGHT 90
#define TABLE_TOP_MARGIN 3
#define TABLE_CHARACTER_TOP MIDDLE_BOTTOM+TABLE_TOP_MARGIN
#define TABLE_LEFT_MARGIN 10
#define TABLE_CHARACTER_LEFT VERTICAL_MARGIN+TABLE_LEFT_MARGIN

#define CIRCLE_Y0 200
#define FIRST_CIRCLE_X0 25
#define CIRCLE_GAP 25
#define CIRCLE_NUMBER 6

#define PIXEL_IN_FRAME(h,w) (((h<VERTICAL_MARGIN)||(h>SCREEN_HEIGHT-VERTICAL_MARGIN-1))||((w<HORIZONTAL_MARGIN)||(w>SCREEN_WIDTH-HORIZONTAL_MARGIN-1)))



/*全局变量*/
extern const uint8_t tongji_logo[176][22];                                //同济校徽点阵数据
extern uint16_t point_color;                                              //画笔颜色

#ifdef LCD_USE_FSMC

static inline uint16_t LCD_ReadReg(uint8_t reg_addr);                     //LCD读寄存器

#endif /* LCD_USE_FSMC */

static inline void LCD_WriteReg(uint16_t reg_addr,uint16_t reg_value);    //LCD写寄存器
void LCD_Clear(uint16_t color);                                           //LCD清屏
void LCD_Window(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);             //LCD设置窗口
void LCD_Init(void);                                                      //LCD初始化	
void LCD_DrawBitmap(LCD_DrawBitmapTypeDef *structure);                    //LCD绘制图片
void LCD_DrawPoint(uint8_t x,uint8_t y);	                                //LCD画点
void LCD_ShowChar(uint8_t x,uint8_t y,uint8_t ch);                        //LCD显示字符
void LCD_SetStart(uint8_t start_x,uint8_t start_y);                       //设置格式化打印起始坐标
void LCD_printf(char *fmt, ...);                                          //LCD格式化打印


void LCD_Full_Circle(uint16_t x0, uint16_t y0, uint16_t color);
void SCREEN_frame_draw(void);
void SCREEN_static_character_draw(void);
void SCREEN_dynamic_character_reflash(void);
void SCREEN_curve_reflash(void);
uint8_t SCREEN_function_list(void);

#endif /* __DRV_LCD_H */
