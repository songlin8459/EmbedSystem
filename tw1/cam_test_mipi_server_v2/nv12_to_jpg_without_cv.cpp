#include <iostream>
#include <opencv2/opencv.hpp>


int yuv2rgb_nv12_without_cv2(unsigned char* pYuvBuf, unsigned char* pRgbBuf, int height, int width)
{
    if(width < 1 || height < 1 || pYuvBuf == NULL || pRgbBuf == NULL)
    {
        return 0;
    }

    const long len = height * width;

    // Y与UV数据地址
    unsigned char *yData = pYuvBuf;
    unsigned char *uvData = yData + len;

    // R、G、B数据地址
    unsigned char *rData = pRgbBuf;
    unsigned char *gData = rData + len;
    unsigned char *bData = gData + len;

    int R[4], G[4], B[4];
    int Y[4], U, V;
    int y0_Idx, y1_Idx, uIdx, vIdx;

    for (int i = 0; i < height; i=i+2)
    {
        for (int j = 0; j < width; j=j+2)
        {
            y0_Idx = i * width + j;
            y1_Idx = (i + 1) * width + j;

            // Y[0]、Y[1]、Y[2]、Y[3]分别代表 Y00、Y01、Y10、Y11
            Y[0] = yData[y0_Idx];
            Y[1] = yData[y0_Idx + 1];
            Y[2] = yData[y1_Idx];
            Y[3] = yData[y1_Idx + 1];

            uIdx = (i / 2) * width + j;
            vIdx = uIdx + 1;

            U = uvData[uIdx];
            V = uvData[vIdx];

            R[0] = Y[0] + 1.402 * (V - 128);
            G[0] = Y[0] - 0.34414 * (U - 128) + 0.71414 * (V - 128);
            B[0] = Y[0] + 1.772 * (U - 128);

            R[1] = Y[1] + 1.402 * (V - 128);
            G[1] = Y[1] - 0.34414 * (U - 128) + 0.71414 * (V - 128);
            B[1] = Y[1] + 1.772 * (U - 128);

            R[2] = Y[2] + 1.402 * (V - 128);
            G[2] = Y[2] - 0.34414 * (U - 128) + 0.71414 * (V - 128);
            B[2] = Y[2] + 1.772 * (U - 128);

            R[3] = Y[3] + 1.402 * (V - 128);
            G[3] = Y[3] - 0.34414 * (U - 128) + 0.71414 * (V - 128);
            B[3] = Y[3] + 1.772 * (U - 128);

            // 像素值限定在 0-255
            for (int k = 0; k < 4; ++k){
                if(R[k] >= 0 && R[k] <= 255){
                    R[k] = R[k];
                }
                else{
                    R[k] = (R[k] < 0) ? 0 : 255;
                }

                if(G[k] >= 0 && G[k] <= 255){
                    G[k] = G[k];
                }
                else{
                    G[k] = (G[k] < 0) ? 0 : 255;
                }

                if(B[k] >= 0 && B[k] <= 255){
                    B[k] = B[k];
                }
                else{
                    B[k] = (B[k] < 0) ? 0 : 255;
                }
            }

            *(rData + y0_Idx) = R[0];
            *(gData + y0_Idx) = G[0];
            *(bData + y0_Idx) = B[0];

            *(rData + y0_Idx + 1) = R[1];
            *(gData + y0_Idx + 1) = G[1];
            *(bData + y0_Idx + 1) = B[1];

            *(rData + y1_Idx) = R[2];
            *(gData + y1_Idx) = G[2];
            *(bData + y1_Idx) = B[2];

            *(rData + y1_Idx + 1) = R[3];
            *(gData + y1_Idx + 1) = G[3];
            *(bData + y1_Idx + 1) = B[3];
        }
    }
    return 1;
}

int main() {
    // 读取YUV文件
    unsigned char *pYuvBuf = nullptr, *pRgbBuf = nullptr;
    std::string input_file = "rkisp_v6.nv12";
    int width = 640; // 图像宽度
    int height = 480; // 图像高度
    //cv::Mat yuv_image(height * 3 / 2, width, CV_8UC1);
    FILE *file = fopen(input_file.c_str(), "rb");
    fread(pYuvBuf, 1, width*height*3/2, file);
    fclose(file);


    int ret = yuv2rgb_nv12_without_cv2(pYuvBuf, pRgbBuf, height, width);
    std::cout << "pYuvBuf.size=" << pYuvBuf.length() <<" ret=" << ret << std::endl;

    // 将YUV图像转换为BGR图像
    cv::Mat bgr_image(height, width, CV_8UC3, pRgbBuf);
    // cv::cvtColor(yuv_image, bgr_image, cv::COLOR_YUV2BGR_I420);
    // cv::cvtColor(bgr_image, bgr_image, cv::COLOR_BGR2RGB);

    // 保存为JPG文件
    std::string output_file = "rkisp_v7.jpg";
    cv::imwrite(output_file, bgr_image);

    std::cout << "转换完成，已保存为 " << output_file << std::endl;
    return 0;
}

