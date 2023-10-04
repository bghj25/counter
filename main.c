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
void InitButton(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void InitSysTick()
{
	SysTick -> LOAD = 100000;
	SysTick -> VAL = 0UL;
	SysTick -> CTRL =  SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

volatile static uint8_t val;
volatile static uint8_t flag;
volatile static uint8_t in1, in2, in3;
void SysTick_Handler(void)
{
	uint8_t cur_in;
	cur_in = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);
	
	if((cur_in == in2) && (cur_in == in3) && (cur_in != in1))
	{
		if (cur_in == 0)
		{
			val++;
			if(val >= 4)
			{
				val = 0;
			}
			
		}
	}
	in1 = in2;
	in2 = in3;
	in3 = cur_in;
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_0+GPIO_Pin_1+GPIO_Pin_10+GPIO_Pin_11);
	switch(val)
	{
		case 0: GPIO_SetBits(GPIOB, GPIO_Pin_0);
		break;
		case 1: GPIO_SetBits(GPIOB, GPIO_Pin_1);
		break;
		case 2: GPIO_SetBits(GPIOB, GPIO_Pin_10);
		break;
		case 3: GPIO_SetBits(GPIOB, GPIO_Pin_11);
		break;
	}
	

}

int main(void)
{
	InitOutput();
	InitButton();
	InitSysTick();
	
	while(1)
	{

	}
		
}
