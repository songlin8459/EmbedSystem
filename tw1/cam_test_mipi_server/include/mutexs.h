#ifndef __MUTEXS_H__
#define __MUTEXS_H__

extern struct jpg_buf_t *jpg;
extern struct jpg_buf_t *jpg_m;
extern int sync_flag;
extern pthread_mutex_t cam_mutex;
extern pthread_mutex_t cam_mutex_m;
#endif
