#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include "ConnectUi.h"
#include <QMutex>
#include <QThread>
#include "zzz.h"
#include <QWaitCondition>



QT_BEGIN_NAMESPACE


namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ConnectUi* getInfo(){return m_info;};


private slots:
    void on_start_clicked();

    void on_operation_clicked();

    void on_setting_clicked();

    void on_set_green_clicked();

    void on_set_white_clicked();

    void on_set_yellow_clicked();

    void on_set_pink_clicked();

    void on_set_black_clicked();

    void on_set_purple_clicked();

    void on_set_blue_clicked();

    void on_execute_clicked();

    void on_execute2_clicked();

    void on_chudi_zyzzq_clicked( );

    void on_test_btn_clicked();

    void on_more_clicked();

    void on_info_quickstart_clicked();

    void on_info_refresh_clicked();

    void on_set_red_clicked();

    void on_rnc_clicked();

    void on_help_clicked();

    void on_faq_clicked();


    void on_display_hide_clicked();

    void on_battle_test_clicked();

private:
    Ui::MainWindow *ui;
    ConnectUi* m_info;
};

#endif // MAINWINDOW_H
