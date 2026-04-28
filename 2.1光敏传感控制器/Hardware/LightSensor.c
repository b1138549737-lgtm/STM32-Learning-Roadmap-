#include "stm32f10x.h"                  // Device header

void LightSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Key;
	GPIO_Key.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_Key.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_13;
	GPIO_Key.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Key);

}
// 获取按键电压的函数
uint8_t LightSensor_Get(void)//定义了一个返回值为8bit整形的函数
{
	
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}