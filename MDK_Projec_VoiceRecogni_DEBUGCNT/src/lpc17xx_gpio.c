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
  Description: GPIO0�� ���Ź���ѡ��
  Input      : 
      @param  GPIO_Pin_x: ��������
        @arg ֻ������GPIO_Pin_0~11��15~30�е�һ��
      @param  GPIOFunc: GPIO����
        @arg GPIOFunc_PORT: ����ͨIO��ʹ��
        @arg GPIOFunc_AF1: ���ù���1
        @arg GPIOFunc_AF2: ���ù���2
        @arg GPIOFunc_AF3: ���ù���3
  Output     : P0.x ���Ź��ܱ��ı�
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
    while(tmpreg != 0x00000001) //����λ�õ���ǰ����λ��
    {
        tmpreg >>= 1;
        ++pinpos;
    }
    pinpos <<= 1;             //����1λ���൱�ڳ���2���õ����������������Ƶ�λ��
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
  Description: GPIO1�� ���Ź���ѡ��
  Input      : 
      @param  GPIO_Pin_x: ��������
        @arg ֻ������GPIO_Pin_0,1,4,8~10,14~31��һ��
      @param  GPIOFunc: GPIO����
        @arg GPIOFunc_PORT: ����ͨIO��ʹ��
        @arg GPIOFunc_AF1: ���ù���1
        @arg GPIOFunc_AF2: ���ù���2
        @arg GPIOFunc_AF3: ���ù���3
  Output     : P1.x ���Ź��ܱ��ı�
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
    while(tmpreg != 0x00000001) //����λ�õ���ǰ����λ��
    {
        tmpreg >>= 1;
        ++pinpos;
    }
    pinpos <<= 1;             //����1λ���൱�ڳ���2���õ����������������Ƶ�λ��
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
  Description: GPIO2�� ���Ź���ѡ��
  Input      : 
      @param  GPIO_Pin_x: ��������
        @arg ֻ������GPIO_Pin_0~13�е�һ��
      @param  GPIOFunc: GPIO����
        @arg GPIOFunc_PORT: ����ͨIO��ʹ��
        @arg GPIOFunc_AF1: ���ù���1
        @arg GPIOFunc_AF2: ���ù���2
        @arg GPIOFunc_AF3: ���ù���3
  Output     : P2.x ���Ź��ܱ��ı�
  Return     : None
  Others     : LPC_PINCON->PINSEL4
