/************************************************************
    Copyright (C), 2013, Hnist FS_GCZX.
    
    File name: .h
    Author:         Version:        Date:
    Description: 
    Others: 
    Function List:
    History: 
    1.Date: huyong      2014-03-12
      Author:
      Modification:
    2. ...
*************************************************************/
#ifndef __LPC17XX_GPIO_H
#define __LPC17XX_GPIO_H

#ifdef __cplusplus
    extern "C" {
#endif 
/**********Includes*********************/
#include "../inc/LPC1768GCZX.h"
// #include ".h"

typedef enum
{
    GPIOFunc_PORT = 0,
    GPIOFunc_AF1,
    GPIOFunc_AF2,
    GPIOFunc_AF3
}GPIOFunc_TypeDef;

typedef enum
{
    GPIOMode_IPU = 0X00, //内部上拉电阻
    GPIOMode_REP,        //中继模式
    GPIOMode_NUND,       //既不上拉也不下拉
    GPIOMode_IPD         //内部下拉电阻
}GPIOMode_TypeDef;

/** 
  * @brief  GPIO_Input and GPIO_Output enumeration  
  */
typedef enum
{
    GPIO_Input = 0,
    GPIO_Output
}GPIODIR_TypeDef;

/** 
  * @brief  Bit_SET and Bit_RESET enumeration  
  */

typedef enum
{   
    Bit_RESET = 0,
    Bit_SET
}BitAction;

typedef enum
{
    GPIOIntEdge_Rising = 0,
    GPIOIntEdge_Falling,
    GPIOIntEdge_Both
}GPIOIntEdge_Typedef;

/**********Macros***********************/
#define GPIO_Pin_0                 ((uint32_t)0x00000001)  /*!< Pin 0 selected */
#define GPIO_Pin_1                 ((uint32_t)0x00000002)  /*!< Pin 1 selected */
#define GPIO_Pin_2                 ((uint32_t)0x00000004)  /*!< Pin 2 selected */
#define GPIO_Pin_3                 ((uint32_t)0x00000008)  /*!< Pin 3 selected */
#define GPIO_Pin_4                 ((uint32_t)0x00000010)  /*!< Pin 4 selected */
#define GPIO_Pin_5                 ((uint32_t)0x00000020)  /*!< Pin 5 selected */
#define GPIO_Pin_6                 ((uint32_t)0x00000040)  /*!< Pin 6 selected */
#define GPIO_Pin_7                 ((uint32_t)0x00000080)  /*!< Pin 7 selected */
#define GPIO_Pin_8                 ((uint32_t)0x00000100)  /*!< Pin 8 selected */
#define GPIO_Pin_9                 ((uint32_t)0x00000200)  /*!< Pin 9 selected */
#define GPIO_Pin_10                ((uint32_t)0x00000400)  /*!< Pin 10 selected */
#define GPIO_Pin_11                ((uint32_t)0x00000800)  /*!< Pin 11 selected */
#define GPIO_Pin_12                ((uint32_t)0x00001000)  /*!< Pin 12 selected */
#define GPIO_Pin_13                ((uint32_t)0x00002000)  /*!< Pin 13 selected */
#define GPIO_Pin_14                ((uint32_t)0x00004000)  /*!< Pin 14 selected */
#define GPIO_Pin_15                ((uint32_t)0x00008000)  /*!< Pin 15 selected */
#define GPIO_Pin_16                ((uint32_t)0x00010000)  /*!< Pin 16 selected */
#define GPIO_Pin_17                ((uint32_t)0x00020000)  /*!< Pin 17 selected */
#define GPIO_Pin_18                ((uint32_t)0x00040000)  /*!< Pin 18 selected */
#define GPIO_Pin_19                ((uint32_t)0x00080000)  /*!< Pin 19 selected */
#define GPIO_Pin_20                ((uint32_t)0x00100000)  /*!< Pin 20 selected */
#define GPIO_Pin_21                ((uint32_t)0x00200000)  /*!< Pin 21 selected */
#define GPIO_Pin_22                ((uint32_t)0x00400000)  /*!< Pin 22 selected */
#define GPIO_Pin_23                ((uint32_t)0x00800000)  /*!< Pin 23 selected */
#define GPIO_Pin_24                ((uint32_t)0x01000000)  /*!< Pin 24 selected */
#define GPIO_Pin_25                ((uint32_t)0x02000000)  /*!< Pin 25 selected */
#define GPIO_Pin_26                ((uint32_t)0x04000000)  /*!< Pin 26 selected */
#define GPIO_Pin_27                ((uint32_t)0x08000000)  /*!< Pin 27 selected */
#define GPIO_Pin_28                ((uint32_t)0x10000000)  /*!< Pin 28 selected */
#define GPIO_Pin_29                ((uint32_t)0x20000000)  /*!< Pin 29 selected */
#define GPIO_Pin_30                ((uint32_t)0x40000000)  /*!< Pin 30 selected */
#define GPIO_Pin_31                ((uint32_t)0x80000000)  /*!< Pin 31 selected */
#define GPIO_Pin_All               ((uint32_t)0xFFFFFFFF)  /*!< All pins selected */

/**********Variables********************/


/**********Function Prototypes**********/
void GPIO0_PinFuncSel(uint32_t GPIO_Pin_x, GPIOFunc_TypeDef GPIOFunc);
void GPIO1_PinFuncSel(uint32_t GPIO_Pin_x, GPIOFunc_TypeDef GPIOFunc);
void GPIO2_PinFuncSel(uint32_t GPIO_Pin_x, GPIOFunc_TypeDef GPIOFunc);
void GPIO3_PinFuncSel(uint32_t GPIO_Pin_x, GPIOFunc_TypeDef GPIOFunc);
void GPIO4_PinFuncSel(uint32_t GPIO_Pin_x, GPIOFunc_TypeDef GPIOFunc);
void GPIO_OpenDrainCmd(LPC_GPIO_TypeDef* LPC_GPIOx, uint32_t GPIO_Pin_x, FunctionalState NewState);
void GPIO_DirectionConfig(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x, GPIODIR_TypeDef dir);
void GPIO_SetBits(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x);
void GPIO_ResetBits(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x);
uint8_t GPIO_ReadDataBit(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x);
uint32_t GPIO_ReadData(LPC_GPIO_TypeDef* LPC_GPIOx);
void GPIO_FIOxMaskCmd(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x, FunctionalState NewState);
void GPIO_INTConfig(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x, GPIOIntEdge_Typedef intEdge, FunctionalState NewState);
ITStatus GPIO_INTGetITStatus(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x, GPIOIntEdge_Typedef intEdge);
void GPIO_INTClear(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x);

#ifdef __cplusplus
}
#endif

#endif
/************************************************************
End of filename
************************************************************/
