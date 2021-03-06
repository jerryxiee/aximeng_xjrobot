
#include <includes.h>

TIM_TypeDef* const gHardTimerList[MAX_HARD_TIMER_CNT+1] = {
    TIM1 , TIM1 , TIM2 , TIM3 , TIM4 , TIM5 , TIM6 , TIM7 , TIM8
};

//////////////////////////////////////////////////////////////////////////
//多个定时器的 编码器功能 IO口配置函数  需要配置每个定时器的 1 2 通道为定时器功能复用
void TimerCode_And_Gpio_Init_TIM1(void)
{
    //BOX_ERROR_HANDLER( 777 );  //未实现 错误报警
}

//	主电机编码器采集	PB4 TIM3_CH1      PB5->TIM3_CH2
void TimerCode_And_Gpio_Init_TIM3(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 ,ENABLE);    /*使能TIM3 时钟*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE); /*使能GPIOB时钟*/

	
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3); //将定时器管脚映射到pb4 引脚
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_TIM3); //将定时器管脚映射到pb5引脚
	
    GPIO_InitStructure.GPIO_Speed  =GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Speed  =GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
}

//	从电机编码器采集
//PB6 – 58 – CK_CODEA_S2 – TIM4_CH1 （重映射）– 从动轮编码器A通道信号采集
//PB7 – 59 – CK_CODEB_S2 – TIM4_CH2 （重映射）– 从动轮编码器B通道信号采集
void TimerCode_And_Gpio_Init_TIM4(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);    /*使能TIM4时钟*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);   /*使能GPIOB时钟*/
	
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
	
    GPIO_InitStructure.GPIO_Speed  =GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7 ; /*timer4 重映射的通道1 2*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
}


// PA0 – 14 – CK_CODEA_CD – TIM5_CH1（重映射）– 从动轮轮子编码器B通道信号采集
// PA1 – 15 – CK_CODEB_CD – TIM5_CH2（重映射）– 从动轮轮子编码器A通道信号采集
void TimerCode_And_Gpio_Init_TIM5(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);    /*使能TIM5时钟*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);   /*使能GPIOD时钟*/
	
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource0 | GPIO_PinSource1, GPIO_AF_TIM5);

    GPIO_InitStructure.GPIO_Speed  =GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; /*timer5 重映射的通道1 2*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
}

// PA5 – 21 – CK_CODEZ_CD – TIM2_CH1（重映射）– 从动轮轮子编码器Z通道信号采集
void TimerCode_And_Gpio_Init_TIM2(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);    /*使能TIM2时钟*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);   /*使能GPIOD时钟*/
	
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM5);

    GPIO_InitStructure.GPIO_Speed  =GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; /*timer5 重映射的通道1*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
}



typedef void (*VoidFuncPtr) (void); 
const VoidFuncPtr TimerCode_And_Gpio_Inits[MAX_HARD_TIMER_CNT+1] = {
    TimerCode_And_Gpio_Init_TIM1 ,//使定时器号码从1开始算
    TimerCode_And_Gpio_Init_TIM1 ,
    TimerCode_And_Gpio_Init_TIM2 ,
    TimerCode_And_Gpio_Init_TIM3 ,
    TimerCode_And_Gpio_Init_TIM4 ,
    TimerCode_And_Gpio_Init_TIM5 ,
    //TimerCode_And_Gpio_Init_TIM6 ,
    //TimerCode_And_Gpio_Init_TIM7 ,
    //TimerCode_And_Gpio_Init_TIM8 ,
};

//定时器 编码器采集功能驱动  TIM1  ~  TIM8
void TimerCode_DefaultFunction_Init(u32 timer_ID)
{
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
    TIM_ICInitTypeDef           TIM4_ICInitStructure;
    
    (*TimerCode_And_Gpio_Inits[timer_ID])();

    TIM_DeInit( gHardTimerList[timer_ID] );
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period        = 0xFFFF;				//设定计数器重装值
    TIM_TimeBaseStructure.TIM_Prescaler     = 0;					//TIM4时钟预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;		//设置时钟分割 T_dts = T_ck_int	
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; //TIM向上计数 
    TIM_TimeBaseInit( gHardTimerList[timer_ID] , &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig( gHardTimerList[timer_ID] , TIM_EncoderMode_TI12, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising);//使用编码器模式3，上升计数
    TIM_ICStructInit(&TIM4_ICInitStructure);						//将结构体中的内容缺省输入   通道1输入
    TIM4_ICInitStructure.TIM_ICFilter = 0;							//选择输入比较滤波器 
    TIM_ICInit( gHardTimerList[timer_ID] , &TIM4_ICInitStructure);	//将TIM_ICInitStructure中的指定参数初始化TIM4

    TIM_ITConfig( gHardTimerList[timer_ID] , TIM_IT_Update, DISABLE );//运行更新中断 禁用

    gHardTimerList[timer_ID]->CNT = 0; //初始化时清空计数
    TIM_Cmd( gHardTimerList[timer_ID] , ENABLE);					    //启动TIM?定时器
}



/************************************************* 
*Function:	 MST_PWM_Init_Tim1_CH2	
*Input:			
*OUTPUT:		    
*Return:		
*DESCRIPTION:主动轮电机PWM波初始化配置函数
*           PB14 –35 – MT_CTL_PWM1 – TIM1_CH2 – 主动轮PWM控制
*************************************************/
void MST_PWM_Init_Tim1_CH2(void)
{
    GPIO_InitTypeDef            GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
    TIM_OCInitTypeDef           TIM_OCInitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //打开B组GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  // 打开定时器1时钟
	
		/* 定时器通道引脚复用 */
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM1); 
	
    /* 定时器通道引脚配置 */															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOB, &GPIO_InitStructure);

    //   TIM_TimeBaseStructure.TIM_RepetitionCounter=1;  . 
    TIM_TimeBaseStructure.TIM_ClockDivision=0;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数
    TIM_TimeBaseStructure.TIM_Period=100;
    TIM_TimeBaseStructure.TIM_Prescaler=360;
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
    //ARR的周期值对应   TIM_TimeBaseStructure.TIM_Period  的设置值
    //PSC的分频值对应   TIM_TimeBaseStructure.TIM_Prescaler 的设置值
    //PWM频率=（72000K/（PSC+1））/ ARR = 2k

    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM2        ;
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_Low     ;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low    ;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable ;
    TIM_OCInitStructure.TIM_Pulse       = 0                      ;
    //占空比值/100 = 设置值/ARR       设置值 =（占空比值/100）* ARR 

    TIM_OCInitStructure.TIM_OutputNState    = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_OCNIdleState    = TIM_OCNIdleState_Reset;
    TIM_OCInitStructure.TIM_OCIdleState     = TIM_OCIdleState_Reset ;

    TIM_OC2Init(TIM1,&TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable); //TIM_1---->通道2[PB14] 

    TIM_CtrlPWMOutputs(TIM1,ENABLE);
    TIM_Cmd(TIM1,ENABLE);
}

