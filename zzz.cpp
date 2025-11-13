#include "zzz.h"
HWND g_Hwnd = NULL;
FLOAT g_Scale = NULL;
WINDOWINFO g_winInfo = { sizeof(WINDOWINFO) };
POINT g_WinCentre = { 0 };
BOOL g_Tmp = FALSE;
HANDLE g_ThreadF11 = NULL;
THREADS g_Threads[THREAD_MAX] = { 0 };
THREADS g_SpecialThreads[THREAD_MAX] = { 0 };
HANDLE g_ThreadDot = NULL;
THREADS g_qt_threads[THREAD_QT_MAX] = { 0 };
BOOL g_qt_dotStatus = TRUE;
BOOL g_F11Status = TRUE;
ROLE_INFOEX yin = ROLE_INFOEX{L"耀佳音",{3000,100,2000,50,2000,NULL,NULL},{0},{0}};
ROLE_INFOEX ya = ROLE_INFOEX{L"星见雅", {5400,100,50,50,1500,0xFF},{1,1,1,1},{0} };
ROLE_INFOEX liu = ROLE_INFOEX{ L"月城柳",{5200,100,1400,50,NULL,NULL},{1,1.01,1},{0} };
ROLE_INFOEX xuan = ROLE_INFOEX{L"仪玄", {0},{1,0.88,1,1.02},{0} };
ROLE_INFOEX hu = ROLE_INFOEX{L"潘引壶", 0 };
ROLE_INFOEX fu = ROLE_INFOEX{L"橘福福", 0 };
ROLE_INFOEX ai = ROLE_INFOEX{L"爱丽丝", {0},{1,0.98,0.98},{0} };
ROLE_INFOEX you = ROLE_INFOEX{L"柚叶", {0},{1,0.84,1},{0} };
ROLE_INFOEX ke = ROLE_INFOEX{L"妮可", 0 };
ROLE_INFOEX tmp = ROLE_INFOEX{L"占位1", 0 };
ROLE_INFOEX tmp2 = ROLE_INFOEX{ L"占位2",{0},{1,0.98,0.98},{0} };
BOOL roleInitCom = FALSE;
BOOL is2Rol = FALSE;
BYTE whoAppear = 0;
BYTE countHitM = 0;
ConnectUi g_cu;
ROLE_INFOEX g_ris[0x3] = { 0 };

BOOL InitVal(HWND Hwnd)
{

    g_Hwnd = Hwnd;
    g_Scale = Game_Zzz_GetScale();


    if (!GetWindowInfo(g_Hwnd, &g_winInfo)) {
        printf("窗口信息获取失败.\r\n");

        return 0;
    }
    g_WinCentre.x = (LONG)(g_winInfo.rcClient.right - (g_winInfo.rcClient.right - g_winInfo.rcClient.left) / 2);
    g_WinCentre.y = (LONG)(g_winInfo.rcClient.bottom - (g_winInfo.rcClient.bottom - g_winInfo.rcClient.top) / 2);

    if (g_Hwnd == NULL || g_Scale == NULL)
    {
        return 0;
    }
    return 1;
}

VOID GetPixelDistance(PINT PDX, PINT PDY)
{

    *PDX = g_WinCentre.x + (INT)(*PDX / g_Scale);
    *PDY = g_WinCentre.y + (INT)(*PDY / g_Scale);
}

FLOAT Game_Zzz_GetScale() {
    return (float)(GetDpiForWindow(g_Hwnd) / 96.0f);
}


void ClickKey(WORD vkCode, _In_opt_ LONG s)
{
    Sleep(50); // 初始延时

    // 映射虚拟键到扫描码
    const WORD scanCode = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);
    if (scanCode == 0) {
        // 处理映射失败（例如无效的 vkCode）
        return;
    }

    // 判断是否为扩展键（一次判断多次使用）
    const bool isExtendedKey =
        vkCode == VK_RSHIFT || vkCode == VK_RCONTROL || vkCode == VK_RMENU ||
        vkCode == VK_INSERT || vkCode == VK_DELETE || vkCode == VK_HOME ||
        vkCode == VK_END || vkCode == VK_PRIOR || vkCode == VK_NEXT ||
        vkCode == VK_UP || vkCode == VK_DOWN || vkCode == VK_LEFT || vkCode == VK_RIGHT;

    // 按下按键
    INPUT downInput = { 0 };
    downInput.type = INPUT_KEYBOARD;
    downInput.ki.wScan = scanCode;
    downInput.ki.dwFlags = KEYEVENTF_SCANCODE;

    if (isExtendedKey) {
        downInput.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
    }
    SendInput(1, &downInput, sizeof(INPUT));

    // 自定义延时（如果参数 s 非零）
    if (s > 0) {
        Sleep(s);
    }

    // 释放按键
    INPUT upInput = { 0 };
    upInput.type = INPUT_KEYBOARD;
    upInput.ki.wScan = scanCode;
    upInput.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP; // 添加释放标志
    if (isExtendedKey) {
        upInput.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
    }
    SendInput(1, &upInput, sizeof(INPUT));
    Sleep(50); // 释放后延时
}

void PressKey(WORD vkCode) {
    Sleep(50);
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;

    // 只使用扫描码，不使用虚拟键码
    input.ki.wScan = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);
    input.ki.dwFlags = KEYEVENTF_SCANCODE;

    // 对于扩展键需要特殊处理
    if (vkCode == VK_RSHIFT || vkCode == VK_RCONTROL || vkCode == VK_RMENU ||
        vkCode == VK_INSERT || vkCode == VK_DELETE || vkCode == VK_HOME ||
        vkCode == VK_END || vkCode == VK_PRIOR || vkCode == VK_NEXT ||
        vkCode == VK_UP || vkCode == VK_DOWN || vkCode == VK_LEFT || vkCode == VK_RIGHT) {
        input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
    }

    SendInput(1, &input, sizeof(INPUT));

    Sleep(50);
}

void ReleaseKey(WORD vkCode) {
    Sleep(50);
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;

    // 只使用扫描码
    input.ki.wScan = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);
    input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;

    // 对于扩展键需要特殊处理
    if (vkCode == VK_RSHIFT || vkCode == VK_RCONTROL || vkCode == VK_RMENU ||
        vkCode == VK_INSERT || vkCode == VK_DELETE || vkCode == VK_HOME ||
        vkCode == VK_END || vkCode == VK_PRIOR || vkCode == VK_NEXT ||
        vkCode == VK_UP || vkCode == VK_DOWN || vkCode == VK_LEFT || vkCode == VK_RIGHT) {
        input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
    }

    SendInput(1, &input, sizeof(INPUT));
    Sleep(50);

}

void MoveMouseTo(int x, int y, __in_opt BYTE base) {
    Sleep(50);
    // float suitScale= g_Scale/MY_SCALE;
    float suitScale = 1;
    int X = int(g_WinCentre.x + (x * suitScale));
    int Y = int(g_WinCentre.y + (y * suitScale));

    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dx = (X * 65535.0) / GetSystemMetrics(SM_CXSCREEN); // 将屏幕坐标转换为相对坐标
    input.mi.dy = (Y * 65535.0) / GetSystemMetrics(SM_CYSCREEN);
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE; // 绝对移动

    SendInput(1, &input, sizeof(INPUT));
    Sleep(50);
}

void ClickMouseEx(UINT32 lmr, LONG interval)
{
    switch (lmr)
    {
    case M_L: {
        Sleep(50);
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = M_L_D; // 鼠标左键按下
        SendInput(1, &input, sizeof(INPUT));
        Sleep(50);
        input.mi.dwFlags = M_L_U; // 鼠标左键释放
        SendInput(1, &input, sizeof(INPUT));
        Sleep(50);
    }
    break;
    case M_R: {
        Sleep(50);
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = M_R_D; // 鼠标左键按下
        SendInput(1, &input, sizeof(INPUT));
        Sleep(50);
        input.mi.dwFlags = M_R_U; // 鼠标左键释放
        SendInput(1, &input, sizeof(INPUT));
        Sleep(50);
    }
    break;
    case M_M: {
        Sleep(50);
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = M_M_D; // 鼠标左键按下
        SendInput(1, &input, sizeof(INPUT));
        Sleep(50);
        input.mi.dwFlags = M_M_U; // 鼠标左键释放
        SendInput(1, &input, sizeof(INPUT));
        Sleep(50);

    }
    break;
    default:
        break;
    }
}

void ClickMouse(_In_opt_ LONG interval, _In_opt_ LONG afterInterval, _In_opt_ LONG beforeInterval) {

    Sleep(beforeInterval);


    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; // 鼠标左键按下
    SendInput(1, &input, sizeof(INPUT));


    Sleep(interval);




    input.mi.dwFlags = MOUSEEVENTF_LEFTUP; // 鼠标左键释放
    SendInput(1, &input, sizeof(INPUT));

    Sleep(afterInterval);

}

void ClickMouseDown(_In_opt_ UINT32 lmr)
{
    Sleep(50);
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = lmr; // 鼠标左键按下
    SendInput(1, &input, sizeof(INPUT));

}

void ClickMouseUp(_In_opt_ UINT32 lmr)
{
    Sleep(50);
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;


    input.mi.dwFlags = lmr; // 鼠标左键释放
    SendInput(1, &input, sizeof(INPUT));
    Sleep(50);

}

VOID PrCursorInfo(INT tmpX, INT tmpY)
{
    COLORREF color = GetRGBAt(tmpX, tmpY);
    printf("game co=%08X X=%.2f  Y=%.2f\t Dpi=%.2f \r\n", color, tmpX * g_Scale, tmpY * g_Scale, g_Scale);
}

COLORREF GetRGBAt(int x, int y, _In_opt_ BYTE _switch) {
    // float suitScale= g_Scale/MY_SCALE;
    float suitScale = 1;
    int X = int(g_WinCentre.x + (x * suitScale));
    int Y = int(g_WinCentre.y + (y * suitScale));
    Sleep(50);
    HDC hdc = GetDC(NULL); // 获取屏幕的设备上下文
    Sleep(20);
    COLORREF color = { 0 };

    color = GetPixel(hdc, X, Y); // 获取指定坐标的像素颜色

    ReleaseDC(NULL, hdc); // 释放设备上下文
    return color;
}

VOID DragMouse(int x, int y) {


    Sleep(50);
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; // 鼠标左键按下
    SendInput(1, &input, sizeof(INPUT));

    Sleep(100);
    if (g_Scale == 1) {
        x = x / 1.5;
        y = y / 1.5;
    }
    else if (g_Scale == 1.25) {
        x = x / 1.2;
        y = y / 1.2;
    }
    MoveMouseTo(x, y);
    Sleep(100);

    input.mi.dwFlags = MOUSEEVENTF_LEFTUP; // 鼠标左键释放
    SendInput(1, &input, sizeof(INPUT));
    Sleep(50);

}

