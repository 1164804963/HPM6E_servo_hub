function code_gen_to_project(model_name, targetFolder)
%将model_name 模型生成代码，代码复制到指令的工程文件夹
    ModelName = model_name;
    sourceFolder = 'code_gen';  %会临时生成本地文件夹
    
    %% 清除之前所有缓存
    clear_buff;  
    
    %% 模型生成代码
    load_system(ModelName); % 载入模型到计算机内存，不会显示UI界面
    rtwbuild(ModelName); % 生成代码核心函数
 
    %% 代码打包到 本地临时 code_gen 文件夹
    code_move;
    

    %% 复制所有代码到 targetFolder

    % 检查源文件夹是否存在
    if ~exist(sourceFolder, 'dir')
        error('源文件夹不存在。');
    end


    % 获取源文件夹中的所有文件
    files = dir(fullfile(sourceFolder, '*')); % 获取所有文件和文件夹
    files = files(~[files.isdir]); % 过滤掉文件夹，只保留文件
    
    % 复制每个文件到目标文件夹
    for i = 1:length(files)
        srcFile = fullfile(sourceFolder, files(i).name); % 源文件的完整路径
        destFile = fullfile(targetFolder, files(i).name); % 目标文件的完整路径
        copyfile(srcFile, destFile); % 复制文件
    end
    
    disp('所有文件已成功复制。');
    disp('succes~!');
end