#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include "led.h"
#include "delay.h"


int main(void)
{
    u16 t;
    u16 len;
    u16 times = 0;
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����NVIC�жϷ���2
    usart_init(115200);  //���ڳ�ʼ��������
    LED_Init();     //LED�˿ڳ�ʼ��
    //KEY_Init();     //��ʼ���밴�����ӵ�Ӳ���˿�
    while (1)
    {
        if (USART_RX_STA & 0x8000)
        {
            len = USART_RX_STA & 0x3fff; // �õ��˴ν��յ����ݳ���
            printf("\r\n�����͵���ϢΪ��\r\n\r\n");
            for (t = 0; t < len; t++)
            {
                USART_SendData(USART1, USART1_RX_BUF[t]); //�򴮿�1��������
                while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET); //�ȴ����ͽ���
            }
            printf("\r\n\r\n");//���뻻��
            USART_RX_STA = 0;
        }
        else
        {
            times++;
            if (times % 5000 == 0)
            {
                printf("\r\nSTM32F103C8T6 ����ʵ��\r\n");
                printf("Amberimzyj\r\n\r\n");
            }
            if (times % 200 == 0)  printf("���������ݣ��Իس�������\n");
            if (times % 30 == 0)  LED0 = !LED0; //��˸LED,��ʾϵͳ��������
            delay_ms(10);
        }
    }
}
