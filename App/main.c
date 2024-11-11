#include <stdint.h>
#include <stdio.h>
#include "gd32f30x.h"
#include "led_drv.h"
#include "key_drv.h"
#include "systick.h"
#include "usb2com_drv.h"
#include "FreeRTOS.h"
#include "task.h"


//��LED����
//�������ȼ�
#define LED_TASK_PRIO				(tskIDLE_PRIORITY + 1)
//�����ջ��С	
#define LED_STK_SIZE 		50  
//������
TaskHandle_t LEDTask_Handler;
//������
void LED_Task(void *pvParameters);

//��Debug����
//�������ȼ�
#define Debug_TASK_PRIO		(tskIDLE_PRIORITY + 2)
//�����ջ��С	
#define Debug_STK_SIZE 		512  
//������
TaskHandle_t Debug_Task_Handler;
//������
void Debug_Task(void *pvParameters);


/**********************************************************************************************************
* �� �� ��: RTOS_Init
* ����˵��: RTOS��ʼ�������ڴ�������
* �� �Σ���
* �� �� ֵ: ��
**********************************************************************************************************/
void RTOS_Init(void)
{
	taskENTER_CRITICAL();           //�����ٽ���
	//����LED����
	xTaskCreate((TaskFunction_t )LED_Task,     	
							(const char*    )"LED_task",   	
							(uint16_t       )LED_STK_SIZE, 
							(void*          )NULL,				
							(UBaseType_t    )LED_TASK_PRIO,	
							(TaskHandle_t*  )&LEDTask_Handler); 
					
	//����Debug����
	xTaskCreate((TaskFunction_t )Debug_Task,     	
							(const char*    )"Debug_task",   	
							(uint16_t       )Debug_STK_SIZE, 
							(void*          )NULL,				
							(UBaseType_t    )Debug_TASK_PRIO,	
							(TaskHandle_t*  )&Debug_Task_Handler); 
							
	taskEXIT_CRITICAL();            //�˳��ٽ���	
	vTaskStartScheduler();          //�����������
}


/**********************************************************************************************************
* �� �� ��: LED_Task
* ����˵��: LED����
* ��  	��: ��
* �� �� ֵ: ��
**********************************************************************************************************/
void LED_Task(void *pvParameters)
{
    while(1)
    {
		ToggleLed(LED1);
		vTaskDelay(500);
		ToggleLed(LED2);
		vTaskDelay(500);
		ToggleLed(LED3);
		vTaskDelay(500);
    }
} 
/**********************************************************************************************************
* �� �� ��: Debug_Task
* ����˵��: Debug����
* ��  	��: ��
* �� �� ֵ: ��
**********************************************************************************************************/
void Debug_Task(void *pvParameters)
{
    while(1)
    {
      printf("Hello FreeRTOS\r\n");
      vTaskDelay(500);
    }
} 

int main(void)
{	
	SystickInit();
	LedDrvInit();
	//KeyDrvInit();
	//Usb2ComDrvInit();
	RTOS_Init();
	

}
