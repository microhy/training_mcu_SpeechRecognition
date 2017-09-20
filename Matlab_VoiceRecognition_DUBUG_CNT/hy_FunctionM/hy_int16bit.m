function matrix_out = hy_int16bit( matrix_in )
% Inputs:
%     matrix_in     输入的矩阵
% 
% Outputs:
%     matrix_out    输出归一化后在定标的矩阵
% 
matrix_out = matrix_in/max(matrix_in(:));   %幅值归一化，使数据在-1~+1之间
matrix_out = int16(matrix_out*(2^15-1)); %归一化后再定标 使数据在-32767~32767
end

