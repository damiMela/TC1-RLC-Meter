close all;
clear;
clc;

%1Hz - 20kHz
f = 1000;
N = 50;

A_v = 1.5; Of_v = 1.65;
A_d = 500; Of_d = 512;

fro = 30e6; %DAC clock
timeStep = 1 / (f*N);
T = 1/f;
phase = pi/5; 

n = 0 : N-1;
w = 2*pi*f;
y = Of_d + A_d*sin(w*n*timeStep + phase);
csvwrite('sin.txt',round(y*(2^6)));

y = Of_v + A_v*sin(w*n*timeStep + phase);

figure;
plot(n*timeStep,y, "-o");

%for LT spice
cycles = 100;
y2 = repmat(y,1,cycles)
plw_t = [0, timeStep+zeros(1,cycles*N-1)].';
M = [plw_t, y2.'];
dlmwrite('sin_spice.txt',M,'precision','+%.10f','delimiter','\t');