/************************************************* 
*Function:	 SLV_PWM_Init_Tim8_CH3	
*Input:			
*OUTPUT:		    
*Return:		
*DESCRIPTION:电机PWM波初始化配置函数
*           PB15 – 36 – MT_CTL_PWM2 – TIM8_CH3 – 从动轮PWM控制
*************************************************/
void SLV_PWM_Init_Tim8_CH3(void)
{
    GPIO_InitTypeDef            GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
    TIM_OCInitTypeDef           TIM_OCInitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //打开B组GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  // 打开定时器8时钟

		/* 定时器通道引脚复用 */
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM8); 
	
		/* 定时器通道引脚配置 */															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	

    //   TIM_TimeBaseStructure.TIM_RepetitionCounter=1;  . 
    TIM_TimeBaseStructure.TIM_ClockDivision=0;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数
    TIM_TimeBaseStructure.TIM_Period=100;
    TIM_TimeBaseStructure.TIM_Prescaler=360;
    TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);
    //ARR的周期值对应   TIM_TimeBaseStructure.TIM_Period  的设置值
    //PSC的分频值对应   TIM_TimeBaseStructure.TIM_Prescaler 的设置值
    //PWM频率=（72000K/（PSC+1））/ ARR = 2k

    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM2        ;
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_Low     ;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low    ;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable ;
    TIM_OCInitStructure.TIM_Pulse       = 0                      ;
    //占空比值/100 = 设置值/ARR       设置值 =（占空比值/100）* ARR 

    TIM_OCInitStructure.TIM_OutputNState    = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_OCNIdleState    = TIM_OCNIdleState_Reset;
    TIM_OCInitStructure.TIM_OCIdleState     = TIM_OCIdleState_Reset ;

    TIM_OC3Init(TIM8,&TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM8,TIM_OCPreload_Enable); //TIM_8---->通道3[PB15]  

    TIM_CtrlPWMOutputs(TIM8,ENABLE);
    TIM_Cmd(TIM8,ENABLE);
}







