#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "gpio_ctl.h"

static char gpio_path[100];
static int gpio_config(const char attr[32], const char val[32])
{
	 char file_path[200];
	 int len = 0;
	 int fd = -1;
	 snprintf(file_path, sizeof(file_path), "%s/%s", gpio_path, attr);
	 if (0 > (fd = open(file_path, O_WRONLY))) {
		 perror("open error");
		 return fd;
	 }
	 len = strlen(val);
	 if (len != write(fd, val, len)) {
		 perror("write error");
		 close(fd);
		 return -1;
	 }
	 close(fd); //关闭文件
	 return 0;
}
int gpio_ctl(char gpio_num[16], char value[16])
{
	int fd, len = 1;

	 /* 判断指定编号的 GPIO 是否导出 */
	 sprintf(gpio_path, "/sys/class/gpio/gpio%s", gpio_num);
	 
	 if (access(gpio_path, F_OK)) {//如果目录不存在 则需要导出
		 if (0 > (fd = open("/sys/class/gpio/export", O_WRONLY))) {
			 perror("open1 error");
			 return -1;
		 }
		 if ((len != write(fd, gpio_num, 1))) {//导出 gpio
			 perror("write1 error");
			 close(fd);
			 return -1;
		 }
		 close(fd); //关闭文件
	 }
	 /* 配置为输出模式 */
	 if (gpio_config("direction", "out"))
	 	return -1;
	 /* 极性设置 */
	 //if (gpio_config("active_low", "0"))
	 	return -1;
	 /* 控制 GPIO 输出高低电平 */
	 if (gpio_config("value", value))
	 	return -1;

	 /* 删除GPIO导出文件*/
	//  if (0 > (fd = open("/sys/class/gpio/unexport", O_WRONLY))) {
	// 	 perror("open2 error");
	// 	 return -1;
	//  }
	//  if (len != write(fd, gpio_num, 1)) {//导出 gpio
	// 	 perror("write2 error");
	// 	 close(fd);
	// 	 return -1;
	//  }
	 close(fd); //关闭文件

	 /* 退出程序 */
	 return 0;
}

