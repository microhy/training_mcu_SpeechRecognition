#include"cr2_fft_hy.h"
#include"cr2_fft_hyTAB.h"

/*自定义函数描述区*/
void cr2_fft128_hy(union Complex_TypeDef *xn)
{
    unsigned int i,j,k,b,p,t;
    union Complex_TypeDef tmpclx;
    union Complex_TypeDef tmpclx2;
    union FFTWNK_TypeDef tmpwnk;
    j = LH_128;
    
    for(i=1; i<N1_128; ++i )
    {
        if(i<j)
        {
            tmpclx = xn[j];
            xn[j] = xn[i];
            xn[i] = tmpclx;
        }
        k = LH_128;
        while( k<=j )
        {
            j = j-k;
            k >>= 1;
        }
        j = j+k;
    }
    for(i=1; i<=M_128; ++i)  //
    {
        b = POW_L_1[i]; //2^i-1 查表实现
        t = b<<1;       //2^i
        for(j=0; j< b; ++j) //
        {    
            p = (NPOINT_128>>i)*j;// 2^M-i= NPOINT_128>>i
            //p = p*j;
            tmpwnk = WNK_128[p];
            for(k=j; k<= N1_128; k=k+t)
            {   //0x4000=16384
                tmpclx2.m_Real  = (xn[k+b].m_Real*tmpwnk.m_Rcos + xn[k+b].m_Image*tmpwnk.m_Isin)/0x4000; 
                tmpclx2.m_Image = (xn[k+b].m_Image*tmpwnk.m_Rcos - xn[k+b].m_Real*tmpwnk.m_Isin)/0x4000;
                tmpclx.m_Real  = (xn[k].m_Real + tmpclx2.m_Real)/2;     //实部归一化
                tmpclx.m_Image = (xn[k].m_Image + tmpclx2.m_Image)/2;   //虚部归一化
                
                xn[k+b].m_Real  = (xn[k].m_Real - tmpclx2.m_Real)/2;    //实部归一化
                xn[k+b].m_Image = (xn[k].m_Image - tmpclx2.m_Image)/2;  //虚部归一化
                xn[k] = tmpclx;
            }
        }
    }
}


void cr2_fft256_hy(union Complex_TypeDef *xn)
{
    unsigned int i,j,k,b,p,t;
    union Complex_TypeDef tmpclx;
    union Complex_TypeDef tmpclx2;
    union FFTWNK_TypeDef tmpwnk;
    j = LH_256;
    
    for(i=1; i<N1_256; ++i )
    {
        if(i<j)
        {
            tmpclx = xn[j];
            xn[j] = xn[i];
            xn[i] = tmpclx;
        }
        k = LH_256;
        while( k<=j )
        {
            j = j-k;
            k >>= 1;
        }
        j = j+k;
    }
    for(i=1; i<=M_256; ++i)  //
    {
        b = POW_L_1[i]; //2^i-1 查表实现
        t = b<<1;       //2^i
        for(j=0; j< b; ++j) //
        {    
            p = (NPOINT_256>>i)*j;// 2^M-i= NPOINT_256>>i
            //p = p*j;
            tmpwnk = WNK_256[p];
            for(k=j; k<= N1_256; k=k+t)
            {                                                   //0x4000=16384
                tmpclx2.m_Real  = (xn[k+b].m_Real*tmpwnk.m_Rcos + xn[k+b].m_Image*tmpwnk.m_Isin)/0x4000; 
                tmpclx2.m_Image = (xn[k+b].m_Image*tmpwnk.m_Rcos - xn[k+b].m_Real*tmpwnk.m_Isin)/0x4000;
                tmpclx.m_Real  = (xn[k].m_Real + tmpclx2.m_Real)/2;     //实部归一化
                tmpclx.m_Image = (xn[k].m_Image + tmpclx2.m_Image)/2;   //虚部归一化
                
                xn[k+b].m_Real  = (xn[k].m_Real - tmpclx2.m_Real)/2;    //实部归一化
                xn[k+b].m_Image = (xn[k].m_Image - tmpclx2.m_Image)/2;  //虚部归一化
                xn[k] = tmpclx;
            }
        }
    }
}
