#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <termios.h>

#include <error.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "tcp_server.h"
#include "serial.h"

#define REQ_DATA_SIZE 32
#define HDR_DATA_SIZE 128

extern int zgbfd;
extern pthread_mutex_t env_mutex;

#include "serial.h"

#define ZGB_DATA_SIZE 36

int zigbee_init(char *devpath, int baudrate)
{
	return serial_init(devpath);
}

int zigbee_get_dat(int fd)
{
	ssize_t ret;
	unsigned char buf[ZGB_DATA_SIZE];

	memset(buf, 0, sizeof(buf));
	ret = serial_recv_exact_nbytes(fd, buf, sizeof(buf));
	if (ret == sizeof(buf))
	{
		/*		int i;*/
		/*		for (i = 0; i < 36; i++){*/
		/*			printf("%.2x ", buf[i]);*/
		/*		}*/
		/*		printf("\n");*/
		if (buf[0] == 0xBB)
		{
			memset(&data, 0, sizeof(struct env));
			data.id = (int)buf[1];
			data.tem = (int)buf[5] + buf[4];
			data.hum = (int)buf[7] + buf[6];
			data.light = (int)((buf[23] << 24) + (buf[22] << 16) + (buf[21] << 8) + buf[20]);
			if ((data.x = (int)buf[8]) > 127)
			{
				data.x -= 256;
			}
			if ((data.y = (int)buf[9]) > 127)
			{
				data.y -= 256;
			}
			if ((data.z = (int)buf[10]) > 127)
			{
				data.z -= 256;
			}
		}
	}
	return ret;
}

int zigbee_exe_cmd(int fd, char *p)
{
	// unsigned char buf[ZGB_DATA_SIZE] = {0xdd, 0x05, 0x24, 0x00, 0x00};
	unsigned char buf[1] = {'0'};
	buf[1] = data.id;
	int ret = 0;
	if (strstr(p, "LIGHT_ON") != NULL)
	{
		// buf[4] = 0x00;
		buf[0] = '1';
	}
	else if (strstr(p, "LIGHT_OFF") != NULL)
	{
		// buf[4] = 0x01;
		buf[0] = '0';
	}
	else if (strstr(p, "BUZZ_ON") != NULL)
	{
		// buf[4] = 0x02;
		buf[0] = '2';
	}
	else if (strstr(p, "BUZZ_OFF") != NULL)
	{
		// buf[4] = 0x03;
		buf[0] = '0';
	}
	else if (strstr(p, "FAN_ON") != NULL)
	{
		// buf[4] = 0x04;
		buf[0] = '3';
	}
	else if (strstr(p, "FAN_OFF") != NULL)
	{
		// buf[4] = 0x08;
		buf[0] = '0';
	}
	else if (strstr(p, "SHU_ON") != NULL)
	{
		// buf[4] = 0x09;
		buf[0] = '4';
	}
	else if (strstr(p, "SHU_OFF") != NULL)
	{
		// buf[4] = 0x0a;
		buf[0] = '0';
	}

	ret = serial_send_exact_nbytes(fd, buf, sizeof(buf));

	return ret;
}

int zigbee_exit(int fd)
{
	return serial_exit(fd);
}
