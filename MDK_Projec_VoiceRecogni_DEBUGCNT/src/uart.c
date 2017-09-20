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
#include "../inc/uart.h"

/**********Macros***********************/
/* */
#define     LCR_BC_Set              ((uint16_t)0x0040)    /*!< Break Control Enable Mask*/
#define     LCR_BC_Reset            ((uint16_t)0xFFBF)    /*!< Break Control Disable Mask*/
/* */       
#define     LCR_DALB_Set            ((uint16_t)0x0080)    /*!< Divisor Latch Access Bit Enable Mask*/
#define     LCR_DALB_Reset          ((uint16_t)0xFF7F)    /*!< Divisor Latch Access Bit Disable Mask */

#define     TER_TXEN_Set            ((uint16_t)0x0080)    /*!< UARTn Transmit Enable Mask  */
#define     TER_TXEN_Reset          ((uint16_t)0xFF7F)    /*!< UARTn Transmit Disable Mask */

#define     LSR_RDR_Set             ((uint16_t)0x0001)

#define     LSR_THRE_Set            ((uint16_t)0x0040)

#define     FCR_FIFOEN_Set          ((uint16_t)0x0001)    /*!< FIFO使能 */
#define     FCR_FIFOEN_Reset        ((uint16_t)0xFFFE)    /*!< FIFO禁能 */

#define     FCR_TRIG_Byte_Mask      ((uint16_t)0xFF3F) 
/**********Variables********************/

/**********Function Prototypes**********/
// #define     USER_INTERRUPT_TX       0
// #define     USER_INTERRUPT_RX       0


void PeripInit_UART0(void )
{
    UART_InitTypeDef UART_InitStruct;
    UART_InitStruct.UART_BaudRate = 9600;
    UART_InitStruct.UART_WordLength = UART_WordLength_8b;
    UART_InitStruct.UART_StopBits = UART_StopBits_1;
    UART_InitStruct.UART_Parity = UART_Parity_No;
    UART_InitStruct.UART_Mode = UART_Mode_TX;
    UART_Init(LPC_UART0, &UART_InitStruct);
    UART_TxCmd(LPC_UART0, ENABLE);
}

/************************************************************
  Function   : UART_Init()
  Description: 
  Input      : UART0,2,3
  Output     : None
  Return     : None
  Others     : 
    UART_InitTypeDef UART_InitStruct;
    UART_InitStruct.UART_BaudRate = 115200;
    UART_InitStruct.UART_WordLength = UART_WordLength_8b;
    UART_InitStruct.UART_StopBits = UART_StopBits_1;
    UART_InitStruct.UART_Parity = UART_Parity_Odd;
    UART_InitStruct.UART_Mode = UART_Mode_TX;
    UART_Init(LPC_UART0, &UART_InitStruct);
************************************************************/
void UART_Init(LPC_UART_TypeDef* LPC_UARTx, UART_InitTypeDef* UART_InitStruct)
{
    uint32_t tmpreg = 0;
    uint16_t Fdiv = 0;
    LPC_UARTx->LCR |= LCR_DALB_Set; //DLAB=1使能访问除数锁存
    Fdiv = (FPCLK>>4)/(UART_InitStruct->UART_BaudRate);
    LPC_UARTx->DLM = Fdiv>>8;       //取高8位数据
    LPC_UARTx->DLL = Fdiv&0x00FF;   //取低8位数据
    tmpreg = UART_InitStruct->UART_WordLength|UART_InitStruct->UART_StopBits|UART_InitStruct->UART_Parity;
    LPC_UARTx->LCR = tmpreg;
}

void UART_TxCmd(LPC_UART_TypeDef* LPC_UARTx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        LPC_UARTx->TER |= TER_TXEN_Set;
    }
    else
    {
        LPC_UARTx->TER &= TER_TXEN_Reset;
    }
}

void UART_SendData(LPC_UART_TypeDef* LPC_UARTx, uint8_t Data)
{
    LPC_UARTx->THR = Data;
    #ifndef USER_INTERRUPT_TX
        while((LPC_UARTx->LSR&LSR_THRE_Set) ==0 );
    #endif
}

uint8_t UART_ReceiveData(LPC_UART_TypeDef* LPC_UARTx)
{   
    #ifndef USER_INTERRUPT_RX
    while( (LPC_UARTx->LSR&LSR_RDR_Set) ==0 );
    #endif
    return ((uint8_t)(LPC_UARTx->RBR&0xFF));
}

void UART_FIFOCmd(LPC_UART_TypeDef* LPC_UARTx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        LPC_UARTx->FCR |= (FCR_FIFOEN_Set);
    }
    else
    {
        LPC_UARTx->FCR &= (FCR_FIFOEN_Reset);
    }
}
/************************************************************
  Function   : UART_FIFOReset()
  Description: 复位FIFO
  Input      : LPC_UART0,2,3
               FIFO_RX or FIFO_TX
  Output     : None
  Return     : None
  Others     : LPC_UARTx->FCR
************************************************************/
void UART_FIFOReset(LPC_UART_TypeDef* LPC_UARTx, uint16_t FIFO_x)
{
    if(FIFO_x == FIFO_RX)
    {
        LPC_UARTx->FCR |= FIFO_RX;
    }
    else if( FIFO_x == FIFO_TX)
    {
        LPC_UARTx->FCR |= FIFO_TX;
    }
    else ;
}

/************************************************************
  Function   : UART_RXTriggerLevel()
  Description: 接收触发点设置
  Input      :  @param  LPC_UART0,2,3
                @param  TRIG_Byte_1
                        TRIG_Byte_4
                        TRIG_Byte_8
                        TRIG_Byte_14
  Output     : None
  Return     : None
  Others     : LPC_UARTx->FCR
************************************************************/
void UART_RXTriggerLevel(LPC_UART_TypeDef* LPC_UARTx, uint8_t TRIG_Byte_x)
{
    uint32_t tmpreg;
    tmpreg = LPC_UARTx->FCR;
    
    tmpreg &= FCR_TRIG_Byte_Mask;   //clear bit7,6
    tmpreg |= TRIG_Byte_x;
    
    LPC_UARTx->FCR = tmpreg;
}

// FlagStatus UART_GetFIFOStatus(LPC_UART_TypeDef* LPC_UARTx, uint16_t FIFOLVL_x)
// {
//     FlagStatus bitstatus = RESET;
//     if(LPC_UARTx-> FIFOLVL_x)
//     {

//     }
//     else
//     {

//     }
//     return(bitstatus);
// }

void UART_ITConfig(LPC_UART_TypeDef* LPC_UARTx, uint16_t UART_IT, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        LPC_UARTx->IER |= (UART_IT);
    }
    else
    {
        LPC_UARTx->IER &=~(UART_IT);
    }
}

/************************************************************
  Function   : ()
  Description: 
  Input      : None
  Output     : None
  Return     : None
  Others     : 对于中断状态函数，首先要确保中断是使能的，这样中断状态标志才有意义
************************************************************/
// ITStatus UART_GetITStatus(LPC_UART_TypeDef* LPC_UARTx, uint16_t UART_IT)
// {
//     uint32_t bitpos = 0x00, itmask = 0x00;
//     ITStatus bitstatus = RESET;
//     if((LPC_UARTx->IER&UART_IT) && (LPC_UARTx->IIR&UART_IT))
//     {
//         bitstatus = SET;
//     }
//     else
//     {
//         bitstatus = RESET;
//     }
//     return(bitstatus);
// }


/************************************************************
End of filename
************************************************************/
