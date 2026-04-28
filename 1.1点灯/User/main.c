#include "stm32f10x.h"
#include "Delay.h"
int main(void)
{
	//初始化GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitLED;
	GPIO_InitLED.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitLED.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitLED.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitLED);
	
	
	while(1)
	{
		//使小灯闪烁 低电平点亮
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)0);
		Delay_ms(500);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)1);
		Delay_ms(500);
	}	

}
