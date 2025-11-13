#ifndef UIMANAGE_H
#define UIMANAGE_H

#include <QString>

const char* color_lightGreen=R"(QMainWindow {background-color:  #C7EDCC;})";
const char* color_lightWhite=R"(QMainWindow {background-color:  #F5F5F5;})";
const char* color_lightYellow=R"(QMainWindow {background-color:  #FFDEAD;})";
const char* color_lightPink=R"(QMainWindow {background-color:  #FFC0CB;})";
const char* color_lightBlack=R"(QMainWindow {background-color: #262626;}
    #set_black{color: #FFFFFF;})";
const char* color_lightPurple=R"(QMainWindow {background-color: #6A5ACD;})";
const char* color_lightBlue=R"(QMainWindow {background-color: #6495ED;})";
const char* color_red=R"(QMainWindow {background-color: #A52A2A;})";

const char* color_btn1_def=R"(QPushButton{background-color: #F0F0F0})";
const char* color_btn1_sel=R"(QPushButton{background-color: #FFD700})";

const char* help_file=u8R"(1.游戏图像设置为1920*1080窗口(不是全屏)
2.游戏窗口移动了，必须进行刷新
3.快速启动：启动zzz程序(如果zzz在运行了就没必要点了，点了也不碍事)
4.日常，需要在N键中显示相对地图才能正常使用，基于2.0地图
5.锄地-配队>音雅柳：手动进入航天城的某地图，进行耀佳音/星见雅/月城柳的配队，当前角色为耀佳音，即可
6.按F11可以暂停/恢复所有有关战斗的线程，比如想手动打怪
7.按小键盘.可以暂停所有任务
支持100%，125%，150%的屏幕缩放)";
#endif // UIMANAGE_H
