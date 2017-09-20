#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef signed char s8;
typedef unsigned char u8;
typedef signed short int s16;
typedef unsigned short int u16;
typedef signed int s32;
typedef unsigned int u32;

#define	__DEBUG_FPOUT__		1
#ifdef __DEBUG_FPOUT__
FILE *fp;
#endif

#include "./inc/x1.h"
#include "./inc/xfront.h"
#include "./inc/xback.h"
#include "./inc/xleft.h"
#include "./inc/xright.h"
#include "./inc/DCT_COEF.h"
#include "./inc/HMK_COEF.h"
#include "./vc_fft_lib/cr2_fft_hy.h"

/*宏定义数据*/
#define		MEL_NUM		24		/*MEL滤波器个数*/
#define		MEL_NUM_HALF 12		/*MEL滤波器个数*1/2*/
#define		FS			8000	/*语音信号的采样频率*/
#define		SOUND_LEN	12000	/*录音时长drt = 1.5秒，序列长度为Fs*drt */
#define		NOISE_LEN	0.32*FS	/*噪声点数 0.32*FS=2560 */
#define		FRAME_SIZE	256		/*分帧的帧长*/
#define		FRAME_INC	128		/*分帧的帧移*/
#define		FRAME_NUM	92		/*语音的帧数*/
#define		NOISE_FRAME_NUM	19		/*噪音的帧数*/
#define		FRAME_N2	129		/*n2 = fix(frameSize/2)+1;*/

extern signed short int vcxn[];	//原始语音，固定识别语音长度，12000点
void VoicePreEmphisas(s16 *x,u16 len);
void VAD_AmpZer(const s16 *x,u16 len,u16 frenum);
void VoiceMFCC(const s16 *x,u16 frenum);
void VoiceDTW(const s16 rmfcc[][MEL_NUM],u16 rM,u32 *dtwDist);

typedef struct
{
    u16 strFre;		//起始帧
    u16 stopFre;	//结束帧
    u16 strTime;	//起始点
    u16 stopTime;	//结束点
    u16 ssfnum;		//有效语音帧总数
} VAD_TypeDef;
typedef struct
{
    u32 front;
    u32 back;
    u32 left;
    u32 right;
} DtwDist_TypeDef;

VAD_TypeDef vadResult;
DtwDist_TypeDef dtwResult;

u32 soundlen=0;
u16 frameNum =0;
//mfcc参数存储二维数组
s16 (* vmfcc)[MEL_NUM];	

int main()
{
    u32 temp;
    soundlen = sizeof(vcxn)/sizeof(vcxn[0]);
    frameNum = ((soundlen-FRAME_SIZE)/FRAME_INC);
    printf("soundlen = %d\tframeNum=%d\n",soundlen,frameNum);

    VoicePreEmphisas(vcxn,soundlen);      //预加重
    VAD_AmpZer(vcxn,soundlen,frameNum);   //短时平均幅度和短时过门限率的端点检测
    printf("strFre = %d\tstopFre = %d\n",vadResult.strFre,vadResult.stopFre);
    printf("strTime = %d\tstopTime = %d\n",vadResult.strTime,vadResult.stopTime);
    vadResult.ssfnum = vadResult.stopFre-vadResult.strFre+1;

    // <frenum x MEL_NUM> free(vmfcc)
    vmfcc=(s16 (*)[MEL_NUM]) malloc(vadResult.ssfnum*MEL_NUM*sizeof(s16));  //动态开辟内存
    VoiceMFCC(vcxn,vadResult.ssfnum);       //提取MFCC参数
    VoiceDTW(XFORNT,21,&dtwResult.front);   //DTW匹配
    VoiceDTW(XBACK,10,&dtwResult.back);
    VoiceDTW(XLEFT,17,&dtwResult.left);
    VoiceDTW(XRIGHT,11,&dtwResult.right);
    free(vmfcc);       //释放                   

	printf("dtwResult.front = %d\n",dtwResult.front);
	printf("dtwResult.back = %d\n",dtwResult.back);
	printf("dtwResult.left = %d\n",dtwResult.left);
	printf("dtwResult.right = %d\n",dtwResult.right);
    
    temp = dtwResult.front;
    if(dtwResult.back<temp)
        temp = dtwResult.back;
    if(dtwResult.left<temp)
        temp = dtwResult.left;
    if(dtwResult.right<temp)
        temp = dtwResult.right;

    if(temp == dtwResult.front)
        printf("识别结果是“前”");
    else if(temp == dtwResult.back)
        printf("识别结果是“后”");
    else if(temp == dtwResult.left)
        printf("识别结果是“左”");
    else
        printf("识别结果是“右”");
    
    return 0;
}

