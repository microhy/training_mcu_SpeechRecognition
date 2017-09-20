/************************************************************
    Copyright (C), 2013, Hnist FS_GCZX.

    File name: lpc_A7105.h
    Author:         Version:        Date:2015_04_22
    Description:
    Others:
    Function List:
    History:
    1.Date:
      Author:
      Modification:
    2. ...
*************************************************************/
#ifndef __LPC_A7105_H
#define __LPC_A7105_H

#ifdef __cplusplus
extern "C" {
#endif
/**********Includes*********************/
#include "../inc/LPC1768GCZX.h"
// A7105模块管脚说明：
// 从靠近晶振的这边开始分别为
// SCS->SCK->SDIO->GPIO1->GND->3.3V
#define PORTA7105             LPC_GPIO2   //PORT2使用的GPIO组
#define A7105_SCS             BIT1  //对应的引脚
#define A7105_SCK             BIT2
#define A7105_SDIO            BIT3
#define A7105_GPIO1           BIT4  /*输入方向*/

//SCS使能信号  enable signal         //可参见FIOCLR寄存器
#define A7105_SCS_0           PORTA7105->FIOCLR |= A7105_SCS
#define A7105_SCS_1           PORTA7105->FIOSET |= A7105_SCS

//SCK时钟信号  serial clock signal
#define A7105_SCK_0           PORTA7105->FIOCLR |= A7105_SCK
#define A7105_SCK_1           PORTA7105->FIOSET |= A7105_SCK

//SDIO串行数据输入、输出 serial data input/output
#define A7105_SDIO_OUT()      PORTA7105->FIODIR |= A7105_SDIO/*方向配置*/
#define A7105_SDIO_IN()       PORTA7105->FIODIR &=~A7105_SDIO

#define A7105_SDIO_0          PORTA7105->FIOCLR |= A7105_SDIO /*数据输出*/
#define A7105_SDIO_1          PORTA7105->FIOSET |= A7105_SDIO

#define A7105_Read_SDIO      (PORTA7105->FIOPIN&A7105_SDIO)  /*读数据*/
//GPIO1
#define A7105_Read_GPIO1     (PORTA7105->FIOPIN&A7105_GPIO1)

/* Exported constants --------------------------------------------------------*/
#define MODE_REG                0x00
#define MODECTRL_REG            0x01
#define CALIBRATION_REG         0x02
#define FIFO1_REG               0x03
#define FIFO2_REG               0x04
#define FIFO_REG                0x05
#define IDCODE_REG              0x06
#define RCOSC1_REG              0x07
#define RCOSC2_REG              0x08
#define RCOSC3_REG              0x09
#define CKO_REG                 0x0A
#define GPIO1_REG               0x0B
#define GPIO2_REG               0x0C
#define CLOCK_REG               0x0D
#define DATARATE_REG            0x0E
#define PLL1_REG                0x0F
#define PLL2_REG                0x10
#define PLL3_REG                0x11
#define PLL4_REG                0x12
#define PLL5_REG                0x13
#define TX1_REG                 0x14
#define TX2_REG                 0x15
#define DELAY1_REG              0x16
#define DELAY2_REG              0x17
#define RX_REG                  0x18
#define RXGAIN1_REG             0x19
#define RXGAIN2_REG             0x1A
#define RXGAIN3_REG             0x1B
#define RXGAIN4_REG             0x1C
#define RSSI_REG                0x1D
#define ADC_REG                 0x1E
#define CODE1_REG               0x1F
#define CODE2_REG               0x20
#define CODE3_REG               0x21
#define IFCAL1_REG              0x22
#define IFCAL2_REG              0x23
#define VCOCCAL_REG             0x24
#define VCOCAL1_REG             0x25
#define VCOCAL2_REG             0x26
#define BATTERY_REG             0x27
#define TXTEST_REG              0x28
#define RXDEM1_REG              0x29
#define RXDEM2_REG              0x2A
#define CPC_REG                 0x2B
#define CRYSTALTEST_REG         0x2C
#define PLLTEST_REG             0x2D
#define VCOTEST1_REG            0x2E
#define VCOTEST2_REG            0x2F
#define IFAT_REG                0x30
#define RSCALE_REG              0x31
#define FILTERTEST_REG          0x32
//strobe command
#define CMD_SLEEP           0x80    //1000,xxxx    SLEEP mode
#define CMD_IDLE            0x90    //1001,xxxx    IDLE mode
#define CMD_STBY            0xA0    //1010,xxxx Standby mode
#define CMD_PLL             0xB0    //1011,xxxx    PLL mode
#define CMD_RX              0xC0    //1100,xxxx    RX mode
#define CMD_TX              0xD0    //1101,xxxx    TX mode
#define CMD_TFR             0xE0    //1110,xxxx    TX FIFO reset
#define CMD_RFR             0xF0    //1111,xxxx    RX FIFO reset
//
#define ch_2400MHz          0x00
#define ch_2480MHz          160
#define ch_2450MHz          100     //2450MHz
#define ch_2449_5MHz        99      //2449.5MHz
/* Exported macro ------------------------------------------------------------*/
#define A7105_ConfigFreq(x)        A7105_WriteREG(PLL1_REG,x)
/* Exported functions ------------------------------------------------------- */
void A7105_InitRF(void);
void A7105_WriteREG(uint8_t addr,uint8_t wdat);
uint8_t A7105_ReadREG(uint8_t addr);
void A7105_SendByte(uint8_t byte);
uint8_t A7105_ReadByte(void);
void A7105_StrobeCmd(uint8_t scmd);
void A7105_WriteFIFO(void);

#ifdef __cplusplus
}
#endif

#endif
/************************************************************
End of lpc_A7105.h
************************************************************/

