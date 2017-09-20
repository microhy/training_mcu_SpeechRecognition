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
  Description: 外设时钟初始化
  Input      : None
  Output     : CPU的时钟CCLK4分频(默认)后作为外设时钟
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
  Description: 将CPU的时钟分频后作为外设的时钟
  Input      : @param  perip: 外设名称
                 @arg PCLK_WDT:
                 @arg PCLK_PCLK_TIMER0:
                 @arg ...详见头文件 PCLK_XXX
                 
               @param  divider: 分频级数
                 @arg CCLK_Div1: CPU的时钟1分频作为外设的时钟
                 @arg CCLK_Div2: CPU的时钟2分频作为外设的时钟
                 @arg CCLK_Div4: CPU的时钟4分频作为外设的时钟
                 @arg CCLK_Div8: CPU的时钟8分频作为外设的时钟
  Output     : 外设的时钟改变
  Return     : None
  Others     : @note  当选择PCLK_CAN1/PCLK1_CAN2/PCLK_ACF为CCLK_8时，
  实际时钟是CCLK/6 （6分频），而且在使用CAN时，这3个的频率要相同
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

    tmpreg = LPC_SC->CLKOUTCFG;         // 读回寄存器中的数据
    tmpreg &= CLKOUT_SEL_Mask;
    tmpreg &= CLKOUT_DIV_Mask;
    
    tmpreg |= clkSource;
    tmpreg |= clkDiv;
    
    LPC_SC->CLKOUTCFG = tmpreg;
}

/************************************************************
  Function   : ClockOutput_Cmd()
  Description: 使能 或 不使能时钟输出
  Input      : @param  NewState: 时钟输出新的状态命令
                 这个参数可以为： ENABLE or DISABLE.
  Output     : 时钟输出 或 不输出
  Return     : None
  Others     : CLKOUTCFG[8] 是CLKOUT_EN位
************************************************************/
void ClockOutput_Cmd(FunctionalState NewState)
{
    if (NewState != DISABLE) // 使能时钟输出
    {
        LPC_SC->CLKOUTCFG |= CLKOUT_EN_Set_Mask;    // 置位CLKOUT_EN位
    }
    else                     // 禁能时钟输出
    {
        LPC_SC->CLKOUTCFG &= CLKOUT_EN_Reset_Mask;  // 复位CLKOUT_EN位                          
    }
}
/************************************************************
  Function   : Peripherals_PowerControl()
  Description: 外设电源控制，即使能、失能控制
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
