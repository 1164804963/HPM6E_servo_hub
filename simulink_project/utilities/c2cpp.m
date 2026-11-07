% 获取当前文件夹中的所有.c文件
files = dir('*.c');

% 遍历这些文件
for i = 1:length(files)
    % 获取当前文件的名称（不包含扩展名）
    [~, name, ~] = fileparts(files(i).name);
    
    % 生成新的文件名（.cpp）
    newname = strcat(name, '.cpp');
    
    % 重命名文件
    movefile(files(i).name, newname);
end

disp('c 2 cpp success~!');