function sys_tf_zeros = tf_zeros(sys_tf)
%TF_ZEROS Summary of this function goes here
%   Detailed explanation goes here
% 归一化分子
[num, den] = tfdata(sys_tf, 'v');     % 获取原始分子和分母系数
k = num(end);           % 获取分子首项系数
num_normalized = num / k;  % 将分子归一化
den_normalized = den / k;  % 相应地归一化分母

% 创建归一化传递函数
sys_tf_zeros = tf(num_normalized, den_normalized);

% %% 验证传递函数归一化是否相等
% % 转换为零极点增益形式
% [z1, p1, k1] = zpkdata(sys_tf, 'v');
% [z2, p2, k2] = zpkdata(sys_tf_zeros, 'v');
% 
% % 比较零点、极点和增益
% if isequal(z1, z2) && isequal(p1, p2) && isequal(k1, k2)
%     disp('归一化后传递函数是等价的。');
% else
%     disp('归一化后传递函数是不等价的。');
% end


end

