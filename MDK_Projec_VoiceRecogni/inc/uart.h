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
#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
    extern "C" {
#endif 
/**********Includes*********************/
#include "../inc/LPC1768GCZX.h"
// #include ".h"

/** 
  * @brief  UART Init Structure definition  
  */
typedef struct
{
    uint32_t UART_BaudRate;
    uint16_t UART_WordLength;
    uint16_t UART_StopBits;
    uint16_t UART_Parity;
    uint16_t UART_Mode;
}UART_InitTypeDef;

#define UART_WordLength_5b                  ((uint16_t)0x0000)
#define UART_WordLength_6b                  ((uint16_t)0x0001)
#define UART_WordLength_7b                  ((uint16_t)0x0002)
#define UART_WordLength_8b                  ((uint16_t)0x0003)

#define UART_StopBits_1                     ((uint16_t)0x0000)
#define UART_StopBits_2                     ((uint16_t)0x0004)
//UART_StopBits_1_5 此情况要在 UART_WordLength_5b时才出现
#define UART_StopBits_1_5                   ((uint16_t)0x0004)

#define UART_Parity_No                      ((uint16_t)0x0000)
#define UART_Parity_Odd                     ((uint16_t)0x0008)
#define UART_Parity_Even                    ((uint16_t)0x0018)
#define UART_Parity_Forced_1                ((uint16_t)0x0028)
#define UART_Parity_Forced_0                ((uint16_t)0x0038)

#define UART_Mode_RX                        ((uint16_t)0x0000)
#define UART_Mode_TX                        ((uint16_t)0x0000)


#define UART_IT_RDA                          ((uint16_t)0x0001)
#define UART_IT_THRE                         ((uint16_t)0x0002)
#define UART_IT_RXLINE                       ((uint16_t)0x0004)
#define UART_IT_ABEO                         ((uint16_t)0x0100)
#define UART_IT_ABTO                         ((uint16_t)0x0200)

// #define UART_IT_RLS
// // #define UART_IT_RDA
// #define UART_IT_CTI
// #define UART_IT_RXLINE_OE
// #define UART_IT_RXLINE_PE
// #define UART_IT_RXLINE_FE
// #define UART_IT_RXLINE_BI

#define FIFO_RX    ((uint16_t)0x0002)
#define FIFO_TX    ((uint16_t)0x0004)

#define TRIG_Byte_1    ((uint16_t)0x0000)
#define TRIG_Byte_4    ((uint16_t)0x0040)
#define TRIG_Byte_8    ((uint16_t)0x0080)
#define TRIG_Byte_14   ((uint16_t)0x00C0)
/**********Variables********************/
       
/**********Function Prototypes**********/
void PeripInit_UART0(void );
void UART_Init(LPC_UART_TypeDef* LPC_UARTx, UART_InitTypeDef* UART_InitStruct);
void UART_TxCmd(LPC_UART_TypeDef* LPC_UARTx, FunctionalState NewState);
void UART_SendData(LPC_UART_TypeDef* LPC_UARTx, uint8_t Data);
uint8_t UART_ReceiveData(LPC_UART_TypeDef* LPC_UARTx);
void UART_FIFOCmd(LPC_UART_TypeDef* LPC_UARTx, FunctionalState NewState);
void UART_FIFOReset(LPC_UART_TypeDef* LPC_UARTx, uint16_t FIFO_x);
void UART_RXTriggerLevel(LPC_UART_TypeDef* LPC_UARTx, uint8_t TRIG_Byte_x);
void UART_ITConfig(LPC_UART_TypeDef* LPC_UARTx, uint16_t UART_IT, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif
/************************************************************
End of filename
************************************************************/
