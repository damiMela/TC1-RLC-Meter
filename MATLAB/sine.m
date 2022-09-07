%1Hz 250kHz
counter_ticks = 30000;
fro = 30e6;
time_tick = counter_ticks / fro;
puntos = 50;
periodo = puntos *time_tick;
frec = 1/periodo;

%con 2 ticks --> 300kHz
%con 24 ticks --> 25kHz
%con 240 ticks --> 2.5kHz
%con 30000 ticks --> 20Hz



counter_ticks = 300;
fro = 30e6; %30MHz
time_tick = counter_ticks / fro;
frec = 1000;
periodo = 1/frec;
puntos = periodo / time_tick;
t = linspace(0,2*pi,puntos);
y = sin(t)+1;
y = fix(y * 1024/2);
csvwrite('sin.txt',y);

figure;
plot(t,y);


