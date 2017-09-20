/************************************************************
    Copyright (C), 2013, Hnist FS_GCZX.
    
    FileName: .c
    Author:     Version :       Date:
    Description:
    Function List: 
    1.
    History:
    <author>    <time>      <version >      <desc>
    
************************************************************/
#include"../inc/lpc_A7105.h"
/* Private define ------------------------------------------------------------*/
//ID code
#define ID_0    0X54
#define ID_1    0X75
#define ID_2    0XCA
#define ID_3    0x21
/* Private macro -------------------------------------------------------------*/
#define _TR_NUM_   8
/* Private variables ---------------------------------------------------------*/
const uint8_t PN9_Tab[]= {
    0xFF,0x83,0xDF,0x17,0x32,0x09,0x4E,0xD1,
    0xE7,0xCD,0x8A,0x91,0xC6,0xD5,0xC4,0xC4,
    0x40,0x21,0x18,0x4E,0x55,0x86,0xF4,0xDC,
    0x8A,0x15,0xA7,0xEC,0x92,0xDF,0x93,0x53,
    0x30,0x18,0xCA,0x34,0xBF,0xA2,0xC7,0x59,
    0x67,0x8F,0xBA,0x0D,0x6D,0xD8,0x2D,0x7D,
    0x54,0x0A,0x57,0x97,0x70,0x39,0xD2,0x7A,
    0xEA,0x24,0x33,0x85,0xED,0x9A,0x1D,0xE0
};  // This table are 64bytes PN9 pseudo random code.
const uint16_t A7105Config[]= {
    0x00, //RESET register, only reset, not use on config
    0x42, //MODE register,
    0x00, //CALIBRATION register,only read, not use on config
    0x7F, //FIFO1 register,     128 bytes
    0xC0, //FIFO2 register,     FPM[1:0]=[11]
    0x00, //FIFO register,  for fifo read/write
    0x00, //IDDATA register,    for idcode
    0x00, //RCOSC1 register,
    0x00, //RCOSC2 register,
    0x00, //RCOSC3 register,
    0x12, //CKO register,
    0x01, //GIO1 register
    0x21, //GIO2 register,
    0x05, //CLOCK register,
    0x09, //DATARATE register,  datarate=50Kbps
    0x50, //PLL1 register,
    0x9E, //PLL2 register,  RFbase 2400MHz
    0x4B, //PLL3 register,
    0x00, //PLL4 register,
    0x02, //PLL5 register,
    0x16, //TX1 register,
    0x2B, //TX2 register,
    0x12, //DELAY1 register,
    0x00, //DELAY2 register,
    0x62, //RX register,
    0x80, //RXGAIN1 register,
    0x80, //RXGAIN2 register,
    0x00, //RXGAIN3 register,
    0x0A, //RXGAIN4 register,
    0x32, //RSSI register,
    0xC3, //ADC register,
    0x07, //CODE1 register,
    0x17, //CODE2 register,
    0x00, //CODE3 register,
    0x00, //IFCAL1 register,
    0x00, //IFCAL2 register,  only read
    0x00, //VCOCCAL register,
    0x00, //VCOCAL1 register,
    0x3A, //VCOCAL2 register,
    0x00, //BATTERY register,
    0x17, //TXTEST register,
    0x27, //RXDEM1 register,
    0x80, //RXDEM2 register,
    0x03, //CPC register,
    0x01, //CRYSTAL register,
    0x45, //PLLTEST register,
    0x18, //VCOTEST1 register,
    0x00, //VCOTEST2 register,
    0x01, //IFAT register,
    0x0F, //RSCALE register,
    0x00  //FILTERTEST
};
/* Private function prototypes -----------------------------------------------*/
static void A7105_GPIO_Init(void);
static void A7105_Cal(void);
static void A7105_WriteID(void);
static void SelVCOBand(uint8_t vb1, uint8_t vb2);
static void A7105_Config(void);

/* Add your application code here
     */
//A7105_InitRF();
void A7105_InitRF(void)
{
    A7105_GPIO_Init();
    A7105_WriteREG(MODE_REG,0x00); //reset rf
    A7105_WriteID();
    A7105_Config();
    A7105_StrobeCmd(CMD_STBY);
}

