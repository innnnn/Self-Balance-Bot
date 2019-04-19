% Goal System ID

ro = zeros(10, 1);

% **** Part 1 : zero input ****
% get ro2 ro4 ro8 ro9
% *****************************
% load data wiht zero input
psi = psi_parse_09/180*pi;  % psi is rad
dT = 0.05;
time = 2;
t = 0 : dT : time;
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

% plot psi, psid, psidd
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

% ro2 ro4
range = 29:39; % 
L = length(range);
A = zeros(L, 2);
for i = range
    A(i-28, :) = [g2(psi(i), psid(i), psidd(i)) g4(psid(i))];
end
b = psidd(range);
x = (A'*A) \ ((A')*b);
ro(2) = x(1);
ro(4) = x(2);

% ro8 ro9
for i = range
    A(i-28, :) = [g8(psid(i), 0) g9(psi(i))];
end
b = psidd(range);
x = (A'*A) \ ((A')*b);
ro(8) = x(1);
ro(9) = x(2);

save("ro_5.mat", "ro");
%clear;

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