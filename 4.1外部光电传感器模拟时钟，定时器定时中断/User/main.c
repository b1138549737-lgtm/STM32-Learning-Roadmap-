#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"
#include "Timer.h" 

uint8_t Num = 0;


int main(void)
{
	
	
	/*模块初始化*/
	OLED_Init();
	Timer_Init();
	
	OLED_ShowString(1, 2, "Clock Systeam");
	
	while (1)
	{
		OLED_ShowHexNum(2,1,Num,8);
		OLED_ShowHexNum(3,1,Timer_GetCounter(),8);
	}
}

void TIM2_IRQHandler(void)
{
// ====================== 1. 判断中断来源 ======================
// 检查是否为【更新中断】触发
if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
{
    // ====================== 2. 中断业务代码 ======================
    // 在这里写你要执行的操作（例如LED翻转、计数等）
    // 示例：LED_Turn();
		Num++;
    // ====================== 3. 清除中断标志位 ======================
    // 必须清除！否则会一直重复进中断
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
}
