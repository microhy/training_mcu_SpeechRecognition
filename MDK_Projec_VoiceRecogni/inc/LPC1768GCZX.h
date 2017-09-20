/************************************************* 
    Copyright (C), 2013, Hnist FS_GCZX. 
    File name: LPC1768GCZX.h     
    Author:Hnist FS_GCZX       Version:13.11        Date: 2013.11.30
    Description: 该文件包含了NXP提供的除去EMAC部分的LPC1768标准演示函数库全部头文件
                实际使用时可根据应用对此头文件的项目进行注释
                在/sytem中也应对相应的.c文件进行删除，以减小代码空间
                使用如下格式包含本文件于所有源代码文件中
                #include "../inc/LPC1768GCZX.h"
*************************************************/
#ifndef __LPC1768GCZX_H
#define __LPC1768GCZX_H

#ifdef __cplusplus
    extern "C" {
#endif 

/**********Includes*********************/
/*"../system_h/"*/
#include "../system_h/stdio.h"
#include "../system_h/stdint.h"
#include "../system_h/stdlib.h"
#include "../system_h/type.h"
#include "../system_h/lpc17xx.h"
        

        
#define     FCCLK                   100000000
#define     FPCLK                   (25000000)
        
#define     BIT0                    ((uint32_t)0x00000001)
#define     BIT1                    ((uint32_t)0x00000002)
#define     BIT2                    ((uint32_t)0x00000004)
#define     BIT3                    ((uint32_t)0x00000008)
#define     BIT4                    ((uint32_t)0x00000010)
#define     BIT5                    ((uint32_t)0x00000020)
#define     BIT6                    ((uint32_t)0x00000040)
#define     BIT7                    ((uint32_t)0x00000080)
#define     BIT8                    ((uint32_t)0x00000100)
#define     BIT9                    ((uint32_t)0x00000200)
#define     BIT10                   ((uint32_t)0x00000400)
#define     BIT11                   ((uint32_t)0x00000800)
#define     BIT12                   ((uint32_t)0x00001000)
#define     BIT13                   ((uint32_t)0x00002000)
#define     BIT14                   ((uint32_t)0x00004000)
#define     BIT15                   ((uint32_t)0x00008000)
#define     BIT16                   ((uint32_t)0x00010000)
#define     BIT17                   ((uint32_t)0x00020000)
#define     BIT18                   ((uint32_t)0x00040000)
#define     BIT19                   ((uint32_t)0x00080000)
#define     BIT20                   ((uint32_t)0x00100000)
#define     BIT21                   ((uint32_t)0x00200000)
#define     BIT22                   ((uint32_t)0x00400000)
#define     BIT23                   ((uint32_t)0x00800000)
#define     BIT24                   ((uint32_t)0x01000000)
#define     BIT25                   ((uint32_t)0x02000000)
#define     BIT26                   ((uint32_t)0x04000000)
#define     BIT27                   ((uint32_t)0x08000000)
#define     BIT28                   ((uint32_t)0x10000000)
#define     BIT29                   ((uint32_t)0x20000000)
#define     BIT30                   ((uint32_t)0x40000000)
#define     BIT31                   ((uint32_t)0x80000000)

#ifdef __cplusplus 
}
#endif
#endif

/************************************************************
End of LPC1768GCZX.h
************************************************************/