BOOL ZZZStart() {
    PWSTR path;
    WCHAR a[1024] = { 0 };
    WCHAR b[] = L"\\miHoYo\\绝区零\\Player.log";

    if (SHGetKnownFolderPath(FOLDERID_LocalAppDataLow, 0, NULL, &path) == S_OK)
    {
        swprintf_s(a, _countof(a), L"%ls", path);
        CoTaskMemFree(path); // 必须释放内存
    }
    memcpy(a + wcslen(a), b, sizeof(b));
    FILE* file;
    _wfopen_s(&file, a, L"rb");
    if (file == NULL)
    {
        printf("文件为NULL...\r\n");
        system("pause");
        return FALSE;
    }
    CHAR* q = (CHAR*)malloc(2048);
    memset(q, 0, 2048);
    char* str1 = fgets(q, 2048, file);
    char tmp[2048]={0};
    while(1){
        char t[2048];
        fgets(t,2048-strlen(str1)-strlen(tmp),file);
        if(t[0]=='['){
            memset(tmp,0,2048);
            memcpy(tmp,t,strlen(t));
            break;
        }

        memcpy(tmp+strlen(t),t,strlen(t));
    }
    fclose(file);
    //切割字符串
    int start=-1;
    int end =-1;
    for (int var = 0; var < strlen(tmp); ++var) {
        if(tmp[var]==':'){
            start=var-1;
        }
        if(tmp[var]=='/'||tmp[var]=='\\'){
            end=var;
        }
    }
    end-=20;
    memset(q,0,2048);
    memcpy(q,tmp+start,end-start);
    memcpy(q + strlen(q), "ZenlessZoneZero.exe", sizeof("ZenlessZoneZero.exe"));

    emit g_cu.update_outInfo(QString("游戏路径%1").arg(q));

    HINSTANCE hInst = ShellExecuteA(
        NULL,           // 父窗口句柄
        "open",        // 操作类型：打开
        q,       // 程序完整路径
        NULL,           // 命令行参数（无参数时为NULL）
        NULL,           // 工作目录（NULL表示使用程序所在目录）
        SW_SHOWNORMAL   // 窗口显示方式：正常显示
        );
    free(q);

    return 1;
}

VOID  Game_Zzz_ConfirmCentre() {

    MoveMouseTo(80, 80);
    ClickMouse(50, 200, 800);
    Sleep(50);

}

BOOL Game_Zzz_CheckStatusInGame(LONG cycle) {
    INT X = 30;
    INT Y = -140;

    BYTE color = 0;
    BYTE darkRGB = 0;
    while (cycle--)
    {
        printf("进入检测...%d\r\n", 10 - cycle);
        Sleep(500);
        PressKey(VK_TAB);
        Sleep(500);
        darkRGB = BYTE(GetRGBAt(X, Y));
        PrCursorInfo(X, Y);
        MoveMouseTo(X, Y);
        Sleep(200);
        color = BYTE(GetRGBAt(X, Y));
        PrCursorInfo(X, Y);
        ReleaseKey(VK_TAB);
        if (darkRGB <= 0x60 && color >= 0x90)
        {
            g_Tmp = 1;
            return TRUE;
        }
        ClickKey(VK_ESCAPE);
        Sleep(800);
        if (BYTE(GetRGBAt(-460, 416)) == 0xFF &&
            BYTE(GetRGBAt(354, 428)) == 0xFF &&
            BYTE(GetRGBAt(-840, 510)) == 0x00
            )
        {
            ClickKey(VK_ESCAPE);
            Sleep(800);
            g_Tmp = 1;
            return TRUE;

        }
    }

    return FALSE;

}

BOOL Game_Zzz_CheckStatusIsNormal(LONG cycle, _In_opt_ LONG sleep)
{
    while (cycle--)
    {
        Sleep(sleep);
        if (WORD(GetRGBAt(600, -480)) == 0xE6E6 || WORD(GetRGBAt(690, -480)) == 0xE6E6)
        {
            return 1;
        }

    }
    return 0;

}

BOOL Game_Zzz_DrinkCoffee(BYTE number) {

    Game_Zzz_CheckStatusIsNormal();
    // printf("喝咖啡...\r\n");
    ClickKey('N');
    Sleep(1000);
    Game_Zzz_ChengHuiPing();
    MoveMouseTo(-160, 470);
    ClickMouse();
    //前往/确认
    Game_Zzz_ConfirmCentre();
    Game_Zzz_CheckStatusIsNormal(10, 2000);
    ClickKey('W', 1000);
    Sleep(1000);
    ClickKey('F');
    Sleep(2000);
    ClickKey(number);
    Sleep(2000);
    ClickKey(VK_ESCAPE);
    Sleep(1000);
    ClickKey(VK_SPACE);
    return 0;

}

BOOL Game_Zzz_DiceRoller() {
    Game_Zzz_CheckStatusIsNormal();
    printf("占卜...\r\n");
    Sleep(200);
    LONG tmpX = -30;
    LONG tmpY = -400;
    ClickKey('N');
    Sleep(1000);
    Game_Zzz_ChengHuiPing();
    MoveMouseTo(-450, 470);
    ClickMouse();
    Game_Zzz_ConfirmCentre();
    Game_Zzz_CheckStatusIsNormal();
    ClickKey('F');
    Sleep(2000);
    if (BYTE(GetRGBAt(532, -50)) <= 0xA0)
    {
        printf("今日占卜已完成，无需重复...\r\n");
        ClickKey(VK_ESCAPE);
        return 0;
    }
    MoveMouseTo(532, -50);
    ClickMouse(50, 200, 1000);
    Sleep(800);

    while (1) {//开
        [](){INPUT inp={0};
            inp.type=INPUT_MOUSE;
            inp.mi.dwFlags=MOUSEEVENTF_LEFTDOWN;
            SendInput(1,&inp,sizeof(INPUT));
            MoveMouseTo(600,0);
            MoveMouseTo(0,0);
            MoveMouseTo(-600,0);
            inp.mi.dwFlags=MOUSEEVENTF_LEFTUP;
            SendInput(1,&inp,sizeof(INPUT));
        }();
        if (BYTE(GetRGBAt(-40, 190)) <= 0x12) {
            break;
        }
    }

    //退出
    for (size_t i = 0; i < 3; i++)
    {
        Sleep(500);
        ClickKey(VK_ESCAPE);
    }
    return 0;
}

BOOL Game_Zzz_OpenBusiness(SHORT boos) {

    Game_Zzz_CheckStatusInGame();
    printf("开店经营...\r\n");
    Sleep(200);
    BYTE rows = (boos & 0xFFFF) >> 4;
    BYTE columns = boos & 0xF;
    ClickKey('N');
    Sleep(1000);
    Game_Zzz_ChengHuiPing();
    MoveMouseTo(150, 460);
    ClickMouse(50, 800, 1000);

    Game_Zzz_ConfirmCentre();

    LONG tmpX = -30;
    LONG tmpY = -400;
    Game_Zzz_CheckStatusInGame();
    ClickKey('F');
    Sleep(3000);
    ClickKey('1');
    Sleep(3000);
    if (BYTE(GetRGBAt(360, -490)) <= 0x80)
    {
        ClickKey(VK_ESCAPE);
    }
    Sleep(500);
    if (BYTE(GetRGBAt(620, 440)) >= 0xC0)
    {
        ClickKey(VK_ESCAPE);
        printf("今日已开店,无需重复...\r\n");
        return 0;
    }
    //结算
    tmpX = 280;
    tmpY = 210;
    MoveMouseTo(tmpX, tmpY);
    Sleep(200);
    ///////////////////////////////////
    //选择宣传员
    tmpX = -130;
    tmpY = 280;
    MoveMouseTo(tmpX, tmpY);
    Sleep(200);
    Sleep(2000);
    LONG tXInit = 0;
    LONG tYInit = 0;
    LONG tXEnd = -350 + 213 * 5;
    LONG tYEnd = -280 + 330 * 2;
    BOOL isNULL = FALSE;
    //220 620
    ClickMouse();
    int k = 0;
    while (1)
    {
        for (size_t i = 0; i < 3; i++)
        {
            for (size_t j = 0; j < 6; j++) {
                MoveMouseTo(-350 + 213 * j, -280 + 330 * i);
                if (rows == (k + 1) && columns == (j + 1))
                {
                    printf("已找到\r\n");
                    ClickMouse();
                    MoveMouseTo(tXEnd, tYEnd + 120);
                    ClickMouse();
                    isNULL = TRUE;
                    break;
                }
                Sleep(200);
            }
            if (isNULL) { break; }
            k++;
        }
        if (isNULL) { break; }
        if (BYTE(GetRGBAt(tXEnd, tYEnd)) >= 0x20 &&
            BYTE(GetRGBAt(tXEnd - 80, tYEnd)) >= 0x20 &&
            BYTE(GetRGBAt(tXEnd, tYEnd - 80)) >= 0x20 &&
            BYTE(GetRGBAt(tXEnd, tYEnd - 80)) >= 0x20)
        {
            break;
        }
        DragMouse(tXEnd, tYEnd - 620);
        Sleep(200);
    }
    Sleep(200);
    MoveMouseTo(210, 210);
    ClickMouse();
    Sleep(200);

    MoveMouseTo(420, 460);
    ClickMouse();//推荐上架

    MoveMouseTo(620, 440);
    ClickMouse();
    Sleep(200);
    Game_Zzz_ConfirmCentre();
    Sleep(200);
    Game_Zzz_ConfirmCentre();
    ClickKey(VK_ESCAPE);

    return 0;

}

BOOL Game_Zzz_SuiBianGuan(BYTE zz) {

    Game_Zzz_CheckStatusInGame();
    printf("进入随便观...\r\n");
    Sleep(200);
    //打开手册
    ClickKey(VK_F2);
    Sleep(500);
    MoveMouseTo(-220, -380);
    PrCursorInfo(-220, -380);
    if (BYTE(GetRGBAt(-220, -380)) < 0x70)
    {
        ClickMouse(80, 1000, 500);
    }
    Sleep(1000);
    MoveMouseTo(460, 230);
    ClickMouse(50, 500);
    Game_Zzz_ConfirmCentre();

    for (size_t i = 0; i < 10; i++)
    {
        Sleep(2000);
        MoveMouseTo(700, -500);
        ClickMouse();
        MoveMouseTo(760, -380);
        if (BYTE(GetRGBAt(760, -380)) == 0xEC)
        {
            break;
        }
    }


    for (size_t i = 0; i < 4; i++)
    {
        Sleep(500);
        if (BYTE(GetRGBAt(760, -330 + 1 + 145 * i)) == 0xBA) {
            MoveMouseTo(860, -340 + 145 * i);
            ClickMouse();//跳转
            Sleep(200);
            MoveMouseTo(600, 400);
            ClickMouse();//收获
            Sleep(200);
            MoveMouseTo(50, 270);
            ClickMouse();//确定
            Sleep(200);
            MoveMouseTo(400, 400);
            ClickMouse(50, 200, 1000);//选邦布
            MoveMouseTo(600, 400);
            ClickMouse();//确定
            Sleep(200);
            MoveMouseTo(760, -500);
            ClickMouse();
        }

    }
    ClickKey(VK_ESCAPE);
    Sleep(800);
    //经营
    MoveMouseTo(362, 30);
    Sleep(200);
    ClickMouse();
    int t = 0;
    for (size_t i = 0; i < 5; i++)
    {
        if (BYTE(GetRGBAt(0, -316)) == 0xFF)
        {
            MoveMouseTo(0, -30);
            ClickMouse();
            break;
        }
        else {
            t++;
        }
        Sleep(200);
    }

    if (t == 5)
    {
        printf("无需再制造..\r\n");
        ClickKey(VK_ESCAPE);
        Sleep(1000);
        ClickKey(VK_ESCAPE);
        return 0;
    }
    BYTE tmp = 1;
    Sleep(500);
    for (size_t i = 0; i < 4; i++)//制造个数
    {
        BYTE a = BYTE(GetRGBAt(-518 + 342 * i, 388));
        if (a >= 0x40 && a <= 0x60) {
            MoveMouseTo(-518 + 342 * i, 388);
            ClickMouse(50, 800, 800);
            for (size_t j = i; j < 6; j++)//遍历货物
            {
                if ((zz & tmp))
                {
                    MoveMouseTo(-648 + 150 * j, -310);
                    ClickMouse(50, 800);
                    if (BYTE(GetRGBAt(700, 442)) <= 0x60)
                    {
                        tmp *= 2;
                        ClickKey(VK_ESCAPE);
                        break;
                    }
                    MoveMouseTo(552, 410);
                    ClickMouse(50, 800);
                    tmp *= 2;
                    break;
                }
                tmp *= 2;

            }
        }
        else
        {
            tmp *= 2;
        }

        Sleep(500);
    }

    for (size_t i = 0; i < 3; i++)
    {
        ClickKey(VK_ESCAPE, 1000);
    }
    return 0;
}

