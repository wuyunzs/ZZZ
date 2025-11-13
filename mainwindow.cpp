#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "UiManage.h"





MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowOpacity(0.98);
    qApp->setWindowIcon(QIcon(":/images/src/tp.ico"));
    //颜色
    qApp->setStyleSheet(color_lightGreen);
    ui->set_green->setStyleSheet("background-color: #C7EDCC;");
    ui->set_white->setStyleSheet("background-color: #F5F5F5;");
    ui->set_yellow->setStyleSheet("background-color: #FFDEAD;");
    ui->set_pink->setStyleSheet("background-color: #FFC0CB;");
    ui->set_black->setStyleSheet("background-color: #262626;");
    ui->set_purple->setStyleSheet("background-color: #6A5ACD;");
    ui->set_blue->setStyleSheet("background-color: #6495ED;");
    ui->set_red->setStyleSheet("background-color: #A52A2A;");

    //其他
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox->addItem("---请选择队伍---");
    ui->comboBox->addItem("音雅柳");
    ui->progressBar->setValue(0);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->plainTextEdit_help->setPlainText(help_file);

    //简介
    ui->hekafei->setToolTip("0x1 默认咖啡\r\n0x2 浓缩咖啡\r\n0x3 不喝");
    ui->kaidian->setToolTip("SHORT大小，后四位是列，其余是行");
    ui->suibianguan->setToolTip("BYTE大小，每位代表一列");
    ui->param->setToolTip("参数,分隔。例子：1,0x9,0x17");

    ui->start->setToolTip("启动/初始化");
    ui->operation->setToolTip("操作任务");
    ui->more->setToolTip("更多");
    ui->setting->setToolTip("设置");
    ui->execute->setToolTip("执行");
    ui->execute2->setToolTip("执行");


    connect(&g_cu, &ConnectUi::updateProgress, ui->progressBar, &QProgressBar::setValue);
    connect(&g_cu,&ConnectUi::update_outInfo,ui->outInfo,&QPlainTextEdit::appendPlainText);
    connect(&g_cu,&ConnectUi::update_outLog,ui->outlog,&QPlainTextEdit::appendPlainText);
    SetWindowDisplayAffinity((HWND)this->winId(), WDA_EXCLUDEFROMCAPTURE);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_test_btn_clicked()
{

    ui->stackedWidget_2->setCurrentIndex(4);



}
void MainWindow::on_start_clicked()
{


    ui->operation->setStyleSheet(color_btn1_def);
    ui->start->setStyleSheet(color_btn1_sel);
    ui->more->setStyleSheet(color_btn1_def);
    ui->stackedWidget_2->setCurrentIndex(1);
    g_ThreadF11 = CreateThread(NULL, NULL, CheckF11, NULL, NULL, NULL);
    g_ThreadDot = CreateThread(NULL, NULL, CheckDot, NULL, NULL, NULL);
}

void MainWindow::on_execute_clicked()
{
    if (!g_Hwnd)return;
    SetForegroundWindow(g_Hwnd);
    Game_Zzz_qt_ThreadsSRT(THREADS_TERNIMATE);
    ui->progressBar->setValue(0);
    int max = 0;
    DWORD task = 0;
    if (ui->hekafei->isChecked()) { task |= TASK_TRY_1_COFFEE; max++; }
    if (ui->zhanbu->isChecked()) { task |= TASK_DIVINATION; max++; }
    if (ui->kaidian->isChecked()) { task |= TASK_OPEN_STORE; max++; }
    if (ui->suibianguan->isChecked()) { task |= TASK_SUIBIAN_TEMPLE; max++; }
    if (ui->huoyuedujiangli->isChecked()) { task |= TASK_REWARD; max++; }
    if (ui->lidu->isChecked()) { task |= TASK_LIDU; max++; }
    ui->outlog->appendPlainText(QString("参数组合：0x%1").arg(task, 0, 16).toUpper());
    QStringList parts = ui->param->text().split(',');
    DWORD a = parts[0].trimmed().split("0x")[1].toInt(0, 16) + 0x30;
    DWORD b = parts[1].trimmed().split("0x")[1].toInt(0, 16);
    DWORD c = parts[2].trimmed().split("0x")[1].toInt(0, 16);
    ui->outlog->appendPlainText(QString("%1  %2  %3").arg(a).arg(b).arg(c));
    DWORD* p = new DWORD[]{ task,a,b,c };

    ui->progressBar->setRange(0, max);

    g_qt_threads[0].threadHandle = CreateThread(NULL, NULL, DailyTask, p, NULL, NULL);
    g_qt_threads[0].threadName = THREAD_EXECUTE;
    Sleep(1000);
    delete[] p;

}

