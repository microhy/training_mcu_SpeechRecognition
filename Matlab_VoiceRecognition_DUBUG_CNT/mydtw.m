function [myDist,myD,myk,myw]=mydtw(t,r)
%Dynamic Time Warping Algorithm
%Dist is unnormalized distance between t and r
%D is the accumulated distance matrix
%k is the normalizing factor 归一化因数
%w is the optimal path 最佳路径存储
%t is the vector you are testing against
%r is the vector you are testing
[N,P]=size(t);
[M,P]=size(r);
d = zeros(N,M);
for n=1:N      % t,r都作为行向量处理
   for m=1:M
       for i=1:P
           d(n,m)=d(n,m)+(t(n,i)-r(m,i))^2;  %%%%%两个行向量求距离
       end
   end
end
% d=(repmat(t(:),1,M)-repmat(r(:)',N,1)).^2; %this replaces the nested for loops from above Thanks Georg Schmitz 

D=zeros(size(d));
D(1,1)=d(1,1);

for n=2:N
    D(n,1)=d(n,1)+D(n-1,1);
end
for m=2:M
    D(1,m)=d(1,m)+D(1,m-1);
end

for n=2:N
    for m=2:M
        dmin = D(n-1,m);   %找出三者中的最小值
        if D(n-1,m-1)<dmin
            dmin = D(n-1,m-1);
        end
        if D(n,m-1)<dmin
            dmin = D(n,m-1);
        end                %找出三者中的最小值
        D(n,m)=d(n,m)+ dmin; %
    end
end

Dist=D(N,M);

%%
%以下部分是求最佳路径
n=N;
m=M;
k=1;    
w=[];   %新建一个变量w为空
w(1,:)=[N,M]; %使w的第一行元素为 N,M
while ((n+m)~=2)  %当n+m不等于2时，由于m,n必定大于等于1
    if (n-1)==0        %若n=1
        m=m-1;      
    elseif (m-1)==0    %若n~=1且m=1
        n=n-1;
    else   %m>1且n>1
        [values,number]=min([D(n-1,m),D(n,m-1),D(n-1,m-1)]);
        switch number
        case 1
            n=n-1;
        case 2
            m=m-1;
        case 3
            n=n-1;
            m=m-1;
        end
    end
    k=k+1;
    w=cat(1,w,[n,m]);
end
myDist=Dist;myD =D;myk=k;myw=w;
end