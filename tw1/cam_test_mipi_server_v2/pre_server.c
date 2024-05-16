#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    // 检查是否存在gpio15和gpio16目录
    if (access("/sys/class/gpio/gpio15", F_OK) == 0 && access("/sys/class/gpio/gpio16", F_OK) == 0) {
        printf("gpio15和gpio16目录已存在\n");
        return 0;
    }

    // 打开/sys/class/gpio/export文件
    int export_fd = open("/sys/class/gpio/export", O_WRONLY);
    if (export_fd == -1) {
        perror("无法打开/sys/class/gpio/export文件");
        exit(EXIT_FAILURE);
    }

    // 写入15或16到/sys/class/gpio/export
    char buf[32];
    if (access("/sys/class/gpio/gpio15", F_OK) != 0) {
        sprintf(buf, "%d", 15);
        write(export_fd, buf, strlen(buf));
        printf("已写入15到/sys/class/gpio/export\n");
    }
    if (access("/sys/class/gpio/gpio16", F_OK) != 0) {
        sprintf(buf, "%d", 16);
        write(export_fd, buf, strlen(buf));
        printf("已写入16到/sys/class/gpio/export\n");
    }

    // 关闭文件描述符
    close(export_fd);

    return 0;
}
