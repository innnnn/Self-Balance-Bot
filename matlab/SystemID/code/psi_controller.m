% PID control for psi(angle of inclination)
clear;
clc;

KP = 0.000313;
KI = 2.99e-07;
KD = 0.0818;

num = conv([0.9856 488.1], [KD KP KI]);
den = [1 8.623 -328.7 17.6 0] + [0 num];

num = [0.9856 488.1];
den = [1 8.623 -328.7 17.6 0];
Gp = tf(num, den);
[c_pid, info] = pidtune(Gp, 'PIDF');