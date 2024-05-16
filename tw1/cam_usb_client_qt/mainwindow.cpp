#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
#include "ipwindow.h"
#include <QTcpSocket>
#include <QMutex>
#include <QTime>

LconWindow::LconWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LconWindow)
{
    pic_socket = NULL;
    pic_timer  = NULL;
    env_socket = NULL;
    env_timer = NULL;

    ui->setupUi(this);
    this->setWindowTitle("TW1_USB_CAM_CLIENT");

    ui->btn_Start->setEnabled(true);
    ui->btn_Stop->setEnabled(false);
    ui->btn_back->setEnabled(false);

    if (env_socket == NULL){
        env_socket = new QTcpSocket();
        connect(env_socket, SIGNAL(connected()), this, SLOT(net_env_connected()));
        connect(env_socket, SIGNAL(disconnected()), this, SLOT(net__env_disconnected()));
        connect(env_socket, SIGNAL(readyRead()), this, SLOT(net_recv_env()));
    }
    if (env_timer == NULL) {
        env_timer = new QTimer(this);
        connect(env_timer, SIGNAL(timeout()), this, SLOT(net_send_env()));
    }

    env_socket->connectToHost(ip, port);

}
LconWindow::~LconWindow()
{
    delete ui;
    py_process->close();
}
#define REQ_DATA_SIZE   32
#define HDR_DATA_SIZE   128

void LconWindow::net_connected()
{
    pic_timer->start(10);
    state = 0;
}
void LconWindow::net_disconnected()
{
    if (pic_timer->isActive()){
        pic_timer->stop();
    }
    pic_socket->close();
    ui->btn_Start->setEnabled(true);
    ui->btn_Stop->setEnabled(false);
}

void LconWindow::net_send_pic()
{
    int ret;
    char request[REQ_DATA_SIZE] = {0};
    if (state == 0) {
        memset(request, 0, sizeof(request));
        strcat(request, "PIC_SEND");
        ret = pic_socket->write(request, sizeof(request));
        if (ret != sizeof(request)) {
            qDebug() << "send request failed";
            pic_timer->stop();
            pic_socket->close();
            ui->btn_Start->setEnabled(true);
            ui->btn_Stop->setEnabled(false);
        }
        pic_socket->flush();
        state = 1;
    }
}

void LconWindow::net_recv_data()
{
    int ret;
    char response[HDR_DATA_SIZE] = {0};

    switch (state) {
    case 1:
        if (pic_socket->bytesAvailable() < sizeof(response))
            return;
        ret = pic_socket->read(response, sizeof(response));
        if (ret != sizeof(response)) {
            qDebug() << "recv response failed";
            goto err;
        }
        ret = sscanf(response, "%dlen", &piclen);
        if (ret != 1) {
            qDebug() << "response format error";
            goto err;
        }
        qDebug()<<"piclen"<<piclen;
        state = 2;
        if (pic_socket->bytesAvailable() >= piclen)
            goto readdat;
        break;
    case 2:
readdat:
        if (pic_socket->bytesAvailable() < piclen){
            qDebug()<<pic_socket->bytesAvailable();
            return;
        }
        if (piclen > 0) {
            unsigned int ret;
            memset(picbuf, 0, sizeof(picbuf));
            ret = pic_socket->read(picbuf, piclen);
            if (ret < piclen) {
                qDebug() << "recv pic failed";
                pic_timer->stop();
                pic_socket->close();
                state = 0;
            }
            QPixmap pixmap;
            pixmap.loadFromData((const uchar *)picbuf, piclen, "JPEG");
            ui->lab_pic->setPixmap(pixmap);
            state = 0;
        }
        state = 0;
        break;
    }
    return;
err:
    pic_timer->stop();
    pic_socket->close();
    state = 0;
    ui->btn_Start->setEnabled(true);
    ui->btn_Stop->setEnabled(false);
    return;
}

void LconWindow::on_btn_Start_clicked()
{
    ui->btn_Start->setEnabled(false);
    ui->btn_Stop->setEnabled(true);
    ui->btn_back->setEnabled(false);
    if(socket != NULL)
        socket->close();
    if (pic_socket == NULL){
        pic_socket = new QTcpSocket();
        connect(pic_socket, SIGNAL(connected()), this, SLOT(net_connected()));
        connect(pic_socket, SIGNAL(disconnected()), this, SLOT(net_disconnected()));
        connect(pic_socket, SIGNAL(readyRead()), this, SLOT(net_recv_data()));
    }
    if (pic_timer == NULL) {
        pic_timer = new QTimer(this);
        connect(pic_timer, SIGNAL(timeout()), this, SLOT(net_send_pic()));
    }
    pic_socket->connectToHost(ip, port);
    state = 0;

}

void LconWindow::net_env_connected()
{

    env_timer = new QTimer(this);
    connect(env_timer, SIGNAL(timeout()), this, SLOT(net_send_env()));
    env_timer->start(1000);
}
void LconWindow::net_env_disconnected()
{
    if(env_timer->isActive())
        env_timer->stop();
    env_socket->close();
    env_socket = NULL;
}

void LconWindow::net_send_env()
{
    char req_buf[] = "ENV_SEND";
    int ret = env_socket->write(req_buf, sizeof(req_buf));
    if (ret != sizeof(req_buf)){
        perror("ENV_SEND");
    }
    //    qDebug()<<"ret = "<< ret;
    env_socket->flush();
}

void LconWindow::net_recv_env()
{
    char buf[128];
    char string[6] = {0};
    env_socket->read(buf, sizeof(buf));

    sscanf(buf, "%did%dt%dh%dl%dx%dy%dz%dled%dfan%dbuzz%dsev", &id, &tmp, &hum, &light, &x, &y, &z, &led, &fan, &buzz, &sev_led);

    //    qDebug()<<"buf:"<<buf;
    /*实时刷新显示环境信息*/
    snprintf(string, sizeof(string), "%d", light);
    //ui->edt_light->setText(string);
}

void LconWindow::on_btn_light_clicked()
{
    static bool state1 = false;
    if (state1 == false){
        env_socket->write("LIGHT_ON", sizeof("LIGHT_ON"));
        state1 = true;
        ui->btn_light->setText("关灯");
    } else {
        env_socket->write("LIGHT_OFF", sizeof("LIGHT_OFF"));
        state1 = false;
        ui->btn_light->setText("开灯");
    }
}

void LconWindow::on_btn_fan_clicked()
{
    static bool state1 = false;
    if (state1 == false){
        env_socket->write("FAN_ON", sizeof("FAN_ON"));
        state1 = true;
        ui->btn_fan->setText("关灯");
    } else {
        env_socket->write("FAN_OFF", sizeof("FAN_OFF"));
        state1 = false;
        ui->btn_fan->setText("开灯");
    }
}

void LconWindow::on_btn_buzz_clicked()
{

}

void LconWindow::on_btn_shuma_clicked()
{

}

void LconWindow::on_btn_Stop_clicked()
{
    if (pic_timer->isActive()){
        pic_timer->stop();
    }
    pic_socket->close();
    ui->btn_Start->setEnabled(true);
    ui->btn_Stop->setEnabled(false);
    ui->btn_back->setEnabled(true);
    pic_socket = NULL;
}
void LconWindow::on_btn_back_clicked()
{
    IPWindow *ipwin;
    ipwin = new IPWindow;

    this->close();
    ipwin->show();
}
void LconWindow::on_btn_out_clicked()
{
    this->close();
}

void LconWindow::on_edt_light_textChanged(const QString &arg1)
{

}

void LconWindow::sleep(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < reachTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