void A7105_WriteREG(uint8_t addr,uint8_t wdat)
{
    uint8_t i;
    A7105_SCS_0;  //serial enable
    for(i=0; i<8; ++i) {
        if(addr&0x80)  //MSB
            A7105_SDIO_1;
        else
            A7105_SDIO_0;
        A7105_SCK_1;
        addr <<= 1;
        A7105_SCK_0;
    }
    for(i=0; i<8; ++i) {
        if(wdat&0x80)  //MSB
            A7105_SDIO_1;
        else
            A7105_SDIO_0;
        A7105_SCK_1;
        wdat <<= 1;
        A7105_SCK_0;
    }
    A7105_SCS_1; //serial disable
}

uint8_t A7105_ReadREG(uint8_t addr)
{
    uint8_t i,Rdat=0x00;
    A7105_SCS_0;  //serial enable
    for(i=0; i<8; ++i) {
        if(addr&0x80)
            A7105_SDIO_1;
        else
            A7105_SDIO_0;
        A7105_SCK_1;
        addr <<= 1;
        A7105_SCK_0;
    }
    A7105_SDIO_IN();
    for(i=0; i<8; ++i) {
        Rdat <<= 1;
        if(A7105_Read_SDIO)
            Rdat |=0x01;
//    else
//      Rdat |=0x00;
        A7105_SCK_1;
        A7105_SCK_0;
    }
    A7105_SCS_1; //serial disable
    A7105_SDIO_OUT();
    return(Rdat);
}

void A7105_WriteFIFO(void)
{
    uint8_t i;
    A7105_SCS_0;
    A7105_SendByte(FIFO_REG); //send address 0x05, bit cmd=0, r/~w=0
    for(i=0; i <_TR_NUM_; ++i)
        A7105_SendByte(PN9_Tab[i]);
    A7105_SCS_1;
}

//A7105_SendByte(FIFO_REG);
void A7105_SendByte(uint8_t byte)
{
    uint8_t i;
    for(i=0; i<8; ++i) {
        if(byte&0x80)
            A7105_SDIO_1;
        else
            A7105_SDIO_0;
        A7105_SCK_1;
        byte <<= 1;
        A7105_SCK_0;
    }
}

uint8_t A7105_ReadByte(void)
{
    uint8_t i,Rdat = 0x00;
    A7105_SDIO_IN();
    for(i=0; i<8; ++i) {
        Rdat <<= 1;
        if(A7105_Read_SDIO)
            Rdat |=0x01;
//    else
//      Rdat |=0x00;
        A7105_SCK_1;
        A7105_SCK_0;
    }
    A7105_SDIO_OUT();
    return(Rdat);
}

/*******************************************************************************
* Function Name  : A7105_StrobeCmd(CMD_TX);
* Description    : 发送4个位的StrobeCmd存储器命令
* Input          : scmd -- StrobeCmd命令字
* Output         : None
* Return         : None
*******************************************************************************/
void A7105_StrobeCmd(uint8_t scmd)
{
    A7105_SCS_0;  //serial enable
    if(scmd&0x80)
        A7105_SDIO_1;
    else
        A7105_SDIO_0;
    A7105_SCK_1;
    A7105_SCK_0;
    if(scmd&0x40)
        A7105_SDIO_1;
    else
        A7105_SDIO_0;
    A7105_SCK_1;
    A7105_SCK_0;
    if(scmd&0x20)
        A7105_SDIO_1;
    else
        A7105_SDIO_0;
    A7105_SCK_1;
    A7105_SCK_0;
    if(scmd&0x10)
        A7105_SDIO_1;
    else
        A7105_SDIO_0;
    A7105_SCK_1;
    A7105_SCK_0;
    A7105_SCS_1; //serial disable
}

static void A7105_GPIO_Init(void)
{
    PORTA7105->FIODIR |= (A7105_SCS|A7105_SCK|A7105_SDIO);//输出方向
    PORTA7105->FIODIR &=~(A7105_GPIO1);  //输入方向
    A7105_SCS_1;  //dis
    A7105_SCK_0;
    A7105_SDIO_1;
}

