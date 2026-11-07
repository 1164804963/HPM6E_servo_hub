function [ZH] = tf_div(H)
%TF_ZEROS Summary of this function goes here
%   Detailed explanation goes here

%传递函数分解
 % 定义二阶传递函数的系数
[numerator, denominator] = tfdata(H, 'v');     % 获取原始分子和分母系数

% % 显示原始传递函数
% disp('原始二阶传递函数:');
% H

% 对传递函数进行部分分式分解
% residue 函数返回分解后的残差、极点和多项式
[r, p, k] = residue(numerator, denominator);

% 将残差和极点转化为传递函数格式
% 初始化分子和分母数组
numCell = {};
denCell = {};

% 遍历每个残差和对应的极点
for i = 1:length(r)
    % 对于每个残差 r(i) 和对应的极点 p(i)
    numCell{i} = r(i); % 设置分子为残差
    denCell{i} = [1 -p(i)]; % 设置分母为 s - p(i)
end

% 转化为TF对象
tfArray = cellfun(@tf, numCell, denCell, 'UniformOutput', false);

% 如果存在直接项，则处理直接项
if ~isempty(k)
    tfDirect = tf(k(end), 1); % 直接项转化为传递函数
    tfArray{end+1} = tfDirect; % 添加到传递函数数组
end

% 显示所有分解后的传递函数
disp('Decomposed Transfer Functions:');
for i = 1:length(tfArray)
    ZH(i) = tf_zeros(tfArray{i});
    display(ZH(i));
end

end

