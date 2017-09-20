/************************************************************
    Copyright (C), 2013, Hnist FS_GCZX.
    
    FileName: .c
    Author:     Version :       Date:
    Description:
    Function List: 
    1.
    History:
    <author>    <time>      <version >      <desc>
    huyong      2014-03-12
************************************************************/

/**********Includes*********************/
#include "../inc/lpc17xx_gpio.h" 

/**********Macros***********************/
#define     GPIOFunc_Mask       ((uint32_t)0x00000003)
#define     GPIOMode_Mask       ((uint32_t)0x00000003)
#define     GPIOFIOX_Mask       ((uint32_t)0x00000001)

/**********Variables********************/

/**********Function Prototypes**********/



/************************************************************
  Function   : GPIO0_PinFuncSel()
  Description: GPIO0组 引脚功能选择
  Input      : 
      @param  GPIO_Pin_x: 引脚名称
        @arg 只可以是GPIO_Pin_0~11，15~30中的一个
      @param  GPIOFunc: GPIO功能
        @arg GPIOFunc_PORT: 作普通IO口使用
        @arg GPIOFunc_AF1: 复用功能1
        @arg GPIOFunc_AF2: 复用功能2
        @arg GPIOFunc_AF3: 复用功能3
  Output     : P0.x 引脚功能被改变
  Return     : None
  Others     : LPC_PINCON->PINSEL0,1
************************************************************/
void GPIO0_PinFuncSel(uint32_t GPIO_Pin_x, GPIOFunc_TypeDef GPIOFunc)
{
    uint32_t tmpreg = 0x00, pinpos = 0x00;
    
    tmpreg = GPIO_Pin_x;
    if (GPIO_Pin_x > GPIO_Pin_15)
    {
        tmpreg >>= 16;
    }
    while(tmpreg != 0x00000001) //右移位得到当前引脚位置
    {
        tmpreg >>= 1;
        ++pinpos;
    }
    pinpos <<= 1;             //左移1位，相当于乘以2，得到后面数据配置左移的位数
    if( GPIO_Pin_x <= GPIO_Pin_15)
    {
        tmpreg = LPC_PINCON->PINSEL0;
        tmpreg &=~(GPIOFunc_Mask<<pinpos); // 0x00000003<<pinpos
        tmpreg |= (GPIOFunc<<pinpos);
        LPC_PINCON->PINSEL0 = tmpreg;
    }
    else
    {
        tmpreg = LPC_PINCON->PINSEL1;
        tmpreg &=~(GPIOFunc_Mask<<pinpos);
        tmpreg |= (GPIOFunc<<pinpos);
        LPC_PINCON->PINSEL1 = tmpreg;
    }
}

/************************************************************
  Function   : GPIO1_PinFuncSel()
  Description: GPIO1组 引脚功能选择
  Input      : 
      @param  GPIO_Pin_x: 引脚名称
        @arg 只可以是GPIO_Pin_0,1,4,8~10,14~31的一个
      @param  GPIOFunc: GPIO功能
        @arg GPIOFunc_PORT: 作普通IO口使用
        @arg GPIOFunc_AF1: 复用功能1
        @arg GPIOFunc_AF2: 复用功能2
        @arg GPIOFunc_AF3: 复用功能3
  Output     : P1.x 引脚功能被改变
  Return     : None
  Others     : LPC_PINCON->PINSEL2,3
************************************************************/
void GPIO1_PinFuncSel(uint32_t GPIO_Pin_x, GPIOFunc_TypeDef GPIOFunc)
{
    uint32_t tmpreg = 0x00, pinpos = 0x00;
    
    tmpreg = GPIO_Pin_x;
    if (GPIO_Pin_x > GPIO_Pin_15)
    {
        tmpreg >>= 16;
    }
    while(tmpreg != 0x00000001) //右移位得到当前引脚位置
    {
        tmpreg >>= 1;
        ++pinpos;
    }
    pinpos <<= 1;             //左移1位，相当于乘以2，得到后面数据配置左移的位数
    if( GPIO_Pin_x <= GPIO_Pin_15)
    {
        tmpreg = LPC_PINCON->PINSEL2;
        tmpreg &=~(GPIOFunc_Mask<<pinpos); // 0x00000003<<pinpos
        tmpreg |= (GPIOFunc<<pinpos);
        LPC_PINCON->PINSEL2 = tmpreg;
    }
    else
    {
        tmpreg = LPC_PINCON->PINSEL3;
        tmpreg &=~(GPIOFunc_Mask<<pinpos);
        tmpreg |= (GPIOFunc<<pinpos);
        LPC_PINCON->PINSEL3 = tmpreg;
    }
}