BOOL Game_Zzz_ReceiveLivenessReward() {
    Game_Zzz_CheckStatusInGame();

    //打开手册
    ClickKey(VK_F2);

    Sleep(500);
    if (BYTE(GetRGBAt(-30, -400)) < 0xE0)
    {
        MoveMouseTo(-30, -400);
        ClickMouse(50, 500, 500);
    }
    MoveMouseTo(482, -270);
    BYTE color = BYTE(GetRGBAt(482, -270));
    if (color < 0x40 && color >= 0x30)
    {
        int i = 0;
        ClickMouse(50, 800);
        color = BYTE(GetRGBAt(482, -270));
        if (color > 0x40 || color < 0x30)//存疑
        {
            i = 0;
        }
        else {
            i = 1;

        }
        for (i; i < 2; i++)
        {
            Sleep(200);
            ClickKey(VK_ESCAPE);
        }
    }
    Sleep(200);
    return 0;
}

BOOL Game_Zzz_Lidu() {
    Game_Zzz_CheckStatusInGame();
    printf("领取丽都奖励...\r\n");
    Sleep(200);
    ClickKey(VK_F3);
    Sleep(2000);
    MoveMouseTo(460, -480);
    ClickMouse();//成长
    MoveMouseTo(810, 490);
    ClickMouse();//领奖
    Sleep(1000);
    MoveMouseTo(300, -490);
    ClickMouse();//回馈

    if (BYTE(GetRGBAt(460, 480)) != 0)
    {
        MoveMouseTo(460, 480);
        ClickMouse();//领奖

    }
    Sleep(800);
    ClickKey(VK_ESCAPE);
    return 0;
}

BOOL Game_Zzz_ChengHuiPing()
{
    MoveMouseTo(-600, -310);
    ClickMouse();
    Sleep(200);
    return 0;
}

BOOL Game_Zzz_HangTianCheng()
{
    Sleep(100);
    MoveMouseTo(-600, 0);
    ClickMouse();
    ClickMouse();
    Sleep(200);
    return 0;
}

BOOL Game_Zzz_Battle() {
    g_Threads[0].threadHandle = CreateThread(NULL, NULL, CheckSpace, NULL, NULL, NULL);
    SetThreadPriority(g_Threads[0].threadHandle, THREAD_PRIORITY_ABOVE_NORMAL);
    g_Threads[0].threadName = L"SPACE";
    g_Threads[1].threadHandle = CreateThread(NULL, NULL, CheckQ, NULL, NULL, NULL);
    SetThreadPriority(g_Threads[1].threadHandle, THREAD_PRIORITY_ABOVE_NORMAL);
    g_Threads[1].threadName = L"Q";
    g_Threads[2].threadHandle = CreateThread(NULL, NULL, CheckE, NULL, NULL, NULL);
    SetThreadPriority(g_Threads[2].threadHandle, THREAD_PRIORITY_ABOVE_NORMAL);
    g_Threads[2].threadName = L"E";
    g_Threads[3].threadHandle = CreateThread(NULL, NULL, CheckA, NULL, NULL, NULL);
    SetThreadPriority(g_Threads[3].threadHandle, THREAD_PRIORITY_LOWEST);
    g_Threads[3].threadName = L"A";
    g_SpecialThreads[0].threadHandle = CreateThread(NULL, NULL, CheckLongA_Exclusive_Ya, NULL, NULL, NULL);
    SetThreadPriority(g_SpecialThreads[0].threadHandle, THREAD_PRIORITY_HIGHEST);
    g_SpecialThreads[0].threadName = L"LongA_Ya";

    //后续....
    for (size_t i = 0; i < 0xFFFFFFFF; i++)
    {
        if (BYTE(GetRGBAt(600, -480)) == 0xE6)
        {
            ClickKey(VK_F4);
            Sleep(1000);
            if (BYTE(GetRGBAt(70, -500)) == 0x00) {
                ClickKey(VK_F11);
                Sleep(800);
                ClickKey(VK_ESCAPE);
                for (size_t i = 0; i < THREAD_MAX; i++)
                {
                    if (g_Threads->threadHandle != NULL)
                    {
                        CloseHandle(g_Threads[i].threadHandle);
                        g_Threads[i].threadHandle = NULL;
                        g_Threads[i].threadName = NULL;
                    }
                }
                CloseHandle(g_SpecialThreads[0].threadHandle);
                g_SpecialThreads[0].threadHandle = NULL;
                g_SpecialThreads[0].threadName = NULL;
                g_F11Status = !g_F11Status;
                return 1;
            }
            else
            {
                ClickKey(VK_ESCAPE);
            }
        }
        Sleep(2000);
    }

    return 0;
}

BOOL Game_Zzz_ThreadsSRT(BYTE sel, const wchar_t* privilege)
{
    switch (sel)
    {
    case THREADS_SUSPEND:
        for (size_t i = 0; i < THREAD_MAX; i++)
        {
            if (g_Threads[i].threadHandle != NULL)
            {
                if (privilege != NULL && !wcscmp(g_Threads[i].threadName, privilege)) {
                    continue;
                }
                SuspendThread(g_Threads[i].threadHandle);
            }
        }
        break;
    case THREADS_RESUME:
        for (size_t i = 0; i < THREAD_MAX; i++)
        {
            if (g_Threads[i].threadHandle != NULL)
            {
                if (privilege != NULL && g_Threads[i].threadName == privilege) {
                    continue;
                }
                ResumeThread(g_Threads[i].threadHandle);
            }
        }
        break;
    case THREADS_TERNIMATE:
        for (size_t i = 0; i < THREAD_MAX; i++)
        {
            if (g_Threads[i].threadHandle != NULL)
            {
                if (privilege != NULL && g_Threads[i].threadName == privilege) {
                    continue;
                }
                TerminateThread(g_Threads[i].threadHandle, 2);
                CloseHandle(g_Threads[i].threadHandle);
                g_Threads[i].threadHandle = NULL;
                g_Threads[i].threadName = NULL;
            }
        }
        ReleaseKeyAll();
        break;
    default:
        break;
    }
    return 0;
}

VOID Game_Zzz_GetRoleInfo(PROLE_INFOEX pRole)
{
    HDC hdc = GetDC(NULL);// -810 -420   -790 -480    -736 -460
    INT32 x1 = WINXC - 810;
    INT32 y1 = WINYC - 450;
    INT32 x2 = WINXC - 790;
    INT32 y2 = WINYC - 480;
    INT32 x3 = WINXC - 740;
    INT32 y3 = WINYC - 460;
    pRole->depict.base1 = GetPixel(hdc, x1, y1);
    pRole->depict.base2 = GetPixel(hdc, x2, y2);
    pRole->depict.base3 = GetPixel(hdc, x3, y3);
    ReleaseDC(NULL, hdc);
    return;
}

bool operator==(ROLE_INFOEX p1, ROLE_INFOEX p2)
{
    return (p1.depict.base1 == p2.depict.base1) &&
           (p1.depict.base2 == p2.depict.base2) &&
           (p1.depict.base3 == p2.depict.base3);
}

BOOL Text()
{
    /****************
    * 仪玄	走路4780ms
    * 雅	走路4780ms	跑步3880ms
    * 柳	走路4840ms	跑步3800ms
    * 音	走路5190ms	跑步4290
    *****************/

    ClickKey('W', 4400);//走路
    //PressKey('W');
    //ClickMouseEx(M_R);
    //Sleep(4500);
    //ReleaseKey('W');


    return 0;
}

DWORD __stdcall DailyTask(PVOID pParam)
{
    auto start = high_resolution_clock::now();
    DWORD task = *(DWORD*)pParam;
    BYTE coffeOpt = (BYTE) * ((DWORD*)pParam + 1);
    BYTE chaOpt = (BYTE) * ((DWORD*)pParam + 2);
    BYTE makeOpt = (BYTE) * ((DWORD*)pParam + 3);
    if (!task) { return 0; }
    if (!coffeOpt || !chaOpt || !makeOpt) { return 0; }


    Game_Zzz_CheckStatusInGame();

    int jindu = 0;
    if (task & TASK_TRY_1_COFFEE) { Game_Zzz_DrinkCoffee(coffeOpt); jindu++; emit  g_cu.updateProgress(jindu); }
    if (task & TASK_DIVINATION) { Game_Zzz_DiceRoller(); jindu++; emit  g_cu.updateProgress(jindu); }
    if (task & TASK_OPEN_STORE) { Game_Zzz_OpenBusiness(chaOpt); jindu++; emit  g_cu.updateProgress(jindu); }
    if (task & TASK_SUIBIAN_TEMPLE) { Game_Zzz_SuiBianGuan(makeOpt); jindu++; emit  g_cu.updateProgress(jindu); }
    if (task & TASK_REWARD) { Game_Zzz_ReceiveLivenessReward(); jindu++; emit  g_cu.updateProgress(jindu); }
    if (task & TASK_LIDU) { Game_Zzz_Lidu();jindu++; emit  g_cu.updateProgress(jindu);}

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(end - start).count();
    double minutes = duration / 60;
    double seconds = duration % 60;
    emit g_cu.update_outInfo(QString("日常概况：耗时为： %1M  %2S").arg(minutes,0,'f',2).arg(seconds,0,'f',2));
    return 0;
}

DWORD __stdcall CheckSpace(PVOID pParam)
{
    BYTE color = 0;
    while (1)
    {
        //if ((BYTE)GetRGBAt(70, -500) != 0x00) {
        if (BYTE(GetRGBAt(826, 408)) >= 0x40||BYTE(GetRGBAt(814,450)) >= 0x40)//826, 408>=0x10;828,442!=0xEE
        {
            ClickKey(VK_SPACE);

        }
        //}
        Sleep(1000);

    }
    return 0;
}

DWORD __stdcall CheckE(PVOID pParam)
{
    BYTE color = 0;
    while (1)
    {
        //if ((BYTE)GetRGBAt(70, -500) != 0x00) {

        if (BYTE(GetRGBAt(-510, -466)) >= 0x50)
        {
            ClickKey('E', 1200);
        }
        //}
        Sleep(100);

    }
    return 0;
}

