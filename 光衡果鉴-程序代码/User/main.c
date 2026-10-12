#include "system.h"

u16 gAdcAdValue = 0;   // 存储AD值
float weight_Kg;
extern uint8_t Class,chance;

int wuping = 0;
int wuping_cnt = 0;
int server_flag = 0;

//单价
#define WUPING_NULL	255	//空
#define WUPING_0 	6	//苹果
#define WUPING_1 	0	//橘子
#define WUPING_2 	5	//西蓝花
#define WUPING_3 	0	//
#define WUPING_4 	6	//桃子
#define WUPING_5 	3	//茄子
#define WUPING_6 	0	//
#define WUPING_7 	2	//洋葱
#define WUPING_8 	0	//
#define WUPING_9 	4	//梨
#define WUPING_10 	0	//
#define WUPING_11 	0	//
#define WUPING_12 	0	//
#define WUPING_13 	0	//
#define WUPING_14 	3	//圆辣椒
#define WUPING_15 	0	//
#define WUPING_16 	4	//橘子	

//物品标签
#define LAB_NULL 			255	//空
#define LAB_PingGuo 		0	//苹果
#define LAB_NanGua 			1	//南瓜
#define LAB_XiLanHua 		2	//西蓝花
#define LAB_HongLaJiao 		3	//红辣椒
#define LAB_TaoZi 			4	//桃子
#define LAB_QieZi 			5	//茄子
#define LAB_NingMeng 		6	//柠檬
#define LAB_YangCong 		7	//洋葱
#define LAB_ShanZhu 		8	//山竹
#define LAB_LiZi 			9	//梨子
#define LAB_DaSuan 			10	//大蒜
#define LAB_QinTianJiao 	11	//青甜椒
#define LAB_MoGu 			12	//蘑菇
#define LAB_QinLaJiao 		13	//青辣椒
#define LAB_HongTianJiao 	14	//红甜椒
#define LAB_FanQie 			15	//番茄
#define LAB_JuZi 			16	//橘子

typedef struct wupin_t
{
	int name;
	int value;
}WuPin;

WuPin wupinArr[256]={
	{LAB_PingGuo, 		WUPING_0},
	{LAB_NanGua, 		WUPING_1},
	{LAB_XiLanHua, 		WUPING_2},
	{LAB_HongLaJiao, 	WUPING_3},
	{LAB_TaoZi, 		WUPING_4},
	{LAB_QieZi, 		WUPING_5},
	{LAB_NingMeng, 		WUPING_6},
	{LAB_YangCong, 		WUPING_7},
	{LAB_ShanZhu, 		WUPING_8},
	{LAB_LiZi, 			WUPING_9},
	{LAB_DaSuan, 		WUPING_10},
	{LAB_QinTianJiao, 	WUPING_11},
	{LAB_MoGu, 			WUPING_12},
	{LAB_QinLaJiao, 	WUPING_13},
	{LAB_HongTianJiao, 	WUPING_14},
	{LAB_FanQie, 		WUPING_15},
	{LAB_JuZi, 			WUPING_16},

	[255] = 
	{LAB_NULL,		WUPING_NULL}
};


void Draw_Lab(int lab);
void Draw_data(int data);

int main(void)
{
	SysTick_Init(72);
	
	Servos_Init();
	
	NVIC_Config();
	OLED_Init();
	K210_Init();
	
//	Servos_Init();
//	Servos2_Init();
	Init_HX711pin();


	Get_Maopi();				//称毛皮重量
	delay_ms(1000);
	delay_ms(1000);
	Get_Maopi();				//重新获取毛皮重量

	while(1)
	{
		delay_ms(50);

		Get_Weight();
		weight_Kg = Weight_Shiwu/6680.0;

		wuping = k210_data;

		Draw_Lab(wuping);
		Draw_data(wupinArr[wuping].value);
		
		if(wuping == LAB_YangCong)
		{
			if(server_flag!=LAB_YangCong) 
			{
				Set_server(0);
				server_flag=LAB_YangCong;
			}
		}
		
		if(wuping == LAB_PingGuo)
		{
			if(server_flag!=LAB_PingGuo) 
			{
				Set_server(1);
				server_flag=LAB_PingGuo;
			}
		}
		
		if(wuping == LAB_NingMeng)
		{
			if(server_flag!=LAB_NingMeng) 
			{
				Set_server(2);
				server_flag=LAB_NingMeng;
			}
		}
	}
}


u8 lab_str_len[17] = {2, 2, 3, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2, 3, 3, 2, 2};
void Draw_Lab(int lab)
{
	if(lab == LAB_NULL)
	{
		OLED_Write(40,0,16,"xxx   ");
		OLED_Write(40,2,16,"0.00kg ");
	}
	else
	{
		int cnt = 0;
		for(int i=0; i<lab; i++)
		{
			cnt += lab_str_len[i];
		}
		for(int i=0; i<lab_str_len[lab]; i++)
		{
			OLED_ShowChinese(40+i*16,0,cnt++);
		}
	}
}

void Draw_data(int data)
{
	if(data == WUPING_NULL)
	{
		int len = OLED_Write(40,4,16,"0") * 8;
		OLED_ShowChinese(len+40, 4, 47);
		len += 16;
		OLED_Write(len+40,4,16,"/kg ");
		len = OLED_Write(40,6,16,"0.00") * 8;
		OLED_ShowChinese(len+40,6,47);
		OLED_Write(len+40+16,4,16,"  ");
	}
	else
	{
		OLED_Write(40,2,16,"%.2fkg ",weight_Kg*8.8);
		int len = OLED_Write(40,4,16,"%d", data) * 8;
		OLED_ShowChinese(len+40, 4, 47);

		len += 16;
		OLED_Write(len+40,4,16,"/kg ");
		len = OLED_Write(40,6,16,"%.2f", weight_Kg*8.8 * data) * 8;
		OLED_ShowChinese(len+40,6,47);
		OLED_Write(len+40+16,4,16,"  ");
	}
}
