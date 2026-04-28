#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	// 原代码缺失这一行：
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);						//将PA1和PA2引脚初始化为推挽输出
	
	/*设置GPIO初始化后的默认电平*/
	GPIO_SetBits(GPIOA, GPIO_Pin_0);		
// 时钟分频：用于数字滤波，不分频（常用配置）
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;

// 计数模式：向上计数（从0数到ARR，溢出后清零）
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

// 自动重装载值（ARR）：计数器数到这个值就溢出
// 范围：0~65535，本配置为10000
	TIM_TimeBaseInitStruct.TIM_Period = 20000 - 1;     //ARR的值

// 预分频器（PSC）：对72MHz时钟分频
// 范围：0~65535，本配置为7200-1
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;     //PSC的值

// 重复计数器：仅高级定时器用，通用定时器TIM2写0即可
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;


	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
		
	TIM_OCInitTypeDef TIM_OC1InitStructure;
	TIM_OCStructInit(&TIM_OC1InitStructure);
	TIM_OC1InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC1InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OC1InitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1InitStructure.TIM_Pulse = 0;               //CCR的值
	TIM_OC1Init(TIM2,&TIM_OC1InitStructure); 
	
	TIM_Cmd(TIM2, ENABLE);
}
void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);

}
