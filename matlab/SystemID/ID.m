% Goal System ID
clear;

ro = zeros(10, 1);

% **** Part 1 : zero input ****
% get ro2 ro4 ro8 ro9
% *****************************
% load data wiht zero input
data = save_psi;
psi = data(:,1)/180*pi;  % psi is rad
dT = 0.01;
time = 10;
t = 0 : dT : time-dT;
length = length(psi);

% psi dot
psid = zeros(length, 1);
for i = 2:length
    psid(i-1) = ( psi(i) - psi(i-1) )/dT;
end
psid(end) = psid(end-1);

% psi dot filter
psidf = zeros(length, 1);
for i = 5:length
    psidf(i-4) = ( psid(i) + psid(i-1) + psid(i-2) + psid(i-3) + psid(i-4)) / 5;
end
psidf(end-3) = psidf(end-4);
psidf(end-2) = psidf(end-4);
psidf(end-1) = psidf(end-4);
psidf(end)   = psidf(end-4);

% plot psid and psidf
figure;
plot(t, psi, t, psid, t, psidf);
xlabel("t (s)");
title("psi & ");
legend("psi", "psid", "psidf");

% psi double dot
psidd = zeros(length, 1);
for i = 2 : length
    psidd(i-1) = ( psidf(i) - psidf(i-1) )/dT;
end
psidd(end) = psidd(end-1);

% psi double dot filter
psiddf = zeros(length, 1);
for i = 5:length
    psiddf(i-4) = ( psidd(i) + psidd(i-1) + psidd(i-2) + psidd(i-3) + psidd(i-4)) / 5;
end
psiddf(end-3) = psiddf(end-4);
psiddf(end-2) = psiddf(end-4);
psiddf(end-1) = psiddf(end-4);
psiddf(end)   = psiddf(end-4);

% ro2 ro4
range = 1:20;
r_psi   = psi  (range);
r_psid  = psid (range);
r_psidd = psidd(range);

A = [ sin(2*r_psi).* sec(r_psi).*r_psid.*r_psid - 2*cos(r_psi).*r_psidd  r_psid ];
b = r_psidd;
x = (A'*A) \ ((A')*b);
ro(2) = x(1);
ro(4) = x(2);

% ro8 ro9
A = [ -r_psid  sin(r_psi) ];
b = r_psidd;
x = (A'*A) \ ((A')*b);
ro(8) = x(1);
ro(9) = x(2);

% **** Part 2 : 5v ****
% get ro1 ro3 ro5 ro6 ro7 ro10
% *****************************
data = load('v50.mat');
data = data.buf;
psi = data(:,1)/180*pi;     % psi is rad
thetad = data(:, 2)/180*pi; % theta is rad

% psi dot
psid = zeros(length, 1);
for i = 2:length
    psid(i-1) = ( psi(i) - psi(i-1) )/dT;
end
psid(end) = psid(end-1);

% psi double dot
psidd = zeros(length, 1);
for i = 2 : length
    psidd(i-1) = ( psid(i) - psid(i-1) )/dT;
end
psidd(end) = psidd(end-1);

% theta double dot
thetadd = zeros(length, 1);
for i = 2:length
    thetadd(i-1) = ( thetad(i) - thetad(i-1) )/dT;
end
thetadd(end) = thetadd(end-1);

% Filter
for k=1:5
    for i=1:length(thetad)-4
        thetad(i)=sum(thetad(i:i+4))/5;
    end
    thetad(length(thetad)-3:length(thetad))=thetad(end-3:end);
end


% ro1 ro3 ro5
range=39:60;
r_psi   = psi  (range);
r_psid  = psid (range);
r_psidd = psidd(range);

r_thetad  = thetad (range);
r_thetadd = thetadd(range);

A = [ -r_thetadd  -r_thetad  5 ];
b = r_psidd - ro(2)*[sin(2*r_psi).* sec(r_psi).*r_psid.*r_psid - 2*cos(r_psi).*r_psidd] - ro(4)*r_psid;
x = (A'*A) \ ((A')*b);
ro(1) = x(1);
ro(3) = x(2);
ro(5) = x(3);

% ro6 ro7 ro8
A = [ -r_thetadd  -cos(r_psi).*r_thetad.*r_thetadd  -5 ];
b = r_psidd - ro(8)*(r_thetad-r_psid) - ro(9)*sin(r_psi);
x = (A'*A) \ ((A')*b);
ro(6) = x(1);
ro(7) = x(2);
ro(10) = x(3);