************************************************************/
void GPIO2_PinFuncSel(uint32_t GPIO_Pin_x, GPIOFunc_TypeDef GPIOFunc)
{
    uint32_t tmpreg = 0x00, pinpos = 0x00;
    
    tmpreg = GPIO_Pin_x;
    if (GPIO_Pin_x < GPIO_Pin_13)
    {   
        while(tmpreg != 0x00000001) //����λ�õ���ǰ����λ��
        {
            tmpreg >>= 1;
            ++pinpos;
        }
        pinpos <<= 1;             //����1λ���൱�ڳ���2���õ����������������Ƶ�λ��
        tmpreg = LPC_PINCON->PINSEL4;
        tmpreg &=~(GPIOFunc_Mask<<pinpos); // 0x00000003<<pinpos
        tmpreg |= (GPIOFunc<<pinpos);
        LPC_PINCON->PINSEL4 = tmpreg;
    }
    else;
}
/************************************************************
  Function   : GPIO3_PinFuncSel()
  Description: GPIO3�� ���Ź���ѡ��
  Input      : 
      @param  GPIO_Pin_x: ��������
        @arg ֻ������GPIO_Pin_25,26�е�һ�������������ű�������
      @param  GPIOFunc: GPIO����
        @arg GPIOFunc_PORT: ����ͨIO��ʹ��
        @arg GPIOFunc_AF1: ���ù���1
        @arg GPIOFunc_AF2: ���ù���2
        @arg GPIOFunc_AF3: ���ù���3
  Output     : P3.x ���Ź��ܱ��ı�
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
  Description: GPIO4�� ���Ź���ѡ��
  Input      : 
      @param  GPIO_Pin_x: ��������
        @arg ֻ������GPIO_Pin_28,29�е�һ�������������ű�������
      @param  GPIOFunc: GPIO����
        @arg GPIOFunc_PORT: ����ͨIO��ʹ��
        @arg GPIOFunc_AF1: ���ù���1
        @arg GPIOFunc_AF2: ���ù���2
        @arg GPIOFunc_AF3: ���ù���3
  Output     : P4.x ���Ź��ܱ��ı�
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
  Description: GPIO��©ģʽѡ��
  Input      : 
      @param  GPIOx: GPIO������
        @arg GPIO0~4
      @param  GPIO_Pin: ��������
        @arg GPIO_Pin_0~31���������
        @arg GPIO_Pin_All �������������
      @param  NewState: �µ�״̬����
        @arg ENABLE: ��©ģʽ
        @arg DISABLE: �ǿ�©ģʽ
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
  Description: �������ŵķ���
  Input      : 
  @param  GPIOx: GPIO������
    @arg GPIO0~4
  @param  GPIO_Pin: ��������
    @arg GPIO_Pin_0~31���������
    @arg GPIO_Pin_All �������������
  @param  dir: ����
    @arg GPIO_Input: �ܽ�����
    @arg GPIO_Output: �ܽ����
  Output     : None
  Return     : None
  Others     : �����ļĴ���: GPIOx->FIODIR
************************************************************/
void GPIO_DirectionConfig(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x, GPIODIR_TypeDef dir)
{
    if (dir )               // ���Ϊ1��������Ϊ�������
    {
        LPC_GPIOx->FIODIR |= (GPIO_Pin_x);
    }
    else                    // ���Ϊ0��������Ϊ���뷽��
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
    �����ļĴ���: GPIOx->FIOSET
  @note ֮���Բ���λ����������ΪFIOxSETд��0ʱ��Ч
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
    �����ļĴ���: GPIOx->FIOCLR
  @note ֮���Բ���λ����������ΪFIOxCLRд��0ʱ��Ч
  */
void GPIO_ResetBits(LPC_GPIO_TypeDef * LPC_GPIOx, uint32_t GPIO_Pin_x)
{
    LPC_GPIOx->FIOCLR = (GPIO_Pin_x);
}

/************************************************************
  Function   : GPIO_ReadDataBit()
  Description: ��ȡIO�ڵĵ�ǰֵ
  Input      :   
  @param  GPIOx: GPIO������
    @arg GPIO0~4
  @param  GPIO_Pin: ��������
    @arg GPIO_Pin_0~31 �е�һ��
  Output     : None
  Return     : bitstatus ��IO�ڵ�ǰ��״̬
  Others     : �����ļĴ���: GPIOx->FIOPIN
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
  Description: ��ȡһ��IO�ڵĵ�ǰֵ
  Input      :   
  @param  GPIOx: GPIO������
    @arg GPIO0~4
  Output     : None
  Return     : ����IO����ֵ
  Others     : �����ļĴ���: GPIOx->FIOPIN
************************************************************/
uint32_t GPIO_ReadData(LPC_GPIO_TypeDef* LPC_GPIOx)
{
    return ((LPC_GPIOx->FIOPIN));
}

/************************************************************
  Function   : GPIO_FIOxMaskCmd()
  Description: GPIO�ܽ���������
  Input      : 
  @param  GPIOx: GPIO������
    @arg GPIO0~4
  @param  GPIO_Pin: ��������
    @arg GPIO_Pin_0~31���������
    @arg GPIO_Pin_All �������������
  @param  NewState: �µ�״̬����
    @arg ENABLE: ���ùܽ�����
    @arg DISABLE: �����θùܽ�
  Output     : �ܽ����ε�״̬�仯
  Return     : None
  Others     : �����ļĴ���: GPIOx->FIOMASK
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
        if( NewState!= DISABLE ) //ENABLEʹ���ж�
        {
            if (intEdge == GPIOIntEdge_Rising)      // �������ж�
            {
                LPC_GPIOINT->IO0IntEnR |= GPIO_Pin_x; 
            }
            else if (intEdge == GPIOIntEdge_Falling)//�½����ж�
            {
                LPC_GPIOINT->IO0IntEnF |= GPIO_Pin_x;
            }
            else        
            {
                LPC_GPIOINT->IO0IntEnR |= GPIO_Pin_x;     //���½��ض��ж�
                LPC_GPIOINT->IO0IntEnF |= GPIO_Pin_x;
            }
        }
        else    //DISABLE �����ж�
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
        if( NewState!= DISABLE ) //ENABLEʹ���ж�
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
        else    //DISABLE �����ж�
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
    {   while(1);  }  // ע�⣺ֻ��GPIO0��GPIO2���жϹ��ܣ���ѡ������ͣ�ڴ˴�
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
            // else bitstatus = RESET �ѱ���ʼ��Ϊ��λ
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
            // else bitstatus = RESET �ѱ���ʼ��Ϊ��λ
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
    {   while(1);  }  // ע�⣺ֻ��GPIO0��GPIO2���жϹ��ܣ���ѡ������ͣ�ڴ˴�
    
    return (bitstatus);
}

/************************************************************
  Function   : GPIO_INTClear()
  Description: GPIO �ж���� IOxIntStatR and IOxStatF
  Input      :   
  @param  GPIOx: GPIO������
    @arg GPIO0 , GPIO2
  @param  GPIO_Pin: ��������
    @arg ��ΪGPIO0ʱ GPIO_Pin_0~30���������
    @arg ��ΪGPIO2ʱ GPIO_Pin_0~13���������
  Output     : None
  Return     : None
  Others     : IO0IntClr �� IO2IntClr ������Ϊ0ʱ��״̬���ı䣬�������ﲻ��λ����
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
    {   while(1);  }  // ע�⣺ֻ��GPIO0��GPIO2���жϹ��ܣ���ѡ������ͣ�ڴ˴�
}


/************************************************************
End of filename
************************************************************/
