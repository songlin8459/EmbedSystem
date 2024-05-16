#include "ipwindow.h"
#include "mythread.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IPWindow w;
    w.show();
    //MyThread th;
    //th.start();

    return a.exec();
}
