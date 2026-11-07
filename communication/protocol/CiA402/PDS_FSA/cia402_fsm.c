#include "cia402_fsm.h"
#include "cia402_error_code.h"
#include "cia402_statusword.h"
#include "Cia402_ObjectDictionary_Variable.h"
#include "app_profile_position_mode.h"
#include "data_param.h"

static bool last_fault_reset_bit = false;
static uint16_t last_controlword = 0;
Cia402State CurrentState = kStart; // Initial state
static bool quick_stop_start_flag = false;
static void PDS_FSA_set_statusword(Cia402State CurrentState);
static void ControlwordBit4UpedgeCheck(void);
static bool QuickStopRun(void);

//Automatic transition
bool AutomaticTransition(void) {
    return true;
}

//Automatic transition after power-on or reset application
bool Transition_0_Event(void) {
    return true;
}

//Drive device self-test and/or self initialisation shall be performed
void Transition_0_Action(void) {
    ;
}

//Communication shall be activated
void Transition_1_Action(void) {
    ;
}

//Shutdown command from control device or local signal
bool Transition_2_Event(void) {
    if(CIA402_READ_BIT(get_Controlword(), kOd6040_ShutdownMark) == kOd6040_Shutdown){
        return true;
    }
    else{
        return false;
    }
}

//The high-level power shall be switched off, if possible
void Transition_2_Action(void) {
    set_app_Controlword(APP_CTRL_DISABLE); //为了清除其它控制指令，恢复到失能状态，切入使能
}

//Switch on command received from control device or local signal
bool Transition_3_Event(void) {
    if(CIA402_READ_BIT(get_Controlword(), kOd6040_StandardMark) == kOd6040_SwitchOn){
        return true;
    }
    else{
        return false;
    }
}

//The high-level power shall be switched on, if possible
void Transition_3_Action(void) {
    ;
}

//detail: cia402pdf, Table 27 - Command Coding
//NOTE Automatic transition to Enable operation state after executing SWITCHED ON state functionality
bool Jump_3_Event(void) {
    if(CIA402_READ_BIT(get_Controlword(), kOd6040_StandardMark) == kOd6040_EnableOperation){
        return true;
    }
    else{
        return false;
    }
}

//Enable operation command received from control device or local signa
bool Transition_4_Event(void) {
    if(CIA402_READ_BIT(get_Controlword(), kOd6040_StandardMark) == kOd6040_EnableOperation){
        return true;
    }
    else{
        return false;
    }
}

//The drive function shall be enabled and all internal set-points cleared
void Transition_4_Action(void) {
    set_app_Controlword(APP_CTRL_ENABLE); // 电机使能
}

//Disable operation command received from control device or local signal
bool Transition_5_Event(void) {
    if(CIA402_READ_BIT(get_Controlword(), kOd6040_StandardMark) == kOd6040_DisableOperation){
        return true;
    }
    else{
        return false;
    }
}

//The drive function shall be disabled
void Transition_5_Action(void) {
    set_app_Controlword(APP_CTRL_DISABLE); // 电机失能
}

//Shutdown command received from control device or local signal
bool Transition_6_Event(void) {
    if(CIA402_READ_BIT(get_Controlword(), kOd6040_ShutdownMark) == kOd6040_Shutdown){
        return true;
    }
    else{
        return false;
    }
}

//The high-level power shall be switched off, if possible
void Transition_6_Action(void) {
    set_app_Controlword(APP_CTRL_DISABLE); // 电机失能
}

//Quick stop or disable voltage command from control device or local signal
bool Transition_7_Event(void) {
    if(CIA402_READ_BIT(get_Controlword(), kOd6040_DisableVoltageMark) == kOd6040_DisableVoltage){
        return true;
    }
    else{
        return false;
    }
}

//Shutdown command from control device or local signal
bool Transition_8_Event(void) {
    if (CIA402_READ_BIT(get_Controlword(), kOd6040_ShutdownMark) == kOd6040_Shutdown){
        return true;
    }
    else{
        return false;
    }
}

//The drive function shall be disabled, and the high-level power shall be switched off, if possible
void Transition_8_Action(void) {
    set_app_Controlword(APP_CTRL_DISABLE); // 电机失能
}

//Disable voltage command from control device or local signal
bool Transition_9_Event(void) {
    if(CIA402_READ_BIT(get_Controlword(), kOd6040_DisableVoltageMark) == kOd6040_DisableVoltage){
        return true;
    }
    else{
        return false;
    }
}

//The drive function shall be disabled, and the high-level power shall be switched off, if possible.
void Transition_9_Action(void) {
    set_app_Controlword(APP_CTRL_DISABLE); // 电机失能
}

//Disable voltage or quick stop command from control device or local signal
bool Transition_10_Event(void) {
    if(CIA402_READ_BIT(get_Controlword(), kOd6040_DisableVoltageMark) == kOd6040_DisableVoltage){
        return true;
    }
    else{
        return false;
    }
}

//The high-level power shall be switched off, if possible
void Transition_10_Action(void) {
    ;
}

