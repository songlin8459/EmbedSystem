#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // 读取YUV文件
    std::string input_file = "rkisp_v6.nv12";
    int width = 640; // 图像宽度
    int height = 480; // 图像高度
    cv::Mat yuv_image(height * 3 / 2, width, CV_8UC1);
    FILE *file = fopen(input_file.c_str(), "rb");
    fread(yuv_image.data, 1, yuv_image.total(), file);
    fclose(file);

    // 将YUV图像转换为BGR图像
    cv::Mat bgr_image(height, width, CV_8UC3);
    cv::cvtColor(yuv_image, bgr_image, cv::COLOR_YUV2BGR_I420);
    cv::cvtColor(bgr_image, bgr_image, cv::COLOR_BGR2RGB);

    // 保存为JPG文件
    std::string output_file = "rkisp_v6.jpg";
    cv::imwrite(output_file, bgr_image);

    std::cout << "转换完成，已保存为 " << output_file << std::endl;
    return 0;
}

