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
#ifndef __LPC17XX_SYSCONTROL_H
#define __LPC17XX_SYSCONTROL_H

#ifdef __cplusplus
    extern "C" {
#endif 
/**********Includes*********************/
#include "../inc/LPC1768GCZX.h"       
// #include ".h"
        
/**********Macros***********************/
//外部中断相关定义
#define     EINT0   0x00000001
#define     EINT1   0x00000002
#define     EINT2   0x00000004
#define     EINT3   0x00000008

#define     EINTMODE_LEVEL      0
#define     EINTMODE_EDGE       1
        
#define     EINTPOLAR_LOW          0
#define     EINTPOLAR_HIGH         1
#define     EINTPOLAR_FALLING      0
#define     EINTPOLAR_RISING       1

#define     CLEAR_EINT0()     SC->EXTINT |= EINT0
#define     CLEAR_EINT1()     SC->EXTINT |= EINT1
#define     CLEAR_EINT2()     SC->EXTINT |= EINT2
#define     CLEAR_EINT3()     SC->EXTINT |= EINT3

//系统控制和状态相关定义
#define     READ_OSCSTAT()    (SC->SCS&BIT6)
/**********Variables********************/
       
/**********Function Prototypes**********/
void EXTINT_Configuration(uint32_t extX, uint32_t extMode, uint32_t extPolar);
    
#ifdef __cplusplus
}
#endif

#endif
/************************************************************
End of filename
************************************************************/
