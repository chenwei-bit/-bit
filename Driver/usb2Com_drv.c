#include <stdint.h>
#include <stdio.h>
#include "gd32f30x.h"

typedef struct
{
	uint32_t uartNo;
	rcu_periph_enum rcuUart;
	rcu_periph_enum rcuGpio;
	uint32_t gpio;
	uint32_t txPin;
	uint32_t rxPin;
} UartHwInfo_t;

static UartHwInfo_t g_uartHwInfo = {USART0, RCU_USART0, RCU_GPIOA, GPIOA, GPIO_PIN_9, GPIO_PIN_10};

static void Usb2ComGpioInit(void)
{
	rcu_periph_clock_enable(g_uartHwInfo.rcuGpio);
	gpio_init(g_uartHwInfo.gpio, GPIO_MODE_AF_PP, GPIO_OSPEED_10MHZ, g_uartHwInfo.txPin);
	gpio_init(g_uartHwInfo.gpio, GPIO_MODE_IPU, GPIO_OSPEED_10MHZ, g_uartHwInfo.rxPin);
}

static void Usb2ComUartInit(uint32_t baudRate)
{
	/* ʹ��UARTʱ�ӣ�*/
	rcu_periph_clock_enable(g_uartHwInfo.rcuUart);
	/* ��λUART��*/
	usart_deinit (g_uartHwInfo.uartNo);
	/* ͨ��USART_CTL0�Ĵ�����WL�����ֳ���*/ 
	//usart_word_length_set(g_uartHwInfo.uartNo, USART_WL_8BIT);
	/* ͨ��USART_CTL0�Ĵ�����PCEN����У��λ��*/ 
	//usart_parity_config(g_uartHwInfo.uartNo, USART_PM_NONE);
	/* ��USART_CTL1�Ĵ�����дSTB[1:0]λ������ֹͣλ�ĳ��ȣ�*/ 
	//usart_stop_bit_set(g_uartHwInfo.uartNo, USART_STB_1BIT);
	/* ��USART_BAUD�Ĵ��������ò����ʣ�*/ 
	usart_baudrate_set(g_uartHwInfo.uartNo, baudRate);
	/* ��USART_CTL0�Ĵ���������TENλ��ʹ�ܷ��͹��ܣ�*/
	usart_transmit_config(g_uartHwInfo.uartNo, USART_TRANSMIT_ENABLE);
	/* ��USART_CTL0�Ĵ�������λUENλ��ʹ��UART��*/ 
	usart_enable(g_uartHwInfo.uartNo);
}

void Usb2ComTest(void)
{
	for (uint8_t i = 0; i <= 250; i++)
	{
		usart_data_transmit(g_uartHwInfo.uartNo, i);
		while (RESET == usart_flag_get(g_uartHwInfo.uartNo, USART_FLAG_TBE));
	}
//	while (RESET == usart_flag_get(g_uartHwInfo.uartNo, USART_FLAG_TC));
//	usart_transmit_config(g_uartHwInfo.uartNo, USART_TRANSMIT_DISABLE);
}

/**
***********************************************************
* @brief USBת����Ӳ����ʼ��
* @param
* @return 
***********************************************************
*/
void Usb2ComDrvInit(void)
{
	Usb2ComGpioInit();
	Usb2ComUartInit(115200);
}

/**
***********************************************************
* @brief printf����Ĭ�ϴ�ӡ�������ʾ�������Ҫ��������ڣ�
		 ��������ʵ��fputc�����������ָ�򴮿ڣ���Ϊ�ض���
* @param
* @return 
***********************************************************
*/
int fputc(int ch, FILE *f)
{
	usart_data_transmit(g_uartHwInfo.uartNo, (uint8_t)ch);
	while (RESET == usart_flag_get(g_uartHwInfo.uartNo, USART_FLAG_TBE));
	return ch;
}