//Quick stop command from control device or local signal
bool Transition_11_Event(void) {
    if (CIA402_READ_BIT(get_Controlword(), kOd6040_QuickStopMark) == kOd6040_QuickStop || \
        get_app_Emergency_brake_requested()) {
        //The quick stop function shall be started,when is completed, into kQuickStopActive state
        // quickstop请求后不跳转，保持当前状态进行减速急停，急停完成后通过内部自动跳转到kQuickStopActive状态
        quick_stop_start_flag = true;
        return false;
    }
    else{
        return false;
    }
}

//The quick stop function shall be started
void Transition_11_Action(void) {
    if ((APP_Emergency_Brake_Mode)get_Quick_stop_option_code() <= EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT){
        CurrentState = kSwitchOnDisable;
    }
}

//Automatic transition when the quick stop function is completed and quick stop option code is 1, 2, 3
//or 4, or disable voltage command received from control device (depends on the quick stop option code)
bool Transition_12_Event(void) {
    // if ((APP_Emergency_Brake_Mode)get_Quick_stop_option_code() <= EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT){
    //     return true;
    // }
    if (CIA402_READ_BIT(get_Controlword(), kOd6040_DisableVoltageMark) == kOd6040_DisableVoltage){
        return true;
    }
    else{
        return false;
    }
}

//The drive function shall be disabled, and the high-level power shall be switched off, if possible
void Transition_12_Action(void) {
    ;
}

//Fault signal (see also /CiA402-3/)
bool Transition_13_Event(void) {
    if(get_Error_code() != 0){
        return true;
    }
    else{
        return false;
    }
}

//The configured fault reaction function shall be executed
void Transition_13_Action(void) {
    ;
}

//The drive function shall be disabled; the highlevel power shall be switched off, if possible
void Transition_14_Action(void) {
    ;
}

//Fault reset command from control device or local signal
bool Transition_15_Event(void) {
    if((CIA402_READ_BIT(get_Controlword(), kOd6040_FaultReset) != 0) && (last_fault_reset_bit == false)){
        set_app_Controlword(APP_CTRL_CLEAR_ERROR);  //清除应用层错误
        return true;
    }
    else{
        return false;
    }
}

//A reset of the fault condition is carried out, if no fault exists currently on the drive device; 
//after leaving the Fault state, the Fault reset bit in the get_Controlword() shall be cleared by the control device.
void Transition_15_Action(void) {
    //执行故障复位操作
    ;
}

//Enable operation command from control device, if the quick stop option code is 5, 6, 7, or 8
bool Transition_16_Event(void) {
    if ((APP_Emergency_Brake_Mode)get_Quick_stop_option_code() > EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT &&\
        CIA402_READ_BIT(get_Controlword(), kOd6040_StandardMark) == kOd6040_EnableOperation){
        return true;
    }
    else{
        return false;
    }
}

//The drive function shall be enabled
void Transition_16_Action(void) {
    set_app_Controlword(APP_CTRL_ENABLE); // 电机使能
}


static const FSATransition stateTable[] = {
    {kStart,                kNotReadyToSwitchOn,    true,   Transition_0_Event,  Transition_0_Action},
    {kNotReadyToSwitchOn,   kSwitchOnDisable,       true,   AutomaticTransition, Transition_1_Action},
    {kSwitchOnDisable,      kReadyToSwitchOn,       false,  Transition_2_Event,  Transition_2_Action},
    {kReadyToSwitchOn,      kSwitchOn,              false,  Transition_3_Event,  Transition_3_Action},
    {kReadyToSwitchOn,      kOperationEnable,       false,  Jump_3_Event,        Transition_4_Action},
    {kSwitchOn,             kOperationEnable,       false,  Transition_4_Event,  Transition_4_Action},
    {kOperationEnable,      kSwitchOn,              false,  Transition_5_Event,  Transition_5_Action},
    {kSwitchOn,             kReadyToSwitchOn,       false,  Transition_6_Event,  Transition_6_Action},
    {kReadyToSwitchOn,      kSwitchOnDisable,       false,  Transition_7_Event,  NULL},
    {kOperationEnable,      kReadyToSwitchOn,       false,  Transition_8_Event,  Transition_8_Action},
    {kOperationEnable,      kSwitchOnDisable,       false,  Transition_9_Event,  Transition_9_Action},
    {kSwitchOn,             kSwitchOnDisable,       false,  Transition_10_Event, Transition_10_Action},
    {kOperationEnable,      kQuickStopActive,       false,  Transition_11_Event, Transition_11_Action},
    {kQuickStopActive,      kSwitchOnDisable,       false,  Transition_12_Event, Transition_12_Action},
    // {kAnyState,             kFaultReactionActive,   false,   Transition_13_Event, Transition_13_Action},  //fault状态由外部触发，不是状态机跳转
    {kFaultReactionActive,  kFault,                 true,   AutomaticTransition, Transition_14_Action},
    {kFault,                kSwitchOnDisable,       false,  Transition_15_Event, Transition_15_Action},
    {kQuickStopActive,      kOperationEnable,       false,  Transition_16_Event, Transition_16_Action}
};

