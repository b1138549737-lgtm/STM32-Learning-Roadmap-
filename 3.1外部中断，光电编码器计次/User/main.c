#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"

int main(void)
{
	uint16_t CountSensor_GetNum;
	CountSensor_Init();
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	
	/*OLED显示*/

	OLED_ShowString(1, 1, "Get:");	//1行3列显示字符串HelloWorld!

	
	while (1)
	{
		CountSensor_GetNum = CountSensor_Get();
		OLED_ShowSignedNum(1,4,CountSensor_GetNum,5);
		
	}
}
