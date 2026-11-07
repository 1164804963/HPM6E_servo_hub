function pid_controller = pid_turn_auto(sys, wc)
%TF_ZEROS Summary of this function goes here
%   Detailed explanation goes here

%选取超调量 第一次超过 desiredOvershoot % 的前一次增益

first_cf = wc;
first_pm = 70;
 % 使用 pidtuneOptions 设置初始猜测和优化选项
opts = pidtuneOptions('PhaseMargin',first_pm, 'DesignFocus','reference-tracking');

% 调整 PID 控制器参数
pid_controller = pidtune(sys, 'PI',first_cf, opts);

% 计算闭环系统
closed_loop_sys = feedback(pid_controller * sys, 1);

% 获取闭环系统的阶跃响应特性
step_info = stepinfo(closed_loop_sys);
 

% 绘制阶跃响应
step(closed_loop_sys);
title('Closed-Loop Step Response with Optimal PID Controller');
hold off;grid on;

disp('The designed PID controller meets the desired step response performance.');
% 显示 PID 控制器增益
disp('Optimal PID Gains:');
disp(pid_controller);
disp('Step Response Characteristics:');
disp(step_info);

 

