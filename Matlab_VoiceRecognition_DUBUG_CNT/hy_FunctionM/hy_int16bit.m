function matrix_out = hy_int16bit( matrix_in )
% Inputs:
%     matrix_in     ����ľ���
% 
% Outputs:
%     matrix_out    �����һ�����ڶ���ľ���
% 
matrix_out = matrix_in/max(matrix_in(:));   %��ֵ��һ����ʹ������-1~+1֮��
matrix_out = int16(matrix_out*(2^15-1)); %��һ�����ٶ��� ʹ������-32767~32767
end

