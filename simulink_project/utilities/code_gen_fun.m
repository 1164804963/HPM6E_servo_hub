function [state] = code_gen_fun(addr, file_type)
%code_gen_fun 代码生成函数
%  代码生成完毕后调用
%  addr  生成所有代码集中放置的地址, 相对路径  'code_gen', 
%        创建 addr 路径并且删除该路径下所有 file_type 类型文件
%  file_type  典型值   '**/*.cpp'   '**/*.h'
%        需要拷贝的文件类型，所有该脚本下所有（包括子文件夹）类型的文件 拷贝到 addr 中  

%% 创建新文件夹  addr
% 新文件夹的名称
folder_name = addr;

% 创建新文件夹
[status, message, message_id] = mkdir(folder_name);

% 检查是否创建成功
if status == 1
    disp(['Folder ' folder_name ' created successfully']);
    state = 1;
else
    disp(['Failed to create folder, error message: ' message]);
end


%% 删除文件夹下所有内容

% 文件夹的名称
folder_name = addr;

% 获取文件夹中所有文件的列表
files = dir(fullfile(folder_name, file_type));

% 循环遍历文件列表
for i = 1:length(files)
    % 如果是文件
    if ~files(i).isdir
        % 删除文件
        delete(fullfile(folder_name, files(i).name));
    end
end

disp(['Folder ' folder_name 'files delete successfully']);


%% 拷贝当前目录下所有 匹配文件 到指定文件夹

folder = './work/codegen'; % 你的文件夹路径
files = dir(fullfile(folder, file_type)); % 搜索 .cpp 文件

% 打印出所有找到的 file_type 文件
for i = 1:length(files)
    source = [files(i).folder ,'\', files(i).name];  % 源文件路径
    destination =  ['.\', addr, '\', files(i).name];  % 目标文件夹路径

    %slprj\_slcc（simulink代码生成缓存文件）不拷贝
    if contains(source, 'slprj\_slcc')
        continue;
    end

    % 复制文件
    [status, message, message_id] = copyfile(source, destination);

    % 检查是否成功
    if status == 1
        % disp('File copied successfully');
    else
        disp(['Failed to copy file, error message: ' message]);
        disp([source, '   to   ', destination]);
    end

end
disp('File copied successfully');



end