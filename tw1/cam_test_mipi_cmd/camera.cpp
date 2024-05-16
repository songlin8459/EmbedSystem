#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // 打开摄像头
    cv::VideoCapture cap(22); // 0表示默认摄像头，如果有多个摄像头，可以更改参数
    if (!cap.isOpened()) {
        std::cerr << "无法打开摄像头" << std::endl;
        return -1;
    }

    // 创建窗口用于显示视频流
    cv::namedWindow("摄像头", cv::WINDOW_AUTOSIZE);

    // 循环捕获和显示视频帧
    cv::Mat frame;
    while (true) {
        // 从摄像头捕获一帧图像
        cap >> frame;

        // 如果捕获失败，跳出循环
        if (frame.empty()) {
            std::cerr << "捕获失败" << std::endl;
            break;
        }

        // 在窗口中显示图像
        cv::imshow("摄像头", frame);

        // 按下ESC键退出循环
        if (cv::waitKey(30) == 27) {
            break;
        }
    }

    // 释放资源并关闭窗口
    cap.release();
    cv::destroyAllWindows();

    return 0;
}

