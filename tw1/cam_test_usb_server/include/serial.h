#ifndef __SERIAL_H__
#define __SERIAL_H__

struct env
{
	int id;
	int tem;
	int hum;
	int light;
	int x;
	int y;
	int z;
};

struct env data;

int serial_Open(char *devpath);
void serial_Close(int fd);
int serial_Set(int fd, int speed, int flow_ctrl, int databits, int stopbits, int parity);
int serial_init(char *devpath);
int serial_recv_exact_nbytes(int fd, void *buf, int count);
int serial_send_exact_nbytes(int fd, unsigned char *buf, int count);
int serial_exit(int fd);

#endif