DWORD __stdcall CheckQ(PVOID pParam)
{
    BYTE color = 0;
    ROLE_INFOEX ri = { 0 };
    while (1)
    {
        color = BYTE(GetRGBAt(820, 280));

        if (!(color >= 0x10 && color <= 0x40))
        {

            Sleep(200);
            Game_Zzz_GetExistRoleInfo(&ri);
            if(ri.name==NULL){
                continue;
            }
            ClickKey('Q');
            Game_Zzz_ThreadsSRT(THREADS_SUSPEND, BATTLE_Q);
            emit g_cu.update_outLog(QString("%1   QTime：%2").arg(QString::fromWCharArray(ri.name)).arg(ri.skill.qTime));
            Sleep(ri.skill.qTime);
            Game_Zzz_ThreadsSRT(THREADS_RESUME, BATTLE_Q);
        }
        Sleep(100);
    }
    return 0;
}

DWORD __stdcall CheckA(PVOID pParam)
{
    while (1)
    {
        //if ((BYTE)GetRGBAt(70, -500) != 0x00) {
        ClickMouse(50, 100, 100);
        //}
        Sleep(50);
    }
    return 0;
}

DWORD __stdcall CheckLongA_Exclusive_Ya(PVOID pParam)
{
    BYTE color = 0;
    ROLE_INFOEX t = { 0 };
    for (size_t i = 0; i < 0xFFFFFFFF; i++)
    {

        Game_Zzz_GetExistRoleInfo(&t);
        if (t == ya && BYTE(GetRGBAt(-730, -422) >> 0x10) == 0xFF)
        {
            Game_Zzz_ThreadsSRT(THREADS_SUSPEND, BETTAL_LA_YA);
            ClickKey(t.skill.lATime);
            Game_Zzz_ThreadsSRT(THREADS_RESUME, BETTAL_LA_YA);
            ClickKey(VK_F11);
            g_F11Status = !g_F11Status;
            ClickMouse(1500);
            g_F11Status = !g_F11Status;
            ClickKey(VK_F11);
        }

        Sleep(200);
    }

    return 0;
}

DWORD __stdcall CheckF11(PVOID pParam)
{
    while (1)
    {
        if (GetAsyncKeyState(VK_F11) & 0x1) {
            printf("F11被按下，当前g_F11Status：%d\r\n", g_F11Status);
            if (g_F11Status)
            {
                for (int i = 0; i < THREAD_MAX; i++) {
                    if (g_Threads[i].threadHandle != NULL)
                    {
                        SuspendThread(g_Threads[i].threadHandle);
                        printf("尝试暂停线程...%ls\r\n", g_Threads[i].threadName);
                    }
                }
                g_F11Status = !g_F11Status;
            }
            else
            {
                for (int i = 0; i < THREAD_MAX; i++) {
                    if (g_Threads[i].threadHandle != NULL)
                    {
                        ResumeThread(g_Threads[i].threadHandle);
                        printf("尝试恢复线程...%ls\r\n", g_Threads[i].threadName);
                    }
                }
                g_F11Status = !g_F11Status;
            }
        }
        Sleep(60);
    }

    return 0;
}

BOOL Game_Zzz_Battle_1()// -810 -450   -790 -480    -736 -460
{
    countHitM++;
    if (BYTE(GetRGBAt(50, -490)) == 00)
    {
        ClickKey(VK_ESCAPE);
        Sleep(500);
    }
    BYTE liudou = { 0 };
    HDC hdc = { 0 };

    g_Threads[0].threadHandle = CreateThread(NULL, NULL, CheckSpace, NULL, NULL, NULL);
    SetThreadPriority(g_Threads[0].threadHandle, THREAD_PRIORITY_ABOVE_NORMAL);
    g_Threads[0].threadName = L"SPACE";
    g_Threads[1].threadHandle = CreateThread(NULL, NULL, CheckQ, NULL, NULL, NULL);
    SetThreadPriority(g_Threads[1].threadHandle, THREAD_PRIORITY_ABOVE_NORMAL);
    g_Threads[1].threadName = L"Q";
    g_Threads[2].threadHandle = CreateThread(NULL, NULL, CheckE, NULL, NULL, NULL);
    SetThreadPriority(g_Threads[2].threadHandle, THREAD_PRIORITY_ABOVE_NORMAL);
    g_Threads[2].threadName = L"E";
    g_Threads[3].threadHandle = CreateThread(NULL, NULL, CheckA, NULL, NULL, NULL);
    SetThreadPriority(g_Threads[3].threadHandle, THREAD_PRIORITY_LOWEST);
    g_Threads[3].threadName = L"A";
    BYTE tip = 0;
    while (1)
    {
        hdc = GetDC(NULL);

        Game_Zzz_GetRoleInfo(&tmp2);
        if (tmp2 == yin)
        {
            if (tip ^ 0x1) { printf("音\r\n"); }
            ClickKey('E');
            Sleep(500);
            ClickKey(VK_SPACE);
            tip = 1;
        }
        else if (tmp2 == ya)
        {
            if (tip ^ 0x2) {
                printf("雅\r\n");
            }
            liudou = BYTE(GetRGBAt(-730, -422) >> 0X10);
            if (liudou == 0xFF)//6豆 ff
            {
                printf("6豆来咯...\r\n");//可以优化
                Game_Zzz_ThreadsSRT(THREADS_SUSPEND);
                Sleep(1200);
                ClickMouse(1400);
                ClickKey(VK_SPACE);
                Game_Zzz_ThreadsSRT(THREADS_RESUME);
            }
            tip = 2;
        }
        else if (tmp2 == liu)
        {
            if (tip ^ 0x4) {
                printf("柳\r\n");
            }
            ClickMouse();
            tip = 4;
        }
        ReleaseDC(NULL, hdc);
        if (Game_Zzz_CheckStatusIsNormal(1, 100))
        {
            Game_Zzz_ThreadsSRT(THREADS_SUSPEND);
            Sleep(1000);
            if (Game_Zzz_CheckStatusIsNormal(1, 100)) {
                Game_Zzz_ThreadsSRT(THREADS_TERNIMATE);
                Sleep(500);
                return 0;
            }
            Game_Zzz_ThreadsSRT(THREADS_RESUME);

        }
        Sleep(50);
    }

    return 0;
}

BOOL Game_Zzz_Battle_2()
{

    return 0;
}

BOOL Game_Zzz_Battle_3()
{
    return 0;
}

BOOL Game_Zzz_InitRoleInfo()
{
    ClickKey(VK_ESCAPE);
    Sleep(500);
    MoveMouseTo(-690, 430);
    ClickMouse();
    Sleep(500);
    MoveMouseTo(-170, -150);
    ClickMouse();
    Sleep(500);
    MoveMouseTo(530, 310);
    ClickMouse();
    Sleep(500);
    MoveMouseTo(-490, 500);
    ClickMouse();
    Sleep(500);
    MoveMouseTo(-290, -390);
    ClickMouse();
    Sleep(500);
    MoveMouseTo(710, 490);
    ClickMouse();
    ClickMouse();
    Sleep(3000);
    while (true)
    {
        if (BYTE(GetRGBAt(50, -490)) >= 0x10) {
            break;
        }
        Sleep(800);
    }
    Sleep(1000);
    if (BYTE(GetRGBAt(50, -490)) == 00)
    {
        ClickKey(VK_ESCAPE);
        Sleep(500);
    }

    switch (whoAppear)
    {
    case XING_JIAN_YA_CODE:
        Game_Zzz_GetRoleInfo(&yin);
        ClickKey(VK_SPACE);
        Sleep(800);
        Game_Zzz_GetRoleInfo(&ya);
        ClickKey(VK_SPACE);
        Sleep(800);
        Game_Zzz_GetRoleInfo(&liu);
        ClickKey(VK_SPACE);
        Sleep(800);
        break;
    case YI_XUAN_CODE:
        Game_Zzz_GetRoleInfo(&xuan);
        ClickKey(VK_SPACE);
        Sleep(800);
        Game_Zzz_GetRoleInfo(&hu);
        ClickKey(VK_SPACE);
        Sleep(800);
        Game_Zzz_GetRoleInfo(&fu);
        ClickKey(VK_SPACE);
        Sleep(800);
        break;
    case AI_LI_SI_CODE:
        Game_Zzz_GetRoleInfo(&you);
        ClickKey(VK_SPACE);
        Sleep(800);
        Game_Zzz_GetRoleInfo(&ai);
        ClickKey(VK_SPACE);
        Sleep(800);
        Game_Zzz_GetRoleInfo(&ke);
        ClickKey(VK_SPACE);
        Sleep(800);
        break;
    default:
        break;
    }

    if (is2Rol)
    {
        ClickKey(VK_SPACE);
        Sleep(800);
    }


    ClickKey(VK_ESCAPE);
    Sleep(500);
    MoveMouseTo(680, 490);
    ClickMouse();
    Game_Zzz_ConfirmCentre();
    Sleep(8000);
    ClickKey(VK_ESCAPE);
    return 0;
}

BOOL Game_Zzz_InitRoleInfoSim()
{
    switch (whoAppear)
    {
    case XING_JIAN_YA_CODE:
        Game_Zzz_GetRoleInfo(&yin);
        ClickKey(VK_SPACE);
        Sleep(800);
        Game_Zzz_GetRoleInfo(&ya);
        ClickKey(VK_SPACE);
        Sleep(800);
        Game_Zzz_GetRoleInfo(&liu);
        ClickKey(VK_SPACE);
        Sleep(800);
        g_ris[0] = yin;
        g_ris[1] = ya;
        g_ris[2] = liu;
        break;
    case YI_XUAN_CODE:
        Game_Zzz_GetRoleInfo(&xuan);
        ClickKey(VK_SPACE);
        Sleep(800);
        Game_Zzz_GetRoleInfo(&hu);
        ClickKey(VK_SPACE);
        Sleep(800);
        Game_Zzz_GetRoleInfo(&fu);
        ClickKey(VK_SPACE);
        Sleep(800);
        g_ris[0] = xuan;
        g_ris[1] = hu;
        g_ris[2] = fu;
        break;
    case AI_LI_SI_CODE:
        Game_Zzz_GetRoleInfo(&you);
        ClickKey(VK_SPACE);
        Sleep(800);
        Game_Zzz_GetRoleInfo(&ai);
        ClickKey(VK_SPACE);
        Sleep(800);
        Game_Zzz_GetRoleInfo(&ke);
        ClickKey(VK_SPACE);
        Sleep(800);
        g_ris[0] = you;
        g_ris[1] = ai;
        g_ris[2] = ke;
        break;
    default:
        break;
    }


    if (is2Rol)
    {
        ClickKey(VK_SPACE);
        Sleep(800);
    }
    return 0;
}

BOOL Game_Zzz_InitRoleInfoMap()
{
    Game_Zzz_CheckStatusInGame();
    ClickKey('N');
    Sleep(800);
    MoveMouseTo(-740, 0);
    ClickMouse(50, 1000, 100);//空洞
    MoveMouseTo(-740, 460);
    DragMouse(260, 460);//减少误差
    MoveMouseTo(-740, 460);
    ClickMouse(50, 1000, 500);//1
    Game_Zzz_ConfirmCentre();
    Sleep(1000);
    Game_Zzz_CheckStatusIsNormal();
    Game_Zzz_InitRoleInfoSim();

    return 0;
}

