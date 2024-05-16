#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#include <unistd.h>
#include "module.h"

struct jpg_buf_t *jpg;

pthread_t cam_tid;
pthread_t zgb_tid;
pthread_t srv_tid;

pthread_mutex_t cam_mutex;
int sync_flag = 3;

int main(int argc, char *argv[])
{
	int srv_ret = -1, cam_ret = -1, zgb_ret = -1;
	pthread_mutex_init(&cam_mutex, NULL);

	/* camera thread */
	while (cam_ret < 0)
	{
		cam_ret = pthread_create(&cam_tid, NULL, thread_cam, NULL);
		if (cam_ret)
		{
			errno = cam_ret;
			perror("create camera thread");
			exit(EXIT_FAILURE);
		}
		else
			printf("create camera thread success\n");
		cam_ret = pthread_detach(cam_tid);
		if (cam_ret)
		{
			errno = cam_ret;
			perror("detach camera thread");
			exit(EXIT_FAILURE);
		}
		else
			printf("detach camera thread success\n");
	}
#if 0
	/*thread_zgb*/
	while (zgb_ret < 0)
	{
		zgb_ret = pthread_create(&zgb_tid, NULL, thread_zgb, NULL);
		if (zgb_ret)
		{
			errno = zgb_ret;
			perror("create zigbee thread");
			exit(EXIT_FAILURE);
		}
		else
			printf("create zigbee thread success\n");
		zgb_ret = pthread_detach(zgb_tid);
		if (zgb_ret)
		{
			errno = zgb_ret;
			perror("detach zigbee thread");
			exit(EXIT_FAILURE);
		}
		else
			printf("detach zigbee thread success\n");
	}
#endif
	/* android server thread */
	while (srv_ret < 0)
	{
		srv_ret = pthread_create(&srv_tid, NULL, thread_srv, NULL);
		if (srv_ret)
		{
			errno = srv_ret;
			perror("create android server thread\n");
			exit(EXIT_FAILURE);
		}
		else
			printf("create android server thread success\n");

		srv_ret = pthread_detach(srv_tid);
		if (srv_ret)
		{
			errno = srv_ret;
			perror("deta`ch android server thread\n");
			exit(EXIT_FAILURE);
		}
		else
			printf("detach android server thread success\n");
	}

	/* main thread, process environment data form m0 board or process short message */
	while (1)
	{
		// pthread_mutex_destroy(&cam_mutex);
	}
	exit(EXIT_SUCCESS);
}
