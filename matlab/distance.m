R = 3.25;
W = 18.7;

thetaL = -54.57;
thetaR = -47.8;

phi = R/W*(thetaL - thetaR);
r = R*thetaL/phi;

x = 2*(r+W/2)*sin(phi);
y = -2*(r+W/2)*cos(phi);