Cia402State get_CurrentState(void){
    return CurrentState;
}

//控制字切换状态机(通过总线或者内部方式改变控制字)
void ControlwordChange_PDAS_FSA(void){

    uint16_t const controlword_tar = get_Controlword();

    //如果控制字bit7保持为1,则其它控制指令均无效
    if((last_fault_reset_bit == true) && (CIA402_READ_BIT(controlword_tar, kOd6040_FaultReset))) {
        return;
    }

    //遍历状态表，找到当前状态对应的转移条件和动作
    for (uint8_t i = 0; i < CIA402_ARRAY_SIZE(stateTable); i++) {
        //The events shall initiate the transition. The transition shall be terminated, after the action has been performed.
        if ((stateTable[i].CurrentState == CurrentState) && (stateTable[i].event())) {
            if(stateTable[i].action != NULL){
                stateTable[i].action();
            }
            CurrentState = stateTable[i].NextState;
            break;
        }
    }
    PDS_FSA_set_statusword(CurrentState);

    last_fault_reset_bit = CIA402_READ_BIT(controlword_tar, kOd6040_FaultReset); //锁存故障复位标志,用于检测故障复位命令(上升沿触发)

    set_app_Halt_running_cmd(CIA402_READ_BIT(controlword_tar, kOd6040_Halt) == kOd6040_Halt); //锁存halt命令,用于检测halt命令(上升沿触发)

    ControlwordBit4UpedgeCheck(); //检测控制字bit4的上升沿事件
}

//轮询状态机(中断或者任务中轮询)
void PDS_FSA_Run(void) {

    //内部紧急停车（QuickStop）需求，运行一次状态机更新进入QuickStop状态
    if (CurrentState == kOperationEnable && get_app_Emergency_brake_requested()) {
        ControlwordChange_PDAS_FSA();
    }

    //任何状态触发错误，直接跳转到故障状态
    if(Transition_13_Event()) {
        CurrentState = kFaultReactionActive;
        Transition_13_Action();
        PDS_FSA_set_statusword(CurrentState);
    }

    //自动切换状态机(自动跳转标志为true)
    for (uint8_t i = 0; i < CIA402_ARRAY_SIZE(stateTable); i++) {
        //The events shall initiate the transition. The transition shall be terminated, after the action has been performed.
        if (stateTable[i].CurrentState == CurrentState && stateTable[i].auto_transition) {
            if(stateTable[i].action != NULL){
                stateTable[i].action();
            }
            CurrentState = stateTable[i].NextState;
            PDS_FSA_set_statusword(CurrentState);
        }
    }

    //启动quick stop功能，在kOperationEnable完成急停动作后，由内部跳转到kQuickStopActive状态
    if (quick_stop_start_flag == true) {
        //如果quick stop动作已经完成，则跳转到kQuickStopActive状态
        if (QuickStopRun() == true) {
            CurrentState = kQuickStopActive;
            Transition_11_Action();
            PDS_FSA_set_statusword(CurrentState);
            quick_stop_start_flag = false;
        }
    }
}


//状态机状态字
void PDS_FSA_set_statusword(Cia402State CurrentState){

    Od6041Mask val = 0;  // 初始化状态值为0

    switch (CurrentState) {
        case kStart:
            val = kOd6041_Start;
            break;
        case kNotReadyToSwitchOn:
            val = kOd6041_NotReadyToSwitchOn;
            break;
        case kSwitchOnDisable:
            val = kOd6041_SwitchedOnDisable;
            break;
        case kReadyToSwitchOn:
            val = kOd6041_ReadyToSwitchOn;
            break;
        case kSwitchOn:
            val = kOd6041_SwitchedOn;
            break;
        case kOperationEnable:
            val = kOd6041_OperationEnable;
            break;
        case kQuickStopActive:
            val = kOd6041_QuickStopActive;
            break;
        case kFaultReactionActive:
            val = kOd6041_FaultReactionActive;
            break;
        case kFault:
            val = kOd6041_Fault;
            break;
        default:
            val = 0;  // 其他状态值保持为0
            break;
    }

    uint16_t state_out_mark = CIA402_READ_BIT(get_Statusword(), (~kOd6041_StateMark));  //读取掩码外位的状态

    set_Statusword(state_out_mark | val);//掩码外状态保留，设置当前状态
}


void ControlwordBit4UpedgeCheck(void)
{
    if (CIA402_READ_BIT(last_controlword, kOd6040_NewSetPoint) == 0 && \
        CIA402_READ_BIT(get_Controlword(), kOd6040_NewSetPoint) != 0)
    {
        set_app_start_upedge_state(true);
    }

    last_controlword = get_Controlword();
}

//static Axis *const axis = &kAxis1;
bool QuickStopRun(void)
{
    set_app_Controlword(MOTOR_CTL_SM_MOTOR_EMERGENCY_BRAKE);  //通过应用层控制电机急停

    //速度为0，快速停止完成
    if (get_velocity_zero_state()) {
        return true;
    }
    else {
        return false;
    }
}
