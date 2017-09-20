function [Dcep,Ccep1,Ccep2]=mymel_dist(s1,s2,fs,num,wlen,inc)

ccc1=mymfcc_m(s1,fs,num,wlen,inc); % ��ȡMel�˲�������
ccc2=mymfcc_m(s2,fs,num,wlen,inc);

[Dist,D,k,w]=dtw(ccc1,ccc2);
figure;plot(w(:,1),w(:,2));grid;

fn1=size(ccc1,1);                % ȡ֡��
Ccep1=ccc1(:,1:num);             % ֻȡMFCC��ǰnum������
Ccep2=ccc2(:,1:num);

for i=1 : fn1                   % ����s1��s2֮��ÿ֡��Mel����
    Cn1=Ccep1(i,:);
    Cn2=Ccep2(i,:);
    Dstu=0;
    for k=1 : num
        Dstu=Dstu+(Cn1(k)-Cn2(k))^2;
    end
    Dcep(i)=sqrt(Dstu);         % ÿ֡��Mel����
end