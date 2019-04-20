% **** Part 2 : 5v ****
% get ro1 ro3 ro5 ro6 ro7 ro10
% *****************************
load("ro_ave.mat");
psi = save_psi_5v/180*pi;       % psi is rad
thetad = save_thetad_5v/390; % theta is rad

dT = 0.05;
time = 10;
t = 0 : dT : time-dT;
L = length(psi);

% psi dot
psid = zeros(L, 1);
for i = 2:L
    psid(i) = ( psi(i) - psi(i-1) )/dT;
end
psid(1) = psid(2);

% psi double dot
psidd = zeros(L, 1);
for i = 2 : L
    psidd(i) = ( psid(i) - psid(i-1) )/dT;
end
psidd(1) = psidd(2);

% plot psi, psid and psidd
figure;
plot(t, psi);
xlabel("t (s)");
title("psi");
legend("psi");

figure;
plot(t, psi, t, psid, t, psidd);
xlabel("t (s)");
title("psi & psid & psidd");
legend("psi", "psid", "psidd");

% theta double dot
thetadd = zeros(L, 1);
for i = 2:L
    thetadd(i) = ( thetad(i) - thetad(i-1) )/dT;
end
thetadd(1) = thetadd(2);

% plot thetad thetadd
figure;
plot(t, thetad);
xlabel("t (s)");
title("thetad");
legend("thetad");

figure;
plot(t, thetad, t, thetadd);
xlabel("t (s)");
title("thetad & thetadd");
legend("thetad", "thetadd");

% ro1 ro3 ro5
first =(0.3)*20+1;
last = (3.1)*20+1;
range = first:last; % 

L = length(range);
A = zeros(L, 3);
b = zeros(L, 1);
for i = range
    A(i-first+1, :) = [g1(thetadd(i)) g3(thetad(i)) g5(-5)];
    b(i-first+1)    = psidd(i) - ro(2)*g2(psi(i), psid(i), psidd(i)) - ro(4)*g4(psid(i));
end
x = (A'*A) \ ((A')*b);
ro(1) = x(1);
ro(3) = x(2);
ro(5) = x(3);

% ro6 ro7 ro8
for i = range
    A(i-first+1, :) = [g6(thetadd(i)) g7(psi(i),thetadd(i)) g10(-5)];
    b(i-first+1)    = psidd(i) - ro(8)*g8(psid(i), thetad(i)) - ro(9)*g9(psi(i));
end
x = (A'*A) \ ((A')*b);
ro(6) = x(1);
ro(7) = x(2);
ro(10) = x(3);
save("ro_final_02", "ro");

function y = g1(thetadd)
    y = -thetadd;
end

function y = g2(psi, psid, psidd)
    y = sin(2*psi)*sec(psi)*psid^2 - 2*cos(psi)*psidd;
end

function y = g3(thetad)
    y = -thetad;
end

function y = g4(psid)
    y = psid;
end

function y = g5(u)
    y = u;
end

function y = g6(thetadd)
    y = -thetadd;
end

function y = g7(psi, thetadd)
    y = -cos(psi)*thetadd;
end

function y = g8(psid, thetad)
    y = thetad-psid;
end

function y = g9(psi)
    y = sin(psi);
end

function y = g10(u)
    y = -u;
end