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
    LPC_SC->PCONP |= PCPWM1;    //打开PWM1的电源控制（默认是打开的）
    PeripheralsClock_Divider(PCLK_PWM1, CCLK_Div4); //默认是/4
    
    LPC_PINCON->PINMODE4 |= BIT0|BIT2|BIT4|BIT6|BIT8|BIT10; //中继模式 
    LPC_PINCON->PINSEL4 &= 0XFFFFF000;
    LPC_PINCON->PINSEL4 |= BIT0|BIT2|BIT4|BIT6|BIT8|BIT10;
    
    LPC_PWM1->TCR = TCR_CntRst; //复位定时器计数器和预分频器  
    LPC_PWM1->TC = 0;           //清零定时器计数器
    
    LPC_PWM1->PR = 10;             //设置预分频
    LPC_PWM1->MR0 = PWM_Frequency;//设置PWM的频率
    LPC_PWM1->MCR |= BIT1;        //PWMTC在与PWMMR0匹配时复位（清零）
    LPC_PWM1->LER |= BIT0;        //锁存MR0的值
}

/************************************************************
  Function   : PWM_ChannelConfig()
  Description: 
  Input      : duty 占空比0~255表示0%~100%。
  Output     : None
  Return     : None
  Others     : 
************************************************************/
void PWM_ChannelConfig(uint32_t pwmchanx, uint8_t duty)
{
    uint32_t tmp;
    if( duty!=0||duty!=255)
    {
        tmp = PWM_Frequency*duty>>8;    //右移8位即除以256，表示占空比（duty/256）
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
  Description: 锁存使能，将MRx的数据锁存
  Input      : 
    @param  pwmchanx 通道名
        @arg PWMChan0~6的任意组合
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
  Description: PWM计数控制寄存器配置
  Input      : cntInSel 计数通道选择 PCAP1_0 或 PCAP1_1
               cntMode 计数模式 
    Mode_Timer 定时器模式
    Mode_Rising 上升沿计数
    Mode_Falling 下降沿沿计数
    Mode_Both 双边沿计数
  Output     : None
  Return     : None
  Others     : 
 操作的寄存器: LPC_PWM1->CTCR
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
  Description: 捕获控制输入通道和捕获模式
  Input      : capInSel 捕获通道选择 PCAP1_0 或 PCAP1_1
               capMode 捕获模式 
    Mode_Rising 上升沿捕获
    Mode_Falling 下降沿捕获
    Mode_Both 双边沿捕获
  Output     : None
  Return     : None
  Others     : 操作的寄存器: LPC_PWM1->CCR
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
  Description: 捕获事件中断命令
  Input      : capInSel 捕获通道选择 PCAP1_0 或 PCAP1_1
               NewState 使能中断或禁能中断
  Output     : None
  Return     : None
  Others     : 操作的寄存器: LPC_PWM1->CCR
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
