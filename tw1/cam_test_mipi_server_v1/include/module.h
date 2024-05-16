#ifndef __MODULE_H__
#define __MODULE_H__

#define	HDR_BUF_LEN	50
void *thread_cam();
void *thread_mipi();
void *thread_zgb(void *arg);
void *thread_srv();
void *thread_srv_mipi();
void *Read_request(void *arg);
void *Read_request_mipi(void *arg);


#endif
