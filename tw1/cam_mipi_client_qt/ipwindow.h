#ifndef IPWINDOW_H
#define IPWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QTcpSocket>

extern QString ip;
extern int port;
extern QTcpSocket *socket;

namespace Ui {
    class IPWindow;
}

class IPWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit IPWindow(QWidget *parent = 0);
    ~IPWindow();

private slots:
    void on_btn_connect_clicked();

    void on_btn_cal_clicked();

    void net_connected();

private:
    Ui::IPWindow *ui;
};

#endif // IPWINDOW_H
