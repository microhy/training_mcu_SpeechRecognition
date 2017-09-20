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

/*�궨������*/
#define        MEL_NUM        24        /*MEL�˲�������*/
#define        MEL_NUM_HALF 12        /*MEL�˲�������*1/2*/
#define        FS            8000    /*�����źŵĲ���Ƶ��*/
#define        SOUND_LEN    12000    /*¼��ʱ��drt = 1.5�룬���г���ΪFs*drt */
#define        NOISE_LEN    0.32*FS    /*�������� 0.32*FS=2560 */
#define        FRAME_SIZE    256        /*��֡��֡��*/
#define        FRAME_INC    128        /*��֡��֡��*/
#define        FRAME_NUM    92        /*������֡��*/
#define        NOISE_FRAME_NUM    19        /*������֡��*/
#define        FRAME_N2    129        /*n2 = fix(frameSize/2)+1;*/

typedef struct
{
    u16 strFre;		//��ʼ֡
    u16 stopFre;	//����֡
    u16 strTime;	//��ʼ��
    u16 stopTime;	//������
    u16 ssfnum;		//��Ч����֡����
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
