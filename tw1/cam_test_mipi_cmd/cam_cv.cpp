#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    std::cout << cv::getBuildInformation() << std::endl;
    cv::VideoCapture cap;
    cap.open("v4l2src device=/dev/video22 ! video/x-raw, format=NV12, width=640, height=480, framerate=30/1 ! videoconvert ! appsink",cv::CAP_GSTREAMER);
    cv::Mat frame;
    int number = 0;
    
    while(cap.read(frame))
    {

        std::cout << "picture stream" << number << std::endl;
        number++;
        //处理图像
    }
    cap.release();

}