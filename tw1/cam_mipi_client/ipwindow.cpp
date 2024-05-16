#include "ipwindow.h"
#include "ui_ipwindow.h"

#include "mainwindow.h"

#include <QMessageBox>
QString ip;
int port;
QTcpSocket *socket;

IPWindow::IPWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IPWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("WAIT FOR CONNECTION");
    ui->edt_ip->setText("172.16.10.253");
    ui->edt_port->setText("8080");
    socket = NULL;
}

IPWindow::~IPWindow()
{
    delete ui;
}

void IPWindow::on_btn_connect_clicked()
{
    socket = NULL;
    ip = ui->edt_ip->text();
    port = ui->edt_port->text().toInt();

    if (socket == NULL){
        socket = new QTcpSocket(this);
        connect(socket, SIGNAL(connected()), this, SLOT(net_connected()));
        socket->connectToHost(ip, port);
    }
}

void IPWindow::on_btn_cal_clicked()
{
    this->close();
}
void IPWindow::net_connected()
{
//    QMessageBox::information(this, "Title", "连接成功");
    //this->hide();
    ui->lab_View->setText("网络连接成功！");
    LconWindow *mwindow;
    mwindow = new LconWindow;

    this->close();
    mwindow->show();
}
