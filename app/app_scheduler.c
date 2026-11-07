#include "app_scheduler.h"

// 应用程序信息结构体
AppInfo kAppInfo[APP_NUM];

// 应用程序列表
static const AppTable app_table[APP_NUM] =
{
    {APP_PP_MODE, PpModeInit, PpModeStart, PpModeRun, PpModeStop, APP_TYPE_PDS},
    {APP_PV_MODE, PvModeInit, PvModeStart, PvModeRun, PvModeStop, APP_TYPE_PDS},
    {APP_PT_MODE, PtModeInit, PtModeStart, PtModeRun, PtModeStop, APP_TYPE_PDS},
    {APP_MIT_MODE, MitModeInit, MitModeStart, MitModeRun, MitModeStop, APP_TYPE_PDS},
    {APP_HM_MODE, HomingModeInit, HomingModeStart, HomingModeRun, HomingModeStop, APP_TYPE_PDS},
    {APP_CSP_MODE, CspModeInit, CspModeStart, CspModeRun, CspModeStop, APP_TYPE_PDS},
    {APP_CSV_MODE, CsvModeInit, CsvModeStart, CsvModeRun, CsvModeStop, APP_TYPE_PDS},
    {APP_CST_MODE, CstModeInit, CstModeStart, CstModeRun, CstModeStop, APP_TYPE_PDS},
    {APP_DIR_ID_MODE, IdDirModeInit, IdDirModeStart, IdDirModeRun, IdDirModeStop, APP_TYPE_PDS},
    {APP_ELEC_ANGLE_ID_MODE, IdElecAngleModeInit, IdElecAngleModeStart, IdElecAngleModeRun, IdElecAngleModeStop, APP_TYPE_PDS},
    {APP_ELEC_ID_MODE, IdElecModeInit, IdElecModeStart, IdElecModeRun, IdElecModeStop, APP_TYPE_PDS},
    {APP_MEC_ID_MODE, IdMecModeInit, IdMecModeStart, IdMecModeRun, IdMecModeStop, APP_TYPE_PDS},
    {APP_POLE_PAIRS_ID_MODE, IdPolePairsModeInit, IdPolePairsModeStart, IdPolePairsModeRun, IdPolePairsModeStop, APP_TYPE_PDS},
    {APP_TQ_FC_ID_MODE, IdTqFcModeInit, IdTqFcModeStart, IdTqFcModeRun, IdTqFcModeStop, APP_TYPE_PDS},
    {APP_NULL, NULL, NULL, NULL, NULL, APP_TYPE_PDS}, // 用于表示空闲状态
};

// APP初始化
void AppInit(void)
{
    for (int i = 0; i < APP_NUM; i++)
    {
        kAppInfo[i].app_ptr = &app_table[i];   // 设置应用程序指针
        kAppInfo[i].enable = false;            // 禁用应用程序
        kAppInfo[i].app_state = APP_STA_IDLE;  // 设置应用程序状态为空闲
        kAppInfo[i].app_result = APP_RET_IDLE; // 设置应用程序结果为空闲
    }
}


