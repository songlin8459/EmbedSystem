#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include "cam.h"
#include "mutexs.h"
#include "convert.h"

#define REQBUFS_COUNT 4
#define FMT_NUM_PLANES 1
struct cam_buf
{
	void *start;
	size_t length;
};

struct v4l2_requestbuffers reqbufs;
struct cam_buf bufs[REQBUFS_COUNT];

int camera_init(char *devpath, unsigned int *width, unsigned int *height, unsigned int *size, unsigned int *isnv12)
{
	int i;
	int fd = -1;
	int ret;
	struct v4l2_buffer vbuf;
	struct v4l2_format format;
	struct v4l2_capability capability;
	struct v4l2_plane planes[FMT_NUM_PLANES];
	/*open 打开设备文件*/
	if ((fd = open(devpath, O_RDWR)) == -1)
	{
		perror("open:");
		return -1;
	}
	/*ioctl 查看支持的驱动*/
	ret = ioctl(fd, VIDIOC_QUERYCAP, &capability);
	if (ret == -1)
	{
		perror("camera->init");
		return -1;
	}
	/*判断设备是否支持视频采集*/
	if (!(capability.capabilities & V4L2_CAP_VIDEO_CAPTURE_MPLANE))
	{
		fprintf(stderr, "camera->init: device can not support V4L2_CAP_VIDEO_CAPTURE_MPLANE\n");
		close(fd);
		return -1;
	}
	/*判断设备是否支持视频流采集*/
	if (!(capability.capabilities & V4L2_CAP_STREAMING))
	{
		fprintf(stderr, "camera->init: device can not support V4L2_CAP_STREAMING\n");
		close(fd);
		return -1;
	}
	/*设置捕获的视频格式 MYJPEG/nv12*/
	memset(&format, 0, sizeof(format));
	format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	format.fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;
	format.fmt.pix.width = *width;
	format.fmt.pix.height = *height;
	format.fmt.pix.field = V4L2_FIELD_ANY;
	ret = ioctl(fd, VIDIOC_S_FMT, &format);
	if (ret == -1)
	{
		perror("camera init");
		return -1;
	}
	else
	{
		*isnv12 = 1;
		fprintf(stdout, "camera->init: picture format is nv12\n");
		goto get_fmt;
	}

get_fmt:
	ret = ioctl(fd, VIDIOC_G_FMT, &format);
	if (ret == -1)
	{
		printf("3\n");
		perror("camera init");
		return -1;
	}
	/*向驱动申请缓存*/
	memset(&reqbufs, 0, sizeof(struct v4l2_requestbuffers));
	reqbufs.count = REQBUFS_COUNT; // 缓存区个数
	reqbufs.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	reqbufs.memory = V4L2_MEMORY_MMAP; // 设置操作申请缓存的方式:映射 MMAP
	ret = ioctl(fd, VIDIOC_REQBUFS, &reqbufs);
	if (ret == -1)
	{
		printf("4\n");
		perror("camera init");
		close(fd);
		return -1;
	}
	/*循环映射并入队*/
	for (i = 0; i < reqbufs.count; i++)
	{
		/*真正获取缓存的地址大小*/
		memset(&vbuf, 0, sizeof(struct v4l2_buffer));
		memset(&planes, 0, sizeof(planes));
		vbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
		vbuf.memory = V4L2_MEMORY_MMAP;
		vbuf.index = i;
		
		if(vbuf.type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		{
			vbuf.m.planes = planes;
			vbuf.length =FMT_NUM_PLANES;
		}
		ret = ioctl(fd, VIDIOC_QUERYBUF, &vbuf);
		if (ret == -1)
		{
			printf("5\n");
			perror("camera init");
			close(fd);
			return -1;
		}
		/*映射缓存到用户空间,通过mmap讲内核的缓存地址映射到用户空间,并切和文件描述符fd相关联*/
		if (V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE == vbuf.type) {
		bufs[i].length = vbuf.m.planes[0].length;
		bufs[i].start = 
			mmap(NULL, 
				vbuf.m.planes[0].length,
				PROT_READ | PROT_WRITE, 
				MAP_SHARED, 
				fd, 
				vbuf.m.planes[0].m.mem_offset);
		}
		if (bufs[i].start == MAP_FAILED)
		{
			printf("6\n");
			perror("camera init");
			close(fd);
			return -1;
		}
		/*每次映射都会入队,放入缓冲队列*/
		vbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
		vbuf.memory = V4L2_MEMORY_MMAP;
		ret = ioctl(fd, VIDIOC_QBUF, &vbuf);
		if (ret == -1)
		{
			printf("7\n");
			perror("camera init");
			close(fd);
			return -1;
		}
	}
	/*返回真正设置成功的宽.高.大小*/
	*width = format.fmt.pix.width;
	*height = format.fmt.pix.height;
	*size = bufs[0].length;
	printf("bufs[0].length:%d\n", bufs[0].length);

	return fd;
}

int camera_start(int fd)
{
	int ret;

	enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	/*ioctl控制摄像头开始采集*/
	ret = ioctl(fd, VIDIOC_STREAMON, &type);
	if (ret == -1)
	{
		perror("camera->start");
		return -1;
	}
	fprintf(stdout, "camera->start: start capture\n");

	return 0;
}

int camera_dqbuf(int fd, void **buf, unsigned int *size, unsigned int *index)
{
	int ret;
	fd_set fds;
	struct timeval timeout;
	struct v4l2_buffer vbuf;
	struct v4l2_plane planes[FMT_NUM_PLANES];
	while (1)
	{
		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		timeout.tv_sec = 2;
		timeout.tv_usec = 0;
		ret = select(fd + 1, &fds, NULL, NULL, &timeout); // 使用select机制,保证fd有图片的时候才能出对
		if (ret == -1)
		{
			printf("d1\n");
			perror("camera->dbytesusedqbuf");
			if (errno == EINTR)
				continue;
			else
				return -1;
		}
		else if (ret == 0)
		{
			printf("d2\n");
			fprintf(stderr, "camera->dqbuf: dequeue buffer timeout\n");
			return -1;
		}
		else
		{
			vbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
			vbuf.memory = V4L2_MEMORY_MMAP;
        	vbuf.m.planes = planes;
			vbuf.length = FMT_NUM_PLANES;
			ret = ioctl(fd, VIDIOC_DQBUF, &vbuf); // 出队,也就是从用户空间取出图片
			if (ret == -1)
			{
				perror("camera->dqbuf");
				return -1;
			}
			for(int i = 0; i < 50; i++)
			{
				printf("%d/", (char)buf[i]);
			}
			printf("\n");
			*buf = bufs[vbuf.index].start;

			for(int i = 0; i < 50; i++)
			{
				printf("%d/", *(char *)(bufs[vbuf.index].start));
				printf("%d/", (char)buf[i]);
			}
			printf("\n");
			*size = vbuf.bytesused;
			printf("vbuf.bytesused = %d\n", vbuf.bytesused);
			*index = vbuf.index;

			return 0;
		}
	}
}

int camera_eqbuf(int fd, unsigned int index)
{
	int ret;
	struct v4l2_buffer vbuf;
	struct v4l2_plane planes[FMT_NUM_PLANES];
	vbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	vbuf.memory = V4L2_MEMORY_MMAP;
	vbuf.index = index;
	vbuf.m.planes = planes;
    vbuf.length = FMT_NUM_PLANES;
	ret = ioctl(fd, VIDIOC_QBUF, &vbuf); // 入队
	if (ret == -1)
	{
		perror("camera->eqbuf");
		return -1;
	}

	return 0;
}

int camera_stop(int fd)
{
	int ret;
	enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;

	ret = ioctl(fd, VIDIOC_STREAMOFF, &type);
	if (ret == -1)
	{
		perror("camera->stop");
		return -1;
	}
	fprintf(stdout, "camera->stop: stop capture\n");

	return 0;
}

int camera_exit(int fd)
{
	int i;
	int ret;
	struct v4l2_buffer vbuf;
	struct v4l2_plane planes[FMT_NUM_PLANES];
	vbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	vbuf.memory = V4L2_MEMORY_MMAP;
	if (V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE == vbuf.type) {
            vbuf.m.planes = planes;
            vbuf.length = FMT_NUM_PLANES;
        }
	for (i = 0; i < reqbufs.count; i++)
	{
		ret = ioctl(fd, VIDIOC_DQBUF, &vbuf);
		if (ret == -1)
			break;
	}
	for (i = 0; i < reqbufs.count; i++)
		munmap(bufs[i].start, bufs[i].length);
	fprintf(stdout, "camera->exit: camera exit\n");
	return close(fd);
}

int camera_on()
{
	int i;
	int fd = -1;
	
	int ret;
	char devpath[32] = {0};
	unsigned int width;
	unsigned int height;
	unsigned int size;
	unsigned int index;
	unsigned int isnv12;
	char *yuv;
	char *rgb;

	width = W;
	height = H;
	int number = 22;
	// while(fd < 0 && number < 50)
	{
		sprintf(devpath,"%s%d", CAMERA_USB, number);
		
		fd = camera_init(devpath, &width, &height, &size, &isnv12);
		number++;
	}
	printf("%s\n", devpath);
	ret = camera_start(fd);
	if (ret == -1)
		return -1;
	jpg = malloc(sizeof(struct jpg_buf_t));
	if (!jpg)
	{
		perror("malloc");
		return -1;
	}
	if (isnv12 != 0)
	{
		printf("------nv12------\n");
		rgb = malloc(width * height * 3);
		convert_rgb_to_jpg_init();
	}
	// 采集几张图片丢弃
	for (i = 0; i < 8; i++)
	{
		ret = camera_dqbuf(fd, (void **)&yuv, &size, &index);
		printf("size = %d index = %d\n", size, index);
		if (ret == -1)
		{
			exit(EXIT_FAILURE);
		}
			

		ret = camera_eqbuf(fd, index);
		if (ret == -1)
			exit(EXIT_FAILURE);
	}

	fprintf(stdout, "init camera success\n");
	/* 循环采集图片 */
	while (1)
	{
		ret = camera_dqbuf(fd, (void **)&yuv, &size, &index);
		
		if (ret == -1)
			return -1;
		if (isnv12 != 0)
		{
			pthread_mutex_lock(&cam_mutex);
			memcpy(jpg->jpg_buf, yuv, size);
			jpg->jpg_size = size;
			pthread_mutex_unlock(&cam_mutex);
		}
		else
		{
			printf("m0\n");
			convert_yuv_to_rgb(yuv, rgb, width, height, 24);
			printf("m1\n");
			pthread_mutex_lock(&cam_mutex);
			memset(jpg, 0, sizeof(jpg));
			printf("m2\n");
			jpg->jpg_size = convert_rgb_to_jpg_work(rgb, jpg->jpg_buf, width, height, 24, 80);
			pthread_mutex_unlock(&cam_mutex);
		}
#if 1
		int fd1 = open("1.jpg", O_RDWR | O_CREAT, 0777);
		int count = 0;
		while (count < jpg->jpg_size)
		{
			int ret = write(fd1, jpg->jpg_buf + count, jpg->jpg_size - count);
			if (ret < jpg->jpg_size)
			{
				printf("-----数据太少-----\n");
			}
			count += ret;
		}
		printf("count = %d\n", count);
		close(fd1);
#endif
		ret = camera_eqbuf(fd, index);
		if (ret == -1)
			return -1;
	}
	/* 代码不应该运行到这里 */
	if (!isnv12)
	{
		convert_rgb_to_jpg_exit();
		free(rgb);
	}
	free(jpg);

	ret = camera_stop(fd);
	if (ret == -1)
		return -1;

	ret = camera_exit(fd);
	if (ret == -1)
		return -1;
}
