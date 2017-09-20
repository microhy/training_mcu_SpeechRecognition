/************************************************************
    Copyright (C), 2013, Hnist FS_GCZX.
    
    File name: sysClock.h
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
#ifndef __SYSCLOCK_H
#define __SYSCLOCK_H

#ifdef __cplusplus
    extern "C" {
#endif 
/**********Includes*********************/
#include "..\inc\LPC1768GCZX.h"       
// #include ".h"
/**********Variables********************/

        
/**********Macros***********************/

//外设分频情况定义
#define     CCLK_Div1      ((uint8_t)0x01)
#define     CCLK_Div2      ((uint8_t)0x02)
#define     CCLK_Div4      ((uint8_t)0x00)
#define     CCLK_Div8      ((uint8_t)0x03)
        
/***************************
*********/
/***PCLKSEL0 控制的外设*/
#define     PCLK_WDT       ((uint8_t)0 )
#define     PCLK_TIMER0    ((uint8_t)2 )
#define     PCLK_TIMER1    ((uint8_t)4 )
#define     PCLK_UART0     ((uint8_t)6 )
#define     PCLK_UART1     ((uint8_t)8 )
// PCLKSEL0 [10:9]  保留
#define     PCLK_PWM1      ((uint8_t)12)
#define     PCLK_I2C0      ((uint8_t)14)
#define     PCLK_SPI       ((uint8_t)16)
// PCLKSEL0 [19:18] 保留
#define     PCLK_SSP1      ((uint8_t)20)
#define     PCLK_DAC       ((uint8_t)22)
#define     PCLK_ADC       ((uint8_t)24)
#define     PCLK_CAN1      ((uint8_t)26)
#define     PCLK_CAN2      ((uint8_t)28)
#define     PCLK_ACF       ((uint8_t)30)

/***PCLKSEL1 控制的外设*/
#define     PCLK_QE1       ((uint8_t)32)
#define     PCLK_GPIOINT   ((uint8_t)34)
#define     PCLK_PCB       ((uint8_t)36)
#define     PCLK_I2C1      ((uint8_t)38)
// PCLKSEL1 [9:8]  保留
#define     PCLK_SPP0      ((uint8_t)42)
#define     PCLK_TIMER2    ((uint8_t)44)
#define     PCLK_TIMER3    ((uint8_t)46)
#define     PCLK_UART2     ((uint8_t)48)
#define     PCLK_UART3     ((uint8_t)50)
#define     PCLK_I2C2      ((uint8_t)52)
#define     PCLK_I2S       ((uint8_t)54)
// PCLKSEL1 [25:24] 保留
#define     PCLK_RIT       ((uint8_t)58)
#define     PCLK_SYSCON    ((uint8_t)60)
#define     PCLK_MC        ((uint8_t)62)

/***************************
*********/
// CLKOUTCFG[3:0] 时钟源选择
#define     CLKOUT_CCLK             ((uint8_t)0x00)
#define     CLKOUT_OSCCLK           ((uint8_t)0x01)
#define     CLKOUT_IRCOSC           ((uint8_t)0x02)
#define     CLKOUT_USBCLK           ((uint8_t)0x03)
#define     CLKOUT_RTCCLK           ((uint8_t)0x04)

// CLKOUTCFG[7:4] 时钟输出分频
#define     CLKOUT_Div1             ((uint8_t)0x00)
#define     CLKOUT_Div2             ((uint8_t)0x10)
#define     CLKOUT_Div3             ((uint8_t)0x20)
#define     CLKOUT_Div4             ((uint8_t)0x30)
#define     CLKOUT_Div5             ((uint8_t)0x40)
#define     CLKOUT_Div6             ((uint8_t)0x50)
#define     CLKOUT_Div7             ((uint8_t)0x60)
#define     CLKOUT_Div8             ((uint8_t)0x70)
#define     CLKOUT_Div9             ((uint8_t)0x80)
#define     CLKOUT_Div10            ((uint8_t)0x90)
#define     CLKOUT_Div11            ((uint8_t)0xA0)
#define     CLKOUT_Div12            ((uint8_t)0xB0)
#define     CLKOUT_Div13            ((uint8_t)0xC0)
#define     CLKOUT_Div14            ((uint8_t)0xD0)
#define     CLKOUT_Div15            ((uint8_t)0xE0)
#define     CLKOUT_Div16            ((uint8_t)0xF0)

//
//#define   Reserved                ((uint32_t)0x00000001)
#define     PCTIM0                  ((uint32_t)0x00000002)
#define     PCTIM1                  ((uint32_t)0x00000004)
#define     PCUART0                 ((uint32_t)0x00000008)
#define     PCUART1                 ((uint32_t)0x00000010)
//#define   Reserved                ((uint32_t)0x00000020)
#define     PCPWM1                  ((uint32_t)0x00000040)
#define     PCI2C0                  ((uint32_t)0x00000080)
#define     PCSPI                   ((uint32_t)0x00000100)
#define     PCRTC                   ((uint32_t)0x00000200)
#define     PCSSP1                  ((uint32_t)0x00000400)
//#define   Reserved                ((uint32_t)0x00000800)
#define     PCADC                   ((uint32_t)0x00001000)
#define     PCCAN1                  ((uint32_t)0x00002000)
#define     PCCAN2                  ((uint32_t)0x00004000)
#define     PCGPIO                  ((uint32_t)0x00008000)
#define     PCRIT                   ((uint32_t)0x00010000)
#define     PCMCPWM                 ((uint32_t)0x00020000)
#define     PCQEI                   ((uint32_t)0x00040000)
#define     PCI2C1                  ((uint32_t)0x00080000)
//#define     Reserved              ((uint32_t)0x00100000)
#define     PCSSP0                  ((uint32_t)0x00200000)
#define     PCTIM2                  ((uint32_t)0x00400000)
#define     PCTIM3                  ((uint32_t)0x00800000)
#define     PCUART2                 ((uint32_t)0x01000000)
#define     PCUART3                 ((uint32_t)0x02000000)
#define     PCI2C2                  ((uint32_t)0x04000000)
#define     PCI2S                   ((uint32_t)0x08000000)
//#define     Reserved              ((uint32_t)0x10000000)
#define     PCGPDMA                 ((uint32_t)0x20000000)
#define     PCENET                  ((uint32_t)0x40000000)
#define     PCUSB                   ((uint32_t)0x80000000)

/**********Function Prototypes**********/
void PeripheralsClock_DeInit(void );
void PeripheralsClock_Divider(uint8_t perip, uint8_t divider);
void ClockOutput_Config(uint8_t clkSource, uint8_t clkDiv);
void ClockOutput_Cmd(FunctionalState NewState);
void Peripherals_PowerControl(uint32_t pcPerip, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif
/************************************************************
End of filename
************************************************************/
