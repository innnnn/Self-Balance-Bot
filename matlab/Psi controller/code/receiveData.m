% Goal: psi controller

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
    data(i, 2) = str2double( x(2) );   % left angle
    data(i, 3) = str2double( x(3) );   % right angle
    data(i, 4) = str2double( x(4) );   % left speed
    data(i, 5) = str2double( x(5) );   % right speed
    data(i, 6) = str2double( x(6) );   % output
end

% plot figure
figure;
plot(t, data(:, 1));
xlabel("t (s)");
ylabel("psi (rad)");
title("real world");
grid;

figure;
plot(t, data(:, 2), t, data(:, 3));
xlabel("t (s)");
ylabel("angle (rad)");
title("real world");
legend("left angle", "right angle");
grid;

figure;
plot(t, data(:, 4), t, data(:, 5));
xlabel("t (s)");
ylabel("speed (rad/s)");
title("real world");
legend("left speed", "right speed");
grid;

figure;
plot(t, data(:, 6));
xlabel("t (s)");
ylabel("voltage (v)");
title("real world");
grid;

% save data
psi = data(:, 1);
save('psi.mat', 'psi');

thataL = data(:, 2);
save('thataL.mat', 'thataL');
thataR = data(:, 3);
save('thataR.mat', 'thataR');

thatadL = data(:, 4);
save('thatadL.mat', 'thatadL');
thatadR = data(:, 5);
save('thatadR.mat', 'thatadR');

output = data(:, 6);
save('output.mat', 'output');
% instrfind: Read serial port objects from memory to MATLAB workspace
objs = instrfind;
fclose(objs);