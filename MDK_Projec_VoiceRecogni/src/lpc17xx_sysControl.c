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
#include "../inc/lpc17xx_sysControl.h" 

/**********Macros***********************/

/**********Variables********************/

/**********Function Prototypes**********/

/**********MAIN Routine*****************/


/************************************************************
  Function   : ()
  Description: 
  Calls      : 
  Called By  : 
  Input      : None
  Output     : None
  Return     : None
  Others     : 
************************************************************/
void EXTINT_Configuration(uint32_t extX, uint32_t extMode, uint32_t extPolar)
{
    uint32_t tmpreg;
    //引脚功能设置
    tmpreg = PINCON->PINSEL4;
    switch (extX)
    {
        case EINT0: tmpreg &=~BIT21; tmpreg|=BIT20;
            break;
        case EINT1: tmpreg &=~BIT23; tmpreg|=BIT22;
            break;
        case EINT2: tmpreg &=~BIT25; tmpreg|=BIT24;
            break;
        case EINT3: tmpreg &=~BIT27; tmpreg|=BIT26;
            break;    
        default: 
            while(1);  //error
    }
    PINCON->PINSEL4 = tmpreg;
    //触发方式设置
    if(extMode != EINTMODE_EDGE)
    {
        SC->EXTMODE &=~ extX;   //电平方式
    }
    else
    {
        SC->EXTMODE |= extX;    //边沿方式
    }
    //极性设置
    if( extPolar != TRUE)   
    {
        SC->EXTPOLAR &=~ extX;  //低电平或下降沿触发
    }
    else
    {
        SC->EXTPOLAR |= extX;   //高电平或上升沿触发
    }
}


/************************************************************
End of filename
************************************************************/
