close all;
clear;
clc;

vectorLen = 100;
n = 0:vectorLen-1;
phase = 65; % in samples
sineAmp = 511;
sineDc = 512;

C1 = sineAmp*sin((2*pi/(vectorLen-1))*n)+sineDc;
C2 = [C1(phase:end-1),C1(1:phase)];

figure; plot(C1);
hold on; plot(C2);

C1s = [mean(C1); 2*std(C1)];
C2s = [mean(C2); 2*std(C2)];

sinsum = C1 + C2;
sinsums = [mean(sinsum); 2*std(sinsum)];

c_fcn = @(theta) sqrt(C1s(2).^2 + C2s(2).^2 + 2*C1s(2).*C2s(2).*cos(theta)) - sinsums(2);
theta = fzero(c_fcn, 1);
thetadeg = theta*180/pi;

sprintf('theta = %.3f rad = %.3f°', theta, thetadeg)
dlmwrite('sin.txt',round(C1));