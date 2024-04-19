#include "mainwindow.h"
#include "config.h"
#include <QApplication>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
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
