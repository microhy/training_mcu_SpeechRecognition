function  hyFlag= hy_OutSparseMatrix(filename,spamat)

hyFlag = 0;
[m n] = size(spamat);   % m行 n列
fid = fopen(filename,'w+'); %写入文件路径
fprintf(fid,'/*Sparse Matrix for matlab hy*/\n');

fprintf(fid,'spamat[] = {\n');
cnt=0;
for i=1:m
    for j=1:n-1
        if(spamat(i,j)~=0)        
            fprintf(fid,'{%d, %d, %d},',i-1,j-1,spamat(i,j));
            cnt = cnt+1;
            if(mod(cnt,5)==0)
                fprintf(fid,'\n');
            end
        end
    end
end
fprintf(fid,'};/*The count is:%d*/',cnt);
end