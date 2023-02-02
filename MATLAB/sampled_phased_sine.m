close all;
clear;
clc;

%%Time specifications:
f = 1000;     % signal frequency
N = 100;    % samples per signal period
Fs = N*f;  % samples per second
dt = 1/Fs;   % seconds per sample (time increment)

t = 0:dt:(2*dt*(N-1)); 
sineAmp = 512;
sineDc = 512;
phase = pi/7;

C1 = sineAmp*sin(2*pi*f*t)+sineDc;
C2 = sineAmp*sin(2*pi*f*t+phase)+sineDc;

figure; plot(C1);
hold on; plot(C2);

%Get angle
Cn = SEF(t,C2,1/f,2);
phi1 = angle(Cn(2))*180/pi+90

%optimize for single armonic
Cn_1 =f*sum(C2.*exp(-1i*2*pi*f*t))*dt;
phi2 = angle(Cn_1)*180/pi+90

%vector based
min = sineAmp+sineDc;
min_pos = 0;
for i=0:(N-2)
    val = abs(C1(i+1)-sineDc);
    if((val < min) && ((C1(i+2)-sineDc)>0))
        min = val;
        min_pos = i;
    end
end

max = 0;
max_pos = 0;
for j= 0:(N-1)
    if((C2(j+1) > max) && (j>min_pos))
        max = C2(j+1);
        max_pos = j;
    end
end

delta_n = max_pos-min_pos;
index = delta_n-ceil(N/4);
ph3 = -((index*360)/(N-1))


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [Cn]=SEF(t,ft,T0,N)
    w0=2*pi/T0;
    dt=t(2)-t(1);

    Cn=zeros(1,N-1);

    for n=0:(N-1)
        Cn(n+1)=(1/T0)*sum(ft.*exp(-1i*w0*n*t))*dt;
    end
    Cn(1)=(1/T0)*sum(ft)*dt;
end
