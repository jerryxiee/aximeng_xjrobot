#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include <includes.h>

static __inline void GpioInit(
	uint32_t RCC_AHB1Periph     ,   //需要使能的总线，一般为 RCC_AHB1Periph_GPIOX
	GPIO_TypeDef* GPIOx         ,   //GPIOA~F
	uint16_t GPIO_Pin           ,   //管脚  GPIO_Pin_0~15
	GPIOMode_TypeDef GPIO_Mode      //模式  GPIO_Mode_Out_OD ...
)
{
    GPIO_InitTypeDef            GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph , ENABLE);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin ; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode ;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}
static __inline void GpioInit_NoPeriph(
	GPIO_TypeDef* GPIOx         ,   //GPIOA~F
	uint16_t GPIO_Pin           ,   //管脚  GPIO_Pin_0~15
	GPIOMode_TypeDef GPIO_Mode      //模式  GPIO_Mode_Out_OD ...
)
{
    GPIO_InitTypeDef            GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin ; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode ;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}

static __inline void GPIO_INIT_OUT_OD(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){
    GpioInit_NoPeriph(GPIOx,GPIO_Pin,GPIO_Mode_OUT);
}
static __inline void GPIO_INIT_OUT_PP(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){
    GpioInit_NoPeriph(GPIOx,GPIO_Pin,GPIO_Mode_OUT);
}
static __inline void GPIO_INIT_IPU   (GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){
    GpioInit_NoPeriph(GPIOx,GPIO_Pin,GPIO_Mode_OUT   );
}
static __inline void GPIO_INIT_AIN   (GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){
    GpioInit_NoPeriph(GPIOx,GPIO_Pin, GPIO_Mode_AIN   );
}
static __inline void GPIO_INIT_IN_FLOAT (GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){
    GpioInit_NoPeriph(GPIOx,GPIO_Pin,GPIO_Mode_IN   );
}


static __inline void GpioSetH(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
    GPIOx->BSRRL = GPIO_Pin;//BSRR寄存器低16位置1，引脚输出高电平 caigz add
}
static __inline void GpioSetL(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
    GPIOx->BSRRH = GPIO_Pin;//BSRR寄存器高16位置1，引脚输出低电平		caigz add
}
static __inline void GpioSetBit(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,bool bHigh)
{
    if( bHigh ) { GpioSetH(GPIOx,GPIO_Pin); }
    else        { GpioSetL(GPIOx,GPIO_Pin); }
}
static __inline void GpioToggle(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
    GPIOx->ODR ^= GPIO_Pin;
}
static __inline bool GpioGet(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
    if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET )
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif
