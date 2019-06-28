% Goal: pos controller

% **** Part 1: receive data ****
instrhwinfo('Bluetooth');
b = Bluetooth('Slave', 1);
fopen(b);

% Collect Data
% imformation of raw data
dT = 0.1;         % sampling time
time = 20;        % record 20 second of data
length = time/dT; % # of raw data
t = 0 : dT : time - dT;
rawData = strings(length, 1);
for i = 1:length
    rawData(i) = fscanf(b);     % receive data from bluetooth
end

% **** Part 2: process raw data ****
% parse the raw data
data = zeros(length, 6);
for i = 1:length
    x = strsplit(rawData(i), ",");
    data(i, 1) = str2double( x(1) );   % psi
    data(i, 2) = str2double( x(2) );   % y
end

% plot figure
figure;
plot(t, data(:, 1));
xlabel("t (s)");
ylabel("psi (rad)");
title("real world");
grid;

figure;
plot(t, data(:, 2));
xlabel("t (s)");
ylabel("distance (cm)");
title("real world");
grid;

% save data
psi = data(:, 1);
save('psi.mat', 'psi');

y = data(:, 2);
save('y.mat', 'y');

% instrfind: Read serial port objects from memory to MATLAB workspace
objs = instrfind;
fclose(objs);