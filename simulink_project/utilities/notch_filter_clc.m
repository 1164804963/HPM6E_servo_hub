function [y1, y0, u2, u1, u0] = notch_filter_clc(b0, b2, depth, t)
    % b0 是位置,b2 是宽度，depth 是深度 t 是采样时间
    b1 = depth * b2;

    num3 = (t^2*b0^2 + 2*b1*t + 4) / (t^2*b0^2 + 2*b2*t + 4);
    num2 = (2*t^2*b0^2 - 8) / (t^2*b0^2 + 2*b2*t + 4);
    num1 = (t^2*b0^2 - 2*b1*t + 4) / (t^2*b0^2 + 2*b2*t + 4);
    den3 = 1;
    den2 = (2*t^2*b0^2 - 8) / (t^2*b0^2 + 2*b2*t + 4);
    den1 = (t^2*b0^2 - 2*b2*t + 4) / (t^2*b0^2 + 2*b2*t + 4);

    u2=num3; 
    u1=num2; 
    u0=num1;
    y0=-den1;
    y1=-den2;
end