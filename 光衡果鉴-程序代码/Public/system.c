#include "system.h"

void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 

//	NVIC_InitStructure.NVIC_IRQChannel=TIM8_CC_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;	
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	
	// NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;               //K210
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;	
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	
	// NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	// NVIC_Init(&NVIC_InitStructure);
	
	// NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;               //À¶ÑÀ
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	
	// NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	// NVIC_Init(&NVIC_InitStructure);

	// NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;               //À¶ÑÀ
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;	
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	
	// NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	// NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;               //À¶ÑÀ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
//	NVIC_InitStructure.NVIC_IRQChannel=UART5_IRQn;               //³µ2Êý¾Ý
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;	
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;	
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	
	// NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// NVIC_Init(&NVIC_InitStructure);

	// NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;               
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	// NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	// NVIC_Init(&NVIC_InitStructure);	
	
//	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn;                  //µç³ØµçÑ¹¼ì²â
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);	
}

