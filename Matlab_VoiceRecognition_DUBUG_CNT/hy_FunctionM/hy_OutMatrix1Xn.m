function  hyFlag= hy_OutMatrix1Xn(filename,matrix)
%%
% Input:
%      matrix ---- �����1Xn���� ����һά����
% 
% Output:
%      hyFlag ---- ����ִ����ɱ�־ '0'δ���;'1'���
%                     
% Examples of use:
% (a)
%       hy_OutMatrix1Xn('HMK_COEF.txt',hmkcoef);      
%       ʹ�ñ�����ǰ�Ƚ����ݹ�һ��������
%
%       ��̶��������ʽΪ�з�����������
hyFlag = 0;
[m n] = size(matrix);   % m�� n��
if n==1
    n=m;
end
fid = fopen(filename,'w+'); %д���ļ�·��
fprintf(fid,'const %s[%d]={\n',filename,n);
for i=1:n-1
    fprintf(fid,'%6d,',matrix(i)); %�����ʽΪ6λ��ʮ��������
end
fprintf(fid,'%6d\n};',matrix(n));
fclose(fid);
hyFlag = 1;
end

