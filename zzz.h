#ifndef ZZZ_H
#define ZZZ_H

#pragma once
#include <windows.h>
#include <shlobj.h>
#include "ConnectUi.h"
#include <QDebug>
#include <functional>
#include <shellapi.h>
using namespace std::chrono;
#pragma comment(lib, "shell32.lib")
#define WINXC g_WinCentre.x
#define WINYC g_WinCentre.y
//鼠标
#define M_L_D MOUSEEVENTF_LEFTDOWN
#define M_L_U MOUSEEVENTF_LEFTUP
#define M_R_D MOUSEEVENTF_RIGHTDOWN
#define M_R_U MOUSEEVENTF_RIGHTUP
#define M_M_D MOUSEEVENTF_MIDDLEDOWN
#define M_M_U MOUSEEVENTF_MIDDLEUP
#define M_L 0x1
#define M_R 0x2
#define M_M 0x3
//地图/区域
#define AREA1 0x1
#define AREA2 0x2
#define AREA3 0x4
#define AREA4 0x8
#define MAP1 0x1
#define MAP2 0x2
#define MAP3 0x4
#define MAP4 0x8
#define MAP5 0x10
#define MAP6 0x20
#define MAP7 0x40
#define MAP8 0x80
//角色编码
#define XING_JIAN_YA_CODE 0x1
#define YI_XUAN_CODE 0x2
#define YUE_CHENG_LIU_CODE 0x3
#define AI_LI_SI_CODE 0x4
#define YOU_YE_CODE 0x5
//配队
#define TEAM_YIN_YA_LIU Game_Zzz_Battle_1
#define TEAM_XUAN_HU_FU Game_Zzz_Battle_2
#define TEAM_YOU_AI_NA Game_Zzz_Battle_3

//任务
#define TASK_TRY_1_COFFEE 0x1
#define TASK_DIVINATION 0x2
#define TASK_OPEN_STORE 0x4
#define TASK_SUIBIAN_TEMPLE 0x8
#define TASK_REWARD 0x10
#define TASK_LIDU 0x20

//其他
#define GAME_NAME L"绝区零"
#define MY_SCALE 1.50  //1.50
#define MAX_BOSS 26
#define THREAD_MAX 0x20
#define THREAD_QT_MAX 0x4
#define THREADS_SUSPEND 0x1
#define THREADS_RESUME 0x2
#define THREADS_TERNIMATE 0x3
#define BATTLE_SPACE L"SPACE"
#define BATTLE_E L"E"
#define BATTLE_Q L"Q"
#define BATTLE_A L"A"
#define THREAD_EXECUTE L"execute"
#define THREAD_EXECUTE2 L"execute2"
#define BETTAL_LA_YA L"LongA_Ya"
//结构体
typedef struct _THREADS {
    HANDLE threadHandle;
    const wchar_t* threadName;
}THREADS, * PTHREADS;


typedef struct _ROLE_INFOEX {
    struct ROLE_SKILL {
        DWORD qTime;
        DWORD eTime;
        DWORD lETime;
        DWORD aTime;
        DWORD lATime;
        DWORD additionalSkillTime;
        BYTE  additionalSC;
    };
    struct ROLE_ACTION {
        FLOAT walkSpeed;     //散步速度
        FLOAT runSpeed;		//短Shift
        FLOAT sprintSpeed;  //长Shift
        FLOAT angle;   //转向的角度
    };
    struct ROLE_DEPICT {
        COLORREF  base1;
        COLORREF  base2;
        COLORREF  base3;
    };
    LPCWSTR name;//名字
    ROLE_SKILL skill;    // 技能数据
    ROLE_ACTION action;  // 动作数据
    ROLE_DEPICT depict;  // 外观数据

}ROLE_INFOEX, * PROLE_INFOEX;

