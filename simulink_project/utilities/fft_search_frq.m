function max_frq = fft_search_frq(Ts, t, y)
%POLYFIX_DIV Summary of this function goes here
%   Detailed explanation goes here
    % 参数设置
    Fs = 1/Ts;            % 采样频率 (Hz)
    
    L = length(y);             % 信号长度
     
    
    % 对信号y进行FFT
    Y = fft(y);
    
    % 计算双边频谱 P2
    P2 = abs(Y/L);
    % 计算单边频谱 P1
    P1 = P2(1:L/2+1);
    P1(2:end-1) = 2*P1(2:end-1);
    
    % 定义频率向量
    f = Fs*(0:(L/2))/L;
    
    % 使用 findpeaks 函数找到峰值
    [peaks, locs] = findpeaks(P1, 'SortStr', 'descend');
    
    % 对找到的峰值和位置进行排序（这里已按振幅大小降序排序）
    sorted_peaks = peaks;
    sorted_freqs = f(locs);
    
    disp('max freqs is ');
    disp(sorted_freqs(1));
   
    disp('secend max freqs is ');
    disp(sorted_freqs(2));
    
    max_frq(1) = sorted_freqs(1);
    max_frq(2) = sorted_freqs(2);

    % 绘制结果
    figure;
    
    % 时域信号
    subplot(2, 1, 1);
    plot(t, y);
    title('Time Domain Signal');
    xlabel('Time (seconds)');
    ylabel('Amplitude');
    
    % 频谱（幅值）
    subplot(2, 1, 2);
    plot(f, P1);
    title('Single-Sided Amplitude Spectrum of y(t)');
    xlabel('Frequency (Hz)');
    ylabel('|P1(f)|');
    hold on;
    plot(f(locs), peaks, 'ro'); % 标记峰值
    hold off;
end