void VoiceMFCC(const s16 *x,u16 frenum)
{
    u16 i,j,k;
    u16 tempA,tempB;
    u32 tt[MEL_NUM]= {0,0,};
    s32 c1[MEL_NUM_HALF]= {0,};
    s16 (*dtmfcc)[MEL_NUM_HALF]; //一阶差分mfcc
    union Complex_TypeDef fftBuff[FRAME_SIZE];

    // <frenum x MEL_NUM_HALF> free(vmfcc)
    dtmfcc = (s16 (*)[MEL_NUM_HALF]) malloc(frenum*MEL_NUM_HALF*sizeof(s16));

    for(i=0; i<frenum; i++)
    {
        tempA = FRAME_INC*(vadResult.strFre+i);
        for(j=0; j<FRAME_SIZE; j++)
        {
            tempB = (x[tempA+j]*WIN_HAMM_COEF[j])>>5; //hamming window
            fftBuff[j].m_Real= tempB;
            fftBuff[j].m_Image = 0;
        }
        cr2_fft256_hy(fftBuff);		//加窗后的数据做FFT
        for(j=0; j<FRAME_N2; j++)	//计算能量谱
        {
            fftBuff[j].u_cpl = fftBuff[j].m_Real*fftBuff[j].m_Real+fftBuff[j].m_Image*fftBuff[j].m_Image;
        }
        tempA =0;
        for(j=0; j<MEL_NUM; j++)
        {
            tt[j]=0;
            for(k=0; k<FRAME_N2; k++)
            {
                //稀疏矩阵遍历
                if(k==HMK_COEF[tempA].column&&j==HMK_COEF[tempA].row)
                {
                    tt[j] += (HMK_COEF[tempA].dat*fftBuff[k].u_cpl);
                    tempA++;
                }
            }
            tt[j] = (u32)log(tt[j]);
        }
        for(j=0; j<MEL_NUM_HALF; j++)
        {
            c1[j]=0;
            for(k=0; k<MEL_NUM; k++)
            {
                c1[j] += (DCT_COEF[j][k]*tt[k]);
            }
            vmfcc[i][j]=(c1[j]*W_COEF[j])>>8;
        }
    }
#ifdef __DEBUG_FPOUT__
    fp = fopen("./txtout/mfcc.txt","w+");	//将数据输出到文件
    fprintf(fp,"标准MFCC参数\nmfcc[%d][%d] = {\n",frenum,MEL_NUM_HALF);
    for(i=0; i<frenum; i++)
    {
        for(j=0; j<MEL_NUM_HALF; j++)
        {
            fprintf(fp,"%10d\t", vmfcc[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"}");
    fclose(fp);
#endif
    for(i=2; i<frenum-2; i++)
    {
        for(j=0; j<MEL_NUM_HALF; j++)
        {
            dtmfcc[i][j] = -2*vmfcc[i-2][j]-vmfcc[i-1][j]+vmfcc[i+1][j]+2*vmfcc[i+2][j];
            dtmfcc[i][j] = dtmfcc[i][j]/3;
            vmfcc[i][j+MEL_NUM_HALF] = dtmfcc[i][j];
        }
    }
    for(i=2; i<frenum-2; i++)
    {
        tempA=i-2;
        for(j=0; j<MEL_NUM; j++)
        {
            vmfcc[tempA][j] = vmfcc[i][j]; //vmfcc <(frenum-4) x MEL_NUM>
        }
    }
#ifdef __DEBUG_FPOUT__
    fp = fopen("./txtout/vmfcc.txt","w+");
    fprintf(fp,"差分MFCC参数\nvmfcc[%d][%d] = {\n",frenum-4,MEL_NUM);
    for(i=0; i<frenum-4; i++)
    {
        for(j=0; j<MEL_NUM; j++)
        {
            fprintf(fp,"%10d\t", vmfcc[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"}");
    fclose(fp);
#endif
    free(dtmfcc);
}

void VoiceDTW(const s16 rmfcc[][MEL_NUM],u16 rM,u32 *dtwDist)
{
    u16 n,m,k,tN;
    u32 (*d)[24];
    u32 (*D)[24];
    u32 dmin=0;
    tN = vadResult.ssfnum-4;
    d = (u32 (*)[24])malloc(tN*24*sizeof(u32)); //free
    D = (u32 (*)[24])malloc(tN*24*sizeof(u32)); //free
    for(n=0; n< tN; n++)
    {
        for(m=0; m< rM; m++)
        {
            d[n][m] = 0;
            for(k=0; k<MEL_NUM; k++)
            {
                d[n][m] += ( abs(vmfcc[n][k]-rmfcc[m][k]) );//两者之间的距离
            }
        }
    }
    D[0][0] = d[0][0];
    for(n=1; n< tN; n++)
    {
        D[n][0] = d[n][0]+D[n-1][0];
    }
    for(m=1; m<rM; m++)
    {
        D[0][m] = d[0][m]+D[0][m-1];
    }
    for(n=1; n<tN; n++)
    {
        for(m=1; m<rM; m++)
        {
            dmin = D[n-1][m];
            if(D[n-1][m-1]<dmin)
                dmin=D[n-1][m-1];
            if(D[n][m-1]<dmin)
                dmin=D[n][m-1];
            D[n][m] = d[n][m]+dmin;
        }
    }
    *dtwDist = D[tN-1][rM-1];
//#ifdef __DEBUG_FPOUT__
//	fp = fopen("./txtout/vmfcc.txt","a+");
//	fprintf(fp,"差分MFCC参数\nvmfcc[%d][%d] = {\n",vadResult.ssfnum-4,MEL_NUM);
//    for(i=0; i<vadResult.ssfnum-4; i++)
//	{
//        for(j=0; j<MEL_NUM; j++)
//		{
//            fprintf(fp,"%10d\t", vmfcc[i][j]);
//        }
//        fprintf(fp,"\n");
//    }
//    fprintf(fp,"};\n");
//	fclose(fp);
//#endif
    free(d);
    free(D);
}
void VAD_AmpZer(const s16 *x,u16 len,u16 frenum)
{
    u16 i,j;
    s32 temp,tempA,tempB;
    u32 *Mn,*Zcr;
    u32 MnMaxVal=0,MnMaxFrame=0,ZcrMaxVal = 0;
    u32 Mn1,Mn2,Zcr3;

    Mn = (u32 *)malloc(frenum*sizeof(u32));  //开辟空间要free(Mn)
    Zcr = (u32 *)malloc(frenum*sizeof(u32)); //开辟空间要free(Zcr)
    if(Mn==NULL||Zcr==NULL)
    {
        printf("Mn or Zcr malloc Error!\n");
        return;
    }
    for(i=0; i<frenum; i++)
    {
        Mn[i] = 0;
        Zcr[i]=0;
        tempA = FRAME_INC*i;
        for(j=0; j<FRAME_SIZE-1; j++)
        {
            tempB = tempA+j;
            Mn[i] += abs(x[tempB]);  //短时平均幅度
            if( (x[tempB]^x[tempB+1])&0x8000 )
            {
                if(abs(x[tempB]-x[tempB+1])>10)
                {
                    Zcr[i]++;		//短时平均过零率
                }
            }
        }
        Mn[i] += abs(x[tempA+FRAME_SIZE-1]); //加一帧中的最后一个数据
        if(Mn[i]>MnMaxVal)
        {
            MnMaxVal = Mn[i];	//找到最大的Mn
            MnMaxFrame = i;		//记录下最大的frame
        }
        if(Zcr[i]>ZcrMaxVal)
        {
            ZcrMaxVal = Zcr[i];	//找到最大的Zcr
        }
    }
    Mn1 = MnMaxVal>>1; // 1/2 门限值
    Mn2 = MnMaxVal>>2; // 1/4
    Zcr3 = ZcrMaxVal>>4; //1/8

    for(i=MnMaxFrame; i>0; i--)
    {
        if(Mn[i]>Mn1)
            tempA=i;  //tempA
    }
    for(i=MnMaxFrame; i<frenum; i++)
    {
        if(Mn[i]>Mn1)
            tempB=i;  //tempB
    }
    for(i=tempA; i>0; i--)
    {
        if(Mn[i]>Mn2)
            tempA=i;
    }
    for(i=tempB; i<frenum; i++)
    {
        if(Mn[i]>Mn2)
            tempB=i;
    }
    if(tempA!=0)
    {
        for(i=tempA; i>0; i--)
        {
            if(Zcr[i]>Zcr3)
                vadResult.strFre=i;
        }
    }
    else
    {
        vadResult.strFre=0;//已经到达第0帧
    }
    if(tempB!=frenum)
    {
        for(i=tempB; i<frenum; i++)
        {
            if(Zcr[i]>Zcr3)
                vadResult.stopFre=i;
        }
    }
    else//已经到达最后一帧 frenum-1
    {
        vadResult.stopFre = frenum-1;
    }
    //vadResult.strFre = tempA;
    //vadResult.stopFre = tempB;
    vadResult.strTime = vadResult.strFre*FRAME_INC; //计算对应的起始点
    vadResult.stopTime = (vadResult.stopFre+1)*FRAME_INC-1; //计算对应的结束点
#ifdef __DEBUG_FPOUT__
    fp = fopen("./txtout/VAD_Mn.txt","w+");	//将数据输出到文件
    fprintf(fp,"Mn[%d] = {\n",frenum);
    temp=0;
    for(i=0; i<frenum; i++)
    {
        temp++;		//换行计数
        fprintf(fp,"%6d,",Mn[i]);
        if(temp/10)
        {
            temp=0;
            fprintf(fp,"\n");
        }
    }
    fclose(fp);
    fp = fopen("./txtout/VAD_Zcr.txt","w+");	//将数据输出到文件
//    fprintf(fp,"ok!\n");
    fprintf(fp,"Zcr[%d] = {\n",frenum);
    temp=0;
    for(i=0; i<frenum; i++)
    {
        temp++;		//换行计数
        fprintf(fp,"%6d,",Zcr[i]);
        if(temp/10)
        {
            temp=0;
            fprintf(fp,"\n");
        }
    }
    fclose(fp);
#endif
    free(Mn);	//
    free(Zcr);	//!!
}
//预加重函数
//soundlen = sizeof(vcxn)/sizeof(vcxn[0]);
//VoicePreEmphisas(vcxn,soundlen);
//
void VoicePreEmphisas(s16 *x,u16 len)
{
    u16 i,temp;
    s16 ftbuff[2]= {0};
    ftbuff[1] = x[0];
    for(i=1; i<len; i++)
    {
        ftbuff[0]=ftbuff[1];
        // 120/128=0.9375 有符号数右移位依赖于机器
        ftbuff[1]=(120*x[i-1])>>7;
        ftbuff[1]=x[i]-ftbuff[1];
        x[i-1]=ftbuff[0];
    }
    x[len-1]=ftbuff[1];
#ifdef __DEBUG_FPOUT__
    /*打开文件*/
    fp = fopen("./txtout/PreEmphasis.txt","w+");	//将数据输出到文件
    fprintf(fp,"x[%d] = {\n",len);
    temp=0;
    for(i=0; i<len; i++)
    {
        temp++;		//换行计数
        fprintf(fp,"%6d,",x[i]);
        if(temp/10)
        {
            temp=0;
            fprintf(fp,"\n");
        }
    }
    fclose(fp);
#endif
}