BOOL CheckAndSwitchToTarRoleInfo(ROLE_INFOEX role,BYTE frequency)
{
    ROLE_INFOEX tmp = { 0 };
    Sleep(500);
    for (size_t i = 0; i < frequency; i++)
    {
        if(i>0&&i%8==0){
            ClickKey('S',2000);
        }
        Game_Zzz_GetRoleInfo(&tmp);
        if (tmp == role)
        {
            return 1;
        }
        ClickKey(VK_SPACE);
        Sleep(800);
    }

    return 0;
}

BOOL CheckFirstIsTarRoleInfo(ROLE_INFOEX role)
{
    ROLE_INFOEX tmp = { 0 };
    Game_Zzz_GetRoleInfo(&tmp);
    if (tmp == role)
    {
        return 1;
    }
    return 0;
}

BOOL TMP9(ROLE_INFOEX role)
{

    return 0;
}

BOOL Game_Zzz_InitRoleInfoScene(BYTE scene)
{
    switch (scene)
    {
    case 1:
        Game_Zzz_InitRoleInfo();

        break;
    case 2:
        Game_Zzz_InitRoleInfoMap();
        break;
    default:
        Game_Zzz_InitRoleInfoSim();
        break;
    }
    roleInitCom = TRUE;
    return 0;
}

BOOL DragMouseEx(int x, int y)
{
    Sleep(50);
    PressKey(VK_MENU);
    Sleep(50);
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; // 鼠标左键按下
    SendInput(1, &input, sizeof(INPUT));

    Sleep(100);
    if (g_Scale == 1) {
        x = x / 1.5;
        y = y / 1.5;
    }
    else if (g_Scale == 1.25) {
        x = x / 1.2;
        y = y / 1.2;
    }
    MoveMouseTo(x, y);
    Sleep(100);

    input.mi.dwFlags = MOUSEEVENTF_LEFTUP; // 鼠标左键释放
    SendInput(1, &input, sizeof(INPUT));
    ReleaseKey(VK_MENU);
    Sleep(50);

    return 0;
}

BOOL Game_Zzz_HollowToArea()
{
    Sleep(100);

    if (BYTE(GetRGBAt(760, 360)) <= 0x16) {
        MoveMouseTo(760, 360);
        ClickMouse();
        Sleep(100);
        return 1;
    }
    else {
        ClickMouse();
        Sleep(100);
        if (BYTE(GetRGBAt(760, 360)) <= 0x16) {
            MoveMouseTo(760, 360);
            ClickMouse();
            Sleep(100);
            return 1;
        }
        else {
            Sleep(100);
            return 0;
        }
    }
    Sleep(100);
    return 0;
}

void Game_Zzz_GetExistRoleInfo(PROLE_INFOEX pRole)
{
    ROLE_INFOEX tmp = { 0 };
    Game_Zzz_GetRoleInfo(&tmp);
    for (int var = 0; var < 3; ++var) {
        if (g_ris[var] == tmp) {
            *pRole = (ROLE_INFOEX)g_ris[var];
            return;
        }
    }
}

BOOL Game_Zzz_qt_ThreadsSRT(BYTE sel, const wchar_t* privilege)
{
    switch (sel)
    {
    case THREADS_SUSPEND:
        for (size_t i = 0; i < THREAD_QT_MAX; i++)
        {
            if (g_qt_threads[i].threadHandle != NULL)
            {
                Game_Zzz_ThreadsSRT(THREADS_SUSPEND);
                if (privilege != NULL && !wcscmp(g_qt_threads[i].threadName, privilege)) {
                    continue;
                }
                SuspendThread(g_qt_threads[i].threadHandle);

            }
        }
        break;
    case THREADS_RESUME:
        for (size_t i = 0; i < THREAD_QT_MAX; i++)
        {
            if (g_qt_threads[i].threadHandle != NULL)
            {
                Game_Zzz_ThreadsSRT(THREADS_RESUME);
                if (privilege != NULL && g_qt_threads[i].threadName == privilege) {
                    continue;
                }
                ResumeThread(g_qt_threads[i].threadHandle);
            }
        }
        break;
    case THREADS_TERNIMATE:
        for (size_t i = 0; i < THREAD_QT_MAX; i++)
        {
            if (g_qt_threads[i].threadHandle != NULL)
            {
                Game_Zzz_ThreadsSRT(THREADS_TERNIMATE);
                if (privilege != NULL && g_qt_threads[i].threadName == privilege) {
                    continue;
                }
                TerminateThread(g_qt_threads[i].threadHandle, 2);
                CloseHandle(g_qt_threads[i].threadHandle);
                g_qt_threads[i].threadHandle = NULL;
                g_qt_threads[i].threadName = NULL;
            }
        }
        break;
    default:
        break;
    }
    return 0;
}

DWORD CheckDot(PVOID pParam)
{
    while (1)
    {
        if (GetAsyncKeyState(VK_DECIMAL) & 0x1) {
            qDebug() << ".被按下 ，当前状态：" << g_qt_dotStatus;
            if (g_qt_dotStatus)
            {
                Game_Zzz_qt_ThreadsSRT(THREADS_SUSPEND);
                ReleaseKeyAll();
                g_qt_dotStatus = !g_qt_dotStatus;
            }
            else
            {
                Game_Zzz_qt_ThreadsSRT(THREADS_RESUME);
                g_qt_dotStatus = !g_qt_dotStatus;
            }
        }
        Sleep(60);
    }

    return 0;
}

DWORD WINAPI Game_Zzz_EntryHollow(LPVOID pParam)
{

    auto start = high_resolution_clock::now();
    DWORD info = *(DWORD*)pParam;
    DWORD team = *((DWORD*)pParam + 1);
    ROLE_INFOEX roin = { 0 };
    DWORD map = info >> 0x8;
    BYTE area = (BYTE)info;
    BattleFunc tt = nullptr;
    Game_Zzz_CheckStatusIsNormal();
    if (team == 1)
    {
        is2Rol = 1;
        whoAppear = XING_JIAN_YA_CODE;
        Game_Zzz_InitRoleInfoScene();
        roin = ya;
        tt = TEAM_YIN_YA_LIU;

    }
    else if (team == 2)
    {
        whoAppear = YI_XUAN_CODE;
        Game_Zzz_InitRoleInfoScene();
        roin = xuan;
        tt = TEAM_XUAN_HU_FU;
    }
    else if (team == 3)
    {
        is2Rol = 1;
        whoAppear = AI_LI_SI_CODE;
        Game_Zzz_InitRoleInfoScene();
        roin = ai;
        tt = TEAM_YOU_AI_NA;
    }

    if (map & MAP1)
    {
        if (area & AREA1)Game_Zzz_Battle_HollowMonster_ZYZZQ(roin, tt);
        if (area & AREA2)Game_Zzz_Battle_HollowMonster_ZYZZQ2(roin, tt);
        if (area & AREA3)Game_Zzz_Battle_HollowMonster_ZYZZQ3(roin, tt);
        if (area & AREA4)Game_Zzz_Battle_HollowMonster_ZYZZQ4(roin, tt);
    }


    if (map & MAP2) { Game_Zzz_Battle_HollowMonster_ZGSQJZ(roin, tt); }
    if (map & MAP3) { Game_Zzz_Battle_HollowMonster_KYYJZ(roin, tt); }
    if (map & MAP4) { Game_Zzz_Battle_HollowMonster_JJZQ(roin, tt); }
    if (map & MAP5) { Game_Zzz_Battle_HollowMonster_CJQZX(roin, tt); }
    if (map & MAP6) { Game_Zzz_Battle_HollowMonster_QSGY(roin, tt); }
    if (map & MAP7) { Game_Zzz_Battle_HollowMonster_HTKXZ(roin, tt); }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(end - start).count();
    double minutes = duration / 60;
    double seconds = duration % 60;
    emit g_cu.update_outInfo(QString("锄地概况：打怪次数为：%1/%2,耗时为： %3M  %4S").arg(countHitM).arg(MAX_BOSS).arg(minutes,0,'f',2).arg(seconds,0,'f',2));
    emit g_cu.update_outLog("完成收工");
    return 0;
}

DWORD WINAPI Test(LPVOID pParam)
{
    // is2Rol = 1;
    // whoAppear = XING_JIAN_YA_CODE;
    // Game_Zzz_InitRoleInfoScene();
    // Game_Zzz_Battle_1();
    // ClickKey('N');
    // Sleep(1000);
    // Game_Zzz_HangTianCheng();
    // int x=-740;
    // int y=460;
    // x*=(2560/1920)*(2560/1920);
    // y*=(1440/1080)*(1440/1080);
    // MoveMouseTo(x, y);
    // CheckAndSwitchToTarRoleInfo(ya);
    return 0;
}

BOOL Game_Zzz_BrushMaterial_Accelerate(ROLE_INFOEX roin, LONG cycle)
{
    ROLE_INFOEX t = { 0 };
    while (cycle) {
        Game_Zzz_GetExistRoleInfo(&t);
        if (t == roin) {
            return 1;
        }
        Sleep(400);
    }
    return 0;
}

BOOL Game_Zzz_AccelerateVerify(ROLE_INFOEX roin, LONG cycle, LONG cycle2, LONG sleep)
{
    if (Game_Zzz_BrushMaterial_Accelerate(roin, cycle) || Game_Zzz_CheckStatusIsNormal(cycle2, sleep)) {

        Sleep(100);
        return 1;
    }
    return 0;
}

void ReleaseKeyAll()
{
    ReleaseKey('W');
    ReleaseKey('A');
    ReleaseKey('S');
    ReleaseKey('D');
    ReleaseKey('E');
    ReleaseKey('Q');
    ReleaseKey(VK_MENU);
    ReleaseKey(VK_TAB);
}

