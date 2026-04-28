#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"

// 定义两个变量，记录 LED 状态
uint8_t LED1_Status = 0;
uint8_t LED2_Status = 0;

int main(void)
{
	uint8_t KeyNum;
	
	/*模块初始化*/
	OLED_Init();
	LED_Init();
	Key_Init();
	
	OLED_ShowString(1, 3, "LED Systeam");
	
	while (1)
	{
		KeyNum = Key_GetNum();
		
		// 按键1按下 → 翻转LED1 → 同步改变状态
		if(KeyNum == 1)
		{
			LED1_Turn();
			LED1_Status = !LED1_Status;
		}
		
		// 按键2按下 → 翻转LED2 → 同步改变状态
		if(KeyNum == 2)
		{
			LED2_Turn();
			LED2_Status = !LED2_Status;
		}
		
		// 根据变量显示，而不是根据按键显示
		if(LED1_Status == 1)
		{
			OLED_ShowString(3, 4, "LED1 ON ");
		}
		else
		{
			OLED_ShowString(3, 4, "LED1 OFF");
		}
		
		if(LED2_Status == 1)
		{
			OLED_ShowString(4, 4, "LED2 ON ");
		}
		else
		{
			OLED_ShowString(4, 4, "LED2 OFF");
		}
	}
}
