#ifndef _USART_K210_H
#define _USART_K210_H

#include "system.h"  

extern u8 k210_data;

void K210_Init(void);
void Set_Temp_K210(float temp);

#endif

