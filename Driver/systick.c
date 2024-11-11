#include <stdint.h>
#include "gd32f30x.h"
#include "FreeRTOS.h"

extern void xPortSysTickHandler(void);

static volatile uint64_t g_sysRunTime = 0;

/**
***********************************************************
* @brief systick��ʼ��
* @param
* @return 
***********************************************************
*/
void SystickInit(void)
{
	/*1ms ����һ�ζ�ʱ�ж�*/
	if (SysTick_Config(rcu_clock_freq_get(CK_AHB) / 1000))
	{
		while (1);
	}
}

/**
***********************************************************
* @brief ��ʱ�жϷ�������1ms����һ���ж�
* @param
* @return 
***********************************************************
*/
void SysTick_Handler(void)
{
	#if (INCLUDE_xTaskGetSchedulerState  == 1 )
	if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
		{	
	#endif   
	xPortSysTickHandler();
	#if (INCLUDE_xTaskGetSchedulerState  == 1 )
		}
	#endif  

}

/**
***********************************************************
* @brief ��ȡϵͳ����ʱ��
* @param
* @return ��1msΪ��λ
***********************************************************
*/
uint64_t GetSysRunTime(void)
{
	return g_sysRunTime;
}
