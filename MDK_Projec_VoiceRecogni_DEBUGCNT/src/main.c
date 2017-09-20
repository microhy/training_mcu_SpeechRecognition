/************************************************************
    Copyright (C), 2013, Hnist FS_GCZX.
    FileName: project.c
    Author:Hnist FS_GCZX   Version: 15.04   Date: 2015_04_22
    Description: 
    Function List:
    1. main(): ʵ��LED����˸
    History:
    <author>  <time>   <version >   <desc>
    �������Գ���
***********************************************************/

// -----Includes----- //
#include "../inc/LPC1768GCZX.h" // �Զ���ͷ�ļ����μ���ͷ�ļ�ע�� //
#include "../inc/main.h"
#include "../inc/voiceRec.h"
#include "../inc_vc/x1.h"       //x1~x10 ������������ͷ�ļ�
#include "../inc_vc/x2.h"
#include "../inc_vc/x3.h"
#include "../inc_vc/x4.h"
#include "../inc_vc/x5.h"
#include "../inc_vc/x6.h"
#include "../inc_vc/x7.h"
#include "../inc_vc/x8.h"
#include "../inc_vc/x9.h"
#include "../inc_vc/x10.h"

// -----Macros------ //
#define     LED1_OFF            LPC_GPIO2->FIOSET = BIT0   /*LED1--P2.0*/
#define     LED1_ON             LPC_GPIO2->FIOCLR = BIT0   /*�͵�ƽ����*/

// -----Function Prototypes----- //
void Hardware_Startup(void );

char debugCNT=0;
uint32_t  vclength=0;
uint32_t index;
int16_t vcxn[10000];    //ԭʼ�������̶�ʶ���������ȣ�10000��

int main(void)
{
    const signed short int *PointVC;
/**������system-LPC17xx.c�У���Ҫ���ϵͳʱ�ӳ�ʼ���ȹ���****************/
//!!!!!!!!!!!!
//    SystemInit(); //!!!!!!!!!!!!
    Hardware_Startup();
    LED1_OFF;
    PeripInit_UART0();
    printf("UART0 Init OK!\n");
//     A7105_InitRF();
//     A7105_ConfigFreq(ch_2450MHz);

    while(debugCNT<10) 
    {
        debugCNT = debugCNT+1;
        switch(debugCNT)
        {
            case 1:PointVC = x1;break;
            case 2:PointVC = x2;break;
            case 3:PointVC = x3;break;
            case 4:PointVC = x4;break;
            case 5:PointVC = x5;break;
            case 6:PointVC = x6;break;
            case 7:PointVC = x7;break;
            case 8:PointVC = x8;break;
            case 9:PointVC = x9;break;
            case 10:PointVC = x10;break;
            default:break;
        }
        vclength =  10000;
        for(index=0; index<vclength; index++)
        {
            vcxn[index] = PointVC[index];
        }
//         printf("......\n���ڲ���\n");
//         printf("�������\n");
//         printf("����ʶ��......\n");
        printf("%d ",debugCNT);
        LED1_OFF;
        VoiceRec_FBLR(vcxn, vclength);
        LED1_ON;
    }
    printf("......�������\n");
    while(1);
}


/** �ض���UART0���������޸�
  * @brief  Retargets the C library printf function to the UART.
  * @param  None
  * @retval None
  */
int fputc(int ch,FILE *f)
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the UART */
    while((LPC_UART0->LSR&0x40) ==0 ); /*�ȴ�������ϣ�ֻҪbit6=0��ȴ�*/
    LPC_UART0->THR = ch; /*����һ���ַ�����*/
    return ch;
}
/************************************************************
  Function   : Hardware_Startup()
  Description: Ӳ��������ʼ������
  Input      : None
  Output     : None
  Return     : ����Ӳ������,�������Ź���
  Others     :
************************************************************/
void Hardware_Startup(void )
{
    LPC_GPIO2->FIODIR |= BIT0;   //P2.0�������
    Peripherals_PowerControl(PCUART0, ENABLE);
    GPIO0_PinFuncSel(GPIO_Pin_2,GPIOFunc_AF1);          //TXD0
    GPIO0_PinFuncSel(GPIO_Pin_3,GPIOFunc_AF1);          //RXD0
}
/*************************************************
    End of project.c
*************************************************/
