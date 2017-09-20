#ifndef __CR2_FFT_HY_H
#define __CR2_FFT_HY_H

#ifdef __cplusplus
    extern "C" {
#endif 

#define     NPOINT_128    128    /*NPOINT*/
#define     M_128         7      /* 2^M = NPOINT*/
#define     LH_128        64
#define     N1_128        127
        
#define     NPOINT_256    256    /*NPOINT*/
#define     M_256         8      /* 2^M = NPOINT*/
#define     LH_256        128
#define     N1_256        255

#pragma anon_unions
union Complex_TypeDef
{ 
    unsigned int u_cpl;
    struct{
    signed short int m_Image;
    signed short int m_Real;
    };
};
   
union FFTWNK_TypeDef
{
    signed int u_wnk;
    struct{
        signed short int m_Isin;
        signed short int m_Rcos;
    };
};
/**/
void cr2_fft128_hy(union Complex_TypeDef *xn);
void cr2_fft256_hy(union Complex_TypeDef *xn);


#ifdef __cplusplus
}
#endif

#endif
/************************************************************
End of __CR2_FFT_HY_H
************************************************************/