extern HWND g_Hwnd;
extern FLOAT g_Scale;
extern WINDOWINFO g_winInfo;
extern POINT g_WinCentre;
extern BOOL g_Tmp;
extern HANDLE g_ThreadF11;
extern THREADS g_Threads[THREAD_MAX];
extern THREADS g_SpecialThreads[THREAD_MAX];
extern THREADS g_qt_threads[THREAD_QT_MAX];
extern HANDLE g_ThreadDot;
extern BOOL g_qt_dotStatus;
extern BOOL g_F11Status;
extern ROLE_INFOEX yin;
extern ROLE_INFOEX ya;
extern ROLE_INFOEX liu;
extern ROLE_INFOEX xuan;
extern ROLE_INFOEX hu;
extern ROLE_INFOEX fu;
extern ROLE_INFOEX ai;
extern ROLE_INFOEX you;
extern ROLE_INFOEX ke;
extern ROLE_INFOEX tmp;
extern ROLE_INFOEX tmp2;
extern BOOL roleInitCom;
extern BOOL is2Rol;
extern BYTE whoAppear;
extern BYTE countHitM;
extern ConnectUi g_cu;
extern ROLE_INFOEX g_ris[0x3];

using BattleFunc = std::function<void()>;
//初始化全局变量
BOOL InitVal(HWND Hwnd);
//基于中心的像素点坐标转换
VOID  GetPixelDistance(PINT PDX, PINT PDY);
//获取缩放
float Game_Zzz_GetScale();

// 模拟按键点击
void ClickKey(WORD vkCode, _In_opt_ LONG s = 50);
// 模拟按键按下
void PressKey(WORD vkCode);
// 模拟按键释放
void ReleaseKey(WORD vkCode);
//释放所有按键
void ReleaseKeyAll();
// 模拟鼠标移动到指定位置
void MoveMouseTo(int x, int y, __in_opt BYTE base = 1);
//支持右键和中键
void ClickMouseEx(_In_opt_ UINT32 lmr = M_L, _In_opt_ LONG interval = 50);
// 模拟鼠标点击
void ClickMouse(_In_opt_ LONG interval = 50, _In_opt_ LONG afterInterval = 200, _In_opt_ LONG beforeInterval = 200);
// 模拟鼠标按下
void ClickMouseDown(_In_opt_ UINT32 lmr = MOUSEEVENTF_LEFTDOWN);
// 模拟鼠标释放
void ClickMouseUp(_In_opt_ UINT32 lmr = MOUSEEVENTF_LEFTUP);

//输出游戏位置的RGB
VOID PrCursorInfo(INT tmpX, INT tmpY);
// 获取指定坐标的RGB值  _switch 二次转换
COLORREF GetRGBAt(int x, int y, _In_opt_ BYTE _switch = 1);
//按ALT+移动
BOOL DragMouseEx(int x, int y);
//拖动鼠标
VOID DragMouse(int endX, int endY);

//启动ZZZ
BOOL ZZZStart();
//屏幕中心的确认
VOID  Game_Zzz_ConfirmCentre();
//检测游戏状态是否在游戏中
BOOL Game_Zzz_CheckStatusInGame(_In_opt_ LONG cycle = 10);
//检测游戏状态是否正常
BOOL Game_Zzz_CheckStatusIsNormal(_In_opt_ LONG cycle = 10, _In_opt_ LONG sleep = 1000);
//加快锄地检测速度
BOOL Game_Zzz_BrushMaterial_Accelerate(ROLE_INFOEX roin, _In_opt_ LONG cycle = 20);
//加速校验
BOOL Game_Zzz_AccelerateVerify(ROLE_INFOEX roin, _In_opt_ LONG cycle = 20, _In_opt_ LONG cycle2 = 10, _In_opt_ LONG sleep = 1000);

//日常任务
DWORD WINAPI DailyTask(PVOID pParam);
//喝咖啡 number为选项
BOOL Game_Zzz_DrinkCoffee(BYTE number);
//占卜
BOOL Game_Zzz_DiceRoller();
//开店    boos 后四位是列，其余是行
BOOL Game_Zzz_OpenBusiness(SHORT boos);
//随便观  zz 制造的列
BOOL Game_Zzz_SuiBianGuan(BYTE zz);
//领日常奖励
BOOL Game_Zzz_ReceiveLivenessReward();
//领大月卡奖励一类
BOOL Game_Zzz_Lidu();

