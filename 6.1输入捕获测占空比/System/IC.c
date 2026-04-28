#include "stm32f10x.h"

void IC_Init(void)
{
    // 1. 开时钟：TIM3 是 APB1，GPIOA 是 APB2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 2. GPIO 初始化：PA6 上拉输入（TIM3_CH1）
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // 输入上拉，正确
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 3. 定时器时基配置
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInitStruct.TIM_Period = 65535;  // 最大值，防止溢出
    TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;  // 72M /72 = 1MHz 计数
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);  // 必须先初始化时基！

    // 4. 输入捕获配置（核心！）
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);  // 必须加，默认值初始化

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0F;
    // ================= 错误 1 修复 =================
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;  // 上升沿触发
    // ===============================================
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);
	
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    // 5. 从模式 + 触发源（ Slave Mode = Reset ）
    TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);

    // 6. 开启定时器
    TIM_Cmd(TIM3, ENABLE);
}

// 获取频率（正确公式）
uint16_t IC_GetFreq(void)
{
    return 1000000 / (TIM_GetCapture1(TIM3)+1);
}
uint16_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM3)+1)*100/(TIM_GetCapture1(TIM3)+1);


}
