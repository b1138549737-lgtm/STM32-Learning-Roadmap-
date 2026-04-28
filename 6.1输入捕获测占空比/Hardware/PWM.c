#include "stm32f10x.h"

void PWM_Init(void)
{
    // 1. 开时钟：TIM2 是 APB1，GPIOA 是 APB2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 2. GPIO 初始化：PA0 复用推挽输出（TIM2_CH1）
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   // 必须是复用推挽！
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 3. 时基单元配置
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    // 自动重装载 ARR：决定周期
    TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;

    // 预分频 PSC：决定频率
    TIM_TimeBaseInitStruct.TIM_Prescaler = 720 - 1;

    // 通用定时器必须写 0
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    // 4. 输出比较 PWM 配置（核心！）
    TIM_OCInitTypeDef TIM_OC1InitStructure;
    TIM_OCStructInit(&TIM_OC1InitStructure);

    TIM_OC1InitStructure.TIM_OCMode = TIM_OCMode_PWM1;        // PWM1 模式
    TIM_OC1InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;// 有效高电平
    TIM_OC1InitStructure.TIM_OutputState = TIM_OutputState_Enable; // 输出使能
    TIM_OC1InitStructure.TIM_Pulse = 0;                      // 初始占空比 0%

    TIM_OC1Init(TIM2, &TIM_OC1InitStructure);

    // 5. 使能 TIM2 外设
    TIM_Cmd(TIM2, ENABLE);
}

// 设置占空比：CCR1 值（0~99）
void PWM_SetCompare1(uint16_t Compare)
{
    TIM_SetCompare1(TIM2, Compare);
}

// 修改预分频器（可动态改频率）
void PWM_SetPrescaler(uint16_t Prescaler)
{
    TIM_PrescalerConfig(TIM2, Prescaler, TIM_PSCReloadMode_Immediate);
}
