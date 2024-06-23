#include "stm32f10x.h"
#include "delay.h"
#include "motor.h"
#include "keysacn.h"
#include "IRSEARCH.h"
#include "IRAvoid.h"
#include "remote.h"   

#define KEYMODE_1   1  // ����ģʽ1-ѭ��ģʽ
#define KEYMODE_2   2  // ����ģʽ2-����ģʽ
#define KEYMODE_3   3  // ����ģʽ3-ң��ģʽ
uint8_t keyMode;      //ָ�޷���8Bit������

void IR_IN()                             //����ң���ӳ���
{
	  u8 key;	
  //  ZYSTM32_brake(10);	
	   key=Remote_Scan();	
			switch(key)
			{    
				case 98:ZYSTM32_run(80,100);break;	    
				case 2:ZYSTM32_brake(100);break;		 	  
				case 194:ZYSTM32_Left(80,100);break;	   
				case 34:ZYSTM32_Right(80,100);break;		  
				case 224:ZYSTM32_Spin_Left(80,100);break;		  
				case 168:ZYSTM32_back(80,100);break;		   
				case 144:ZYSTM32_Spin_Right(80,100);break;		    
			}
}

void KeyScanTask(void)//�����ӳ���
{
	static u8 keypre = 0;//����������ʱ��1
	
	if((keypre == 0)&& (KEY))
	{
		keypre = 1; //��1������������°���ʱ�ٴν���˺�����
		switch(keyMode)
		{
			case KEYMODE_1:keyMode = KEYMODE_2; break;
			case KEYMODE_2:keyMode = KEYMODE_3; break;
			case KEYMODE_3:keyMode = KEYMODE_1; break;
			default: break;
		}
	}
	if(!KEY)  //�������ſ�
	{
		keypre = 0;//��0�������ٴ��л�LEDģʽ
	}
}

//����ѭ�������ϡ�ң��ģʽ����
void LEDTask()
{
		switch(keyMode)
		{
			case KEYMODE_1:
				LED_D4_SET;
				LED_D3_RESET;
				SearchRun();
			  	break;
			case KEYMODE_2:
				LED_D4_RESET;
			  	LED_D3_SET;
        		AVoidRun();
			  	break;
			case KEYMODE_3:
				LED_D4_SET;
			  	LED_D3_SET;
        		IR_IN();			
			  	break;
			default:
         		break;
		}
}
	

//	  int val;
//  val=KEY;  //��ȡ����
//  while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))//������û�б�����ʱ��һֱѭ��
//  {
//    val=KEY;//�ʾ��ʡ�ԣ�����ѭ���ܿ�
//  }
//  while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))//������������ʱ
//  {
//    delay_ms(10);	  //��ʱ10ms
//    val=KEY;//��ȡ���ֶ˿�PC2�ڵ�ƽֵ����Val
//    if(val==1)  //�ڶ����жϰ����Ƿ񱻰���
//    {
//      BEEP_SET;		//��������
//      while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))	//�жϰ�ʱ�Ƿ��ɿ�
//        BEEP_RESET;	//������ֹͣ
//    }
//    else
//				BEEP_RESET;//������ֹͣ
//  }
//}


 int main(void)
 {	
	delay_init();
	KEY_Init();
	IRSearchInit();
	IRAvoidInit();
	TIM4_PWM_Init(7199,0);  //��ʼ��PWM
	Remote_Init();			    //������ճ�ʼ��	
	ZYSTM32_brake(500);
//	 keysacn();		

	keyMode = KEYMODE_1;//

	while(1)
	{  
		//ͨ�������л�ģʽ
		KeyScanTask();
		
		LEDTask();			
	}
 }

