#ifndef __GPIO_CTL_H__
#define __GPIO_CTL_H__

static int gpio_config(const char attr[32], const char val[32]);

int gpio_ctl(char gpio_num[16], char value[16]);


#endif