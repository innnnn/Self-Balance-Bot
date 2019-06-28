%

% pid
kp = 95.3;
ki = 600;
kd = 1.1;

% the system with cascase controller
num = -0.9856 * [kd kp ki];
den = [1 -21.3271 -3.8995 0];
H = tf(num, den);
G = feedback(H, 1);