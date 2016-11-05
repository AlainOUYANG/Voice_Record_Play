/*********************************************************************************
   *      Copyright:  (C) 2016 SCUEC
   *                  All rights reserved.
   *
   *       Filename:  main.c
   *    Description: 
   *
   *        Version:  1.0.0(5/11/16)
   *         Author:  LI WJNG <liwjng@gmail.com>
   *      ChangeLog:  1, Release initial version on "5/11/16 10:52:13"
   *
   ********************************************************************************/
	 
#include "stm32f4xx.h"
#include "stm32f4_flash.h"
#include "stm32f4_timer.h"
#include "stm32f4_adc.h"
#include "stm32f4_dac.h"
#include "stm32f4_key.h"
#include "stm32f4_led.h"

extern uint32_t g_writeAdder;
extern uint32_t g_readAdder;
volatile u16 g_flag = 0;
void Record(void);
void  Play(void);

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
  key_config();       //������ʼ��
  Init_LED_GPIO();    //LED��ʼ��
  TIM2_config();      //TIM2��ʱ������
	TIM3_config();      //TIM3��ʱ�����ã�
	ADC_config();       //ADC����
	DMA_config();       //DMA����
	DAC_config();       //DAC����
	
	while(1)
  {		
		if(key_pressed(KEY1) && !g_flag)
		{
			Record();
		}
		
		if(g_flag && key_pressed(KEY2))
		{
			Play();//��ʼִ��Play����
			if(g_readAdder == 0x0800C004)
			{
			 TIM_Cmd(TIM2,DISABLE);
			}
		}
  }

}
 


/***************�ɼ����Ҵ洢**************/		
void Record(void)
{
	turn_led(LED2,ON);//LED��ز������ã�����LED3
	TIM_Cmd(TIM3,ENABLE); 
}


/*****��ȡflash�е�ֵ��ͨ��DAC���*/
void Play(void)
{
	TIM_Cmd(TIM2,ENABLE); //ʹ�ܶ�ʱ��2
	turn_led(LED4,ON);
}




