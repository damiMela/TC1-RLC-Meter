close all;
clear;
clc;

%1Hz - 20kHz
frec = 1000;
puntos = 49;

fro = 30e6; %DAC clock
timeStep = 1 / (frec*puntos);
periodo = 1/frec;

N = 0 : puntos-1;
w = 2*pi*frec;
y = 1.65 + 1.5*sin(w*N*timeStep);
csvwrite('sin.txt',y);

figure;
plot(N*timeStep,y, "-o");

%for LT spice
plw_t = [0, timeStep+zeros(1,puntos-1)].';
M = [plw_t, y.'];
dlmwrite('sin.txt',M,'precision','+%.10f','delimiter','\t');