#include "mainwindow.h"
#include "config.h"
#include <QApplication>
#include <QProcess>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(argv);
    // 获取主屏幕
    QScreen *screen = QGuiApplication::primaryScreen();
    // 获取主屏幕的分辨率
    QRect screenGeometry = screen->geometry();
    // 计算窗口的起始位置
    int startX = screenGeometry.width() / 2 - w.width() / 2;
    int startY = screenGeometry.height() / 2 - w.height() / 2;
    // 移动窗口到屏幕的中央
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