// 运行应用程序
void AppRun(uint8_t hw_ready_state)
{
    // 遍历应用程序列表
    for (int i = 0; i < APP_NUM; i++)
    {
        if (kAppInfo[i].enable)
        {

            // 启动应用程序
            if (kAppInfo[i].app_state == APP_STA_READY)
            {

                if (kAppInfo[i].app_ptr->start != NULL)
                {
                    kAppInfo[i].app_result = kAppInfo[i].app_ptr->start();
                    if (kAppInfo[i].app_result == APP_RET_RUNNING)
                    { // start处于等待状态
                        kAppInfo[i].app_state = APP_STA_READY;
                    }
                    else if (kAppInfo[i].app_result == APP_RET_SUCCESS)
                    { // start成功,进入run状态
                        kAppInfo[i].app_state = APP_STA_RUNNING;
                    }
                    else if (kAppInfo[i].app_result == APP_RET_FAIL)
                    { // start失败,进入错误状态
                        kAppInfo[i].app_state = APP_STA_ERROR;
                    }
                }
            }

            // 运行应用程序
            if (kAppInfo[i].app_state == APP_STA_RUNNING)
            {
                if (kAppInfo[i].app_ptr->run != NULL)
                {
                    // 回读PWM准备好状态，准备好则运行APP 否则等待处于 READY 状态
                    if (hw_ready_state)
                    {
                        kAppInfo[i].app_result = kAppInfo[i].app_ptr->run();
                        if (kAppInfo[i].app_result == APP_RET_RUNNING)
                        {
                            kAppInfo[i].app_state = APP_STA_RUNNING;
                        }
                        else if (kAppInfo[i].app_result == APP_RET_SUCCESS)
                        {
                            kAppInfo[i].app_state = APP_STA_SUCCESS;
                        }
                        else if (kAppInfo[i].app_result == APP_RET_FAIL)
                        {
                            kAppInfo[i].app_state = APP_STA_ERROR;
                        }
                    }
                    else
                    {
                        kAppInfo[i].app_state = APP_STA_READY;
                    }
                }
            }

            // 停止应用程序
            if ((kAppInfo[i].app_state == APP_STA_SUCCESS) || (kAppInfo[i].app_state == APP_STA_ERROR))
            {
                if (kAppInfo[i].app_ptr->stop != NULL)
                {
                    kAppInfo[i].app_ptr->stop();
                }
                kAppInfo[i].enable = false;           // 禁用应用程序
                kAppInfo[i].app_state = APP_STA_IDLE; // 设置应用程序状态为空闲
            }
        }
    }
}

// 停止当前应用程序
void AppStop(APP_NAMES name)
{
    for (int i = 0; i < APP_NUM; i++)
    {
        if (app_table[i].name == name)
        {
            if (kAppInfo[i].app_ptr->stop != NULL)
            {
                kAppInfo[i].app_ptr->stop(); // 停止应用程序
            }
            kAppInfo[i].app_state = APP_STA_IDLE; // 设置应用程序状态为空闲
            kAppInfo[i].enable = false;           // 禁用应用程序
            break;
        }
    }
}

// 设置应用程序
void set_app(APP_NAMES name)
{
    for (int i = 0; i < APP_NUM; i++)
    {
        if (app_table[i].name == name)
        {
            // APP_TYPE_PDS类型的应用程序只能运行一个
            if (app_table[i].type == APP_TYPE_PDS)
            {
                for (int j = 0; j < APP_NUM; j++)
                {
                    if (app_table[j].type == APP_TYPE_PDS && app_table[j].name != name)
                    {
                        if (kAppInfo[j].app_state != APP_STA_IDLE)
                        {
                            // 若有PDS类型的应用程序正在运行，则停止它
                            AppStop(app_table[j].name);
                        }
                    }
                }
            }
            // APP_TYPE_NORMOL类型的应用程序可以同时运行多个
            else if (app_table[i].type == APP_TYPE_NORMOL)
            {
                // 如果当前应用程序正在运行，则停止它
                if (kAppInfo[i].app_state != APP_STA_IDLE)
                {
                    AppStop(app_table[i].name);
                }
            }

            // 初始化应用程序
            if (kAppInfo[i].app_ptr->init != NULL)
            {
                if (kAppInfo[i].app_ptr->init() == APP_RET_SUCCESS)
                {
                    kAppInfo[i].app_state = APP_STA_READY;
                }
                else
                {
                    kAppInfo[i].app_state = APP_STA_ERROR;
                }
            }

            kAppInfo[i].enable = true;             // 启用应用程序
            kAppInfo[i].app_result = APP_RET_IDLE; // 设置应用程序结果为空闲
            break;
        }
    }
}

// 获取当前应用程序信息
AppInfo get_current_app_info(APP_NAMES name)
{
    for (int i = 0; i < APP_NUM; i++)
    {
        if (app_table[i].name == name)
        {
            return kAppInfo[i];
        }
    }
    return (AppInfo){0}; // 返回一个空的应用程序信息结构体
}
