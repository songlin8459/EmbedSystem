#ifndef _RLE_H
#define _RLE_H

#include<stdio.h>
#include<string.h>
#define N 64
typedef struct 
{
    char cont[N];
    int cont_n[N];
    int counter_final;
}CONT;




CONT *ZIP(char *arr);
CONT *UNZIP(CONT *incont);
CONT *UNZIP2(CONT *incont);
#endif