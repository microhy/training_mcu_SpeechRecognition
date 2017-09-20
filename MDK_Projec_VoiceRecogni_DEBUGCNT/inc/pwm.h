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
#ifndef __PWM_H
#define __PWM_H

#ifdef __cplusplus
    extern "C" {
#endif 
/**********Includes*********************/
#include "../inc/LPC1768GCZX.h"
        
/**********Macros***********************/
//PWM Timer Control Register (PWM1TCR 0x4001 8004)
#define     TCR_CntEn      BIT0
#define     TCR_CntRst     BIT1
#define     TCR_PwmEn      BIT3

//PWM Count Control Register (PWM1CTCR - 0x4001 8070)
#define     PCAP1_0     0
#define     PCAP1_1     4
        
typedef enum
{
    Mode_Timer = 0  ,
    Mode_Rising     ,
    Mode_Falling    ,
    Mode_Both
}PWMMode_Typedef;



#define PWMSEL2     BIT2
#define PWMSEL3     BIT3
#define PWMSEL4     BIT4
#define PWMSEL5     BIT5
#define PWMSEL6     BIT6

#define PWMChan0       BIT8
#define PWMChan1       BIT9
#define PWMChan2       BIT10
#define PWMChan3       BIT11
#define PWMChan4       BIT12
#define PWMChan5       BIT13
#define PWMChan6       BIT14 
//以上通道定义在右移8位后即为下列使能位
// #define LER_EN0     BIT0
// #define LER_EN1     BIT1
// #define LER_EN2     BIT2
// #define LER_EN3     BIT3
// #define LER_EN4     BIT4
// #define LER_EN5     BIT5
// #define LER_EN6     BIT6

// #define PWMEN1     BIT9
// #define PWMEN2     BIT10
// #define PWMEN3     BIT11
// #define PWMEN4     BIT12
// #define PWMEN5     BIT13
// #define PWMEN6     BIT14


#define PWM_Start()    LPC_PWM1->TCR = TCR_CntEn|TCR_PwmEn
#define PWM_Stop()     LPC_PWM1->TCR = TCR_CntRst
/**********Variables********************/
       
/**********Function Prototypes**********/
void PWM_InitConfig(void );
void PWM_ChannelConfig(uint32_t pwmchanx, uint8_t duty);
void PWM_OutputCmd(uint32_t pwmchanx, FunctionalState NewState);
void PWM_LogicEnable(uint32_t pwmchanx);

void PWM_CntTimerControl(uint32_t cntInSel, PWMMode_Typedef cntMode);
void PWM_CaputreControl(uint32_t capInSel, PWMMode_Typedef capMode);
void PWM_CaptureIntCmd(uint32_t capInSel, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif
/************************************************************
End of filename
************************************************************/
