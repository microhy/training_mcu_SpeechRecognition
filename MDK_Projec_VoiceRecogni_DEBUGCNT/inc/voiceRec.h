#ifndef __VOICEREC_H
#define __VOICEREC_H

#ifdef __cplusplus
    extern "C" {
#endif

typedef signed char s8;
typedef unsigned char u8;
typedef signed short int s16;
typedef unsigned short int u16;
typedef signed int s32;
typedef unsigned int u32;

/*宏定义数据*/
#define        MEL_NUM        24        /*MEL滤波器个数*/
#define        MEL_NUM_HALF 12        /*MEL滤波器个数*1/2*/
#define        FS            8000    /*语音信号的采样频率*/
#define        SOUND_LEN    12000    /*录音时长drt = 1.5秒，序列长度为Fs*drt */
#define        NOISE_LEN    0.32*FS    /*噪声点数 0.32*FS=2560 */
#define        FRAME_SIZE    256        /*分帧的帧长*/
#define        FRAME_INC    128        /*分帧的帧移*/
#define        FRAME_NUM    92        /*语音的帧数*/
#define        NOISE_FRAME_NUM    19        /*噪音的帧数*/
#define        FRAME_N2    129        /*n2 = fix(frameSize/2)+1;*/

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

void VoiceRec_FBLR(s16 *vcxn,u32 soundlen);
void VoiceDTW(const s16 rmfcc[][MEL_NUM],u16 rM,u32 *dtwDist);
void VoiceMFCC(const s16 *x,u16 frenum);
void VAD_AmpZer(const s16 *x,u16 len,u16 frenum);
void VoicePreEmphisas(s16 *x,u16 len);

#ifdef __cplusplus
}
#endif

#endif
