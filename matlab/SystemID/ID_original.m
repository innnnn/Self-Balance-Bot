%For (sigma4,5)  (rho2,4,5)
clear;clc;
x = save_psi;
phi=x(:,1)/180*pi;  % phi is rad
time=10;


phid = zeros
for i=2:length(phi)
    phid(i-1)=(phi(i)-phi(i-1))/time*1000;
end
phid(length(phi))=phid(end);  % rad/s

for i=2:length(phid)
    phidd(i-1)=(phid(i)-phid(i-1))/time*1000;
end
phidd(length(phid))=phidd(end);
phidd=phidd';   % rad/s^2

t = 0:0.01:30-0.01;
plot(t, phi, t, phid, t, phidd);
xlabel("t (s)");
%ylabel("angle (degree)");
title("psi");
legend;


%%%%% �ݽվ�
range=300;350;
A=[-phid(range) sin(phi(range))];
coe=pinv(A'*A)*A'*phidd(range);
sigma4=coe(1)
sigma5=coe(2)

C=[(-cos(phi(range)).*phidd(range)) (sin(2*phi(range)).*sec(phi(range)).*phid(range).*phid(range)) (phid(range))];
coe2 = pinv(C'*C)*C'*phidd(range);
rho2 = coe2(1)
rho4 = coe2(2)
rho5 = coe2(3)

%for sigma1
clear coe A C phidd phid phi time x i range
x = save_psi;
phi=x/180*pi;  % phi is rad
time=50;
x = save_thetad;
thetad=x;  % rad/s

%����peak
%%%%% �ݽվ�
head=44;
tail=49;
A=[head*head head 1;tail*tail tail 1;(tail+1)*(tail+1) (tail+1) 1];
coe=pinv(A)*[phi(head);phi(tail);phi(tail+1)];
for i=head+1:tail-1
    phi(i)=i*i*coe(1)+i*coe(2)+coe(3);
end


for i=2:length(phi)
    phid(i-1)=(phi(i)-phi(i-1))/time*1000;
end
phid(length(phi))=phid(end);
phid=phid';

for i=2:length(phid)
    phidd(i-1)=(phid(i)-phid(i-1))/time*1000;
end
phidd(length(phid))=phidd(end);
phidd=phidd';

figure;
plot(t, phi, t, phid, t, phidd);
xlabel("t (s)");
%ylabel("angle (degree)");
title("psi");
legend;

% ���Ƥ�
for k=1:5
    for i=1:length(thetad)-4
        thetad(i)=sum(thetad(i:i+4))/5;
    end
    thetad(length(thetad)-3:length(thetad))=thetad(end-3:end);
end

for i=2:length(thetad)
    thetadd(i-1)=(thetad(i)-thetad(i-1))/time*1000;
end
thetadd(length(thetad))=thetadd(end);
thetadd=thetadd';

figure;
plot(t, thetad, t, thetadd);
xlabel("t (s)");
%ylabel("angle (degree)");
title("thetad");
legend;

%%%%% �ݽվ�
range=80:100;
A=[thetadd(range) cos(phi(range)).*thetadd(range) -thetad(range) -50*ones(21, 1)];
B=-1*phidd(range) - sigma4*phid(range) + sigma5*sin(phi(range));
coe=pinv(A'*A)*A'*B;
sigma1 = coe(1)
sigma2 = coe(2)
sigma3 = coe(3)
sigma6 = coe(4)

C = [thetadd(range) thetad(range) -50*ones(21, 1)];
D = (-phidd(range))+(-cos(phi(range)).*phidd(range))+(sin(2*phi(range)).*sec(phi(range)).*phid(range).*phid(range))+(phid(range));
coe2=pinv(C'*C)*C'*D;
rho1 = coe2(1)
rho3 = coe2(2)
rho6 = coe2(3)

r1=rho1;
r2=rho2;
r3=rho3;
r4=rho4;
r5=rho5;
r6=rho6;
rho=[r1 r2 r3 r4 r5 r6]
r6=rho6;

s1=sigma1;
s2=sigma2;
s3=sigma3;
s4=sigma4;
s5=sigma5;
s6=sigma6;
sigma=[s1 s2 s3 s4 s5 s6]