/************************************************************
  Function   : GPIO2_PinFuncSel()
  Description: GPIO2组 引脚功能选择
  Input      : 
      @param  GPIO_Pin_x: 引脚名称
        @arg 只可以是GPIO_Pin_0~13中的一个
      @param  GPIOFunc: GPIO功能
        @arg GPIOFunc_PORT: 作普通IO口使用
        @arg GPIOFunc_AF1: 复用功能1
        @arg GPIOFunc_AF2: 复用功能2
        @arg GPIOFunc_AF3: 复用功能3
  Output     : P2.x 引脚功能被改变
  Return     : None
  Others     : LPC_PINCON->PINSEL4
************************************************************/
void GPIO2_PinFuncSel(uint32_t GPIO_Pin_x, GPIOFunc_TypeDef GPIOFunc)
{
    uint32_t tmpreg = 0x00, pinpos = 0x00;
    
    tmpreg = GPIO_Pin_x;
    if (GPIO_Pin_x < GPIO_Pin_13)
    {   
        while(tmpreg != 0x00000001) //右移位得到当前引脚位置
        {
            tmpreg >>= 1;
            ++pinpos;
        }
        pinpos <<= 1;             //左移1位，相当于乘以2，得到后面数据配置左移的位数
        tmpreg = LPC_PINCON->PINSEL4;
        tmpreg &=~(GPIOFunc_Mask<<pinpos); // 0x00000003<<pinpos
        tmpreg |= (GPIOFunc<<pinpos);
        LPC_PINCON->PINSEL4 = tmpreg;
    }
    else;
}
/************************************************************
  Function   : GPIO3_PinFuncSel()
  Description: GPIO3组 引脚功能选择
  Input      : 
      @param  GPIO_Pin_x: 引脚名称
        @arg 只可以是GPIO_Pin_25,26中的一个；（其它引脚被保留）
      @param  GPIOFunc: GPIO功能
        @arg GPIOFunc_PORT: 作普通IO口使用
        @arg GPIOFunc_AF1: 复用功能1
        @arg GPIOFunc_AF2: 复用功能2
        @arg GPIOFunc_AF3: 复用功能3
  Output     : P3.x 引脚功能被改变
  Return     : None
  Others     : LPC_PINCON->PINSEL7
************************************************************/
void GPIO3_PinFuncSel(uint32_t GPIO_Pin_x, GPIOFunc_TypeDef GPIOFunc)
{
    uint32_t tmpreg = 0x00;
    
    tmpreg = LPC_PINCON->PINSEL7;
    if(GPIO_Pin_x == GPIO_Pin_25)
    {
        tmpreg &=~ (GPIOFunc_Mask<<18);
        tmpreg |= (GPIOFunc<<18);
    }
    else if(GPIO_Pin_x == GPIO_Pin_26)
    {
        tmpreg &=~ (GPIOFunc_Mask<<20);
        tmpreg |= (GPIOFunc<<20);
    }
    else ;
    LPC_PINCON->PINSEL7 = tmpreg;
}
/************************************************************
  Function   : GPIO4_PinFuncSel()
  Description: GPIO4组 引脚功能选择
  Input      : 
      @param  GPIO_Pin_x: 引脚名称
        @arg 只可以是GPIO_Pin_28,29中的一个；（其它引脚被保留）
      @param  GPIOFunc: GPIO功能
        @arg GPIOFunc_PORT: 作普通IO口使用
        @arg GPIOFunc_AF1: 复用功能1
        @arg GPIOFunc_AF2: 复用功能2
        @arg GPIOFunc_AF3: 复用功能3
  Output     : P4.x 引脚功能被改变
  Return     : None
  Others     : LPC_PINCON->PINSEL9
************************************************************/
void GPIO4_PinFuncSel(uint32_t GPIO_Pin_x, GPIOFunc_TypeDef GPIOFunc)
{
    uint32_t tmpreg = 0x00;
    
    tmpreg = LPC_PINCON->PINSEL9;
    if(GPIO_Pin_x == GPIO_Pin_28)
    {
        tmpreg &=~ (GPIOFunc_Mask<<24);
        tmpreg |= (GPIOFunc<<24);
    }
    else if(GPIO_Pin_x == GPIO_Pin_29)
    {
        tmpreg &=~ (GPIOFunc_Mask<<26);
        tmpreg |= (GPIOFunc<<26);
    }
    else ;
    LPC_PINCON->PINSEL9 = tmpreg;
}
/************************************************************
  Function   : GPIO_OpenDrainCmd()
  Description: GPIO开漏模式选择
  Input      : 
      @param  GPIOx: GPIO组名称
        @arg GPIO0~4
      @param  GPIO_Pin: 引脚名称
        @arg GPIO_Pin_0~31的任意组合
        @arg GPIO_Pin_All 该组的所有引脚
      @param  NewState: 新的状态命令
        @arg ENABLE: 开漏模式
        @arg DISABLE: 非开漏模式
  Output     : None
  Return     : None
  Others     : GPIO_OpenDrainCmd(GPIO0, GPIO_Pin_10, ENABLE);
************************************************************/
void GPIO_OpenDrainCmd(LPC_GPIO_TypeDef* LPC_GPIOx, uint32_t GPIO_Pin, FunctionalState NewState)
{
    if(LPC_GPIOx==LPC_GPIO0)
    {
        if( NewState != DISABLE)
            LPC_PINCON->PINMODE_OD0 |= GPIO_Pin;
        else
            LPC_PINCON->PINMODE_OD0 &=~(GPIO_Pin);
    }
    else if(LPC_GPIOx==LPC_GPIO1)
    {
        if( NewState != DISABLE)
            LPC_PINCON->PINMODE_OD1 |= GPIO_Pin;
        else
            LPC_PINCON->PINMODE_OD1 &=~(GPIO_Pin);
    }
    else if(LPC_GPIOx==LPC_GPIO2)
    {
        if( NewState != DISABLE)
            LPC_PINCON->PINMODE_OD2 |= GPIO_Pin;
        else
            LPC_PINCON->PINMODE_OD2 &=~(GPIO_Pin);
    }    
    else if(LPC_GPIOx==LPC_GPIO3)
    {
        if( NewState != DISABLE)
            LPC_PINCON->PINMODE_OD3 |= GPIO_Pin;
        else
            LPC_PINCON->PINMODE_OD3 &=~(GPIO_Pin);
    }
    else if(LPC_GPIOx==LPC_GPIO4)
    {
        if( NewState != DISABLE)
            LPC_PINCON->PINMODE_OD4 |= GPIO_Pin;
        else
            LPC_PINCON->PINMODE_OD4 &=~(GPIO_Pin);
    }
    else
        while(1); //error
}

