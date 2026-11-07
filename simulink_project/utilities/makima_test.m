clc;clear;close all;

dt = 0.001;   %模拟主站1ms更新目标位置
dt_p = 0.0001;%模拟位置环运行周期100us 

%% 1. 数据准备
x = 0:dt:dt*1000;   
y = 10.*sin(10.*x);   % 函数值
xx = 0:dt_p:dt*1000;  % 精细网格用于绘图  以dt_p 为周期进行插值

%% 2. MAKIMA插值
% 方法1: 直接计算插值点
yy = makima(x, y, xx);

% 方法2: 获取分段多项式表示
pp = makima(x, y);  % 返回分段多项式结构
yy_pp = ppval(pp, xx);  % 通过ppval计算

%% 3. 计算一阶导数
% 对分段多项式求导
pp_der1 = fnder(pp, 1);  % 一阶导数
yy_der1 = ppval(pp_der1, xx);  % 计算一阶导数值


%% 4. 计算二阶导数
pp_der2 = fnder(pp, 2);  % 二阶导数
yy_der2 = ppval(pp_der2, xx);

%% 5. 绘制结果
figure('Position', [100, 100, 1200, 400]);

% 函数值
subplot(1, 3, 1);
plot(x, y, 'ko', 'MarkerFaceColor', 'k', 'MarkerSize', 8, 'DisplayName', '数据点');
hold on;
plot(xx, yy, 'b-', 'LineWidth', 2, 'DisplayName', 'MAKIMA插值');
title('MAKIMA插值函数');
xlabel('x'); ylabel('f(x)');
legend('Location', 'best');
grid on;

% 一阶导数
subplot(1, 3, 2);
plot(xx, yy_der1, 'r-', 'LineWidth', 2, 'DisplayName', '一阶导数');
hold on;
% 标记节点处的一阶导数
x_nodes = x(2:end-1);  % 内部节点
y_der1_nodes = ppval(pp_der1, x_nodes);
plot(x_nodes, y_der1_nodes, 'ro', 'MarkerFaceColor', 'r', 'DisplayName', '节点处导数值');
title('一阶导数 f''(x)');
xlabel('x'); ylabel('f''(x)');
legend('Location', 'best');
grid on;

% 二阶导数
subplot(1, 3, 3);
plot(xx, yy_der2, 'g-', 'LineWidth', 2, 'DisplayName', '二阶导数');
title('二阶导数 f''''(x)');
xlabel('x'); ylabel('f''''(x)');
legend('Location', 'best');
grid on;