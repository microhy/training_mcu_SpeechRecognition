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
#include "../inc/lpc17XX_i2c.h" 
#include "../inc/lpc17xx_gpio.h"

/**********Macros***********************/
#define I2C_SLAVEADDRESS   0x55
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
void I2C0_PortConfig(void )
{
    //电源使能
    Peripherals_PowerControl(PCI2C0, ENABLE);
    //时钟分频
    PeripheralsClock_Divider(PCLK_I2C0 ,CCLK_Div2);
    //引脚功能配置
    GPIO0_PinFuncSel(Pin_27, GPIOFunc_AF1); //SDA0
    GPIO0_PinFuncSel(Pin_28, GPIOFunc_AF1); //SCL0
}


void I2C_Init(I2C_TypeDef* I2Cx, I2CMode_TypeDef modex)
{
    I2Cx->I2ADR0 = I2C_SLAVEADDRESS;   //从机地址
    if (modex != I2CMode_Slave)
    {
        I2Cx->I2CONSET = 0x40;  //主机模式
    }
    else
    {
        I2Cx->I2CONSET = 0x44;  //从机模式
    }
}
/************************************************************
End of filename
************************************************************/
