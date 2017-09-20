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
#ifndef __MYMFCC_H
#define __MYMFCC_H

#ifdef __cplusplus
    extern "C" {
#endif 
/**********Includes*********************/
      
#include "../inc/LPC1768GCZX.h"
        
/**********Macros***********************/
#define     MCNUM      30
/**********Variables********************/
typedef struct{
    uint8_t row;
    uint8_t column;
    float stoData;
}SpaStoOrg_DataDef;



/**********Function Prototypes**********/
extern const SpaStoOrg_DataDef MELCOEF[MCNUM];
    
#ifdef __cplusplus
}
#endif

#endif
/************************************************************
End of filename
************************************************************/
