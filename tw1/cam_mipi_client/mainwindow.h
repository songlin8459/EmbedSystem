#ifndef LCONWINDOW_H
#define LCONWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>

#include "mythread.h"

namespace Ui {
    class LconWindow;
}

class LconWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LconWindow(QWidget *parent = 0);
    ~LconWindow();

private slots:
    void on_btn_Start_clicked();

    void on_btn_Stop_clicked();

    void on_btn_back_clicked();

    void on_btn_out_clicked();

    void net_connected();
    void net_recv_data();
    void net_disconnected();
    void net_send_pic();

    void net_env_connected();
    void net_recv_env();
    void net_env_disconnected();
    void net_send_env();

    void on_btn_light_clicked();

    void on_btn_fan_clicked();

    void on_btn_buzz_clicked();

    void on_btn_shuma_clicked();

    void on_edt_light_textChanged(const QString &arg1);

    void sleep(unsigned int msec);


private:
    Ui::LconWindow *ui;
    QTcpSocket *pic_socket, *env_socket;
    QTimer *pic_timer, *env_timer;
    unsigned int state;
    unsigned int piclen;
    char picbuf[1024 * 1024];
    int id, tmp, hum, light, x, y, z, led, fan, buzz, sev_led;
    QProcess *py_process;
    QString argument;


};

#endif // LCONWINDOW_H
