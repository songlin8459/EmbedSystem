#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc/types_c.h>

#define USB_CAM_INDEX 31
#define MIPI_CAM_INDEX 22

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pb_exit_clicked();
    void video_show(); //画面显示
    void on_cb_cam_sel_currentIndexChanged(const int &arg1);
    void on_pb_flush_net_clicked();

    void on_pb_green_clicked();

    void on_pb_red_clicked();

private:
    Ui::Widget *ui;
    cv::VideoCapture *cap_usb;//usb画面展示载体
    cv::VideoCapture *cap_mipi;//mipi画面展示载体
    int cam_index = MIPI_CAM_INDEX; //摄像头序号
    bool open_flag = false; // 摄像头打开标志
    void botton_init(); //按键初始化
    void show_interface_ips(); // 显示本机网络ip
    void On_BtnGetHostInfo();
    void led_init();

};
#endif // WIDGET_H
