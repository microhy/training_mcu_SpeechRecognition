function  hyFlag= hy_OutMatrix_MxN(filename,matrix_MxN)
%%
% Input:
%      matrix_MxN ---- 输入的 MxN 矩阵
% 
% Output:
%      hyFlag ---- 函数执行完成标志 '0'未完成;'1'完成
%                     
% Examples of use:
% (a)   bank = melbankm(P,frameSize,fs,0,0.5,'t'); 
%       bank = full(bank);
%       bank = bank/max(bank(:));   %幅值归一化，方便定标
%       hmkcoef = int16(bank*(2^15-1)); %归一化后再定标
%       hy_OutMatrix2X2(bank);      %使用本函数前先将数据归一化及定标
%
%       ∴固定了输出格式为有符号数短整型
hyFlag = 0;
[m n] = size(matrix_MxN);   % m行 n列
fid = fopen(filename,'w+'); %写入文件路径
fprintf(fid,'const signed short int %s[%d][%d]={\n',filename,m,n);
%matrix_MxN = int16(matrix_MxN);    %%%%%%%%
for i=1:m
    fprintf(fid,'{');
    for j=1:n-1
        fprintf(fid,'%6d,',matrix_MxN(i,j)); %输出格式为6位的十进制整数
    end
    fprintf(fid,'%6d},\n',matrix_MxN(i,n));
end
fprintf(fid,'};');
fclose(fid);
hyFlag = 1;
end

