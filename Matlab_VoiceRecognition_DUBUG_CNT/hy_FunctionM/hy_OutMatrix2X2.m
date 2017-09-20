function  hyFlag= hy_OutMatrix_MxN(filename,matrix_MxN)
%%
% Input:
%      matrix2x2 ---- �����2X2����
% 
% Output:
%      hyFlag ---- ����ִ����ɱ�־ '0'δ���;'1'���
%                     
% Examples of use:
% (a)   bank = melbankm(P,frameSize,fs,0,0.5,'t'); 
%       bank = full(bank);
%       bank = bank/max(bank(:));   %��ֵ��һ�������㶨��
%       hmkcoef = int16(bank*(2^15-1)); %��һ�����ٶ���
%       hy_OutMatrix2X2(bank);      %ʹ�ñ�����ǰ�Ƚ����ݹ�һ��������
%
%       ��̶��������ʽΪ�з�����������
hyFlag = 0;
[m n] = size(matrix2x2);   % m�� n��
fid = fopen(filename,'w+'); %д���ļ�·��
fprintf(fid,'const signed short int %s[%d][%d]={\n',filename,m,n);
for i=1:m
    fprintf(fid,'{');
    for j=1:n-1
        fprintf(fid,'%6d,',matrix2x2(i,j)); %�����ʽΪ6λ��ʮ��������
    end
    fprintf(fid,'%6d},\n',matrix2x2(i,n));
end
fprintf(fid,'};');
fclose(fid);
hyFlag = 1;
end

