function ccc = mymfcc_m(x,fs,p,frameSize,inc)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

%%
%系数:将MEL滤波器的频响系数导出
%调用，在0-0.5区间设计24个mel滤波器，用三角窗窗函数
bank = mymelbankm(p,frameSize,fs,0,0.5,'t'); 
bank = full(bank);
bank = bank/max(bank(:));   %幅值归一化，方便定标  bank=0~1
if(find(bank<0))
    HMK_COEF = int8(bank*(2^7-1));  %disp('归一化后bank范围-1~1,int8定标bank*(2^7-1)')
else
    HMK_COEF = uint8(bank*(2^8-1));%disp('归一化后bank范围0~1,uint8定标bank*(2^8-1)')
end
hy_OutSparseMatrix('.\txtout\HMK_COEF.txt',HMK_COEF);
bank = double(HMK_COEF);%%%
%%
%%系数:计算DCT系数
P = p; P2 = P/2;  %Mel滤波器的个数为p
p2 = p/2;
for k=1:P2;
    n = 0:P-1;
    dctcoef(k,:) = cos((2*n+1)*k*pi/(2*P));  % cosx = -1~1
end
if(find(dctcoef<0))
    DCT_COEF = int8(dctcoef*(2^7-1));   %disp('归一化后dctcoef范围-1~1,int8定标dctcoef*(2^7-1)')
else
    DCT_COEF = uint8(dctcoef*(2^8-1));  %disp('归一化后dctcoef范围0~1,uint8定标dctcoef*(2^8-1)')
end
hy_OutMatrix_MxN('.\txtout\DCT_COEF.txt',DCT_COEF);
dctcoef = double(DCT_COEF);%%%
%%
%系数:归一化倒谱提升
w = 1+6*sin(pi*[1:P2]./P2); %均为正值
w = w/max(w);  
W_COEF = uint8(w*(2^8-1));hy_OutMatrix1Xn('.\txtout\W_COEF.txt',W_COEF);
w = double(W_COEF);%%%
%预加重滤波
xx = double(x);
%xx = filter([1 -0.9375],1,xx);
xx = int16(xx);hy_OutMatrix1Xn('.\txtout\xx.txt',xx);
xx = enframe(xx, frameSize, inc);   %%%%分帧
n2 = fix(frameSize/2)+1;
%%
%计算每帧的MFCC参数
win_hamm = hamming(frameSize);  %  0<=win_hamm<=1
WIN_HAMM_COEF = uint8(win_hamm*255);hy_OutMatrix1Xn('.\txtout\WIN_HAMM_COEF.txt',WIN_HAMM_COEF);
win_hamm = double(WIN_HAMM_COEF);
s = zeros(size(xx));
t = zeros(size(xx));
for i=1:size(xx,1); %取行数（帧数）
    s(i,:) = int16((xx(i,:)'.*win_hamm(:))/32);
    s(i,:) = double(s(i,:));
    t(i,:) = abs(fft(s(i,:))/frameSize);
    t(i,:) = t(i,:).^2;       %由于下面的计算只要t(1:n2),故这里计算能量时可以只算1:n2  
    c1(i,:) = log(bank*t(i,1:n2)');
    c2(i,:) = (dctcoef*c1(i,:)')';
    m(i,:) = c2(i,:).*w;
end
%%
%%%%差分系数
dtm = zeros(size(m));  %dtm<帧数xP2>的零矩阵
for i=3:size(m,1)-2
    for j=1:P2
        dtm(i,j)=-2*m(i-2,j)-m(i-1,j)+m(i+1,j)+2*m(i+2,j);
        dtm(i,j)=dtm(i,j)/3;
    end
end
ccc = [m dtm];
ccc = ccc(3:size(m,1)-2,:);
ccc = ccc/2^8;
end

