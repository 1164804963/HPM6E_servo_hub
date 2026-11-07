
targetFolder = '..\simulink_code_gen';

%检查文件夹是否存在
if ~exist(targetFolder, 'dir')
    % 如果不存在，则创建该文件夹
    mkdir(targetFolder);
end

% 调用uigetfile函数，让用户选择一个文件
[file, path] = uigetfile('*.slx', '选择需要生成代码的模型文件');

% 检查用户是否选择了文件
if isequal(file, 0)
    disp('用户取消了选择');
else
    % 获取完整的文件名（包括路径）
    fullFileName = fullfile(path, file);
    % 使用fileparts分解文件名
    [filename, pathname, ext] = fileparts(file);
    
    % 输出不包含后缀的文件名
    disp(fullfile(pathname, filename)); % 这将输出myModel，不含后缀
    
end

%  将用户输入的模型名作为参数传递给函数
code_gen_to_project(pathname, targetFolder);


% 删除生成的C/C++源代码时间注释,版本注释
subfolder_files = dir(fullfile(targetFolder, '*'));
for k = 1:length(subfolder_files)
    if endsWith(subfolder_files(k).name, '.c') || endsWith(subfolder_files(k).name, '.h')
        deleteLineFromFile(fullfile(targetFolder, subfolder_files(k).name), 10);  % 删除* Model version
        deleteLineFromFile(fullfile(targetFolder, subfolder_files(k).name), 11);  % 删除* C/C++ source code generated on
    end
end

% 删除指定行
function deleteLineFromFile(filename, lineNumber)

    fid = fopen(filename, 'r');
    
    if fid == -1
        error('无法打开文件：%s', filename);
    end
    
    fileContent = {};
    tline = fgetl(fid);
    while ischar(tline)
        fileContent{end+1} = tline;
        tline = fgetl(fid);
    end
    
    fclose(fid);
    
    % 检查行号范围是否有效
    if lineNumber > 0 && lineNumber <= length(fileContent)
        %如果fileContent(lineNumber)内容包含* C/C++ source code generated on
        %或者 * Model version 则删除该行
        %删除指定行
        if (contains(fileContent{lineNumber}, '* C/C++ source code generated on') || contains(fileContent{lineNumber}, ' * Model version'))
            fileContent(lineNumber) = [];
        end
    else
        warning('指定的行号无效：%d', lineNumber);
        return;
    end
    
    fid = fopen(filename, 'w');
    
    if fid == -1
        error('无法打开文件：%s', filename);
    end
    
    for i = 1:length(fileContent)
        fprintf(fid, '%s\n', fileContent{i});
    end

    fclose(fid);
    
end
