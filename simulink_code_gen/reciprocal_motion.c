/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: reciprocal_motion.c
 *
 * Code generated for Simulink model 'reciprocal_motion'.
 *
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "reciprocal_motion.h"
#include "servo_hub_database_type.h"
#include <math.h>
#include "yuanhub_math.h"
#include "rtwtypes.h"

/* System initialize for referenced model: 'reciprocal_motion' */
void reciprocal_motion_Init(void)
{
    /* '<S3>:1:11' q0_int = int64(0); */
    /* '<S3>:1:12' q0_dec = single(0); */
    /* '<S3>:1:13' dq0 = single(0); */
    /* '<S3>:1:14' ddq0 = single(0); */
    /* '<S3>:1:15' state = int8(0); */
    /* '<S2>:1:7' times = single(0); */
    /*   true目标位置1   flase目标位置2 */
    /* '<S2>:1:10' pos_id = boolean(0); */
}

/* Output and update for referenced model: 'reciprocal_motion' */
void reciprocal_motion(const ReciprocalMotionConfig *rtu_config,
                       ReciprocalMotionOutput *rty_output,
                       reciprocal_motion_DW_f *localDW)
{
    int64_T qY;
    int32_T hd;
    real32_T aa;
    real32_T ad;
    real32_T ad_inv;
    real32_T h;
    real32_T v0_2;
    real32_T vmax_abs;
    int8_T state;
    boolean_T tmp;

    /* MATLAB Function: '<S1>/tv_tra_gen' incorporates:
     *  Delay: '<Root>/Delay'
     */
    /*  state_now  规划状态   */
    /*  0 初始状态 */
    /*  1 规划完成 */
    /*  2 规划中 */
    /* MATLAB Function 'pos_trajectory_planning/tv_tra_gen': '<S3>:1' */
    /* '<S3>:1:10' if isempty(q0_int) */
    /* '<S3>:1:19' vmax_abs = abs(vmax); */
    vmax_abs = fabsf(rtu_config->profile_velocity_p_s);

    /* '<S3>:1:20' q1 = int64(pos_tar); */
    /* '<S3>:1:21' v0 = single(dq0); */
    /* '<S3>:1:22' v0_2 = v0 * v0; */
    v0_2 = localDW->dq0 * localDW->dq0;

    /* '<S3>:1:23' v1 = single(0); */
    /* '<S3>:1:24' v1_2 = v1 * v1; */
    /* '<S3>:1:25' h = single(pos_tar - q0_int) - q0_dec; */
    tmp = ((localDW->pos_last >= 0LL) && (localDW->q0_int < localDW->pos_last -
            MAX_int64_T));
    if (tmp)
    {
        qY = MAX_int64_T;
    }
    else if ((localDW->pos_last < 0LL) && (localDW->q0_int > localDW->pos_last -
              MIN_int64_T))
    {
        qY = MIN_int64_T;
    }
    else
    {
        qY = localDW->pos_last - localDW->q0_int;
    }

    h = (real32_T)qY - localDW->q0_dec;

    /* 规划误差 */
    /* '<S3>:1:26' aa = abs(acc); */
    /* '<S3>:1:27' ad = abs(dec); */
    ad = fabsf(rtu_config->profile_dec_p_ss);

    /* '<S3>:1:28' aa_inv = single(0); */
    /* '<S3>:1:29' ad_inv = single(0); */
    /* '<S3>:1:30' vf = single(0); */
    /* '<S3>:1:31' Vv = single(0); */
    /* '<S3>:1:32' dt = Ts; */
    /* '<S3>:1:33' dt_inv_ = single(1.0 / dt); */
    /* '<S3>:1:34' Ta = single(0); */
    /* '<S3>:1:35' La = single(0); */
    /* '<S3>:1:36' Td = single(0); */
    /* '<S3>:1:37' Ld = single(0); */
    /* '<S3>:1:38' Tv = single(0); */
    /* '<S3>:1:39' Lv = single(0); */
    /* '<S3>:1:40' tt = single(0); */
    /* '<S3>:1:41' hd = single(1); */
    /* 误差方向 */
    /* '<S3>:1:43' if (h >= 0) */
    if (h >= 0.0F)
    {
        /* 判断误差方向 */
        /* '<S3>:1:44' hd = single(1); */
        hd = 1;
    }
    else
    {
        /* '<S3>:1:45' else */
        /* '<S3>:1:46' hd = single(-1); */
        hd = -1;
    }

    /*  轮廓速度非常小 等于 0   暂停指令会将轮廓速度设置为0 */
    /* '<S3>:1:50' if (abs(vmax_abs) < single(0.00001)) */
    if (vmax_abs < 1.0E-5F)
    {
        /* '<S3>:1:51' if (v0 > 0) */
        if (localDW->dq0 > 0.0F)
        {
            /* '<S3>:1:52' ddq0 = -ad; */
            aa = -ad;
        }
        else
        {
            /* '<S3>:1:53' else */
            /* '<S3>:1:54' ddq0 = ad; */
            aa = ad;
        }

        /* 根据速度判断规划完成 */
        /* '<S3>:1:58' if (abs(v0) < (int32(abs(ad * dt)) + int32(1))) */
        ad_inv = roundf(fabsf(ad * rtu_config->dt_s));
        if (ad_inv < 2.14748365E+9F)
        {
            hd = (int32_T)ad_inv;
        }
        else
        {
            hd = MAX_int32_T;
        }

        if (hd > 2147483646)
        {
            hd = MAX_int32_T;
        }
        else
        {
            hd++;
        }

        if ((real_T)fabsf(localDW->dq0) < hd)
        {
            /* '<S3>:1:59' dq0 = single(0); */
            localDW->dq0 = 0.0F;

            /* '<S3>:1:60' ddq0 = single(0); */
            aa = 0.0F;

            /* '<S3>:1:61' state = int8(1); */
            state = 1;

            /* 规划完成 */
        }
        else
        {
            /* '<S3>:1:62' else */
            /* '<S3>:1:63' dq0 = dq0 + ddq0 * dt; */
            localDW->dq0 += aa * rtu_config->dt_s;

            /* '<S3>:1:64' q0_dec = q0_dec + (dq0+ single(0.5) * ddq0 * dt) * dt; */
            localDW->q0_dec += (0.5F * aa * rtu_config->dt_s + localDW->dq0) *
                rtu_config->dt_s;

            /* '<S3>:1:65' state = int8(2); */
            state = 2;

            /* 规划中 */
        }

        /*  异常规划 */
    }
    else
    {
        ad_inv = (real32_T)hd * localDW->dq0;
        if (ad_inv < 0.0F)
        {
            /* '<S3>:1:68' elseif (hd * v0 < single(0)) */
            /* 需要先减速到 0 */
            /* '<S3>:1:69' ddq0 = hd * ad; */
            aa = (real32_T)hd * ad;

            /* '<S3>:1:70' dq0 = dq0 + ddq0 * dt; */
            localDW->dq0 += aa * rtu_config->dt_s;

            /* '<S3>:1:71' q0_dec = q0_dec + (dq0+ single(0.5) * ddq0 * dt) * dt; */
            localDW->q0_dec += (0.5F * aa * rtu_config->dt_s + localDW->dq0) *
                rtu_config->dt_s;

            /* '<S3>:1:72' state = int8(2); */
            state = 2;

            /* 规划中 */
        }
        else if (ad_inv > vmax_abs)
        {
            /* '<S3>:1:73' elseif (hd * v0 > vmax_abs) */
            /* 先减速到最大速度限制 */
            /* '<S3>:1:74' if (hd * (dq0+ (-hd * ad * dt)) <  vmax_abs) */
            aa = -(real32_T)hd * ad;
            ad_inv = aa * rtu_config->dt_s + localDW->dq0;
            if (ad_inv * (real32_T)hd < vmax_abs)
            {
                /* 判断速度越界 */
                /* '<S3>:1:75' ddq0 = (hd * vmax_abs - v0) * dt_inv_; */
                vmax_abs *= (real32_T)hd;
                aa = (vmax_abs - localDW->dq0) * (1.0F / rtu_config->dt_s);

                /* '<S3>:1:76' dq0 = hd * vmax_abs; */
                localDW->dq0 = vmax_abs;
            }
            else
            {
                /* '<S3>:1:77' else */
                /* '<S3>:1:78' ddq0 = -hd * ad; */
                /* '<S3>:1:79' dq0 = dq0 + ddq0 * dt; */
                localDW->dq0 = ad_inv;
            }

            /* '<S3>:1:81' q0_dec = q0_dec + (dq0+ single(0.5) * ddq0 * dt) * dt; */
            localDW->q0_dec += (0.5F * aa * rtu_config->dt_s + localDW->dq0) *
                rtu_config->dt_s;

            /* '<S3>:1:82' state = int8(2); */
            state = 2;

            /* 规划中 */
            /*  正常规划 */
        }
        else
        {
            real32_T La;
            real32_T Ld;
            real32_T Td;
            real32_T aa_inv;
            real32_T v0_2_tmp;
            real32_T vf;

            /* '<S3>:1:84' else */
            /* '<S3>:1:85' aa = hd * aa; */
            aa = (real32_T)hd * fabsf(rtu_config->profile_acc_p_ss);

            /* 加速度 */
            /* '<S3>:1:86' ad = -hd * ad; */
            ad *= -(real32_T)hd;

            /* 减速度 */
            /* '<S3>:1:88' aa_inv = single(1) / aa; */
            aa_inv = 1.0F / aa;

            /* '<S3>:1:89' ad_inv = single(1) / ad; */
            ad_inv = 1.0F / ad;

            /*  确定运行过程中最大速度 */
            /* '<S3>:1:92' kk = single(ad * aa / (ad - aa)); */
            /* 运算公共系数 */
            /*  计算运动过程中最大速度 */
            /* '<S3>:1:95' vf = sqrt((single(2) * h - v1_2 * ad_inv + v0_2 * aa_inv) * kk); */
            /* '<S3>:1:97' vf = hd * vf; */
            vf = yuanhub_sqrt_f32((2.0F * h + v0_2 * aa_inv) * (ad * aa / (ad -
                                    aa))) * (real32_T)hd;

            /* '<S3>:1:99' if (hd * vf >= vmax_abs) */
            if ((real32_T)hd * vf >= vmax_abs)
            {
                /* '<S3>:1:100' Vv = hd * vmax_abs; */
                vf = (real32_T)hd * vmax_abs;
            }
            else
            {
                /* '<S3>:1:101' else */
                /* '<S3>:1:102' Vv = vf; */
            }

            /*  计算加速和减速段时间 */
            /* '<S3>:1:106' Ta = (Vv - v0) * aa_inv; */
            vmax_abs = (vf - localDW->dq0) * aa_inv;

            /* '<S3>:1:107' La = (v0 + single(0.5) * aa * Ta) * Ta; */
            La = (0.5F * aa * vmax_abs + localDW->dq0) * vmax_abs;

            /* '<S3>:1:108' Td = (v1 - Vv) * ad_inv; */
            Td = (0.0F - vf) * ad_inv;

            /* '<S3>:1:109' Ld = (Vv + single(0.5) * ad * Td) * Td; */
            Ld = (0.5F * ad * Td + vf) * Td;

            /* '<S3>:1:110' Tv = (h - (Vv * Vv - v0_2) * single(0.5) * aa_inv - (v1_2 - Vv * Vv) * ... */
            /* '<S3>:1:111'         single(0.5) * ad_inv) / Vv; */
            v0_2_tmp = vf * vf;
            v0_2 = ((h - (v0_2_tmp - v0_2) * 0.5F * aa_inv) - (0.0F - v0_2_tmp) *
                    0.5F * ad_inv) / vf;

            /* '<S3>:1:112' Lv = h - La - Ld; */
            /* '<S3>:1:113' tt = dt - Ta - Tv; */
            v0_2_tmp = rtu_config->dt_s - vmax_abs;
            aa_inv = v0_2_tmp - v0_2;

            /* '<S3>:1:115' if (dt < Ta) */
            if (rtu_config->dt_s < vmax_abs)
            {
                /*  加速时间 */
                /* '<S3>:1:116' q0_dec = q0_dec + (dq0+ single(0.5) * aa * dt) * dt; */
                localDW->q0_dec += (0.5F * aa * rtu_config->dt_s + localDW->dq0)
                    * rtu_config->dt_s;

                /* '<S3>:1:117' dq0 = dq0 + aa * dt; */
                localDW->dq0 += aa * rtu_config->dt_s;

                /* '<S3>:1:118' ddq0 = aa; */
                /* '<S3>:1:119' state = int8(2); */
                state = 2;

                /* 规划中 */
            }
            else
            {
                ad_inv = vmax_abs + v0_2;
                if ((rtu_config->dt_s >= vmax_abs) && (rtu_config->dt_s <=
                        ad_inv))
                {
                    /* '<S3>:1:120' elseif (dt >= Ta && (dt <= (Ta + Tv))) */
                    /* 匀速时间 */
                    /* '<S3>:1:121' q0_dec = q0_dec + La + Vv * (dt - Ta); */
                    localDW->q0_dec = v0_2_tmp * vf + (localDW->q0_dec + La);

                    /* '<S3>:1:122' dq0 = Vv; */
                    localDW->dq0 = vf;

                    /* '<S3>:1:123' ddq0 = single(0); */
                    aa = 0.0F;

                    /* '<S3>:1:124' state = int8(2); */
                    state = 2;

                    /* 规划中 */
                }
                else if ((rtu_config->dt_s > ad_inv) && (rtu_config->dt_s <
                          ad_inv + Td))
                {
                    /* '<S3>:1:125' elseif ((dt > Ta + Tv) && (dt < Ta + Tv + Td)) */
                    /*  减速时间 */
                    /* '<S3>:1:126' pos_err = int64(pos_tar - q0_int); */
                    if (tmp)
                    {
                        qY = MAX_int64_T;
                    }
                    else if ((localDW->pos_last < 0LL) && (localDW->q0_int >
                              localDW->pos_last - MIN_int64_T))
                    {
                        qY = MIN_int64_T;
                    }
                    else
                    {
                        qY = localDW->pos_last - localDW->q0_int;
                    }

                    /* '<S3>:1:127' Ld_int = int64(Ld); */
                    ad_inv = roundf(Ld);
                    if (ad_inv < 9.22337204E+18F)
                    {
                        if (ad_inv >= -9.22337204E+18F)
                        {
                            localDW->x = (int64_T)ad_inv;
                        }
                        else
                        {
                            localDW->x = MIN_int64_T;
                        }
                    }
                    else
                    {
                        localDW->x = MAX_int64_T;
                    }

                    /* '<S3>:1:129' if (abs(Ld_int) > abs(pos_err)) */
                    if (localDW->x < 0LL)
                    {
                        if (localDW->x <= MIN_int64_T)
                        {
                            localDW->x = MAX_int64_T;
                        }
                        else
                        {
                            localDW->x = -localDW->x;
                        }
                    }

                    if (qY < 0LL)
                    {
                        if (qY <= MIN_int64_T)
                        {
                            qY = MAX_int64_T;
                        }
                        else
                        {
                            qY = -qY;
                        }
                    }

                    if (localDW->x > qY)
                    {
                        /* 先减速到 0 */
                        /* '<S3>:1:130' ddq0 = ad; */
                        aa = ad;

                        /* '<S3>:1:131' dq0 = dq0 + ddq0 * dt; */
                        localDW->dq0 += ad * rtu_config->dt_s;

                        /* '<S3>:1:132' q0_dec = q0_dec + (dq0 + single(0.5) * ddq0 * dt) * dt; */
                        localDW->q0_dec += (0.5F * ad * rtu_config->dt_s +
                                            localDW->dq0) * rtu_config->dt_s;

                        /* '<S3>:1:133' state = int8(2); */
                        state = 2;

                        /* 规划中 */
                    }
                    else
                    {
                        /* '<S3>:1:134' else */
                        /* '<S3>:1:135' q0_dec = q0_dec + La + Lv + (Vv + single(0.5) * ad * tt) * tt; */
                        localDW->q0_dec = (0.5F * ad * aa_inv + vf) * aa_inv +
                            (((h - La) - Ld) + (localDW->q0_dec + La));

                        /* '<S3>:1:136' dq0 = Vv + ad * tt; */
                        localDW->dq0 = ad * aa_inv + vf;

                        /* '<S3>:1:137' ddq0 = ad; */
                        aa = ad;

                        /* '<S3>:1:138' state = int8(2); */
                        state = 2;

                        /* 规划中 */
                    }
                }
                else
                {
                    /* '<S3>:1:140' else */
                    /* 即将到达目标位置 */
                    /* '<S3>:1:141' q0_int = q1; */
                    localDW->q0_int = localDW->pos_last;

                    /* '<S3>:1:142' q0_dec = single(0); */
                    localDW->q0_dec = 0.0F;

                    /* '<S3>:1:143' dq0 = single(0); */
                    localDW->dq0 = 0.0F;

                    /* '<S3>:1:144' ddq0 = single(0); */
                    aa = 0.0F;

                    /* '<S3>:1:145' state = int8(1); */
                    state = 1;

                    /* 规划完成 */
                }
            }
        }
    }

    /* '<S3>:1:150' q0_dec_int = int64(q0_dec); */
    ad_inv = roundf(localDW->q0_dec);
    if (ad_inv < 9.22337204E+18F)
    {
        if (ad_inv >= -9.22337204E+18F)
        {
            qY = (int64_T)ad_inv;
        }
        else
        {
            qY = MIN_int64_T;
        }
    }
    else
    {
        qY = MAX_int64_T;
    }

    /* '<S3>:1:152' q0_dec = q0_dec - single(q0_dec_int); */
    localDW->q0_dec -= (real32_T)qY;

    /* '<S3>:1:153' q0_int = q0_int + q0_dec_int; */
    if ((localDW->q0_int < 0LL) && (qY < MIN_int64_T - localDW->q0_int))
    {
        localDW->q0_int = MIN_int64_T;
    }
    else if ((localDW->q0_int > 0LL) && (qY > MAX_int64_T - localDW->q0_int))
    {
        localDW->q0_int = MAX_int64_T;
    }
    else
    {
        localDW->q0_int += qY;
    }

    /* '<S3>:1:155' q_int = q0_int; */
    /* '<S3>:1:156' q_dec = q0_dec; */
    /* '<S3>:1:157' dq = dq0; */
    rty_output->v_tar_p_s = localDW->dq0;

    /* '<S3>:1:158' ddq = ddq0; */
    rty_output->acc_tar_p_ss = aa;

    /* '<S3>:1:159' state_now = state; */
    rty_output->state_now = state;

    /* BusCreator: '<Root>/Bus Creator' incorporates:
     *  MATLAB Function: '<S1>/tv_tra_gen'
     */
    rty_output->pos_tar_p = localDW->q0_int;

    /* MATLAB Function: '<Root>/reciprocal_motion' incorporates:
     *  MATLAB Function: '<S1>/tv_tra_gen'
     */
    /* MATLAB Function 'reciprocal_motion': '<S2>:1' */
    /* '<S2>:1:6' if isempty(times) */
    /* '<S2>:1:9' if isempty(pos_id) */
    /* 到达目标位置累计时间 */
    /* '<S2>:1:14' if pos_gen == pos1 || pos_gen == pos2 */
    if ((localDW->q0_int == rtu_config->pos_tar1_p) || (localDW->q0_int ==
            rtu_config->pos_tar2_p))
    {
        /* '<S2>:1:15' times = times + dt; */
        localDW->times += rtu_config->dt_s;
    }
    else
    {
        /* '<S2>:1:16' else */
        /* 规划中 时间清零 */
        /* '<S2>:1:17' times = single(0); */
        localDW->times = 0.0F;
    }

    /* '<S2>:1:21' if times >= wait */
    if (localDW->times >= rtu_config->dwell_time_s)
    {
        /* '<S2>:1:22' times = single(0); */
        localDW->times = 0.0F;

        /* '<S2>:1:23' pos_id = ~pos_id; */
        localDW->pos_id = !localDW->pos_id;
    }

    /* '<S2>:1:26' if pos_id == boolean(0) */
    if (!localDW->pos_id)
    {
        /* Update for Delay: '<Root>/Delay' */
        /* '<S2>:1:27' pos_tar = pos2; */
        localDW->pos_last = rtu_config->pos_tar2_p;
    }
    else
    {
        /* Update for Delay: '<Root>/Delay' */
        /* '<S2>:1:28' else */
        /* '<S2>:1:29' pos_tar = pos1; */
        localDW->pos_last = rtu_config->pos_tar1_p;
    }

    /* End of MATLAB Function: '<Root>/reciprocal_motion' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
