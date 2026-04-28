#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	//初始化a0a1引脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_LED;
	GPIO_LED.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_LED.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_LED.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_LED);
	//使引脚上拉为高电平（要不然小灯初始为亮）
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1);
	
}
//开关小灯函数
void LED1_ON(void)
{
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}
void LED1_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_0);

}
void LED2_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);

}
void LED2_OFF(void)
{
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

//小灯亮不亮取反函数

void LED1_Turn(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)//读取了小灯引脚的电位
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
	else
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	
}

void LED2_Turn(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0)
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	else
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	
}