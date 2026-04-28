#include "stm32f10x.h"
#include "Delay.h"   // 用你自己的延时函数

uint16_t CountSensor_Count = 0;

void CountSensor_Init(void)
{
    // 开时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // PA8 上拉输入
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 中断引脚映射
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);

    // EXTI 配置
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line8;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStruct);

    // NVIC 优先级分组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // NVIC 通道
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    CountSensor_Count = 0;
}

// 获取计数值
uint16_t CountSensor_Get(void)
{
    return CountSensor_Count;
}

// 中断服务函数（带防抖）
void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line8) == SET)
    {
        // 防抖：延时10ms，等待电平稳定
        Delay_ms(10);
        
        // 再次确认引脚是低电平，才计数
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0)
        {
            CountSensor_Count ++;
        }

        // 清除中断标志位
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
}