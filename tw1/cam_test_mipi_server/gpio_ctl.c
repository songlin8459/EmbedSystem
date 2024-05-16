#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static char gpio_path[100];
static int gpio_config(const char *attr, const char *val)
{
	 char file_path[100];
	 int len;
	 int fd;
	 sprintf(file_path, "%s/%s", gpio_path, attr);
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
int gpio_check(char index[16]) {
    // 打开/sys/class/gpio/export文件
    int export_fd = open("/sys/class/gpio/export", O_WRONLY);
    if (export_fd == -1) {
        perror("open /sys/class/gpio/export failed\n");
        exit(EXIT_FAILURE);
    }

	sprintf(gpio_path, "/sys/class/gpio/gpio%s", index);

    if (access(gpio_path, F_OK) != 0) {

        write(export_fd, index, strlen(index));
        printf("gpio%s was written in /sys/class/gpio/export\n", index);
    }
	else{
		printf("gpio%s exist\n", index);
	}
    // 关闭文件描述符
    close(export_fd);

    return 0;
}
int main(int argc, char *argv[])
{
	int fd, len;
    if (3 != argc) {
    fprintf(stderr, "error: %s  <value>\n", argv[0]);
    exit(-1);
    }
	 /* 判断指定编号的 GPIO 是否导出 */
	 char index[16];
	 sprintf(index, "/sys/class/gpio/gpio%s", argv[1]);
	gpio_check(index);

	 /* 配置为输出模式 */
	 if (gpio_config("direction", "out"))
	 	exit(-1);
	 /* 极性设置 */
	 if (gpio_config("active_low", "0"))
	 	exit(-1);
	 /* 控制 GPIO 输出高低电平 */
	 if (gpio_config("value", argv[2]))
	 	exit(-1);

	 /* 删除GPIO导出文件*/
	 if (0 > (fd = open("/sys/class/gpio/unexport", O_WRONLY))) {
		 perror("open2 error");
		 exit(-1);
	 }
	 if (len != write(fd, argv[1], 1)) {//导出 gpio
		 perror("write2 error");
		 close(fd);
		 exit(-1);
	 }
	 close(fd); //关闭文件

	 /* 退出程序 */
	 exit(0);
}

