#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC

void InitOutput(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0+GPIO_Pin_1+GPIO_Pin_10+GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void InitSysTick()
{
	SysTick -> LOAD = 0x423F;
	SysTick -> VAL = 0UL;
	SysTick -> CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}
volatile static uint8_t flag;
void SysTick_Handler(void)
{
	if (flag == 0)
		{
		GPIO_SetBits(GPIOB, GPIO_Pin_11);
		flag = 1;
		}
		else
		{
		GPIO_ResetBits(GPIOB, GPIO_Pin_11);
		flag = 0;
		}
}

int main(void)
{
	SysTick_Config(80000);
	InitOutput();
	//InitSysTick();
	
	//GPIO_SetBits(GPIOB, GPIO_Pin_11);
	
}