/************************************************************
  Function   : GPIO_DirectionConfig()
  Description: 设置引脚的方向
  Input      : 
  @param  GPIOx: GPIO组名称
    @arg GPIO0~4
  @param  GPIO_Pin: 引脚名称
    @arg GPIO_Pin_0~31的任意组合
    @arg GPIO_Pin_All 该组的所有引脚
  @param  dir: 方向
    @arg GPIO_Input: 管脚输入
    @arg GPIO_Output: 管脚输出
  Output     : None
  Return     : None
  Others     : 操作的寄存器: GPIOx->FIODIR
************************************************************/
void GPIO_DirectionConfig(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x, GPIODIR_TypeDef dir)
{
    if (dir )               // 如果为1，即设置为输出方向
    {
        LPC_GPIOx->FIODIR |= (GPIO_Pin_x);
    }
    else                    // 如果为0，即设置为输入方向
    {
        LPC_GPIOx->FIODIR &=~(GPIO_Pin_x);
    }
}

/**
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: where x can be (0..4) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..31).
  * @retval None
    操作的寄存器: GPIOx->FIOSET
  @note 之所以不用位操作，是因为FIOxSET写入0时无效
  */
void GPIO_SetBits(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x)
{
    LPC_GPIOx->FIOSET = (GPIO_Pin_x);
}

