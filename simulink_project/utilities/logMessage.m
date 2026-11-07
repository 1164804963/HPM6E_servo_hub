function logMessage(logFileName, message)
    % 打开文件以读模式 ('r')
    fileID = fopen(logFileName, 'r');
    if fileID == -1
        % 文件不存在，创建一个新的空文件
        old_logs = '';
    else
        % 读取现有日志文件内容
        old_logs = fread(fileID, '*char')';
        fclose(fileID);
    end

    % 创建并写入新的日志信息
    timestamp = datestr(now, 'yyyy-mm-dd HH:MM:SS'); % 当前时间戳
    new_log = sprintf('[%s] %s\n', timestamp, message);

    % 合并新日志和旧日志
    updated_logs = [new_log old_logs];

    % 打开文件以写模式 ('w')
    fileID = fopen(logFileName, 'w');
    if fileID == -1
        error('Failed to open log file.');
    end

    % 写入更新后的日志信息
    fwrite(fileID, updated_logs, 'char');
    fclose(fileID);
end