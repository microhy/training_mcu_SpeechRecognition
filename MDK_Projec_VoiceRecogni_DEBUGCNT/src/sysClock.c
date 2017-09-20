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
#include "../inc/sysClock.h" 

/**********Macros***********************/
#define     PCLK_Mask                     ((uint32_t)0x00000003)

#define     CLKOUT_SEL_Mask               ((uint32_t)0xFFFFFFF0)
#define     CLKOUT_DIV_Mask               ((uint32_t)0xFFFFFF0F)

#define     CLKOUT_EN_Reset_Mask          ((uint32_t)0xFFFFFEFF)
#define     CLKOUT_EN_Set_Mask            ((uint32_t)0x00000100)

/**********Variables********************/

/**********Function Prototypes**********/




/**********Function Routine*****************/
/************************************************************
  Function   : PeripheralsClock_DeInit()
  Description: ����ʱ�ӳ�ʼ��
  Input      : None
  Output     : CPU��ʱ��CCLK4��Ƶ(Ĭ��)����Ϊ����ʱ��
  Return     : None
  Others     : Default Init
************************************************************/
void PeripheralsClock_DeInit(void )
{
    LPC_SC->PCLKSEL0 = 0x00000000;
    LPC_SC->PCLKSEL1 = 0x00000000;
}

/************************************************************
  Function   : PeripheralsClock_Divider()
  Description: ��CPU��ʱ�ӷ�Ƶ����Ϊ�����ʱ��
  Input      : @param  perip: ��������
                 @arg PCLK_WDT:
                 @arg PCLK_PCLK_TIMER0:
                 @arg ...���ͷ�ļ� PCLK_XXX
                 
               @param  divider: ��Ƶ����
                 @arg CCLK_Div1: CPU��ʱ��1��Ƶ��Ϊ�����ʱ��
                 @arg CCLK_Div2: CPU��ʱ��2��Ƶ��Ϊ�����ʱ��
                 @arg CCLK_Div4: CPU��ʱ��4��Ƶ��Ϊ�����ʱ��
                 @arg CCLK_Div8: CPU��ʱ��8��Ƶ��Ϊ�����ʱ��
  Output     : �����ʱ�Ӹı�
  Return     : None
  Others     : @note  ��ѡ��PCLK_CAN1/PCLK1_CAN2/PCLK_ACFΪCCLK_8ʱ��
  ʵ��ʱ����CCLK/6 ��6��Ƶ����������ʹ��CANʱ����3����Ƶ��Ҫ��ͬ
************************************************************/
void PeripheralsClock_Divider(uint8_t perip, uint8_t divider)
{
    uint32_t tmpreg = 0;
    uint8_t tmpperip;
    tmpperip = perip;
    
    if (tmpperip <= 30)
    {
        tmpreg = LPC_SC->PCLKSEL0;
        tmpreg &=~ (PCLK_Mask << tmpperip);
        tmpreg |= (divider << tmpperip);
        LPC_SC->PCLKSEL0 = tmpreg;
    }
    else
    {
        tmpreg = LPC_SC->PCLKSEL1;
        tmpreg &=~ (PCLK_Mask << tmpperip);
        tmpperip = tmpperip - 32;
        tmpreg |= (divider << tmpperip);
        LPC_SC->PCLKSEL1 = tmpreg;
    }
}

/************************************************************
  Function   : ClockOutput_Config()
  Description: 
  Calls      : 
  Called By  : 
  Input      : None
  Output     : None
  Return     : None
  Others     : 
************************************************************/
void ClockOutput_Config(uint8_t clkSource, uint8_t clkDiv)
{
    uint32_t tmpreg = 0;

    tmpreg = LPC_SC->CLKOUTCFG;         // ���ؼĴ����е�����
    tmpreg &= CLKOUT_SEL_Mask;
    tmpreg &= CLKOUT_DIV_Mask;
    
    tmpreg |= clkSource;
    tmpreg |= clkDiv;
    
    LPC_SC->CLKOUTCFG = tmpreg;
}

/************************************************************
  Function   : ClockOutput_Cmd()
  Description: ʹ�� �� ��ʹ��ʱ�����
  Input      : @param  NewState: ʱ������µ�״̬����
                 �����������Ϊ�� ENABLE or DISABLE.
  Output     : ʱ����� �� �����
  Return     : None
  Others     : CLKOUTCFG[8] ��CLKOUT_ENλ
************************************************************/
void ClockOutput_Cmd(FunctionalState NewState)
{
    if (NewState != DISABLE) // ʹ��ʱ�����
    {
        LPC_SC->CLKOUTCFG |= CLKOUT_EN_Set_Mask;    // ��λCLKOUT_ENλ
    }
    else                     // ����ʱ�����
    {
        LPC_SC->CLKOUTCFG &= CLKOUT_EN_Reset_Mask;  // ��λCLKOUT_ENλ                          
    }
}
/************************************************************
  Function   : Peripherals_PowerControl()
  Description: �����Դ���ƣ���ʹ�ܡ�ʧ�ܿ���
  Input      : @param pcPerip
                 PCTIM0 ~ PCUSB
               @param NewState
  Output     : None
  Return     : None
  Others     : Peripherals_PowerControl(PCADC, ENABLE)
************************************************************/    
void Peripherals_PowerControl(uint32_t pcPerip, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        LPC_SC->PCONP |= (pcPerip);
    }
    else
    {
        LPC_SC->PCONP &=~(pcPerip);
    }
}

/************************************************************
End of filename
************************************************************/
