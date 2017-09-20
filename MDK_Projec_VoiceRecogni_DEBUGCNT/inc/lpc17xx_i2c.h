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
#ifndef __LPC17XX_I2C_H
#define __LPC17XX_I2C_H

#ifdef __cplusplus
    extern "C" {
#endif 
/**********Includes*********************/
#include "../inc/LPC1768GCZX.h"       
// #include ".h"
        
/**********Macros***********************/
typedef enum
{
    I2CMode_Master = 0,
    I2CMode_Slave
}I2CMode_TypeDef;
/**********Variables********************/
       
/**********Function Prototypes**********/
void I2C0_PortConfig(void );
void I2C_Init(I2C_TypeDef* I2Cx, I2CMode_TypeDef modex);

#ifdef __cplusplus
}
#endif

#endif
/************************************************************
End of filename
************************************************************/
