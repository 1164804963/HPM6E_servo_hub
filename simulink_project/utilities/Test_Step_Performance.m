% By ZFS@wust  2020
% 获取更多Matlab/Simulink原创资料和程序，清关注微信公众号：Matlab Fans

% Eg 1 一阶系统
sys = tf(1,[3 1]);
[y,t] = step(sys,25);
[ys,tr,ts,tm,ov] = Fun_Step_Performance(t,y);

% Eg 2 复杂系统
sys = tf(1,[1 2*0.20*1 1]) * tf(1,[2 1]) * tf([1.5 1],[1 2*0.25*3 9]);  % 5阶系统
[y,t] = step(sys,35);
[ys,tr,ts,tm,ov] = Fun_Step_Performance(t,y);


% Eg 3 求解不同阻尼比时二阶系统的阶跃响应特性
wn = 1;    % 固有频率
kes_vet = [0.2 0.4 0.6 0.8 1 1.2];   % 阻尼比序列
figure
hold on
for ii = 1:length(kes_vet)
    kes = kes_vet(ii);
    sys = tf(1,[1 2*kes*wn wn^2]);   % 二阶系统传递函数
    [y,t] = step(sys,50);            % 阶跃响应
    [ys(ii),tr(ii),ts(ii),tm(ii),ov(ii)] = Fun_Step_Performance(t,y,0);  % 求解阶跃响应,不绘图
    plot(t,y)
    Str{ii} = [ '\xi = '  num2str(kes)];
end
legend(Str)
xlabel('时间t/s')
ylabel('输出响应y')

figure
subplot(221)
plot( kes_vet,tr,'-o' )
xlabel('阻尼比\xi')
ylabel('上升时间/s')
subplot(222)
plot( kes_vet,ts,'-o' )
xlabel('阻尼比\xi')
ylabel('调整时间/s')
subplot(223)
plot( kes_vet,tm,'-o' )
xlabel('阻尼比\xi')
ylabel('峰值时间/s')
subplot(224)
plot( kes_vet,ov,'-o' )
xlabel('阻尼比\xi')
ylabel('超调量/%')

