%% 陷波滤波器原始伯德图
close all;
b0 = 400;     %陷波滤波器频率 rad/s
b2 = 20;      %滤波宽度 rad/s
depth = 0.1; %滤波器深度  0.1 = -20db, 0.01 = -40db  以此类推
b1 = b2 * depth;
Ts = 10e-5;

figure  
H = tf([1 b1 b0^2],[1 b2 b0^2]);
bodeplot(H);
grid on;

%% 陷波滤波器原始伯德图
figure
Hdt = c2d(H,Ts,"tustin");  %双线性变换离散化
Hdp = c2d(H,Ts,"prewarp",b0);   %双线性变换离散化+带频率矫正
bodeplot(H,"b",Hdt,"m",Hdp,"g")
grid on
legend("Continuous","Tustin","Tustin with prewarping");