#include <stdio.h>
#include <malloc.h>
#include <string.h>
/*防止重复展开头文件*/
#ifndef _SEQLIST_H
#define _SEQLIST_H

#define N 64 
typedef int data_t;

typedef struct seqlist
{
    data_t data[N]; /*存放顺序表的元素*/
    int last;/*表尾指针，用于表示最后一个元素下标*/
}Seqlist;


Seqlist *Seqlist_Create();//创建顺序表
void Seqlist_Insert_Pos(Seqlist *list, int pos, data_t data);//插入元素
void Seqlist_Show(Seqlist *list);//打印顺序表
int Seqlist_Is_Full(Seqlist *list);//判满
int Seqlist_Is_Empty(Seqlist *list);//判空
void Seqlist_Delete_Pos(Seqlist *list, int pos);//删除指定位置元素
void Seqlist_Delete_Data(Seqlist *list, data_t data);//删除指定数据元素
void Seqlist_Updata_Pos(Seqlist *list, int pos, data_t data);//修改指定位置元素
void Seqlist_Updata_Data(Seqlist *list, data_t data_original, data_t data_new);//修改指定数据元素
data_t Seqlist_Search_Pos(Seqlist *list, int pos);//查找指定位置元素
int Seqlist_Search_Data(Seqlist *list, data_t data);//查找指定数据元素
void Seqlist_Destory(Seqlist **plist);//删除表
#endif