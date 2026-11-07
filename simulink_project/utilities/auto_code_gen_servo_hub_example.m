% 获取脚本所在目录
scriptDir = fileparts(mfilename('fullpath'));

% 获取工作目录
workDir = fileparts(scriptDir);

% 获取当前工作目录
currentDir = pwd;

% 如果不同，则切换到脚本目录
if ~strcmp(workDir, currentDir)
    cd(workDir);
end
disp(['当前工作目录：', pwd()]);

targetFolder = '..\simulink_code_gen';
codegenFolder = '.\code_gen';

%检查文件夹是否存在
if ~exist(targetFolder, 'dir')
    % 如果不存在，则创建该文件夹
    mkdir(targetFolder);
end

%清除之前生成的代码
delete([targetFolder,'\*.c']);
delete([targetFolder,'\*.h']);
delete([targetFolder,'\*.cpp']);
delete([targetFolder,'\*.hpp']);

delete([codegenFolder,'\*.c']);
delete([codegenFolder,'\*.h']);
delete([codegenFolder,'\*.cpp']);
delete([codegenFolder,'\*.hpp']);

%  将用户输入的模型名作为参数传递给函数
code_gen_to_project('servo_hub_example', targetFolder);


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
