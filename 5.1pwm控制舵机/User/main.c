#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"
#include "PWM.h"

int main(void)
{
	uint16_t i=0;
	
	/*模块初始化*/
	OLED_Init();
	PWM_Init();
	

	while (1)
	{
		i=500;
		PWM_SetCompare1(i);
		OLED_ShowString(1, 1, "PWM:");
		OLED_ShowSignedNum(1,4,i,8);
		Delay_s(2);
		i=2500;
		PWM_SetCompare1(i);
		OLED_ShowString(1, 1, "PWM:");
		OLED_ShowSignedNum(1,4,i,8);
		Delay_s(2);
	}
}
