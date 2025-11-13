#ifndef CONNECTUI_H
#define CONNECTUI_H
#include <QObject.h>
#include <Windows.h>
class ConnectUi : public  QObject{
    Q_OBJECT
signals:

    void updateProgress(int progress);
    void update_outInfo(QString qs);
    void update_outLog(QString qs);
};
#endif // CONNECTUI_H
