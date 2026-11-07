function Hd = tf2ztf(hs_num, hs_den, ts)
%% 将hs 连续时间下的传递函数模型 转化为 离散时间下的 Z变化 传递函数模型
    % ts 采样时间
    
    % 定义连续时间的传递函数模型
    Hs = tf(hs_num, hs_den);
    
    % 使用双线性变换方法进行离散化
    Hd = c2d(Hs, ts, 'tustin');
    
    % 显示离散时间的传递函数模型
    disp(Hd);
end