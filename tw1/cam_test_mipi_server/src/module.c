#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h> //read

#include <sys/types.h> //send
#include <sys/socket.h>

#include <sys/shm.h>
#include <pthread.h>

#include "serial.h"
#include "zigbee.h"
#include "cam.h"
#include "cam_mipi.h"
#include "mutexs.h"
#include "module.h"
#include "tcp_server.h"

#define REQ_DATA_SIZE 32
#define HDR_DATA_SIZE 128

int zgbfd, srvfd;

void *thread_cam()
{
	int ret = -1;
	while (ret < 0)
	{
		ret = camera_on();
		sleep(3);
	}
	return (void *)0;
}
void *thread_mipi(void *arg)
{
	int ret = -1;
	while (ret < 0)
	{
		ret = cam_mipi_on();
		sleep(3);
	}
	return (void *)0;
}
void *thread_zgb(void *arg)
{
	char *devpath[] = {"/dev/ttyUSB0", "/dev/ttyUSB1"};
	int i = 0;
AA:
	zgbfd = serial_init(devpath[i]);
	if (zgbfd == -1)
	{
		sleep(2);
		i = 1;
		goto AA;
	}
	else
		fprintf(stdout, "init zigbee success\n");

	//	pthread_mutex_unlock(&env_mutex);
	while (1)
	{
		//		pthread_mutex_lock(&env_mutex);
		int ret = zigbee_get_dat(zgbfd);
		if (ret < 0)
		{
			perror("env_recv:");
		}
		sleep(1);
		//		pthread_mutex_unlock(&env_mutex);
	}
}

void *thread_srv()
{
	int *tempfd;
	int connfd;
	pthread_t requst_tid; // 服务器读取客户端线程号

	int s = tcp_server_init(8080, 16); 
	if (0 > s)
	{
		printf("init_server failed!\n");
		pthread_exit(NULL);
	}
	while (1)
	{
		if ((connfd = tcp_server_wait_connect(s)) != -1)
		{
			tempfd = malloc(sizeof(int));
			if (!tempfd)
			{
				fprintf(stderr, "server->malloc: malloc failure\n");
				close(connfd);
				close(s);
			}
			*tempfd = connfd;
			int ret = pthread_create(&requst_tid, NULL, Read_request, tempfd);
			if (ret)
			{
				errno = ret;
				perror("server->thread");
				close(connfd);
				close(s);
			}
			else
				printf("server->thread: create client thread success\n");
		}
	}
}

void *Read_request(void *arg)
{
	int ret;
	int connfd = *(int *)arg;
	char request[REQ_DATA_SIZE] = {0};
	char response[HDR_DATA_SIZE] = {0};
	while (1)
	{
		memset(request, 0, sizeof(request));
		ret = tcp_server_recv(connfd, request, sizeof(request));
		if (ret <= 0)
			return (void *)-1;
		fprintf(stdout, "%s", request);
		if (strstr(request, "PIC_SEND") != NULL)
		{
			pthread_mutex_lock(&cam_mutex);
			snprintf(response, sizeof(response), " %dlen", jpg->jpg_size);
			ret = tcp_server_send_exact_nbytes(connfd, response, sizeof(response));
			if (ret != sizeof(response))
			{
				fprintf(stderr, "server->write: send response failed\n");
				return (void *)-1;
			}
			printf("%s\n", response);
			ret = tcp_server_send_exact_nbytes(connfd, jpg->jpg_buf, jpg->jpg_size);
			if (ret != jpg->jpg_size)
			{
				fprintf(stderr, "server->write: send response failed\n");
				return (void *)-1;
			}
			printf("send pic\n");
			pthread_mutex_unlock(&cam_mutex);
		}
#if 1
		else if (strstr(request, "ENV_SEND") != NULL)
		{
			
			memset(response, 0, sizeof(response));
			snprintf(response, sizeof(response), "%did%dt%dh%dl%dx%dy%dz", data.id, data.tem, data.hum, data.light, data.x, data.y, data.z);

			printf("%did%dt%dh%dl%dx%dy%dz\n", data.id, data.tem, data.hum, data.light, data.x, data.y, data.z);

			int ret = tcp_server_send_exact_nbytes(connfd, response, sizeof(response));
			if (ret != sizeof(response))
			{
				fprintf(stderr, "server->write: send response failed\n");
				sleep(2);
				continue;
			}
			memset(request, 0, sizeof(request));
		}
#endif
		else
		{
			printf("%s\n", request);
			if(strstr(request, "LIGHT_ON") != NULL)
			{
				system("./gpio_ctl 15 1");
			}
			if(strstr(request, "LIGHT_OFF") != NULL)
			{
				system("./gpio_ctl 15 0");
			}
			if(strstr(request, "FAN_ON") != NULL)
			{
				system("./gpio_ctl 16 1");
			}
			if(strstr(request, "FAN_OFF") != NULL)
			{
				system("./gpio_ctl 16 0");
			}
			zigbee_exe_cmd(zgbfd, request);
			memset(request, 0, sizeof(request));
		}
		printf("\n");
	}
	return (void *)0;
}
