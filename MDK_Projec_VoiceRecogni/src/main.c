/************************************************************
    Copyright (C), 2013, Hnist FS_GCZX.
    FileName: project.c
    Author:Hnist FS_GCZX   Version: 15.04   Date: 2015_04_22
    Description: 
    Function List:
    
    History:
    <author>  <time>   <version >   <desc>
     ����ǵ�������ʶ�����
***********************************************************/

// -----Includes----- //
#include "../inc/LPC1768GCZX.h" // �Զ���ͷ�ļ����μ���ͷ�ļ�ע�� //
#include "../inc/main.h"
#include "../inc/voiceRec.h"
#include "../inc_vc/x1.h"       //ʶ���������ݵ�ͷ�ļ�

// -----Macros------ //
#define     LED1_OFF            LPC_GPIO2->FIOSET = BIT0   /*LED1--P2.0*/
#define     LED1_ON             LPC_GPIO2->FIOCLR = BIT0   /*�͵�ƽ����*/

// -----Function Prototypes----- //
void Hardware_Startup(void );

uint32_t  vclength=0;
uint32_t index;
int16_t vcxn[12000];    //ԭʼ�������̶�ʶ���������ȣ�12000��

int main(void)
{
//     int (*d)[10];
//     i=10;
//     j=3;
//     d = (int (*)[10]) malloc(i*10*sizeof(int));
//     free(d);

/**������system-LPC17xx.c�У���Ҫ���ϵͳʱ�ӳ�ʼ���ȹ���****************/
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
//         printf("......\n���ڲ���\n");
//         printf("�������\n");
        printf("����ʶ��......\n");
        LED1_OFF;
        VoiceRec_FBLR(vcxn, vclength);
        LED1_ON;
    }
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
