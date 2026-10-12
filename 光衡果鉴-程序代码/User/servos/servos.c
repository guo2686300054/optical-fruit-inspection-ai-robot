#include "servos.h"

//-90度
//TIM_SetCompare1(TIM4,1750);//占空比（2000-1750）/2000*20ms=2.5ms

//45度
//TIM_SetCompare1(TIM4,1800);//占空比（2000-1800）/2000*20ms=2ms

//0度
//TIM_SetCompare1(TIM4,1850);//占空比（2000-1850）/2000*20ms=1.5ms

//-45度
//TIM_SetCompare1(TIM4,1900);//占空比（2000-1900）/2000*20ms=1ms

//-90度
//TIM_SetCompare1(TIM4,1945);//占空比（2000-1945）/2000*20ms=0.5ms  	
		
//PB6
void Servos_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  ,ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  ,ENABLE); 

	//设置该引脚为复用输出功能
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//初始化TIM4
	TIM_TimeBaseStruct.TIM_Period = 20000-1;//重装载值 
	TIM_TimeBaseStruct.TIM_Prescaler = 72-1;//预分频值 
	TIM_TimeBaseStruct.TIM_ClockDivision = 0; //时钟分频1、2、4分频	
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//设置计数模式
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct);
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);
	
	//初始化输出比较参数
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性
	TIM_OC1Init(TIM2,&TIM_OCInitTypeStruct); //选择定时器输出通道 TIM4_CH1
	
//	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式
//	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_Low;//输出极性
	TIM_OC2Init(TIM2,&TIM_OCInitTypeStruct); //选择定时器输出通道 TIM4_CH1
	TIM_OC2Init(TIM4,&TIM_OCInitTypeStruct); //选择定时器输出通道 TIM4_CH1
	
	//使能预装载寄存器
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	//使能定时器
	TIM_Cmd(TIM2,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
	
	TIM_SetCompare1(TIM2,1500);
	TIM_SetCompare2(TIM2,1500);
	TIM_SetCompare2(TIM4,1500);
}

void Servos2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  ,ENABLE); 
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//初始化TIM4
	TIM_TimeBaseStruct.TIM_Period = 20000-1;//重装载值 
	TIM_TimeBaseStruct.TIM_Prescaler = 72-1;//预分频值 
	TIM_TimeBaseStruct.TIM_ClockDivision = 0; //时钟分频1、2、4分频	
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//设置计数模式
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);
	
	//初始化输出比较参数
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性

	TIM_OC2Init(TIM4,&TIM_OCInitTypeStruct); //选择定时器输出通道 TIM4_CH1
	
	//使能预装载寄存器
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	//使能定时器
	TIM_Cmd(TIM4,ENABLE);
	
	TIM_SetCompare2(TIM4,1500);
}

void Set_server(int id)
{
	if(id==0)
	{
		TIM_SetCompare1(TIM2,1300);
		delay_ms(700);
		TIM_SetCompare1(TIM2,1500);
		delay_ms(700);
		TIM_SetCompare1(TIM2,1700);
		delay_ms(700);
		TIM_SetCompare1(TIM2,1500);
	}
	else if(id==1)
	{
		TIM_SetCompare2(TIM2,1200);
		delay_ms(500);
		TIM_SetCompare2(TIM2,1500);
		delay_ms(700);
		TIM_SetCompare2(TIM2,1800);
		delay_ms(500);
		TIM_SetCompare2(TIM2,1500);
	}
	else if(id==2)
	{
		TIM_SetCompare2(TIM4,1200);
		delay_ms(400);
		TIM_SetCompare2(TIM4,1500);
		delay_ms(700);
		TIM_SetCompare2(TIM4,1800);
		delay_ms(400);
		TIM_SetCompare2(TIM4,1500);
	}
}

//2150-1250
void Set_X(u16 k)
{
	TIM_SetCompare4(TIM3,k);
}

//1150-2050
void Set_Y(u16 k)
{
	TIM_SetCompare3(TIM3,k);
}
