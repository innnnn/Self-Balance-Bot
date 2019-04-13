% Goal: System ID

% **** Part 1: receive data ****
% Method: 1.serial port   2.Bluetooth
clear;

% Method 1
% serial port COM8
% set BaudRate to 9600
% set terminator to CR
% CR: carriage return, /r
% LF: line feed, /n
s = serial('COM11', 'BaudRate', 9600, 'Terminator', 'CR');
fopen(s);

% Method 2
%{
instrhwinfo('Bluetooth');
b = Bluetooth('Slave', 1);
fopen(b);
%}

% Collect Data
% imformation of raw data
dT = 0.01;        % sampling frequency
time = 10;        % record 10 second of data
length = time/dT; % # of raw data
t = 0 : dT : time - dT;  
rawData = strings(length, 1);
for i = 1:length
    rawData(i) = fscanf(s);     % receive data from serial port
%    rawData(i) = fscanf(b);     % receive data from bluetooth    
end


% **** Part 2: process raw data ****
% parse the raw data
data = zeros(length, 3);
for i = 1:1000
    data(i, 1) = str2double( extractBetween(rawData(i), "speed_left  = ", ", speed_right = ") );   % left speed
    data(i, 2) = str2double( extractBetween(rawData(i), ", speed_right = ", ", phi = ") );         % right speed
    data(i, 3) = str2double( extractAfter  (rawData(i), ", phi = ") );                             % phi
end

% plot left speed, right speed, phi with respect to t
% 390 cpr =  360 degree  ==>  1 cpr = 360/390 degree
figure;
plot(t, data(:, 1));
xlabel("t");
ylabel("speed (cpr/s)");
title("Left speed");

figure;
plot(t, data(:, 2));
xlabel("t (s)");
ylabel("speed (cpr/s)");
title("Right speed");

figure;
plot(t, data(:, 3));
xlabel("t (s)");
ylabel("angle (degree)");
title("phi");

% instrfind: Read serial port objects from memory to MATLAB workspace
objs = instrfind;
fclose(objs);