/**
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: where x can be (0..4) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..31).
  * @retval None
    操作的寄存器: GPIOx->FIOCLR
  @note 之所以不用位操作，是因为FIOxCLR写入0时无效
  */
void GPIO_ResetBits(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x)
{
    LPC_GPIOx->FIOCLR = (GPIO_Pin_x);
}

/************************************************************
  Function   : GPIO_ReadDataBit()
  Description: 读取IO口的当前值
  Input      :   
  @param  GPIOx: GPIO组名称
    @arg GPIO0~4
  @param  GPIO_Pin: 引脚名称
    @arg GPIO_Pin_0~31 中的一个
  Output     : None
  Return     : bitstatus 此IO口当前的状态
  Others     : 操作的寄存器: GPIOx->FIOPIN
************************************************************/
uint8_t GPIO_ReadDataBit(LPC_GPIO_TypeDef* LPC_GPIOx, uint32_t GPIO_Pin_x)
{
    uint8_t bitstatus = 0;
    
    if ((LPC_GPIOx->FIOPIN & GPIO_Pin_x) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    
    return (bitstatus);
}
/************************************************************
  Function   : GPIO_ReadData()
  Description: 读取一组IO口的当前值
  Input      :   
  @param  GPIOx: GPIO组名称
    @arg GPIO0~4
  Output     : None
  Return     : 改组IO口数值
  Others     : 操作的寄存器: GPIOx->FIOPIN
************************************************************/
uint32_t GPIO_ReadData(LPC_GPIO_TypeDef* LPC_GPIOx)
{
    return ((LPC_GPIOx->FIOPIN));
}

/************************************************************
  Function   : GPIO_FIOxMaskCmd()
  Description: GPIO管脚屏蔽命令
  Input      : 
  @param  GPIOx: GPIO组名称
    @arg GPIO0~4
  @param  GPIO_Pin: 引脚名称
    @arg GPIO_Pin_0~31的任意组合
    @arg GPIO_Pin_All 该组的所有引脚
  @param  NewState: 新的状态命令
    @arg ENABLE: 将该管脚屏蔽
    @arg DISABLE: 不屏蔽该管脚
  Output     : 管脚屏蔽的状态变化
  Return     : None
  Others     : 操作的寄存器: GPIOx->FIOMASK
************************************************************/
void GPIO_FIOxMaskCmd(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        LPC_GPIOx->FIOMASK |= GPIO_Pin_x;
    }
    else
    {
        LPC_GPIOx->FIOMASK &=~(GPIO_Pin_x);
    }
}

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
void GPIO_INTConfig(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x, GPIOIntEdge_Typedef intEdge, FunctionalState NewState)
{
    if (LPC_GPIOx == LPC_GPIO0)
    {
        if( NewState!= DISABLE ) //ENABLE使能中断
        {
            if (intEdge == GPIOIntEdge_Rising)      // 上升沿中断
            {
                LPC_GPIOINT->IO0IntEnR |= GPIO_Pin_x; 
            }
            else if (intEdge == GPIOIntEdge_Falling)//下降沿中断
            {
                LPC_GPIOINT->IO0IntEnF |= GPIO_Pin_x;
            }
            else        
            {
                LPC_GPIOINT->IO0IntEnR |= GPIO_Pin_x;     //上下降沿都中断
                LPC_GPIOINT->IO0IntEnF |= GPIO_Pin_x;
            }
        }
        else    //DISABLE 禁能中断
        {
            if (intEdge == GPIOIntEdge_Rising)
            {
                LPC_GPIOINT->IO0IntEnR &=~ (GPIO_Pin_x);
            }
            else if (intEdge == GPIOIntEdge_Falling)
            {
                LPC_GPIOINT->IO0IntEnF &=~ (GPIO_Pin_x);
            }
            else
            {
                LPC_GPIOINT->IO0IntEnR &=~ (GPIO_Pin_x);
                LPC_GPIOINT->IO0IntEnR &=~ (GPIO_Pin_x);
            }
        }
    }

    else if (LPC_GPIOx == LPC_GPIO2)
    {
        if( NewState!= DISABLE ) //ENABLE使能中断
        {
            if (intEdge == GPIOIntEdge_Rising)
            {
                LPC_GPIOINT->IO2IntEnR |= GPIO_Pin_x;
            }
            else if (intEdge == GPIOIntEdge_Falling)
            {
                LPC_GPIOINT->IO2IntEnF |= GPIO_Pin_x;
            }
            else
            {
                LPC_GPIOINT->IO2IntEnR |= GPIO_Pin_x;
                LPC_GPIOINT->IO2IntEnF |= GPIO_Pin_x;
            }
        }
        else    //DISABLE 禁能中断
        {
            if (intEdge == GPIOIntEdge_Rising)
            {
                LPC_GPIOINT->IO2IntEnR &=~ (GPIO_Pin_x);
            }
            else if (intEdge == GPIOIntEdge_Falling)
            {
                LPC_GPIOINT->IO2IntEnF &=~ (GPIO_Pin_x);
            }
            else
            {
                LPC_GPIOINT->IO2IntEnR &=~ (GPIO_Pin_x);
                LPC_GPIOINT->IO2IntEnR &=~ (GPIO_Pin_x);
            }
        }
    }
    else
    {   while(1);  }  // 注意：只有GPIO0和GPIO2有中断功能，当选择其他停在此处
}

