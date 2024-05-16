#ifndef __CAM_MIPI_H__
#define __CAM_MIPI_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <asm/types.h>
#include <linux/videodev2.h>
#include <linux/v4l2-subdev.h>

struct v4l2_dev
{
    int fd;
    int sub_fd;
    const char *path;
    const char *name;
    const char *subdev_path;
    const char *out_type;
    enum v4l2_buf_type buf_type;
    int format;
    int width;
    int height;
    unsigned int req_count;
    enum v4l2_memory memory_type;
    struct buffer *buffers;
    unsigned long int timestamp;
    int data_len;
    unsigned char *out_data;
};

void close_device(struct v4l2_dev *dev);

void exit_failure(struct v4l2_dev *dev);

void open_device(struct v4l2_dev *dev);

void get_capabilities(struct v4l2_dev *dev);

void set_fmt(struct v4l2_dev *dev);

void require_buf(struct v4l2_dev *dev);

void alloc_buf(struct v4l2_dev *dev);

void queue_buf(struct v4l2_dev *dev);

void stream_on(struct v4l2_dev *dev);

void get_frame(struct v4l2_dev *dev, int skip_frame);

void save_picture(const char *filename, unsigned char *file_data, unsigned int len, int is_overwrite);

void stream_off(struct v4l2_dev *dev);

void set_fps(struct v4l2_dev *dev, unsigned int fps);

int cam_mipi_on();



#endif