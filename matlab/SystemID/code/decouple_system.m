% decouple system
clear;

load('final_rho');
temp = [1+rho(2) rho(1);
        1        rho(6)+rho(7)];
c = inv(temp);

% psi
A = [0 1 0 0;
     c(1,2)*rho(9) c(1,1)*rho(4)-c(1,2)*rho(8) 0 0;
     0 0 0 0;
     0 0 0 0];
B = [0;
    c(1,1)*rho(5)-c(1,2)-rho(10);
    0;
    0];
C = [1 0 0 0;  %psi
     0 0 0 0]; %theta
D = [0;
     0];
[n,d] = ss2tf(A,B,C,D);
h_decouple_psi = tf(n(1,:), d)
[p1,z1] = pzmap(h_decouple_psi); 

% theta
A = [0 0 0 0;
     0 0 0 0;
     0 0 0 1;
     0 0 0 -c(2,1)*rho(3)+c(2,2)*rho(8)];
B = [0;
     0;
     0;
     c(2,1)*rho(5)-c(2,2)-rho(10)];
C = [1 0 0 0;
     0 0 1 0]; %theta
D = [0;
     0];
[n,d] = ss2tf(A,B,C,D);
h_decouple_theta = tf(n(2,:), d)
[p2,z2] = pzmap(h_decouple_theta);