/************************************************************
    Copyright (C), 2013, Hnist FS_GCZX.
    FileName: project.c
    Author:Hnist FS_GCZX   Version: 15.04   Date: 2015_04_22
    Description: 
    Function List:
    
    History:
    <author>  <time>   <version >   <desc>
     这个是单个语音识别程序
***********************************************************/

// -----Includes----- //
#include "../inc/LPC1768GCZX.h" // 自定义头文件，参见该头文件注释 //
#include "../inc/main.h"
#include "../inc/voiceRec.h"
#include "../inc_vc/x1.h"       //识别语音数据的头文件

// -----Macros------ //
#define     LED1_OFF            LPC_GPIO2->FIOSET = BIT0   /*LED1--P2.0*/
#define     LED1_ON             LPC_GPIO2->FIOCLR = BIT0   /*低电平点亮*/

// -----Function Prototypes----- //
void Hardware_Startup(void );

uint32_t  vclength=0;
uint32_t index;
int16_t vcxn[12000];    //原始语音，固定识别语音长度，12000点

int main(void)
{
//     int (*d)[10];
//     i=10;
//     j=3;
//     d = (int (*)[10]) malloc(i*10*sizeof(int));
//     free(d);

/**定义于system-LPC17xx.c中，主要完成系统时钟初始化等功能****************/
//!!!!!!!!!!!!
//    SystemInit(); //!!!!!!!!!!!!
    Hardware_Startup();
    LED1_OFF;
    PeripInit_UART0();
    printf("UART0 Init OK!\n");
//     A7105_InitRF();
//     A7105_ConfigFreq(ch_2450MHz);

    while(1) {
        vclength =  sizeof(x1)/sizeof(x1[0]);
        for(index=0; index<vclength; index++)
        {
            vcxn[index] = x1[index];
        }
//         printf("......\n正在采样\n");
//         printf("采样完成\n");
        printf("正在识别......\n");
        LED1_OFF;
        VoiceRec_FBLR(vcxn, vclength);
        LED1_ON;
    }
}


/** 重定向到UART0，可自行修改
  * @brief  Retargets the C library printf function to the UART.
  * @param  None
  * @retval None
  */
int fputc(int ch,FILE *f)
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the UART */
    while((LPC_UART0->LSR&0x40) ==0 ); /*等待发送完毕，只要bit6=0则等待*/
    LPC_UART0->THR = ch; /*发送一个字符函数*/
    return ch;
}
/************************************************************
  Function   : Hardware_Startup()
  Description: 硬件启动初始化设置
  Input      : None
  Output     : None
  Return     : 启动硬件外设,配置引脚功能
  Others     :
************************************************************/
void Hardware_Startup(void )
{
    LPC_GPIO2->FIODIR |= BIT0;   //P2.0输出方向
    Peripherals_PowerControl(PCUART0, ENABLE);
    GPIO0_PinFuncSel(GPIO_Pin_2,GPIOFunc_AF1);          //TXD0
    GPIO0_PinFuncSel(GPIO_Pin_3,GPIOFunc_AF1);          //RXD0
}
/*************************************************
    End of project.c
*************************************************/
