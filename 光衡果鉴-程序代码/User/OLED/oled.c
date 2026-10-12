#include "oled.h"
#include "oledfont.h"
#include "bmp.h"
#include "stdarg.h"
#include "string.h"

void IIC_Start(void)
{
	OLED_SCL_Set();
	OLED_SDA_Set();
	OLED_SDA_Clr();
	OLED_SCL_Clr();
}

void IIC_Stop(void)
{
  OLED_SCL_Set() ;
	OLED_SDA_Clr();
	OLED_SDA_Set();
}

void IIC_Ack(void)
{
	OLED_SCL_Set();
	OLED_SCL_Clr();
}

void IIC_XIE(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCL_Clr();
	for(i=0;i<8;i++)		
	{
		m=da;
		m=m&0x80;
		if(m==0x80)
		{
		  OLED_SDA_Set();
		}
		else 
		{
			OLED_SDA_Clr();
		}
			da=da<<1;
		  OLED_SCL_Set();
		  OLED_SCL_Clr();
		}
}

void IIC_XIE_ML(unsigned char IIC_Command)
{
   IIC_Start();
   IIC_XIE(0x78);
	 IIC_Ack();	
   IIC_XIE(0x00);
	 IIC_Ack();	
   IIC_XIE(IIC_Command); 
	 IIC_Ack();	
   IIC_Stop();
}

void IIC_XIE_DATA(unsigned char IIC_Command)
{
   IIC_Start();
   IIC_XIE(0x78);
	 IIC_Ack();	
   IIC_XIE(0x40);
	 IIC_Ack();	
   IIC_XIE(IIC_Command); 
	 IIC_Ack();	
   IIC_Stop();
}

void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	
	IIC_XIE_ML(0xb0+y);
	IIC_XIE_ML(((x&0xf0)>>4)|0x10);
	IIC_XIE_ML(x&0x0f); 
}

void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		IIC_XIE_ML (0xb0+i); 
		IIC_XIE_ML (0x00);
		IIC_XIE_ML (0x10);
		for(n=0;n<128;n++)IIC_XIE_DATA(0); 
	}
}

void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{
	unsigned char c=0,i=0;	
	c=chr-' ';//得到偏移后的值			
	if(x>128-1){x=0;y=y+2;}
	if(Char_Size ==16)
	{
		OLED_Set_Pos(x,y);
		for(i=0;i<8;i++) IIC_XIE_DATA(F8X16[c*16+i]);
		
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++) IIC_XIE_DATA(F8X16[c*16+i+8]);
	}
	else 
	{	
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++) IIC_XIE_DATA(F6x8[c][i]);
	}
}

u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}		

void OLED_ShowNum(uint8_t x, uint8_t y, int_least64_t num, uint8_t len, uint8_t sizey)
{
  uint8_t t, temp, m = 0;
  uint8_t enshow = 0;
	if(num<0)
	{
		num=-num;
		OLED_ShowChar(x,y,'-',16);
		x=x+8;
	}
  if (sizey == 8)
    m = 2;
  for (t = 0; t < len; t++)
  {
    temp = (num / oled_pow(10, len - t - 1)) % 10;
    if (enshow == 0 && t < (len - 1))
    {
      if (temp == 0)
      {
        OLED_ShowChar(x + (sizey / 2 + m) * t, y, ' ', sizey);
        continue;
      }
      else
        enshow = 1;
    }
    OLED_ShowChar(x + (sizey / 2 + m) * t, y, temp + '0', sizey);
  }
}