BOOL Game_Zzz_Battle_HollowMonster_ZYZZQ(ROLE_INFOEX roin, BattleFunc func)
{

    {
        ClickKey('N');
        Sleep(1000);
        Game_Zzz_HangTianCheng();
        MoveMouseTo(-740, 460);
        // DragMouse(260, 460);//减少误差
        ClickMouse(50, 1000, 500);//1
        Game_Zzz_ConfirmCentre();
        Game_Zzz_AccelerateVerify(roin);
        ///////////////////////////进地图
        if (!CheckFirstIsTarRoleInfo(roin)) {
            CheckAndSwitchToTarRoleInfo(roin);
            Game_Zzz_CheckStatusInGame();
            ClickKey('N');
            Sleep(1000);
            MoveMouseTo(-740, 0);
            ClickMouse(50, 1000, 100);//空洞
            MoveMouseTo(-740, 460);
            // DragMouse(260, 460);//减少误差
            MoveMouseTo(-740, 460);
            ClickMouse(50, 1000, 500);//1
            Game_Zzz_ConfirmCentre();
            Sleep(1000);
            Game_Zzz_CheckStatusIsNormal();
        }
        DragMouseEx(-116, 0);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(3400 * roin.action.runSpeed);
        DragMouseEx(132, 0);
        Sleep(3500 * roin.action.runSpeed);
        DragMouseEx(302, 0);
        Sleep(2000 * roin.action.runSpeed);
        DragMouseEx(-230, 0);
        Sleep(2000 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50))//boss1
        {
            func();
        }else{
            emit g_cu.update_outInfo("中央制造区-东侧-1未发现boss");
        }

        CheckAndSwitchToTarRoleInfo(roin);
        ///////////////////////////////
        ClickKey('M');
        Sleep(800);
        ClickKey('D', 1000);
        ClickKey('W', 3000);
        MoveMouseTo(-268, 268);
        ClickMouse(100, 800, 500);
        if (!Game_Zzz_HollowToArea()) {//前往
            ClickKey('D', 500);
            ClickKey('W', 500);
            MoveMouseTo(-268, 268);
            ClickMouse(100, 800, 500);
            Game_Zzz_HollowToArea();
        }
        ///////////////
        Game_Zzz_AccelerateVerify(roin);
        PressKey('A');
        ClickMouseEx(M_R);
        ReleaseKey('A');
        Sleep(800);
        DragMouseEx(-420 * roin.action.angle, 0);//转向
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(2800 * roin.action.runSpeed);
        DragMouseEx(40, 0);
        Sleep(2300 * roin.action.runSpeed);
        DragMouseEx(-120, 0);
        Sleep(1000 * roin.action.runSpeed);
        ReleaseKey('W');
        Sleep(500);
        if (!Game_Zzz_CheckStatusIsNormal(1, 50))//打boss2
        {
            func();
        }else{
            emit g_cu.update_outInfo("中央制造区-东侧-2未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        ////////////////////////////////////////
        ClickKey('M');
        Sleep(1000);
        ClickKey('A', 1000);
        ClickKey('W', 1000);
        MoveMouseTo(-340, 180);
        ClickMouse(50, 200, 1000);
        if (!Game_Zzz_HollowToArea()) {//前往
            ClickKey('A', 500);
            ClickKey('W', 500);
            MoveMouseTo(-340, 180);
            ClickMouse(50, 200, 1000);
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        ClickKey('W', 500 * roin.action.runSpeed);
        DragMouseEx(-280, 0);
        ClickKey('W', 5000 * roin.action.runSpeed);
        DragMouseEx(-252 * roin.action.angle, 0);
        ClickKey('W', 2000 * roin.action.runSpeed);//抵达boss3
        if (!Game_Zzz_CheckStatusIsNormal(1, 50))
        {
            func();
        }
        else
        {
            emit g_cu.update_outInfo("中央制造区-东侧-3未发现boss");

            PressKey('W');
            ClickMouseEx(M_R);
            Sleep(6800 * roin.action.runSpeed);
            ReleaseKey('W');
            DragMouseEx(-290 * roin.action.angle, 0);
            PressKey('W');
            ClickMouseEx(M_R);
            Sleep(5000 * roin.action.runSpeed);
            ReleaseKey('W');
            DragMouseEx(-158, 0);
            ClickKey('W', 4000 * roin.action.runSpeed);//抵达boss4
            Sleep(500);
            if (!Game_Zzz_CheckStatusIsNormal(1, 50))
            {
                func();
            }else{
                emit g_cu.update_outInfo("中央制造区-东侧-4未发现boss");
            }
            CheckAndSwitchToTarRoleInfo(roin);
            emit g_cu.update_outLog("中央制造区-东侧完成");
            return 0;
        }
        CheckAndSwitchToTarRoleInfo(roin);
        ////////////////////////////////////////
        ClickKey('M');
        Sleep(1000);
        ClickKey('A', 1000);
        ClickKey('W', 1000);
        MoveMouseTo(-340, 180);
        ClickMouse(50, 200, 1000);
        if (!Game_Zzz_HollowToArea()) {//前往
            ClickKey('A', 500);
            ClickKey('W', 500);
            MoveMouseTo(-340, 180);
            ClickMouse(50, 200, 1000);
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        ClickKey('W', 500 * roin.action.runSpeed);
        DragMouseEx(-280, 0);
        ClickKey('W', 5000 * roin.action.runSpeed);
        DragMouseEx(-256, 0);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(8500 * roin.action.runSpeed);
        ReleaseKey('W');
        DragMouseEx(-290 * roin.action.angle, 0);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(5000 * roin.action.runSpeed);
        ReleaseKey('W');
        DragMouseEx(-160, 0);
        ClickKey('W', 4000 * roin.action.runSpeed);//抵达boss4
        Sleep(500);
        if (!Game_Zzz_CheckStatusIsNormal(1, 50))
        {
            func();
        }else{
            emit g_cu.update_outInfo("中央制造区-东侧-4未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        emit g_cu.update_outLog("中央制造区-东侧完成");
        return 0;
    }

}

BOOL Game_Zzz_Battle_HollowMonster_ZYZZQ2(ROLE_INFOEX roin, BattleFunc func)
{

    {
        if (!CheckFirstIsTarRoleInfo(roin))
        {
            Game_Zzz_CheckStatusInGame();
            CheckAndSwitchToTarRoleInfo(roin);

            ClickKey('N');
            Sleep(800);
            MoveMouseTo(-740, 0);
            ClickMouse(50, 1000, 100);//空洞
            MoveMouseTo(-740, 460);
            DragMouse(260, 460);//减少误差
            MoveMouseTo(-740, 460);
            ClickMouse(50, 1000, 500);//1
            Game_Zzz_ConfirmCentre();
            Sleep(1000);
            Game_Zzz_CheckStatusIsNormal();
        }
        Sleep(800);
        ClickKey('M');
        Sleep(800);
        MoveMouseTo(-720, 480);
        ClickMouse(50, 500, 800);
        if (BYTE(GetRGBAt(-720, 340)) != 0x32) {
            ClickMouse(50, 500, 500);
        }
        MoveMouseTo(-720, 340);
        ClickMouse(100, 500, 500);//大楼西侧
        MoveMouseTo(292, -220);
        ClickMouse(100, 500, 500);
        if (!Game_Zzz_HollowToArea()) {//前往
            MoveMouseTo(-720, 480);
            ClickMouse(50, 500, 500);
            MoveMouseTo(-720, 340);
            ClickMouse(100, 500, 500);
            MoveMouseTo(292, -220);
            ClickMouse(100, 500, 500);
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        ////////////////////////
        PressKey('W');
        Sleep(200);
        ClickMouseEx(M_R);
        Sleep(3500 * roin.action.runSpeed);
        DragMouseEx(280 * roin.action.angle, 0);
        Sleep(3800 * roin.action.runSpeed);
        DragMouseEx(-90, 0);
        Sleep(3000 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50))//boss1
        {
            func();
        }else{
            emit g_cu.update_outInfo("中央制造区-西侧-1未发现boss");
        }
        // ////////////////////////////////
        CheckAndSwitchToTarRoleInfo(roin);
        ClickKey('M');
        Sleep(800);
        ClickKey('A', 2000);
        ClickKey('S', 1000);
        MoveMouseTo(-355, -75);
        ClickMouse(100, 500, 500);
        if (!Game_Zzz_HollowToArea()) {//前往
            ClickKey('A', 500);
            ClickKey('S', 500);
            MoveMouseTo(-355, -75);
            ClickMouse(100, 500, 500);
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        PressKey('W');
        Sleep(200);
        ClickMouseEx(M_R);
        Sleep(1800 * roin.action.runSpeed);
        DragMouseEx(140, 0);
        Sleep(9200 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50))//boss2
        {
            func();
        }else{
            emit g_cu.update_outInfo("中央制造区-西侧-2未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        emit g_cu.update_outLog("中央制造区-西侧完成");
        return 0;
    }

}

BOOL Game_Zzz_Battle_HollowMonster_ZYZZQ3(ROLE_INFOEX roin, BattleFunc func)
{
    {
        if (!CheckFirstIsTarRoleInfo(roin))
        {
            Game_Zzz_CheckStatusInGame();
            CheckAndSwitchToTarRoleInfo(roin);
            ClickKey('N');
            Sleep(800);
            MoveMouseTo(-740, 0);
            ClickMouse(50, 1000, 100);//空洞
            MoveMouseTo(-740, 460);
            DragMouse(260, 460);//减少误差
            MoveMouseTo(-740, 460);
            ClickMouse(50, 1000, 500);//1
            Game_Zzz_ConfirmCentre();
            Sleep(1000);
            Game_Zzz_CheckStatusIsNormal();
        }
        ClickKey('M');
        Sleep(800);
        MoveMouseTo(-720, 480);
        ClickMouse(50, 500, 500);
        Sleep(800);
        if (BYTE(GetRGBAt(-720, 260)) != 0x32) {
            ClickMouse(50, 500, 500);
        }
        MoveMouseTo(-720, 260);
        ClickMouse(50, 500, 500);//顶楼
        MoveMouseTo(30, -110);
        ClickMouse(100, 500, 500);
        if (!Game_Zzz_HollowToArea()) {//前往
            MoveMouseTo(-720, 480);
            ClickMouse(50, 500, 500);
            Sleep(800);
            MoveMouseTo(-720, 260);
            ClickMouse(100, 500, 500);
            MoveMouseTo(30, -110);
            ClickMouse(100, 500, 500);
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        ////////////////////////
        PressKey('W');
        Sleep(1400);
        DragMouseEx(290, 0);
        Sleep(2300 * roin.action.runSpeed);
        DragMouseEx(290, 0);
        Sleep(3000 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50))
        {
            func();
        }else{
            emit g_cu.update_outInfo("中央制造区-顶楼未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        emit g_cu.update_outLog("中央制造区-顶楼完成");
        return 0;
    }

}

BOOL Game_Zzz_Battle_HollowMonster_ZYZZQ4(ROLE_INFOEX roin, BattleFunc func)
{
    {

        if (!CheckFirstIsTarRoleInfo(roin)) {
            Game_Zzz_CheckStatusInGame();
            CheckAndSwitchToTarRoleInfo(roin);
            ClickKey('N');
            Sleep(800);
            MoveMouseTo(-740, 0);
            ClickMouse(50, 1000, 100);//空洞
            MoveMouseTo(-740, 460);
            DragMouse(260, 460);//减少误差
            MoveMouseTo(-740, 460);
            ClickMouse(50, 1000, 500);//1
            Game_Zzz_ConfirmCentre();
            Sleep(1000);
            Game_Zzz_CheckStatusIsNormal();

        }
        ClickKey('M');
        Sleep(800);
        MoveMouseTo(-720, 480);
        ClickMouse(50, 500, 500);
        if (BYTE(GetRGBAt(-720, 180)) != 0x32) {
            ClickMouse(50, 500, 500);
        }
        MoveMouseTo(-720, 180);
        ClickMouse(100, 500, 500);//物流储存室
        MoveMouseTo(60, -150);
        ClickMouse(100, 500, 500);
        if (!Game_Zzz_HollowToArea()) {//前往
            MoveMouseTo(-720, 480);
            ClickMouse(50, 500, 500);
            MoveMouseTo(-720, 180);
            ClickMouse(100, 500, 500);
            MoveMouseTo(60, -150);
            ClickMouse(100, 500, 500);
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(7000 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50)) {
            func();
        }else{
            emit g_cu.update_outInfo("中央制造区-物流仓储区-1未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        Sleep(500);
        ClickKey('M');
        Sleep(800);
        ClickKey('S', 1000);
        ClickKey('D', 1000);
        MoveMouseTo(-570, -280);
        ClickMouse(100, 500, 500);
        if (!Game_Zzz_HollowToArea()) {//前往
            ClickKey('S', 500);
            ClickKey('D', 500);
            MoveMouseTo(-570, -280);
            ClickMouse(100, 500, 500);
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        DragMouseEx(250, 0);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(4000 * roin.action.runSpeed);
        DragMouseEx(-250, 0);
        Sleep(1800 * roin.action.runSpeed);
        DragMouseEx(320, 0);
        Sleep(2500 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50)) {
            func();
        }else{
            emit g_cu.update_outInfo("中央制造区-物流仓储区-2未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        emit g_cu.update_outLog("中央制造区-物流仓储区完成");
        return 0;
    }

}

BOOL Game_Zzz_Battle_HollowMonster_ZGSQJZ(ROLE_INFOEX roin, BattleFunc func)
{
    {
        if (!CheckFirstIsTarRoleInfo(roin)) {
            Game_Zzz_CheckStatusInGame();
            CheckAndSwitchToTarRoleInfo(roin);
            ClickKey('N');
            Sleep(800);
            MoveMouseTo(-740, 0);
            ClickMouse(50, 1000, 100);//空洞
            MoveMouseTo(-740, 460);
            // DragMouse(260, 460);//减少误差
            MoveMouseTo(-740, 460);
            ClickMouse(50, 1000, 500);//1
            Game_Zzz_ConfirmCentre();
            Sleep(1000);
            Game_Zzz_CheckStatusIsNormal();
        }

        ClickKey('M');
        Sleep(800);
        MoveMouseTo(600, 138);
        ClickMouse(100, 500, 500);
        Sleep(800);
        MoveMouseTo(-900, 163);
        ClickMouse(100, 500, 500);
        if (!Game_Zzz_HollowToArea()) {//前往
            MoveMouseTo(600, 138);
            ClickMouse(100, 500, 500);
            Sleep(800);
            MoveMouseTo(-900, 163);
            ClickMouse(100, 500, 500);
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        DragMouseEx(220, 0);
        ClickKey('W', 4000 * roin.action.runSpeed);
        if (!Game_Zzz_CheckStatusIsNormal(1, 50))//boss1
        {
            func();
        }else{
            emit g_cu.update_outInfo("职工社区旧址-1未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        /////////////////////////////
        ClickKey('M');
        Sleep(800);
        ClickKey('A', 500);
        ClickKey('W', 2000);
        MoveMouseTo(-90, 370);
        ClickMouse(100, 500, 500);
        if (!Game_Zzz_HollowToArea()) {//前往
            ClickKey('A', 500);
            ClickKey('W', 500);
            MoveMouseTo(-90, 370);
            ClickMouse(100, 500, 500);
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        DragMouseEx(340, 0);
        PressKey('W');
        Sleep(1800 * roin.action.runSpeed);
        DragMouseEx(200, 0);
        Sleep(4200 * roin.action.runSpeed);
        DragMouseEx(-300, 0);
        Sleep(3000 * roin.action.runSpeed);
        DragMouseEx(-120, 0);
        Sleep(2500 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50))//boss2
        {
            func();
        }else{
            emit g_cu.update_outInfo("职工社区旧址-2未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        //////////////////////////////////
        ClickKey('M');
        Sleep(800);
        ClickKey('D', 2000);
        ClickKey('S', 2000);
        MoveMouseTo(-470, -430);
        ClickMouse(100, 500, 500);
        if (!Game_Zzz_HollowToArea()) {//前往
            ClickKey('D', 500);
            ClickKey('S', 500);
            MoveMouseTo(-470, -430);
            ClickMouse(100, 500, 500);
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        DragMouseEx(-200, 0);
        DragMouseEx(-320, 0);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(1000 * roin.action.runSpeed);
        DragMouseEx(200, 0);
        DragMouseEx(80, 0);
        Sleep(600 * roin.action.runSpeed);
        DragMouseEx(-200, 0);
        Sleep(800 * roin.action.runSpeed);
        DragMouseEx(200, 0);
        Sleep(800 * roin.action.runSpeed);
        DragMouseEx(-200, 0);
        DragMouseEx(-100, 0);
        Sleep(800 * roin.action.runSpeed);
        ReleaseKey('W');
        DragMouseEx(220, 0);
        DragMouseEx(180, 0);
        PressKey('W');
        Sleep(3000 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50))//boss3
        {
            func();
        }else{
            emit g_cu.update_outInfo("职工社区旧址-3未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        ///////////////////////////////////
        ClickKey('M');
        Sleep(800);
        ClickKey('D', 1000);
        ClickKey('W', 2000);
        MoveMouseTo(-180, 380);
        ClickMouse(100, 500, 500);
        if (!Game_Zzz_HollowToArea()) {//前往
            ClickKey('D', 500);
            ClickKey('W', 500);
            MoveMouseTo(-180, 380);
            ClickMouse(100, 500, 500);
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        ClickKey('S', 1300 * roin.action.walkSpeed);
        DragMouseEx(-200, 0);
        DragMouseEx(-40, 0);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(3400 * roin.action.runSpeed);
        DragMouseEx(200, 0);
        Sleep(1600 * roin.action.runSpeed);
        DragMouseEx(-100, 0);
        Sleep(2800 * roin.action.runSpeed);
        DragMouseEx(100, 0);
        Sleep(2000 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50))//BOSS4
        {
            func();
        }else{
            emit g_cu.update_outInfo("职工社区旧址-4未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        emit g_cu.update_outLog("职工社区旧址完成");
        return 0;
    }

}

BOOL Game_Zzz_Battle_HollowMonster_KYYJZ(ROLE_INFOEX roin, BattleFunc func)
{
    {

        if (!CheckFirstIsTarRoleInfo(roin)) {
            Game_Zzz_CheckStatusInGame();
            CheckAndSwitchToTarRoleInfo(roin);
            ClickKey('N');
            Sleep(800);
            MoveMouseTo(-740, 0);
            ClickMouse(50, 1000, 100);//空洞
            MoveMouseTo(-740, 460);
            // DragMouse(260, 460);//减少误差
            MoveMouseTo(-740, 460);
            ClickMouse(50, 1000, 500);//1
            Game_Zzz_ConfirmCentre();
            Sleep(1000);
            Game_Zzz_CheckStatusIsNormal();
        }
        ClickKey('N');
        Sleep(1000);
        Game_Zzz_HangTianCheng();

        MoveMouseTo(-140, 450);
        ClickMouse();
        Game_Zzz_ConfirmCentre();
        Game_Zzz_AccelerateVerify(roin);

        ClickKey('M');
        Sleep(800);
        ClickKey('A', 2000);
        Sleep(800);
        MoveMouseTo(-420, 460);
        ClickMouse();
        Sleep(500);
        BYTE r = (BYTE)GetRGBAt(720, -310);
        if (r <= 0x20 || r >= 0x30) {
            ClickMouse();
        }
        MoveMouseTo(720, -310);
        ClickMouse();
        if (!Game_Zzz_HollowToArea()) {//前往
            MoveMouseTo(720, -310);
            ClickMouse();
            Game_Zzz_HollowToArea();
        }

        Game_Zzz_AccelerateVerify(roin);
        DragMouseEx(-140, 0);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(3000 * roin.action.runSpeed);
        DragMouseEx(-140, 0);
        Sleep(2000 * roin.action.runSpeed);
        DragMouseEx(-200, 0);
        Sleep(3000 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50)) {//boss1
            func();
        }else{
            emit g_cu.update_outInfo("科研院旧址-1未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);

        ClickKey('M');
        Sleep(800);
        ClickKey('A', 1000);
        ClickKey('W', 2000);
        MoveMouseTo(150, 160);
        ClickMouse();
        if (!Game_Zzz_HollowToArea()) {//前往
            MoveMouseTo(150, 160);
            ClickMouse();
            Game_Zzz_HollowToArea();
        }

        Game_Zzz_AccelerateVerify(roin);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(500 * roin.action.runSpeed);
        DragMouseEx(200, 0);
        Sleep(3200 * roin.action.runSpeed);
        DragMouseEx(-200, 0);
        Sleep(2600 * roin.action.runSpeed);
        DragMouseEx(200, 0);
        DragMouseEx(80, 0);
        Sleep(600 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50)) {//boss2
            func();
        }else{
            emit g_cu.update_outInfo("科研院旧址-2未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);

        ClickKey('M');
        Sleep(800);
        ClickKey('D', 1500);
        ClickKey('S', 2500);
        Sleep(500);
        MoveMouseTo(-620, -360);
        ClickMouse();
        if (!Game_Zzz_HollowToArea()) {//前往
            MoveMouseTo(-620, -360);
            ClickMouse();
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        DragMouseEx(200, 0);
        DragMouseEx(80, 0);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(500 * roin.action.runSpeed);
        DragMouseEx(-80, 0);
        Sleep(1000 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50)) {//boss3
            func();
        }else{
            emit g_cu.update_outInfo("科研院旧址-3未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);

        ClickKey('M');
        Sleep(800);
        ClickKey('D', 1500);
        ClickKey('S', 2000);
        Sleep(500);
        MoveMouseTo(-620, -360);
        ClickMouse();
        if (!Game_Zzz_HollowToArea()) {//前往
            MoveMouseTo(-620, -360);
            ClickMouse();
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        DragMouseEx(200, 0);
        DragMouseEx(200, 0);
        PressKey('W');
        Sleep(800);//走路
        ReleaseKey('W');
        DragMouseEx(200, 0);
        DragMouseEx(70, 0);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(11000 * roin.action.runSpeed);//跑步
        DragMouseEx(-200, 0);
        Sleep(1000 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50)) {//boss4
            func();
        }else{
            emit g_cu.update_outInfo("科研院旧址-4未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);

        ClickKey('M');
        Sleep(800);
        ClickKey('D', 1500);
        ClickKey('S', 2000);
        Sleep(500);
        MoveMouseTo(-620, -360);
        ClickMouse();
        if (!Game_Zzz_HollowToArea()) {//前往
            MoveMouseTo(-620, -360);
            ClickMouse();
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        PressKey('W');
        Sleep(500);
        ReleaseKey('W');
        DragMouseEx(-200, 0);
        DragMouseEx(-180, 0);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(1000 * roin.action.runSpeed);//跑步
        DragMouseEx(200, 0);
        Sleep(100 * roin.action.runSpeed);
        DragMouseEx(160, 0);
        Sleep(100 * roin.action.runSpeed);
        DragMouseEx(200, 0);
        DragMouseEx(10, 0);
        Sleep(3200 * roin.action.runSpeed);
        DragMouseEx(200, 0);
        Sleep(700 * roin.action.runSpeed);
        DragMouseEx(-200, 0);
        Sleep(1800 * roin.action.runSpeed);
        DragMouseEx(-200, 0);
        DragMouseEx(-80, 0);
        Sleep(2000 * roin.action.runSpeed);
        ReleaseKey('W');
        ClickMouse();
        if (!Game_Zzz_CheckStatusIsNormal(1, 50)) {//boss5
            func();
        }else{
            emit g_cu.update_outInfo("科研院旧址-5未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        emit g_cu.update_outLog("科研院旧址完成");
        return 0;
    }

}

BOOL Game_Zzz_Battle_HollowMonster_JJZQ(ROLE_INFOEX roin, BattleFunc func)
{
    {
        if (!CheckFirstIsTarRoleInfo(roin)) {
            Game_Zzz_CheckStatusInGame();
            CheckAndSwitchToTarRoleInfo(roin);
            ClickKey('N');
            Sleep(800);
            MoveMouseTo(-740, 0);
            ClickMouse(50, 1000, 100);//空洞
            MoveMouseTo(-740, 460);
            // DragMouse(260, 460);//减少误差
            MoveMouseTo(-740, 460);
            ClickMouse(50, 1000, 500);//1
            Game_Zzz_ConfirmCentre();
            Sleep(1000);
            Game_Zzz_CheckStatusIsNormal();
        }
        ClickKey('N');
        Sleep(800);
        Game_Zzz_HangTianCheng();

        MoveMouseTo(160, 460);
        ClickMouse();
        Game_Zzz_ConfirmCentre();
        Game_Zzz_AccelerateVerify(roin);
        PressKey('W');
        ClickMouseEx(M_R);

        Sleep(3500 * roin.action.runSpeed);
        DragMouseEx(200, 0);
        Sleep(1000 * roin.action.runSpeed);
        DragMouseEx(140, 0);
        Sleep(1500 * roin.action.runSpeed);
        DragMouseEx(-200, 0);
        DragMouseEx(-160, 0);
        Sleep(4400 * roin.action.runSpeed);
        DragMouseEx(-200, 0);
        DragMouseEx(-80, 0);
        Sleep(2800 * roin.action.runSpeed);
        DragMouseEx(-160, 0);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50)) {
            func();

        }else{
            emit g_cu.update_outInfo("旧建筑群未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        emit g_cu.update_outLog("旧建筑群完成");
        return 0;

    }

}

BOOL Game_Zzz_Battle_HollowMonster_CJQZX(ROLE_INFOEX roin, BattleFunc func)
{
    {
        if (!CheckFirstIsTarRoleInfo(roin)) {
            Game_Zzz_CheckStatusInGame();
            CheckAndSwitchToTarRoleInfo(roin);
            ClickKey('N');
            Sleep(800);
            MoveMouseTo(-740, 0);
            ClickMouse(50, 1000, 100);//空洞
            MoveMouseTo(-740, 460);
            // DragMouse(260, 460);//减少误差
            MoveMouseTo(-740, 460);
            ClickMouse(50, 1000, 500);//1
            Game_Zzz_ConfirmCentre();
            Sleep(1000);
            Game_Zzz_CheckStatusIsNormal();
        }
        ClickKey('N');
        Sleep(800);
        Game_Zzz_HangTianCheng();
        MoveMouseTo(760, 460);
        ClickMouse();
        Game_Zzz_ConfirmCentre();
        CheckAndSwitchToTarRoleInfo(roin);
        DragMouseEx(-70, 0);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(1500 * roin.action.runSpeed);
        DragMouseEx(-200, 0);
        Sleep(6000 * roin.action.runSpeed);
        DragMouseEx(150, 0);
        Sleep(1500 * roin.action.runSpeed);
        if (!Game_Zzz_CheckStatusIsNormal(1, 50)) {//boss1
            func();
        }else{
            emit g_cu.update_outInfo("粗加工中心-1未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);

        ClickKey('M');
        Sleep(800);
        ClickKey('A', 1000);
        ClickKey('W', 3000);
        MoveMouseTo(-320, 260);
        ClickMouse();
        if (!Game_Zzz_HollowToArea()) {//前往
            MoveMouseTo(-320, 260);
            ClickMouse();
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);

        DragMouseEx(-60, 0);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(3000 * roin.action.runSpeed);
        DragMouseEx(80, 0);
        Sleep(2400 * roin.action.runSpeed);
        DragMouseEx(-200, 0);
        DragMouseEx(-100, 0);
        Sleep(3000 * roin.action.runSpeed);
        DragMouseEx(200, 0);
        Sleep(1000 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50)) {//boss2
            func();
        }else{
            emit g_cu.update_outInfo("粗加工中心-2未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);

        ClickKey('M');
        Sleep(800);
        ClickKey('A', 1500);
        ClickKey('W', 1500);
        MoveMouseTo(-320, 260);
        ClickMouse();
        if (!Game_Zzz_HollowToArea()) {//前往
            MoveMouseTo(-320, 260);
            ClickMouse();
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(1600 * roin.action.runSpeed);
        DragMouseEx(200, 0);
        DragMouseEx(100, 0);
        Sleep(1800 * roin.action.runSpeed);
        DragMouseEx(-200, 0);
        DragMouseEx(-200, 0);
        DragMouseEx(-200, 0);
        Sleep(500 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1, 50)) {//boss3
            func();
        }else{
            emit g_cu.update_outInfo("粗加工中心-3未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        emit g_cu.update_outLog("粗加工中心完成");
        return 0;
    }

}

BOOL Game_Zzz_Battle_HollowMonster_QSGY(ROLE_INFOEX roin, BattleFunc func)
{
    {
        if (!CheckFirstIsTarRoleInfo(roin)) {
            Game_Zzz_CheckStatusInGame();
            CheckAndSwitchToTarRoleInfo(roin);
            ClickKey('N');
            Sleep(800);
            MoveMouseTo(-740, 0);
            ClickMouse(50, 1000, 100);//空洞
            MoveMouseTo(-740, 460);
            // DragMouse(260, 460);//减少误差
            MoveMouseTo(-740, 460);
            ClickMouse(50, 1000, 500);//1
            Game_Zzz_ConfirmCentre();
            Sleep(1000);
            Game_Zzz_CheckStatusIsNormal();

        }

        ClickKey('N');
        Sleep(800);
        Game_Zzz_HangTianCheng();
        MoveMouseTo(760, 460);
        DragMouseEx(-600, 460);
        MoveMouseTo(460, 460);
        ClickMouse();
        Game_Zzz_ConfirmCentre();
        Game_Zzz_AccelerateVerify(roin);
        ClickKey('M');
        Sleep(800);
        MoveMouseTo(-470, 150);
        ClickMouse();
        if (!Game_Zzz_HollowToArea()) {
            MoveMouseTo(-470, 150);
            ClickMouse();
            Game_Zzz_HollowToArea();
        }
        ClickMouse();
        Game_Zzz_AccelerateVerify(roin);
        DragMouseEx(200, 0);
        DragMouseEx(200, 0);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(2000 * roin.action.runSpeed);
        DragMouseEx(-120, 0);
        Sleep(2400 * roin.action.runSpeed);
        DragMouseEx(50, 0);
        Sleep(3500 * roin.action.runSpeed);
        DragMouseEx(200, 0);
        Sleep(500);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1,50)) {
            func();
        }else{
            emit g_cu.update_outInfo("轻松公寓未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        emit g_cu.update_outLog("轻松公寓完成");
        return 0;
    }

}

BOOL Game_Zzz_Battle_HollowMonster_HTKXZ(ROLE_INFOEX roin, BattleFunc func)
{
    {

        if (!CheckFirstIsTarRoleInfo(roin)) {
            Game_Zzz_CheckStatusInGame();
            CheckAndSwitchToTarRoleInfo(roin);
            ClickKey('N');
            Sleep(800);
            MoveMouseTo(-740, 0);
            ClickMouse(50, 1000, 100);//空洞
            MoveMouseTo(-740, 460);
            // DragMouse(260, 460);//减少误差
            MoveMouseTo(-740, 460);
            ClickMouse(50, 1000, 500);//1
            Game_Zzz_ConfirmCentre();
            Sleep(1000);
            Game_Zzz_CheckStatusIsNormal();
        }

        ClickKey('N');
        Sleep(800);
        Game_Zzz_HangTianCheng();
        MoveMouseTo(760, 460);
        DragMouseEx(-600, 460);
        MoveMouseTo(760, 460);
        ClickMouse();
        Game_Zzz_ConfirmCentre();
        Game_Zzz_CheckStatusIsNormal();
        Game_Zzz_AccelerateVerify(roin);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(1500 * roin.action.runSpeed);
        DragMouseEx(140, 0);
        Sleep(1000 * roin.action.runSpeed);
        DragMouseEx(-200, 0);
        DragMouseEx(-160, 0);
        Sleep(2000 * roin.action.runSpeed);
        ReleaseKey('W');
        Sleep(200);
        if (!Game_Zzz_CheckStatusIsNormal(1,50)) {//boss1
            func();
        }else{
            emit g_cu.update_outInfo("航天科学站-1未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);

        ClickKey('M');
        Sleep(800);
        ClickKey('A', 2000);
        ClickKey('S', 3000);
        MoveMouseTo(-20, -320);
        ClickMouse();
        if (!Game_Zzz_HollowToArea()) {
            MoveMouseTo(-20, -320);
            ClickMouse();
            Game_Zzz_HollowToArea();
        }
        Game_Zzz_AccelerateVerify(roin);
        DragMouseEx(200, 0);
        DragMouseEx(60, 0);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(1500 * roin.action.runSpeed);
        DragMouseEx(200, 0);
        DragMouseEx(80, 0);
        Sleep(500 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1,50)) {//boss2
            func();
            CheckAndSwitchToTarRoleInfo(roin);
            ClickKey('M');
            Sleep(800);
            ClickKey('A', 2000);
            ClickKey('S', 3000);
            MoveMouseTo(-20, -320);
            ClickMouse();
            if (!Game_Zzz_HollowToArea()) {
                MoveMouseTo(-20, -320);
                ClickMouse();
                Game_Zzz_HollowToArea();
            }
            Game_Zzz_AccelerateVerify(roin);
            DragMouseEx(200, 0);
            DragMouseEx(60, 0);
            PressKey('W');
            ClickMouseEx(M_R);
            Sleep(1500 * roin.action.runSpeed);
            DragMouseEx(200, 0);
            DragMouseEx(80, 0);
            Sleep(500 * roin.action.runSpeed);
            ReleaseKey('W');
            PressKey('W');
            ClickMouseEx(M_R);
            Sleep(1000 * roin.action.runSpeed);
            DragMouseEx(180, 0);
            Sleep(1500 * roin.action.runSpeed);
            DragMouseEx(-200, 0);
            DragMouseEx(-160, 0);
            Sleep(1000 * roin.action.runSpeed);
            DragMouseEx(200, 0);
            DragMouseEx(200, 0);
            DragMouseEx(100, 0);
            Sleep(2500 * roin.action.runSpeed);
            ReleaseKey('W');
            if (!Game_Zzz_CheckStatusIsNormal(1,50)) {//boss3
                func();
                CheckAndSwitchToTarRoleInfo(roin);
                emit g_cu.update_outLog("航天科学站完成");
                return 0;
            }else{
                emit g_cu.update_outInfo("航天科学站-3未发现boss");
            }
            CheckAndSwitchToTarRoleInfo(roin);
            emit g_cu.update_outLog("航天科学站完成");
            return 0;
        }else{
            emit g_cu.update_outInfo("航天科学站-2未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        PressKey('W');
        ClickMouseEx(M_R);
        Sleep(1000 * roin.action.runSpeed);
        DragMouseEx(180, 0);
        Sleep(1500 * roin.action.runSpeed);
        DragMouseEx(-200, 0);
        DragMouseEx(-160, 0);
        Sleep(1000 * roin.action.runSpeed);
        DragMouseEx(200, 0);
        DragMouseEx(200, 0);
        DragMouseEx(100, 0);
        Sleep(2500 * roin.action.runSpeed);
        ReleaseKey('W');
        if (!Game_Zzz_CheckStatusIsNormal(1,50)) {//boss3
            func();
        }else{
            emit g_cu.update_outInfo("航天科学站-3未发现boss");
        }
        CheckAndSwitchToTarRoleInfo(roin);
        emit g_cu.update_outLog("航天科学站完成");
        return 0;
    }

}
