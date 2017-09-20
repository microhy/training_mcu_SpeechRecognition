/************************************************************
    Copyright (C), 2013, Hnist FS_GCZX.
    
    FileName: .c
    Author:     Version :       Date:
    Description:
    Function List: 
    1.
    History:
    <author>    <time>      <version >      <desc>
    huyong      2014-2-27   
************************************************************/

/**********Includes*********************/
#include "../inc/sysTick.h" 

/**********Macros***********************/


/**********Variables********************/
__IO ITStatus   SysTick_Flag = RESET;

/**********Function Prototypes**********/

void SysTick_Delayus(uint32_t nus)
{
    SysTick->LOAD = FAC_US*nus-1;
    SysTick->VAL = (0x00);
    // 打开计数器开始倒数，关中断，选择CPU时钟
    SysTick->CTRL = (BIT0|BIT2);       
    while(! (SysTick->CTRL&BIT16));
    SysTick->CTRL &=~BIT0;
    SysTick_Flag = RESET;
}
    
void SysTick_Delayms(uint32_t nms)
{
    SysTick->LOAD = FAC_MS*nms-1;
    SysTick->VAL = (0x00);
    // 打开计数器开始倒数，关中断，选择CPU时钟
    SysTick->CTRL = (BIT0|BIT2);       
    while(! (SysTick->CTRL&BIT16));
    SysTick->CTRL &=~BIT0;
    SysTick_Flag = RESET;
}

void SysTick_Handler (void)
{
    SysTick->CTRL &=~ BIT16;
    SysTick_Flag = SET;
}
/************************************************************
End of filename
************************************************************/
