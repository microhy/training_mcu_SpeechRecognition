/************************************************************
    Copyright (C), 2013, Hnist FS_GCZX.
    
    File name: .h
    Author:         Version:        Date:
    Description: 
    Others: 
    Function List:
    History: 
    1.Date:
      Author:
      Modification:
    2. ...
*************************************************************/
#ifndef __SYSTICK_H
#define __SYSTICK_H

#ifdef __cplusplus
    extern "C" {
#endif 
/**********Includes*********************/
#include "../inc/LPC1768GCZX.h"       
// #include ".h"

        
#define     FAC_US      (FCCLK/1000000)
#define     FAC_MS      (FCCLK/1000)
/**********Macros***********************/
//使能或禁能系统节拍定时器
#define     SysTick_Enable()            SysTick->CTRL |= BIT0
#define     SysTick_Disable()           SysTick->CTRL &=~BIT0
        
//使能或禁能系统节拍中断                
#define     SysTick_IntEnable()         SysTick->CTRL |= BIT1
#define     SysTick_IntDisable()        SysTick->CTRL &=~BIT1
/**********Variables********************/
       
/**********Function Prototypes**********/
void SysTick_Delayus(uint32_t nus);
void SysTick_Delayms(uint32_t nms);
    
#ifdef __cplusplus
}
#endif

#endif
/************************************************************
End of filename
************************************************************/
