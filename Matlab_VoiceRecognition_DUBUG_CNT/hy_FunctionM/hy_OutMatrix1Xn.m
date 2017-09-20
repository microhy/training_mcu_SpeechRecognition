function  hyFlag= hy_OutMatrix1Xn(filename,matrix)
%%
% Input:
%      matrix ---- 输入的1Xn矩阵 即：一维向量
% 
% Output:
%      hyFlag ---- 函数执行完成标志 '0'未完成;'1'完成
%                     
% Examples of use:
% (a)
%       hy_OutMatrix1Xn('HMK_COEF.txt',hmkcoef);      
%       使用本函数前先将数据归一化及定标
%
%       ∴固定了输出格式为有符号数短整型
hyFlag = 0;
[m n] = size(matrix);   % m行 n列
if n==1
    n=m;
end
fid = fopen(filename,'w+'); %写入文件路径
fprintf(fid,'const %s[%d]={\n',filename,n);
for i=1:n-1
    fprintf(fid,'%6d,',matrix(i)); %输出格式为6位的十进制整数
end
fprintf(fid,'%6d\n};',matrix(n));
fclose(fid);
hyFlag = 1;
end