void MainWindow::on_execute2_clicked()
{
    if (!g_Hwnd)return;
    Game_Zzz_qt_ThreadsSRT(THREADS_TERNIMATE);
    SetForegroundWindow(g_Hwnd);
    DWORD info = 0;
    DWORD mapInf = 0;
    DWORD areaInf = 0;
    if (ui->chudi_zyzzq->isChecked()) { mapInf |= MAP1; };
    if (ui->cd_dc->isChecked()) { areaInf |= AREA1; };
    if (ui->cd_xc->isChecked()) { areaInf |= AREA2; };
    if (ui->cd_dl->isChecked()) { areaInf |= AREA3; };
    if (ui->cd_ccq->isChecked()) { areaInf |= AREA4; };
    if (ui->chudi_zgsqjz->isChecked()) { mapInf |= MAP2; };
    if (ui->chudi_kyyjz->isChecked()) { mapInf |= MAP3; };
    if (ui->chudi_jjzq->isChecked()) { mapInf |= MAP4; };
    if (ui->chudi_cjgzx->isChecked()) { mapInf |= MAP5; };
    if (ui->chudi_qsgy->isChecked()) { mapInf |= MAP6; };
    if (ui->chudi_htkxz->isChecked()) { mapInf |= MAP7; };
    info = (mapInf << 8) | areaInf;
    DWORD ind = ui->comboBox->currentIndex();
    if (info == 0 || ind == 0) {
        return;
    }
    DWORD* p = new DWORD[]{ info,ind };

    g_qt_threads[1].threadHandle = CreateThread(NULL, NULL, Game_Zzz_EntryHollow, p, NULL, NULL);
    g_qt_threads[1].threadName = THREAD_EXECUTE2;
    Sleep(1000);
    delete[] p;
}


void MainWindow::on_operation_clicked()
{
    ui->operation->setStyleSheet(color_btn1_sel);
    ui->start->setStyleSheet(color_btn1_def);
    ui->more->setStyleSheet(color_btn1_def);
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_setting_clicked()
{

    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_set_green_clicked()
{
    qApp->setStyleSheet(color_lightGreen);
}

void MainWindow::on_set_white_clicked()
{
    qApp->setStyleSheet(color_lightWhite);
}

void MainWindow::on_set_yellow_clicked()
{
    qApp->setStyleSheet(color_lightYellow);
}

void MainWindow::on_set_pink_clicked()
{
    qApp->setStyleSheet(color_lightPink);
}

void MainWindow::on_set_black_clicked()
{
    qApp->setStyleSheet(color_lightBlack);
}

void MainWindow::on_set_purple_clicked()
{
    qApp->setStyleSheet(color_lightPurple);
}

void MainWindow::on_set_blue_clicked()
{
    qApp->setStyleSheet(color_lightBlue);
}

void MainWindow::on_set_red_clicked()
{
    qApp->setStyleSheet(color_red);
}


void MainWindow::on_chudi_zyzzq_clicked()
{
    if (ui->chudi_zyzzq->isChecked()) {
        ui->cd_dc->setCheckable(true);
        ui->cd_xc->setCheckable(true);
        ui->cd_dl->setCheckable(true);
        ui->cd_ccq->setCheckable(true);
        ui->cd_dc->setChecked(true);
        ui->cd_xc->setChecked(true);
        ui->cd_dl->setChecked(true);
        ui->cd_ccq->setChecked(true);
    }
    else {
        ui->cd_dc->setCheckable(false);
        ui->cd_xc->setCheckable(false);
        ui->cd_dl->setCheckable(false);
        ui->cd_ccq->setCheckable(false);
        ui->cd_dc->setChecked(false);
        ui->cd_xc->setChecked(false);
        ui->cd_dl->setChecked(false);
        ui->cd_ccq->setChecked(false);

    }
}


void MainWindow::on_more_clicked()
{
    ui->operation->setStyleSheet(color_btn1_def);
    ui->start->setStyleSheet(color_btn1_def);
    ui->more->setStyleSheet(color_btn1_sel);
    ui->stackedWidget_2->setCurrentIndex(3);
}


void MainWindow::on_info_quickstart_clicked()
{
    HWND hwnd = FindWindow(NULL, GAME_NAME);
    if (!hwnd) {
        ui->outInfo->appendPlainText("启动中>_<");
        if (!ZZZStart()) {
            ui->outInfo->appendPlainText("启动失败O_o");
            return;
        }
        Sleep(3000);
        hwnd = FindWindow(NULL, GAME_NAME);
    }
    else {
        ui->outInfo->appendPlainText("无需启动O_O");
    }
    g_Hwnd = hwnd;

}


void MainWindow::on_info_refresh_clicked()
{
    HWND hwnd = FindWindow(NULL, GAME_NAME);
    g_Hwnd = hwnd;
    if (!InitVal(g_Hwnd)) {
        ui->outInfo->appendPlainText("初始化/刷新失败-_-");
        return;
    }
    ui->outInfo->appendPlainText("初始化/刷新完成^_^");
    WINDOWINFO winInfo = { sizeof(WINDOWINFO) };
    GetWindowInfo(g_Hwnd, &winInfo);
    int ww = winInfo.rcClient.right - winInfo.rcClient.left;
    int hh = winInfo.rcClient.bottom - winInfo.rcClient.top;
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    ui->outInfo->appendPlainText(QString("game w=%1  h=%2  sys w=%3 h=%4 s=%5").arg(ww).arg(hh).arg(LONG(screenWidth)).arg(LONG(screenHeight)).arg(g_Scale));
}




void MainWindow::on_rnc_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_help_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_faq_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_display_hide_clicked()
{
    HWND selfH = (HWND)this->winId();
    DWORD status = 0;
    GetWindowDisplayAffinity(selfH, &status);
    if (status == WDA_NONE) {
        SetWindowDisplayAffinity(selfH, WDA_EXCLUDEFROMCAPTURE);

    }
    else {
        SetWindowDisplayAffinity(selfH, WDA_NONE);
    }
}


void MainWindow::on_battle_test_clicked()
{
    if (!g_Hwnd)return;
    SetForegroundWindow(g_Hwnd);
    g_qt_threads[2].threadHandle=CreateThread(NULL,NULL,Test,NULL,NULL,NULL);
    g_qt_threads[2].threadName=L"test";
}

