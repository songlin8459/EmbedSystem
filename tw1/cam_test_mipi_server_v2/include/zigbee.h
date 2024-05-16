#ifndef __ZIGBEE_H__
#define __ZIGBEE_H__

int zigbee_init( char *devpath, int baudrate);
int zigbee_get_dat(int fd);
int zigbee_exe_cmd(int fd, char *p);
int zigbee_exit(int fd);

#endif
