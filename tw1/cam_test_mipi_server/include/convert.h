#ifndef __CONVERT_H__
#define __CONVERT_H__

void convert_yuv_to_rgb(void *yuv, void *rgb, unsigned int width, unsigned int height, unsigned int bps);
void convert_rgb_to_jpg_init(void);
int convert_rgb_to_jpg_work(void *rgb, void *jpeg, unsigned int width, unsigned int height, unsigned int bpp, int quality);
void convert_rgb_to_jpg_exit(void);
int convert_nv12_to_rgb(unsigned char* pYuvBuf, unsigned char* pRgbBuf, int height, int width);

#endif



