#include "widget.h"
#include "ui_widget.h"
#include <opencv4/opencv2/opencv.hpp>
#include <QTimer>
#include <QDebug>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QStringList>
#include <QList>
#include <QNetworkAddressEntry>
#include <QFileInfo>
#include <QFile>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //启动计时器
    QTimer *timer = new QTimer(this);
    timer->start(1000/30);
    cap_usb = new cv::VideoCapture;
    cap_mipi = new cv::VideoCapture;
    cap_usb->open(USB_CAM_INDEX);

    if(!cap_usb->isOpened()){
        qDebug() << "Failed to open USB_CAM";
    }
    cap_mipi->open(MIPI_CAM_INDEX);
    if(!cap_mipi->isOpened()){
        qDebug() << "Failed to open MIPI_CAM";
    }
    //按钮初始化
    botton_init();

    // gpio初始化
    //led_init();

    //时间到后启动cam_open时间
    connect(timer, SIGNAL(timeout()), this, SLOT(video_show()));

}

Widget::~Widget()
{
    system("/usr/share/TW1_CamNetGpio_Desk_V1/gpio_ctl 15 0");
    system("/usr/share/TW1_CamNetGpio_Desk_V1/gpio_ctl 16 0");
    delete cap_mipi;
    delete cap_usb;
    delete ui;
}

void Widget::botton_init()
{
    ui->pb_open->setEnabled(false);
    ui->pb_close->setEnabled(false);
    ui->le_eth0->setReadOnly(true);
    ui->le_eth1->setReadOnly(true);
}
//在lable上显示
void Widget::video_show()
{
    ui->lb_show->clear();
    //读取图片
    cv::Mat frame, srcmat2;
    switch (cam_index) {
    case USB_CAM_INDEX:
        cap_usb->read(frame);
        break;
    case MIPI_CAM_INDEX:
        cap_mipi->read(frame);
        break;
    default:
        break;
    }
    cv::cvtColor(frame, srcmat2, CV_BGR2RGB);
    QImage img_2 = QImage((const unsigned char *)srcmat2.data, srcmat2.cols, srcmat2.rows, srcmat2.step, QImage::Format_RGB888);
    int a2 = ui->lb_show->width();
    int b2 = ui->lb_show->height();
    QImage imgg = img_2.scaled(a2, b2);
    ui->lb_show->setPixmap(QPixmap::fromImage(imgg));
    ui->lb_show->show();
}

void Widget::on_pb_exit_clicked()
{
    this->close();
}

void Widget::on_cb_cam_sel_currentIndexChanged(const int &arg1)
{
    switch (arg1) {
    case 0:
        cam_index = MIPI_CAM_INDEX;
        break;
    case 1:
        cam_index = USB_CAM_INDEX;
        break;
    default:
        break;
    }
}

