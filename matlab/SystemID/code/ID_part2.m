% **** Part 2 : 5v ****
% get ro1 ro3 ro5 ro6 ro7 ro10
% *****************************
load("ro_ave.mat");
psi = save_psi_5v/180*pi;       % psi is rad
thetad = save_thetad_5v/180*pi; % theta is rad

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
ylabel("rad");
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
ylabel("rad/s");
title("thetad");
legend("thetad");

figure;
plot(t, thetad, t, thetadd);
xlabel("t (s)");
title("thetad & thetadd");
legend("thetad", "thetadd");


first =(6.8)*20+1;
last = (7.15)*20+1;
range = first:last;
L = length(range);

g1 = -thetadd(range);
g2 = sin(psi(range)).*psid(range).^2 - cos(psi(range)).*psidd(range);
g3 = -thetad(range);
g4 = psid(range);
g5 = -5*ones(L, 1);
g6 = -thetadd(range);
g7 = -cos(psi(range)).*thetadd(range);
g8 = thetad(range)-psid(range);
g9 = sin(psi(range));
g10 = -5*ones(L, 1);
e = psidd(range);

% ro1 ro3 ro5
A = [g1 g3 g5];
b = e - ro(2)*g2 - ro(4)*g4;
x = (A'*A) \ ((A')*b);
ro(1) = x(1);
ro(3) = x(2);
ro(5) = x(3);

% ro6 ro7 ro10
A = [g6 g7 g10];
b = e - ro(8)*g8 - ro(9)*g9;
x = (A'*A) \ ((A')*b);
ro(6) = x(1);
ro(7) = x(2);
ro(10) = x(3);
save("ro_final_08", "ro");