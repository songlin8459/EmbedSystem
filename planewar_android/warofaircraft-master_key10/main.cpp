#include "mainwindow.h"
#include "config.h"
#include <QApplication>
#include <QProcess>
#include <QScreen>
#include <QDebug>
#include <QtAndroidExtras/QtAndroid>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w(argv);
    // 窗口的起始位置
    int startX = 0;
    int startY = 0;
    w.move(startX, startY);
    w.show();

    // 重启(实现返回主菜单的功能)
    int ret = a.exec();
    if (ret == RESTART_CODE)
    {
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
        return 0;
    }

    return ret;
}
