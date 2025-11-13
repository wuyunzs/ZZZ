/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QPushButton *start;
    QSpacerItem *verticalSpacer_2;
    QPushButton *operation;
    QSpacerItem *verticalSpacer_3;
    QPushButton *more;
    QSpacerItem *verticalSpacer;
    QPushButton *test_btn;
    QVBoxLayout *verticalLayout_5;
    QStackedWidget *stackedWidget_2;
    QWidget *page_6;
    QScrollArea *scrollArea_4;
    QWidget *scrollAreaWidgetContents_4;
    QWidget *page_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *info_refresh;
    QPushButton *info_quickstart;
    QWidget *page_4;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QPushButton *rnc;
    QWidget *page_5;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QPushButton *setting;
    QPushButton *help;
    QPushButton *faq;
    QWidget *page_9;
    QPushButton *display_hide;
    QPushButton *battle_test;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *pushButton;
    QWidget *page_1;
    QPushButton *set_green;
    QPushButton *set_white;
    QPushButton *set_yellow;
    QPushButton *set_pink;
    QPushButton *set_blue;
    QPushButton *set_black;
    QPushButton *set_purple;
    QPushButton *set_red;
    QWidget *page_2;
    QGroupBox *daily;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *hekafei;
    QCheckBox *zhanbu;
    QCheckBox *kaidian;
    QCheckBox *suibianguan;
    QCheckBox *huoyuedujiangli;
    QCheckBox *lidu;
    QLineEdit *param;
    QHBoxLayout *horizontalLayout_3;
    QProgressBar *progressBar;
    QPushButton *execute;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QCheckBox *cd_xc;
    QCheckBox *chudi_zyzzq;
    QCheckBox *cd_dc;
    QCheckBox *chudi_zgsqjz;
    QCheckBox *cd_dl;
    QCheckBox *chudi_kyyjz;
    QCheckBox *chudi_cjgzx;
    QCheckBox *chudi_jjzq;
    QCheckBox *cd_ccq;
    QCheckBox *chudi_qsgy;
    QCheckBox *chudi_htkxz;
    QPushButton *execute2;
    QComboBox *comboBox;
    QWidget *page_7;
    QPlainTextEdit *plainTextEdit_help;
    QWidget *page_8;
    QHBoxLayout *horizontalLayout_4;
    QPlainTextEdit *outInfo;
    QPlainTextEdit *outlog;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1256, 787);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        start = new QPushButton(centralwidget);
        start->setObjectName("start");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(start->sizePolicy().hasHeightForWidth());
        start->setSizePolicy(sizePolicy);
        start->setMinimumSize(QSize(0, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/src/zzz.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        start->setIcon(icon);
        start->setIconSize(QSize(32, 32));

        verticalLayout_4->addWidget(start);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_4->addItem(verticalSpacer_2);

        operation = new QPushButton(centralwidget);
        operation->setObjectName("operation");
        sizePolicy.setHeightForWidth(operation->sizePolicy().hasHeightForWidth());
        operation->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/src/task.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        operation->setIcon(icon1);
        operation->setIconSize(QSize(32, 32));

        verticalLayout_4->addWidget(operation);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_4->addItem(verticalSpacer_3);

        more = new QPushButton(centralwidget);
        more->setObjectName("more");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/src/more.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        more->setIcon(icon2);
        more->setIconSize(QSize(32, 32));

        verticalLayout_4->addWidget(more);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        test_btn = new QPushButton(centralwidget);
        test_btn->setObjectName("test_btn");
        sizePolicy.setHeightForWidth(test_btn->sizePolicy().hasHeightForWidth());
        test_btn->setSizePolicy(sizePolicy);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/src/test.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        test_btn->setIcon(icon3);
        test_btn->setIconSize(QSize(32, 32));

        verticalLayout_4->addWidget(test_btn);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        stackedWidget_2 = new QStackedWidget(centralwidget);
        stackedWidget_2->setObjectName("stackedWidget_2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stackedWidget_2->sizePolicy().hasHeightForWidth());
        stackedWidget_2->setSizePolicy(sizePolicy1);
        stackedWidget_2->setMinimumSize(QSize(200, 0));
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        scrollArea_4 = new QScrollArea(page_6);
        scrollArea_4->setObjectName("scrollArea_4");
        scrollArea_4->setGeometry(QRect(0, 0, 201, 751));
        scrollArea_4->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName("scrollAreaWidgetContents_4");
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 199, 749));
        scrollArea_4->setWidget(scrollAreaWidgetContents_4);
        stackedWidget_2->addWidget(page_6);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        scrollArea = new QScrollArea(page_3);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 0, 201, 751));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 199, 749));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy2);
        info_refresh = new QPushButton(scrollAreaWidgetContents);
        info_refresh->setObjectName("info_refresh");
        info_refresh->setGeometry(QRect(0, 70, 199, 71));
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(info_refresh->sizePolicy().hasHeightForWidth());
        info_refresh->setSizePolicy(sizePolicy3);
        info_refresh->setStyleSheet(QString::fromUtf8(" text-align: left; \n"
"vertical-align: middle;"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/src/refresh.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        info_refresh->setIcon(icon4);
        info_refresh->setIconSize(QSize(40, 40));
        info_quickstart = new QPushButton(scrollAreaWidgetContents);
        info_quickstart->setObjectName("info_quickstart");
        info_quickstart->setGeometry(QRect(0, 0, 199, 71));
        QSizePolicy sizePolicy4(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(info_quickstart->sizePolicy().hasHeightForWidth());
        info_quickstart->setSizePolicy(sizePolicy4);
        info_quickstart->setStyleSheet(QString::fromUtf8(" text-align: left; \n"
"vertical-align: middle;"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/src/quickStart.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        info_quickstart->setIcon(icon5);
        info_quickstart->setIconSize(QSize(40, 40));
        scrollArea->setWidget(scrollAreaWidgetContents);
        stackedWidget_2->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        scrollArea_2 = new QScrollArea(page_4);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setGeometry(QRect(0, 0, 201, 751));
        sizePolicy4.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy4);
        scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 199, 749));
        rnc = new QPushButton(scrollAreaWidgetContents_2);
        rnc->setObjectName("rnc");
        rnc->setGeometry(QRect(0, 0, 201, 61));
        rnc->setStyleSheet(QString::fromUtf8(" text-align: left; \n"
"vertical-align: middle;"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/src/richang.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        rnc->setIcon(icon6);
        rnc->setIconSize(QSize(40, 40));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        stackedWidget_2->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        scrollArea_3 = new QScrollArea(page_5);
        scrollArea_3->setObjectName("scrollArea_3");
        scrollArea_3->setGeometry(QRect(0, 0, 201, 841));
        sizePolicy3.setHeightForWidth(scrollArea_3->sizePolicy().hasHeightForWidth());
        scrollArea_3->setSizePolicy(sizePolicy3);
        scrollArea_3->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollArea_3->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName("scrollAreaWidgetContents_3");
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 199, 839));
        setting = new QPushButton(scrollAreaWidgetContents_3);
        setting->setObjectName("setting");
        setting->setGeometry(QRect(0, 0, 201, 61));
        sizePolicy.setHeightForWidth(setting->sizePolicy().hasHeightForWidth());
        setting->setSizePolicy(sizePolicy);
        setting->setStyleSheet(QString::fromUtf8(" text-align: left; \n"
"vertical-align: middle;"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/src/setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        setting->setIcon(icon7);
        setting->setIconSize(QSize(40, 40));
        help = new QPushButton(scrollAreaWidgetContents_3);
        help->setObjectName("help");
        help->setGeometry(QRect(0, 60, 201, 61));
        help->setStyleSheet(QString::fromUtf8(" text-align: left; \n"
"vertical-align: middle;"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/src/help.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        help->setIcon(icon8);
        help->setIconSize(QSize(40, 40));
        faq = new QPushButton(scrollAreaWidgetContents_3);
        faq->setObjectName("faq");
        faq->setGeometry(QRect(0, 120, 201, 61));
        faq->setStyleSheet(QString::fromUtf8(" text-align: left; \n"
"vertical-align: middle;"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/src/faq.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        faq->setIcon(icon9);
        faq->setIconSize(QSize(40, 40));
        scrollArea_3->setWidget(scrollAreaWidgetContents_3);
        stackedWidget_2->addWidget(page_5);
        page_9 = new QWidget();
        page_9->setObjectName("page_9");
        display_hide = new QPushButton(page_9);
        display_hide->setObjectName("display_hide");
        display_hide->setGeometry(QRect(0, 0, 201, 61));
        battle_test = new QPushButton(page_9);
        battle_test->setObjectName("battle_test");
        battle_test->setGeometry(QRect(0, 60, 201, 61));
        stackedWidget_2->addWidget(page_9);

        verticalLayout_5->addWidget(stackedWidget_2);


        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        sizePolicy2.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy2);
        stackedWidget->setMinimumSize(QSize(0, 0));
        page = new QWidget();
        page->setObjectName("page");
        pushButton = new QPushButton(page);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 0, 1001, 491));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/images/src/bz1.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon10);
        pushButton->setIconSize(QSize(2800, 4800));
        stackedWidget->addWidget(page);
        page_1 = new QWidget();
        page_1->setObjectName("page_1");
        set_green = new QPushButton(page_1);
        set_green->setObjectName("set_green");
        set_green->setGeometry(QRect(20, 20, 61, 31));
        set_white = new QPushButton(page_1);
        set_white->setObjectName("set_white");
        set_white->setGeometry(QRect(100, 20, 61, 31));
        set_yellow = new QPushButton(page_1);
        set_yellow->setObjectName("set_yellow");
        set_yellow->setGeometry(QRect(180, 20, 61, 31));
        set_pink = new QPushButton(page_1);
        set_pink->setObjectName("set_pink");
        set_pink->setGeometry(QRect(260, 20, 61, 31));
        set_blue = new QPushButton(page_1);
        set_blue->setObjectName("set_blue");
        set_blue->setGeometry(QRect(500, 20, 61, 31));
        set_black = new QPushButton(page_1);
        set_black->setObjectName("set_black");
        set_black->setGeometry(QRect(340, 20, 61, 31));
        set_purple = new QPushButton(page_1);
        set_purple->setObjectName("set_purple");
        set_purple->setGeometry(QRect(420, 20, 61, 31));
        set_red = new QPushButton(page_1);
        set_red->setObjectName("set_red");
        set_red->setGeometry(QRect(580, 20, 61, 31));
        stackedWidget->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        daily = new QGroupBox(page_2);
        daily->setObjectName("daily");
        daily->setGeometry(QRect(0, 0, 1001, 141));
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(daily->sizePolicy().hasHeightForWidth());
        daily->setSizePolicy(sizePolicy5);
        verticalLayout = new QVBoxLayout(daily);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        hekafei = new QCheckBox(daily);
        hekafei->setObjectName("hekafei");

        horizontalLayout_2->addWidget(hekafei);

        zhanbu = new QCheckBox(daily);
        zhanbu->setObjectName("zhanbu");

        horizontalLayout_2->addWidget(zhanbu);

        kaidian = new QCheckBox(daily);
        kaidian->setObjectName("kaidian");

        horizontalLayout_2->addWidget(kaidian);

        suibianguan = new QCheckBox(daily);
        suibianguan->setObjectName("suibianguan");

        horizontalLayout_2->addWidget(suibianguan);

        huoyuedujiangli = new QCheckBox(daily);
        huoyuedujiangli->setObjectName("huoyuedujiangli");

        horizontalLayout_2->addWidget(huoyuedujiangli);

        lidu = new QCheckBox(daily);
        lidu->setObjectName("lidu");

        horizontalLayout_2->addWidget(lidu);


        verticalLayout->addLayout(horizontalLayout_2);

        param = new QLineEdit(daily);
        param->setObjectName("param");

        verticalLayout->addWidget(param);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        progressBar = new QProgressBar(daily);
        progressBar->setObjectName("progressBar");
        progressBar->setBaseSize(QSize(0, 0));
        progressBar->setMinimum(0);
        progressBar->setValue(98);

        horizontalLayout_3->addWidget(progressBar);

        execute = new QPushButton(daily);
        execute->setObjectName("execute");
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/images/src/execute.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        execute->setIcon(icon11);
        execute->setIconSize(QSize(32, 32));

        horizontalLayout_3->addWidget(execute);


        verticalLayout->addLayout(horizontalLayout_3);

        groupBox = new QGroupBox(page_2);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 150, 1001, 341));
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(0, 20, 681, 301));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        cd_xc = new QCheckBox(gridLayoutWidget);
        cd_xc->setObjectName("cd_xc");
        cd_xc->setCheckable(false);

        gridLayout->addWidget(cd_xc, 2, 0, 1, 1);

        chudi_zyzzq = new QCheckBox(gridLayoutWidget);
        chudi_zyzzq->setObjectName("chudi_zyzzq");

        gridLayout->addWidget(chudi_zyzzq, 0, 0, 1, 1);

        cd_dc = new QCheckBox(gridLayoutWidget);
        cd_dc->setObjectName("cd_dc");
        cd_dc->setCheckable(false);

        gridLayout->addWidget(cd_dc, 1, 0, 1, 1);

        chudi_zgsqjz = new QCheckBox(gridLayoutWidget);
        chudi_zgsqjz->setObjectName("chudi_zgsqjz");

        gridLayout->addWidget(chudi_zgsqjz, 0, 1, 1, 1);

        cd_dl = new QCheckBox(gridLayoutWidget);
        cd_dl->setObjectName("cd_dl");
        cd_dl->setCheckable(false);

        gridLayout->addWidget(cd_dl, 3, 0, 1, 1);

        chudi_kyyjz = new QCheckBox(gridLayoutWidget);
        chudi_kyyjz->setObjectName("chudi_kyyjz");

        gridLayout->addWidget(chudi_kyyjz, 1, 1, 1, 1);

        chudi_cjgzx = new QCheckBox(gridLayoutWidget);
        chudi_cjgzx->setObjectName("chudi_cjgzx");

        gridLayout->addWidget(chudi_cjgzx, 3, 1, 1, 1);

        chudi_jjzq = new QCheckBox(gridLayoutWidget);
        chudi_jjzq->setObjectName("chudi_jjzq");

        gridLayout->addWidget(chudi_jjzq, 2, 1, 1, 1);

        cd_ccq = new QCheckBox(gridLayoutWidget);
        cd_ccq->setObjectName("cd_ccq");
        cd_ccq->setCheckable(false);

        gridLayout->addWidget(cd_ccq, 4, 0, 1, 1);

        chudi_qsgy = new QCheckBox(gridLayoutWidget);
        chudi_qsgy->setObjectName("chudi_qsgy");

        gridLayout->addWidget(chudi_qsgy, 0, 2, 1, 1);

        chudi_htkxz = new QCheckBox(gridLayoutWidget);
        chudi_htkxz->setObjectName("chudi_htkxz");

        gridLayout->addWidget(chudi_htkxz, 1, 2, 1, 1);

        execute2 = new QPushButton(groupBox);
        execute2->setObjectName("execute2");
        execute2->setGeometry(QRect(820, 290, 121, 38));
        execute2->setIcon(icon11);
        execute2->setIconSize(QSize(32, 32));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(820, 50, 161, 23));
        stackedWidget->addWidget(page_2);
        page_7 = new QWidget();
        page_7->setObjectName("page_7");
        plainTextEdit_help = new QPlainTextEdit(page_7);
        plainTextEdit_help->setObjectName("plainTextEdit_help");
        plainTextEdit_help->setGeometry(QRect(0, 0, 1001, 481));
        plainTextEdit_help->setStyleSheet(QString::fromUtf8("font-size: 20px;"));
        stackedWidget->addWidget(page_7);
        page_8 = new QWidget();
        page_8->setObjectName("page_8");
        stackedWidget->addWidget(page_8);

        verticalLayout_2->addWidget(stackedWidget);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        outInfo = new QPlainTextEdit(centralwidget);
        outInfo->setObjectName("outInfo");
        sizePolicy2.setHeightForWidth(outInfo->sizePolicy().hasHeightForWidth());
        outInfo->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(outInfo);

        outlog = new QPlainTextEdit(centralwidget);
        outlog->setObjectName("outlog");

        horizontalLayout_4->addWidget(outlog);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalLayout_2->setStretch(0, 2);
        verticalLayout_2->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(2, 2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1256, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget_2->setCurrentIndex(0);
        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\344\274\221\346\201\257\344\270\200\344\270\213", nullptr));
        start->setText(QString());
        operation->setText(QString());
        more->setText(QString());
#if QT_CONFIG(tooltip)
        test_btn->setToolTip(QCoreApplication::translate("MainWindow", "\346\265\213\350\257\225\345\212\237\350\203\275\347\224\250\347\232\204", nullptr));
#endif // QT_CONFIG(tooltip)
        test_btn->setText(QString());
        info_refresh->setText(QCoreApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226/\345\210\267\346\226\260", nullptr));
        info_quickstart->setText(QCoreApplication::translate("MainWindow", "\345\277\253\351\200\237\345\220\257\345\212\250", nullptr));
        rnc->setText(QCoreApplication::translate("MainWindow", "\346\227\245\345\270\270/\351\224\204\345\234\260", nullptr));
        setting->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        help->setText(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\346\226\207\346\241\243", nullptr));
        faq->setText(QCoreApplication::translate("MainWindow", "Faq", nullptr));
        display_hide->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272/\351\232\220\350\227\217", nullptr));
        battle_test->setText(QCoreApplication::translate("MainWindow", "\346\210\230\346\226\227-yyl", nullptr));
        pushButton->setText(QString());
        set_green->setText(QCoreApplication::translate("MainWindow", "\347\273\277\350\211\262", nullptr));
        set_white->setText(QCoreApplication::translate("MainWindow", "\347\231\275\350\211\262", nullptr));
        set_yellow->setText(QCoreApplication::translate("MainWindow", "\351\273\204\350\211\262", nullptr));
        set_pink->setText(QCoreApplication::translate("MainWindow", "\347\262\211\350\211\262", nullptr));
        set_blue->setText(QCoreApplication::translate("MainWindow", "\350\223\235\350\211\262", nullptr));
        set_black->setText(QCoreApplication::translate("MainWindow", "\351\273\221\344\270\235", nullptr));
        set_purple->setText(QCoreApplication::translate("MainWindow", "\347\264\253\350\211\262", nullptr));
        set_red->setText(QCoreApplication::translate("MainWindow", "\347\272\242\350\211\262", nullptr));
        daily->setTitle(QCoreApplication::translate("MainWindow", "\346\227\245\345\270\270", nullptr));
        hekafei->setText(QCoreApplication::translate("MainWindow", "\345\226\235\345\222\226\345\225\241", nullptr));
        zhanbu->setText(QCoreApplication::translate("MainWindow", "\345\215\240\345\215\234", nullptr));
        kaidian->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\272\227", nullptr));
        suibianguan->setText(QCoreApplication::translate("MainWindow", "\351\232\217\344\276\277\350\247\202", nullptr));
        huoyuedujiangli->setText(QCoreApplication::translate("MainWindow", "\346\264\273\350\267\203\345\245\226\345\212\261", nullptr));
        lidu->setText(QCoreApplication::translate("MainWindow", "\344\270\275\351\203\275\345\237\216\345\213\237", nullptr));
        param->setText(QCoreApplication::translate("MainWindow", "0x1,0x11,0x17", nullptr));
        execute->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\347\251\272\346\264\236\351\224\204\345\234\260", nullptr));
        cd_xc->setText(QCoreApplication::translate("MainWindow", "\342\200\224>\350\245\277\344\276\2472", nullptr));
        chudi_zyzzq->setText(QCoreApplication::translate("MainWindow", "\344\270\255\345\244\256\345\210\266\351\200\240\345\214\272", nullptr));
        cd_dc->setText(QCoreApplication::translate("MainWindow", "\342\200\224>\344\270\234\344\276\2474", nullptr));
        chudi_zgsqjz->setText(QCoreApplication::translate("MainWindow", "\350\201\214\345\267\245\347\244\276\345\214\2724", nullptr));
        cd_dl->setText(QCoreApplication::translate("MainWindow", "\342\200\224>\351\241\266\346\245\2741", nullptr));
        chudi_kyyjz->setText(QCoreApplication::translate("MainWindow", "\347\247\221\347\240\224\351\231\2425", nullptr));
        chudi_cjgzx->setText(QCoreApplication::translate("MainWindow", "\347\262\227\345\212\240\345\267\245\344\270\255\345\277\2033", nullptr));
        chudi_jjzq->setText(QCoreApplication::translate("MainWindow", "\346\227\247\345\273\272\347\255\221\347\276\2441", nullptr));
        cd_ccq->setText(QCoreApplication::translate("MainWindow", "\342\200\224>\345\202\250\345\255\230\345\214\2722", nullptr));
        chudi_qsgy->setText(QCoreApplication::translate("MainWindow", "\350\275\273\346\235\276\345\205\254\345\257\2231", nullptr));
        chudi_htkxz->setText(QCoreApplication::translate("MainWindow", "\350\210\252\345\244\251\347\247\221\345\255\246\347\253\2313", nullptr));
        execute2->setText(QString());
        plainTextEdit_help->setPlainText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
