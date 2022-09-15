%1Hz 250kHz
counter_ticks = 30000;
fro = 30e6;
time_tick = counter_ticks / fro;
puntos = 50;
periodo = puntos *time_tick;
frec = 1/periodo;

%con 1 ticks --> 300kHz
%con 12 ticks --> 25kHz
%con 120 ticks --> 2.5kHz
%con 1200 ticks --> 250Hz
%con 12000 ticks --> 25Hz
%con 30000 ticks --> 10Hz


counter_ticks = 120;
fro = 30e6; %30MHz
time_tick = counter_ticks / fro;
frec = 2500;
periodo = 1/frec;
puntos = periodo /(2 * time_tick);
t = linspace(0,2*pi,puntos);
y = sin(t)+1;
y = fix(y * 1024/2);
csvwrite('sin.txt',y);

figure;
plot(t,y);

%1Hz 250kHz
counter_ticks = 60000;
fro = 30e6;
time_tick = counter_ticks / fro;
puntos = 50;
periodo = puntos *time_tick;
frec = 1/periodo;

%con 2 ticks --> 300kHz
%con 25 ticks --> 24kHz
%con 250 ticks --> 2.4kHz
%con 2500 ticks --> 240Hz
%con 25000 ticks --> 24Hz
%con 60000 ticks --> 10Hz