static void A7105_WriteID(void)
{
    uint8_t rid[4];
    A7105_SCS_0;    //serial enable
    A7105_SendByte(IDCODE_REG);
    A7105_SendByte(ID_0);
    A7105_SendByte(ID_1);
    A7105_SendByte(ID_2);
    A7105_SendByte(ID_3);
    A7105_SCS_1;
    A7105_SCS_0;
    A7105_SendByte((IDCODE_REG|0x40)); //read reg
    rid[0] = A7105_ReadByte();
    rid[1] = A7105_ReadByte();
    rid[2] = A7105_ReadByte();
    rid[3] = A7105_ReadByte();
    A7105_SCS_1; // debug breakpoint check idcode
}
static void A7105_Config(void)
{
    uint8_t i;
    //0x00 mode register, for reset
    //0x05 fifo data register
    //0x06 id code register
    //0x23 IF calibration II, only read
    //0x32 filter test register
    for (i=0x01; i<=0x04; i++)
        A7105_WriteREG(i, A7105Config[i]);

    for (i=0x07; i<=0x22; i++)
        A7105_WriteREG(i, A7105Config[i]);

    for (i=0x24; i<=0x31; i++)
        A7105_WriteREG(i, A7105Config[i]);
}

static void A7105_Cal(void)
{
    uint8_t tmp;
    uint8_t fb,fbcf;
    uint8_t vb1,vbcf1,dvt1;
    uint8_t vb2,vbcf2,dvt2;
    A7105_StrobeCmd(CMD_STBY);//calibration @STB state
    //calibration IF procedure
    A7105_WriteREG(CALIBRATION_REG, 0x01);
    do {
        tmp = A7105_ReadREG(CALIBRATION_REG);
    } while(tmp&0x01);
    //for check
    tmp = A7105_ReadREG(IFCAL1_REG);
    fb = tmp & 0x0F;
    fbcf = (tmp >>4) & 0x01;

    if (fbcf ==1) { //Err_State();
        while(1);
    }
    //calibration vco procedure
    A7105_WriteREG(VCOCCAL_REG, 0x13); //manual VCOC=3
    //band
    A7105_WriteREG(VCOCAL2_REG, 0x3B); //VTL=3, VTH=7
    
    A7105_ConfigFreq(ch_2400MHz);      //setting 2400MHz
    A7105_WriteREG(CALIBRATION_REG, 0x02);
    do {
        tmp = A7105_ReadREG(CALIBRATION_REG);
    } while(tmp&0x02);
    tmp = A7105_ReadREG(VCOCAL1_REG);//读VCOCAL1_REG寄存器
    vb1 = tmp & 0x07; //取低3位
    // VB2，1，0：VCO back自動校準值，调试时可观察是否与设定值相同
    vbcf1 = (tmp >> 3) & 0x01; //取BIT4
    // VBCF: 0 校准成功，1 校准失败
    dvt1 = (tmp >> 4) & 0x03; //取BIT4，5
    // DVT0，1：DVT值输出
    A7105_ConfigFreq(ch_2480MHz);             //setting 2480MHz
    A7105_WriteREG(CALIBRATION_REG, 0x02);
    do {
        tmp = A7105_ReadREG(CALIBRATION_REG);
    } while(tmp&0x02);
    tmp = A7105_ReadREG(VCOCAL1_REG);
    vb2 = tmp & 0x07;
    vbcf2 = (tmp >> 3) & 0x01;
    dvt2 = (tmp >> 4) & 0x03;
    SelVCOBand(vb1, vb2);
    if (vbcf1==1 && vbcf2==1) { //Err_State();
        while(1);
    }
}

static void SelVCOBand(uint8_t vb1, uint8_t vb2)
{
    uint8_t diff1,diff2;

    if (vb1>=4)
        diff1 = vb1-4;
    else
        diff1 = 4-vb1;

    if (vb2>=4)
        diff2 = vb2-4;
    else
        diff2 = 4-vb2;

    if (diff1 == diff2 || diff1 > diff2)
        A7105_WriteREG(VCOCAL1_REG, (vb1 | 0x08));//manual setting vb1 value
    else
        A7105_WriteREG(VCOCAL1_REG, (vb2 | 0x08));//manual setting vb2 value
}
