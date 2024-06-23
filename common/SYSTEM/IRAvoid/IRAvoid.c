#include "IRAvoid.h"
#include "delay.h"
#include "motor.h"
#include "keysacn.h"
#include "stm32f10x.h"                  // Device header

int SR_2;    //�ұߺ�����ϴ�����״̬
int SL_2;    //��ߺ�����ϴ�����״̬
void IRAvoidInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = AVOID_RIGHT_PIN;//����ʹ��GPIO�ܽ� PB1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//����GPIOģʽ,��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����GPIO�˿��ٶ�
	GPIO_Init(AVOID_RIGHT_PIN_GPIO , &GPIO_InitStructure); 
	
  GPIO_InitStructure.GPIO_Pin = AVOID_LEFT_PIN;//����ʹ��GPIO�ܽ� PB1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//����GPIOģʽ,��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����GPIO�˿��ٶ�
	GPIO_Init(AVOID_LEFT_PIN_GPIO , &GPIO_InitStructure); 
}


void AVoidRun(void)
{
	SR_2 = AVOID_RIGHT_IO;
	SL_2 = AVOID_LEFT_IO;
	if(SL_2 == 1 && SR_2 == 1)
	{
		 ZYSTM32_run(40,1);
		 BEEP_RESET;
     LED_D3_RESET;		
	}
	else if (SL_2 == 1 && SR_2 == 0)
	{
//		ZYSTM32_back(70,200);  
//		ZYSTM32_brake(30);//ֹͣ30MS
		ZYSTM32_Spin_Left(70,300);
	}
	else if(SR_2 == 1 && SL_2 == 0)
	{
//		ZYSTM32_back(70,200);   
//		ZYSTM32_brake(30);//ֹͣ30MS		
			ZYSTM32_Spin_Right(70,300);
	}
	else
	{
		BEEP_SET;
     	LED_D3_SET;	
	   	ZYSTM32_brake(300);//ֹͣ300MS
		ZYSTM32_back(70,1000);//����400MS
		
		ZYSTM32_Spin_Left(100,500);//��ת500MS
		
				
	}
	
}
