#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"
#include "PWM.h"

int main(void)
{
	uint8_t i;
	
	/*模块初始化*/
	OLED_Init();
	PWM_Init();
	
	OLED_ShowString(1, 1, "PWM LED Systeam");
	
	while (1)
	{
		for(i=0;i<=100;i++)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
		for(i=0;i<=100;i++)
		{
			PWM_SetCompare1(100-i);
			Delay_ms(10);
		}
	}
}
