/************************************************************
    Copyright (C), 2013, Hnist FS_GCZX.
    
    FileName: .c
    Author:     Version :       Date:
    Description:
    Function List: 
    1.
    History:
    <author>    <time>      <version >      <desc>
    David       96/10/12        1.0         build this moudle
************************************************************/

/**********Includes*********************/
#include "../inc/pwm.h" 

/**********Macros***********************/
#define     PWM_Frequency       4096
/**********Variables********************/

/**********Function Prototypes**********/

void PWM_InitConfig(void )
{
    LPC_SC->PCONP |= PCPWM1;    //��PWM1�ĵ�Դ���ƣ�Ĭ���Ǵ򿪵ģ�
    PeripheralsClock_Divider(PCLK_PWM1, CCLK_Div4); //Ĭ����/4
    
    LPC_PINCON->PINMODE4 |= BIT0|BIT2|BIT4|BIT6|BIT8|BIT10; //�м�ģʽ 
    LPC_PINCON->PINSEL4 &= 0XFFFFF000;
    LPC_PINCON->PINSEL4 |= BIT0|BIT2|BIT4|BIT6|BIT8|BIT10;
    
    LPC_PWM1->TCR = TCR_CntRst; //��λ��ʱ����������Ԥ��Ƶ��  
    LPC_PWM1->TC = 0;           //���㶨ʱ��������
    
    LPC_PWM1->PR = 10;             //����Ԥ��Ƶ
    LPC_PWM1->MR0 = PWM_Frequency;//����PWM��Ƶ��
    LPC_PWM1->MCR |= BIT1;        //PWMTC����PWMMR0ƥ��ʱ��λ�����㣩
    LPC_PWM1->LER |= BIT0;        //����MR0��ֵ
}

/************************************************************
  Function   : PWM_ChannelConfig()
  Description: 
  Input      : duty ռ�ձ�0~255��ʾ0%~100%��
  Output     : None
  Return     : None
  Others     : 
************************************************************/
void PWM_ChannelConfig(uint32_t pwmchanx, uint8_t duty)
{
    uint32_t tmp;
    if( duty!=0||duty!=255)
    {
        tmp = PWM_Frequency*duty>>8;    //����8λ������256����ʾռ�ձȣ�duty/256��
    }
    else
    {
        tmp = PWM_Frequency;
    }
    switch (pwmchanx)
    {
        case PWMChan1: LPC_PWM1->MR1 = tmp; break;
        case PWMChan2: LPC_PWM1->MR2 = tmp; break;
        case PWMChan3: LPC_PWM1->MR3 = tmp; break;
        case PWMChan4: LPC_PWM1->MR4 = tmp; break;
        case PWMChan5: LPC_PWM1->MR5 = tmp; break;
        case PWMChan6: LPC_PWM1->MR6 = tmp; break;
        default: while(1);
    }
}

void PWM_OutputCmd(uint32_t pwmchanx, FunctionalState NewState)
{
    if( NewState!= DISABLE)
    {
        LPC_PWM1->PCR |= (pwmchanx);
    }
    else
    {
        LPC_PWM1->PCR &=~(pwmchanx);
    }
}
/************************************************************
  Function   : PWM_LogicEnable()
  Description: ����ʹ�ܣ���MRx����������
  Input      : 
    @param  pwmchanx ͨ����
        @arg PWMChan0~6���������
  Output     : None
  Return     : None
  Others     : 
************************************************************/
void PWM_LogicEnable(uint32_t pwmchanx)
{
     LPC_PWM1->LER |=((pwmchanx)>>8);
}

/************************************************************
  Function   : PWM_CntTimerControl()
  Description: PWM�������ƼĴ�������
  Input      : cntInSel ����ͨ��ѡ�� PCAP1_0 �� PCAP1_1
               cntMode ����ģʽ 
    Mode_Timer ��ʱ��ģʽ
    Mode_Rising �����ؼ���
    Mode_Falling �½����ؼ���
    Mode_Both ˫���ؼ���
  Output     : None
  Return     : None
  Others     : 
 �����ļĴ���: LPC_PWM1->CTCR
************************************************************/
void PWM_CntTimerControl(uint32_t cntInSel, PWMMode_Typedef cntMode)
{
    uint32_t tmpreg ;
    tmpreg = LPC_PWM1->CTCR;
    
    tmpreg &= 0xFFFFFFF0;   //clear bit0,1,2,3
    
    tmpreg |= cntMode;
    if (cntInSel != PCAP1_0)
    {
        tmpreg |= PCAP1_1;
    }
    LPC_PWM1->CTCR = tmpreg;
}

/************************************************************
  Function   : PWM_CaputreControl()
  Description: �����������ͨ���Ͳ���ģʽ
  Input      : capInSel ����ͨ��ѡ�� PCAP1_0 �� PCAP1_1
               capMode ����ģʽ 
    Mode_Rising �����ز���
    Mode_Falling �½��ز���
    Mode_Both ˫���ز���
  Output     : None
  Return     : None
  Others     : �����ļĴ���: LPC_PWM1->CCR
************************************************************/
void PWM_CaputreControl(uint32_t capInSel, PWMMode_Typedef capMode)
{
    uint32_t tmpreg ;
    tmpreg = LPC_PWM1->CCR;
    
    if(capInSel==PCAP1_0)
    {
        tmpreg &=0xFFFFFFFC;    //clear bit0,1
        tmpreg |= capMode;
    }
    else if(capInSel==PCAP1_1)
    {
        tmpreg &=0xFFFFFFE7;    //clear bit3,4
        tmpreg |= ((uint32_t)capMode<<3);
    }
    else
        while(1); //error
    LPC_PWM1->CCR = tmpreg;
}

/************************************************************
  Function   : PWM_CaptureIntCmd()
  Description: �����¼��ж�����
  Input      : capInSel ����ͨ��ѡ�� PCAP1_0 �� PCAP1_1
               NewState ʹ���жϻ�����ж�
  Output     : None
  Return     : None
  Others     : �����ļĴ���: LPC_PWM1->CCR
************************************************************/
void PWM_CaptureIntCmd(uint32_t capInSel, FunctionalState NewState)
{
    if( NewState!= DISABLE)
    {
        if( capInSel == PCAP1_0)
        {
            LPC_PWM1->CCR |= BIT2;
        }
        else if(capInSel == PCAP1_1)
        {
            LPC_PWM1->CCR |= BIT5;
        }
        else
            while(1);//error
    }
    else
    {
        if( capInSel == PCAP1_0)
        {
            LPC_PWM1->CCR &=~BIT2;
        }
        else if(capInSel == PCAP1_1)
        {
            LPC_PWM1->CCR &=~BIT5;
        }
        else
            while(1);//error
    }
}
/************************************************************
End of filename
************************************************************/
