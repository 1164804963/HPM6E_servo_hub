
    % 获取当前文件夹路径
    currentFolder = pwd;
    
    % 定义要处理的文件类型（例如：所有文本文件）
    fileExtensions = {'*.c', '*.h', '*.cpp'};
    
    % 创建备份文件夹（防止误操作）
    backupDir = fullfile(currentFolder, 'backup_before_crlf_conversion');
    if ~exist(backupDir, 'dir')
        mkdir(backupDir);
    end
    
    % 遍历所有指定类型的文件
    for i = 1:length(fileExtensions)
        fileList = dir(fullfile(currentFolder, fileExtensions{i}));
        for j = 1:length(fileList)
            filePath = fullfile(fileList(j).folder, fileList(j).name);
            
            % 备份原文件
            copyfile(filePath, fullfile(backupDir, fileList(j).name));
            
            % 读取文件内容（自动检测编码）
            fid = fopen(filePath, 'r', 'n', 'UTF-8'); % UTF-8 编码读取
            content = fread(fid, '*char')';
            fclose(fid);
            
            % 替换 LF (\n) 为 CRLF (\r\n)
            content = strrep(content, newline, sprintf('\r\n'));
            
            % 重新写入文件（UTF-8 编码）
            fid = fopen(filePath, 'w', 'n', 'UTF-8');
            fwrite(fid, content, 'char');
            fclose(fid);
        end
    end
    disp('转换完成！原文件已备份至 backup_before_crlf_conversion 文件夹。');