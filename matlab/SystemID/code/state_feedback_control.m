clear;

load('final_rho');
temp = [1+rho(2) rho(1);
        1        rho(6)+rho(7)];
c = inv(temp);
A = [0 1 0 0;
    c(1,2)*rho(9) c(1,1)*rho(4)-c(1,2)*rho(8) 0 -c(1,1)*rho(3)+c(1,2)*rho(8);
    0 0 0 1;
    c(2,2)*rho(9) c(2,1)*rho(4)-c(2,2)*rho(8) 0 -c(2,1)*rho(3)+c(2,2)*rho(8)];
B = [0;
    c(1,1)*rho(5)-c(1,2)-rho(10);
    0;
    c(2,1)*rho(5)-c(2,2)-rho(10)];
C = [1 0 0 0;  %psi
     0 0 1 0]; %theta
D = [0;
     0];
 
%convert state-space representation to transfer funciton
[n,d] = ss2tf(A,B,C,D);

% psi
h = tf(n(1,:), d);
figure;
rlocus(h);
figure;
bode(h);

% theta
h = tf(n(2,:), d);
figure;
rlocus(h);
figure;
bode(h);