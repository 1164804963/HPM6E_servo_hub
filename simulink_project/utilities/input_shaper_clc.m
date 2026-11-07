function [A, T] = input_shaper_clc(xi, wn_rad_s, dt, type)
    e =2.718281828;
    V=0.0;  % 残余振动比
    
    if type==1 % ZV
        t2=pi/(wn_rad_s*sqrt(1-xi^2));
        A1=e^(xi*wn_rad_s*t2)/(1+e^(xi*wn_rad_s*t2));
        A2=1/(1+e^(xi*wn_rad_s*t2));
        A3=0;    
       
    elseif type==2 % ZVD
        t2=pi/(wn_rad_s*sqrt(1-xi^2));
        K=e^(-xi*pi/sqrt(1-xi^2));
        A1=1/(1+2*K+K^2);
        A2=2*K/(1+2*K+K^2);
        A3=K^2/(1+2*K+K^2);
        
    elseif type==3 % EI
        A1 = (1+V)/4;
        A2 = (1-V)/2;
        A3 = (1+V)/4;
        t2 = pi/wn_rad_s;
    end
    t1_num = uint32(0);
    t2_num = uint32(t2/dt);
    t3_num = 2*t2_num;
    A = [A1 A2 A3];
    T = [t1_num t2_num t3_num];
end