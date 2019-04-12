% Goal: Receive data
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
length = 1000;
dataTemp = strings(1000, 1);
for i = 1:length
    dataTemp(i) = fscanf(s);
end
step = 0.01;
data = zeros(length, 3);
for i = 1:length
    data(i, 1) = str2double( extractBetween(dataTemp(i), "speed_left  = ", ", speed_right = ") );   % speed_left
    data(i, 2) = str2double( extractBetween(dataTemp(i), ", speed_right = ", ", phi = ") ); % speed_right
    data(i, 3) = str2double( extractAfter(dataTemp(i), ", phi = ") );                       % phi
end

plot(0:step:10-step, data(:, 1));
xlabel("t");
ylabel("speed");
title("Left speed");

figure;
plot(0:step:10-step, data(:, 2));
xlabel("t");
ylabel("speed");
title("Right speed");

figure;
plot(0:step:10-step, data(:, 3));
xlabel("t");
ylabel("angle");
title("phi");

% instrfind: Read serial port objects from memory to MATLAB workspace
objs = instrfind;
fclose(objs);