ITStatus GPIO_INTGetITStatus(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x, GPIOIntEdge_Typedef intEdge)
{
    uint32_t tmpreg = 0;
    FlagStatus bitstatus = RESET;
    
    tmpreg =~ (GPIO_Pin_x);
    if( LPC_GPIOx == LPC_GPIO0 )
    {
        if ( intEdge == GPIOIntEdge_Rising)
        {
            if( (LPC_GPIOINT->IO0IntEnR&tmpreg) != RESET)
            {
                bitstatus = SET;
            }
            // else bitstatus = RESET 已被初始化为复位
        }
        else if (intEdge == GPIOIntEdge_Falling)
        {
            if( (LPC_GPIOINT->IO0IntEnF&tmpreg) != RESET)
            {
                bitstatus = SET;
            }
        }
        else
        {
            
        }
    }
    else if ( LPC_GPIOx == LPC_GPIO2 )
    {
        if ( intEdge == GPIOIntEdge_Rising)
        {
            if( (LPC_GPIOINT->IO2IntEnR&tmpreg) != RESET)
            {
                bitstatus = SET;
            }
            // else bitstatus = RESET 已被初始化为复位
        }
        else if (intEdge == GPIOIntEdge_Falling)
        {
            if( (LPC_GPIOINT->IO2IntEnF&tmpreg) != RESET)
            {
                bitstatus = SET;
            }
        }
        else
        {
            
        }
    }
    else
    {   while(1);  }  // 注意：只有GPIO0和GPIO2有中断功能，当选择其他停在此处
    
    return (bitstatus);
}

/************************************************************
  Function   : GPIO_INTClear()
  Description: GPIO 中断清除 IOxIntStatR and IOxStatF
  Input      :   
  @param  GPIOx: GPIO组名称
    @arg GPIO0 , GPIO2
  @param  GPIO_Pin: 引脚名称
    @arg 当为GPIO0时 GPIO_Pin_0~30的任意组合
    @arg 当为GPIO2时 GPIO_Pin_0~13的任意组合
  Output     : None
  Return     : None
  Others     : IO0IntClr 和 IO2IntClr 当配置为0时，状态不改变，所以这里不做位运算
************************************************************/
void GPIO_INTClear(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x)
{
    
    if( LPC_GPIOx == LPC_GPIO0 )
    {
        LPC_GPIOINT->IO0IntClr = GPIO_Pin_x;
    }
    else if ( LPC_GPIOx == LPC_GPIO2 )
    {
        LPC_GPIOINT->IO2IntClr = GPIO_Pin_x;
    }
    else
    {   while(1);  }  // 注意：只有GPIO0和GPIO2有中断功能，当选择其他停在此处
}


/************************************************************
End of filename
************************************************************/
