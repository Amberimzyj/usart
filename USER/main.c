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
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC中断分组2
    usart_init(115200);  //串口初始化波特率
    LED_Init();     //LED端口初始化
    //KEY_Init();     //初始化与按键连接的硬件端口
    while (1)
    {
        if (USART_RX_STA & 0x8000)
        {
            len = USART_RX_STA & 0x3fff; // 得到此次接收的数据长度
            printf("\r\n您发送的消息为：\r\n\r\n");
            for (t = 0; t < len; t++)
            {
                USART_SendData(USART1, USART1_RX_BUF[t]); //向串口1发送数据
                while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET); //等待发送结束
            }
            printf("\r\n\r\n");//插入换行
            USART_RX_STA = 0;
        }
        else
        {
            times++;
            if (times % 5000 == 0)
            {
                printf("\r\nSTM32F103C8T6 串口实验\r\n");
                printf("Amberimzyj\r\n\r\n");
            }
            if (times % 200 == 0)  printf("请输入数据，以回车键结束\n");
            if (times % 30 == 0)  LED0 = !LED0; //闪烁LED,表示系统正在运行
            delay_ms(10);
        }
    }
}

