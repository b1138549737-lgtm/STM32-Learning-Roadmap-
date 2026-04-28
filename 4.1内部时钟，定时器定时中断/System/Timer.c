#include "stm32f10x.h"

// 这里声明外部变量（告诉编译器 Num 在别的文件里）
extern uint8_t Num;

/**
  * 函    数：Timer_Init
  * 功    能：TIM2定时器初始化 【1秒触发一次更新中断】
  * 计算公式：定时时间 = (PSC+1)*(ARR+1) / 72MHz
  * 本配置：(7200)*(10000)/72000000 = 1秒
  */
void Timer_Init(void)
{
// ====================== 1. 开启TIM2时钟 ======================
// TIM2挂载在APB1总线上，必须先开时钟才能操作寄存器
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

// ====================== 2. 选择定时器时钟源 ======================
// 配置为【内部时钟】(72MHz)，默认也是内部时钟，显式配置更规范
TIM_InternalClockConfig(TIM2);

// ====================== 3. 时基单元配置（核心） ======================
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

// 时钟分频：用于数字滤波，不分频（常用配置）
TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;

// 计数模式：向上计数（从0数到ARR，溢出后清零）
TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

// 自动重装载值（ARR）：计数器数到这个值就溢出
// 范围：0~65535，本配置为10000
TIM_TimeBaseInitStruct.TIM_Period = 10000 - 1;

// 预分频器（PSC）：对72MHz时钟分频
// 范围：0~65535，本配置为7200-1
TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1;

// 重复计数器：仅高级定时器用，通用定时器TIM2写0即可
TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;

// 初始化时基单元
TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

// ====================== 4. 清除初始中断标志位 ======================
// 防止刚初始化就进一次不必要的中断
TIM_ClearFlag(TIM2, TIM_FLAG_Update);

// ====================== 5. 使能【更新中断】 ======================
// 计数器溢出/归零 → 触发更新中断
TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

// ====================== 6. NVIC中断配置 ======================
// 中断分组（整个工程只需配置一次，建议放main函数开头）
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

NVIC_InitTypeDef NVIC_InitStructure;

// 正确的TIM2中断通道！
NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;

// 使能中断通道
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

// 抢占优先级：1
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;

// 子优先级：1
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

// 初始化NVIC
NVIC_Init(&NVIC_InitStructure);

// ====================== 7. 启动TIM2定时器 ======================
TIM_Cmd(TIM2, ENABLE);
}

/**
  * 函    数：TIM2_IRQHandler
  * 功    能：TIM2中断服务函数（系统自动调用）
  * 说    明：每1秒进入一次中断
  */
/*void TIM2_IRQHandler(void)
{
// ====================== 1. 判断中断来源 ======================
// 检查是否为【更新中断】触发
if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
{
    // ====================== 2. 中断业务代码 ======================
    Num++;
    
    // ====================== 3. 清除中断标志位 ======================
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
}*/