void Widget::show_interface_ips() 
{
    // 获取所有网络接口
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    // 遍历每个接口
    for (const QNetworkInterface &interface : interfaces) {

        //qDebug() << "Device:" << interface.name();
        if(interface.name() == "eth0")
        {
            // 遍历每个IP地址
            for (const QHostAddress &address : interface.allAddresses()) {
                // 显示IPv4地址
                if (address.protocol() == QAbstractSocket::IPv4Protocol) {
                    qDebug() << "IPv4 address:" << address.toString();
                    if(address.toString() != "127.0.0.1") {
                        ui->le_eth0->setText(address.toString());
                    }
                }
            }
        }
        if(interface.name() == "eth1") {
            for (const QHostAddress &address : interface.allAddresses()) {
                if (address.protocol() == QAbstractSocket::IPv4Protocol) {
                    qDebug() << "IPv4 address:" << address.toString();
                    if(address.toString() != "127.0.0.1") {
                        ui->le_eth1->setText(address.toString());
                    }
                }
            }
        }
    }
}
void Widget::On_BtnGetHostInfo()
{
    ui->le_eth0->setText("null");
    ui->le_eth1->setText("null");

    QList<QNetworkInterface>list = QNetworkInterface::allInterfaces();//获取所有网络接口的列表
    foreach(QNetworkInterface interface,list)//遍历每个网络接口
    {
        //qDebug() << "Device:" << interface.name();//设备名
        //qDebug() << "HardwareAddress:" << interface.hardwareAddress();//硬件地址
        if(interface.name() == "eth0")
        {
            //获取IP地址条目列表，每个条目中包含一个IP地址，一个子网掩码和一个广播地址
            QList<QNetworkAddressEntry> entryList = interface.addressEntries();

            foreach(QNetworkAddressEntry entry,entryList)//遍历每一个IP地址条目
            {
                if(!entry.ip().toString().isEmpty())
                {
                    if(!entry.ip().toString().at(0).isLetter())
                        ui->le_eth0->setText(entry.ip().toString());
                }

//                qDebug() << tr("-------------------------------------------------------");
//                qDebug() << "IP Address:" << entry.ip().toString();              //IP地址
//                qDebug() << "Netmask:" << entry.netmask().toString();            //子网掩码
//                qDebug() << "Broadcast:" << entry.broadcast().toString();        //广播地址
//                qDebug() << tr("-------------------------------------------------------");
            }

        }
        if(interface.name() == "eth1")
        {
            //获取IP地址条目列表，每个条目中包含一个IP地址，一个子网掩码和一个广播地址
            QList<QNetworkAddressEntry> entryList = interface.addressEntries();

            foreach(QNetworkAddressEntry entry,entryList)//遍历每一个IP地址条目
            {
                if(!entry.ip().toString().isEmpty())
                {
                    if(!entry.ip().toString().at(0).isLetter())
                        ui->le_eth1->setText(entry.ip().toString());
                }

//                qDebug() << tr("-------------------------------------------------------");
//                qDebug() << "IP Address:" << entry.ip().toString();              //IP地址
//                qDebug() << "Netmask:" << entry.netmask().toString();            //子网掩码
//                qDebug() << "Broadcast:" << entry.broadcast().toString();        //广播地址
//                qDebug() << tr("-------------------------------------------------------");
            }

        }
    }
}

void Widget::led_init()
{
    QFileInfo fi_15("sys/class/gpio/gpio15");
    if(!fi_15.isDir())
    {
        system("sudo echo 15 > /sys/class/gpio/export");
    }
    else
    {
        system("sudo echo out > /sys/class/gpio15/direction");
    }
    QFileInfo fi_16("sys/class/gpio/gpio16");
    if(!fi_16.isDir())
    {
        system("sudo echo 16 > /sys/class/gpio/export");
    }
    else
    {
        system("sudo echo out > /sys/class/gpio16/direction");
    }
}


void Widget::on_pb_flush_net_clicked()
{
    //show_interface_ips();
    On_BtnGetHostInfo();
}

void Widget::on_pb_green_clicked()
{
    if(ui->pb_green->text() == "开灯"){
        ui->pb_green->setText("关灯");
        system("/usr/share/TW1_CamNetGpio_Desk_V1/gpio_ctl 15 1");
        return;
    }
    if(ui->pb_green->text() == "关灯"){
        ui->pb_green->setText("开灯");
        system("/usr/share/TW1_CamNetGpio_Desk_V1/gpio_ctl 15 0");
        return;
    }
}

void Widget::on_pb_red_clicked()
{
    if(ui->pb_red->text() == "开灯"){
        ui->pb_red->setText("关灯");
        system("/usr/share/TW1_CamNetGpio_Desk_V1/gpio_ctl 16 1");
        return;
    }
    if(ui->pb_red->text() == "关灯"){
        ui->pb_red->setText("开灯");
        system("/usr/share/TW1_CamNetGpio_Desk_V1/gpio_ctl 16 0");
        return;
    }
}
