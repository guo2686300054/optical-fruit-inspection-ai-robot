#ifndef _OLED_H
#define _OLED_H

#include "system.h"

#define OLED_NUM     0
#define OLED_Str     1
#define OLED_f       2

#define OLED_IIC_SCL_RCC   RCC_APB2Periph_GPIOB
#define OLED_IIC_SCL_GPIO  GPIOB
#define OLED_IIC_SCL_PIN   GPIO_Pin_8

#define OLED_IIC_SDA_RCC   RCC_APB2Periph_GPIOB
#define OLED_IIC_SDA_GPIO  GPIOB
#define OLED_IIC_SDA_PIN   GPIO_Pin_9

//#define IIC_SCL				PAout(5)
//#define IIC_SDA				PAout(4)//Êä³öÊý¾Ý

#define OLED_SCL_Clr() GPIO_ResetBits(OLED_IIC_SCL_GPIO,OLED_IIC_SCL_PIN)//SCL
#define OLED_SCL_Set() GPIO_SetBits(OLED_IIC_SCL_GPIO,OLED_IIC_SCL_PIN)

#define OLED_SDA_Clr() GPIO_ResetBits(OLED_IIC_SDA_GPIO,OLED_IIC_SDA_PIN)//SDA
#define OLED_SDA_Set() GPIO_SetBits(OLED_IIC_SDA_GPIO,OLED_IIC_SDA_PIN)

void OLED_Init(void);
void OLED_IIC_Init(void);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_ShowChinese(u8 x,u8 y,u8 no);
void OLED_ShowString(u8 x,u8 y,char *chr,u8 Char_Size);
void OLED_float(float a,int x,int y);
void OLED_ShowNum(uint8_t x, uint8_t y, int_least64_t num, uint8_t len, uint8_t sizey);
u32 oled_pow(u8 m,u8 n);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_Clear(void);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void IIC_XIE_DATA(unsigned char IIC_Command);
void IIC_XIE_ML(unsigned char IIC_Command);
void IIC_XIE(unsigned char IIC_Byte);
void IIC_Ack(void);
void IIC_Stop(void);
void IIC_Start(void);
int OLED_Write(int x,int y,int Size,const char *formate,...);


#endif