void OLED_float(float a,int x,int y)
{
	uint16_t b,k;
	uint32_t c;
	int m=0,i=0;
	uint32_t a1;
	if(a<0)
	{
		a=-a;
		OLED_ShowChar(x,y,'-',16);
		x=x+8;
	}
	b=(uint16_t)a;
	k=(uint16_t)a;
	while(b)
	{
		b=b/10;
		m++;
	}
	c=(uint32_t)(a*100000);
	a1=c%(oled_pow(10,5));
	OLED_ShowNum(x,y,k,m,16);
	OLED_ShowChar(m*8+x,y,'.',16);
	OLED_ShowNum((m+1)*8+x,y,a1,5,16);
//	OLED_ShowNum(x,5,c,5+m,16);
	while(c%10==0)
	{
		c=c/10;
		i++;
	}
	while(i)
	{
		OLED_ShowChar((m+6-i)*8+x,y,' ',16);
		i--;
	}
}

void OLED_ShowString(u8 x,u8 y,char *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		
		OLED_ShowChar(x,y,chr[j],Char_Size);
		x+=8;
		if(x>120)
		{
			x=0;y+=2;
		}
		j++;
	}
}

void OLED_ShowChinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
  for(t=0;t<16;t++)
  {
   	IIC_XIE_DATA(Hzk2[2*no][t]);
		adder+=1;
  }	
	OLED_Set_Pos(x,y+1);	
  for(t=0;t<16;t++)
	{	
		IIC_XIE_DATA(Hzk2[2*no+1][t]);
		adder+=1;
  }					
}

void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	IIC_XIE_DATA(BMP[j++]);	    	
	    }
	}
}

void OLED_IIC_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(OLED_IIC_SCL_RCC|OLED_IIC_SDA_RCC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = OLED_IIC_SCL_PIN;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(OLED_IIC_SCL_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = OLED_IIC_SDA_PIN;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(OLED_IIC_SDA_GPIO, &GPIO_InitStructure);
}

void OLED_Init(void)
{
	OLED_IIC_Init();
	delay_ms(200);
	IIC_XIE_ML(0xAE);
	IIC_XIE_ML(0x00);
	IIC_XIE_ML(0x10);
	IIC_XIE_ML(0x40);
	IIC_XIE_ML(0xB0);
	IIC_XIE_ML(0x81);
	IIC_XIE_ML(0xFF);
	IIC_XIE_ML(0xA1);
	IIC_XIE_ML(0xA6);
	IIC_XIE_ML(0xA8);
	IIC_XIE_ML(0x3F);
	IIC_XIE_ML(0xC8);
	IIC_XIE_ML(0xD3);
	IIC_XIE_ML(0x00);
	IIC_XIE_ML(0xD5);
	IIC_XIE_ML(0x80);
	IIC_XIE_ML(0xD8);
	IIC_XIE_ML(0x05);
	IIC_XIE_ML(0xD9);
	IIC_XIE_ML(0xF1);
	IIC_XIE_ML(0xDA);
	IIC_XIE_ML(0x12);
	IIC_XIE_ML(0xDB);
	IIC_XIE_ML(0x30);
	IIC_XIE_ML(0x8D);
	IIC_XIE_ML(0x14);
	IIC_XIE_ML(0xAF);
	OLED_Clear();

	void Menu_Init(void);
	Menu_Init();
}  

int OLED_Write(int x,int y,int Size,const char *formate,...)
{
	char buf[32]={'\0'};
	va_list ap;
	va_start(ap,formate);
	vsprintf(buf,formate,ap);
	va_end(ap);
	OLED_ShowString(x,y,buf,Size);
	return strlen(buf);
}

void Menu_Init(void)
{
	OLED_ShowChinese(0,0,14+27);
	OLED_ShowChinese(16,0,15+27);
	OLED_Write(32,0,16,":");

	OLED_ShowChinese(0,2,12+27);
	OLED_ShowChinese(16,2,13+27);
	OLED_Write(32,2,16,":");

	OLED_ShowChinese(0,4,16+27);
	OLED_ShowChinese(16,4,17+27);
	OLED_Write(32,4,16,":");

	OLED_ShowChinese(0,6,18+27);
	OLED_ShowChinese(16,6,19+27);
	OLED_Write(32,6,16,":");
}
