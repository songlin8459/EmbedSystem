#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QProcess>

class MyThread : public QThread
{
public:

    explicit MyThread(QObject *parent = nullptr);

    void run();
private:
    QProcess *py_process;
    QString argument;
};

#endif // MYTHREAD_H