//定位澄辉坪
BOOL Game_Zzz_ChengHuiPing();
//定位航天城
BOOL Game_Zzz_HangTianCheng();
//小区域
BOOL Game_Zzz_HollowToArea();



//线程 暂停1和恢复2 关闭线程3
BOOL Game_Zzz_ThreadsSRT(_In_opt_ BYTE sel = 0, _In_opt_ const wchar_t* privilege = NULL);

//qt线程 暂停1和恢复2 关闭线程3
BOOL Game_Zzz_qt_ThreadsSRT(_In_opt_ BYTE sel = 0, _In_opt_ const wchar_t* privilege = NULL);

//获取角色信息
VOID Game_Zzz_GetRoleInfo(PROLE_INFOEX pRole);
//获取已初始化的当前角色信息
VOID Game_Zzz_GetExistRoleInfo(PROLE_INFOEX pRole);

bool operator==(ROLE_INFOEX p1, ROLE_INFOEX  p2);

//按键
DWORD WINAPI CheckSpace(PVOID pParam);
DWORD WINAPI CheckE(PVOID pParam);
DWORD WINAPI CheckQ(PVOID pParam);
DWORD WINAPI CheckA(PVOID pParam);
DWORD WINAPI CheckLongA_Exclusive_Ya(PVOID pParam);
DWORD WINAPI CheckF11(PVOID pParam);
DWORD WINAPI CheckDot(PVOID pParam);
//音雅柳
BOOL  Game_Zzz_Battle_1();
//仪玄 壶 福福
BOOL  Game_Zzz_Battle_2();
//柚叶 爱丽丝 丽娜
BOOL  Game_Zzz_Battle_3();

//初始化的场景, 设置训练场1,进地图2,别的都是直接
BOOL Game_Zzz_InitRoleInfoScene(_In_opt_ BYTE scene = 0);

BOOL Game_Zzz_InitRoleInfo();
BOOL Game_Zzz_InitRoleInfoSim();
BOOL Game_Zzz_InitRoleInfoMap();
//切换到目标角色
BOOL CheckAndSwitchToTarRoleInfo(ROLE_INFOEX role,BYTE frequency=0x10);
//当前角色是否为目标角色
BOOL CheckFirstIsTarRoleInfo(ROLE_INFOEX role);


//空洞
DWORD WINAPI Game_Zzz_EntryHollow(LPVOID pParam);

BOOL Game_Zzz_Battle_HollowMonster_ZYZZQ(ROLE_INFOEX roin, BattleFunc func);
BOOL Game_Zzz_Battle_HollowMonster_ZYZZQ2(ROLE_INFOEX roin, BattleFunc func);
BOOL Game_Zzz_Battle_HollowMonster_ZYZZQ3(ROLE_INFOEX roin, BattleFunc func);
BOOL Game_Zzz_Battle_HollowMonster_ZYZZQ4(ROLE_INFOEX roin, BattleFunc func);
BOOL Game_Zzz_Battle_HollowMonster_ZGSQJZ(ROLE_INFOEX roin, BattleFunc func);
BOOL Game_Zzz_Battle_HollowMonster_KYYJZ(ROLE_INFOEX roin, BattleFunc func);
BOOL Game_Zzz_Battle_HollowMonster_JJZQ(ROLE_INFOEX roin, BattleFunc func) ;
BOOL Game_Zzz_Battle_HollowMonster_CJQZX(ROLE_INFOEX roin, BattleFunc func);
BOOL Game_Zzz_Battle_HollowMonster_QSGY(ROLE_INFOEX roin, BattleFunc func);
BOOL Game_Zzz_Battle_HollowMonster_HTKXZ(ROLE_INFOEX roin, BattleFunc func);
//测试
BOOL Game_Zzz_Battle();
BOOL Text();
DWORD WINAPI Test(LPVOID pParam);
BOOL TMP9(ROLE_INFOEX role);
#endif // ZZZ_H
