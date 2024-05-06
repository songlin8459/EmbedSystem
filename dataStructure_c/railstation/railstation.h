#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _RAILSTATION_H
#define _RAILSTATION_H

#define N 64
//路线信息(顺序表)
typedef struct line
{
	struct station station[N]; //站点信息
	int station_num;       	//站点编号

}Line;
//站点信息
typedef struct station
{
	char name_chinese[N];   //站点中文名字
	char name_english[N];   //站点英文名字
	int arrive_time;        //到站时间
	int door;               //开门方向(左侧为0，右侧为1，两侧为2)
	int change_line[N/10];     //换乘路线
}Station;

//车厢节点信息（顺序表）
typedef struct box
{
	struct station *now_station; 	//当前车站信息
	int box_num;                	//车厢号
}Box;


Line *Line_Create(void);//创建路线
void Line_Inser(Line *line, char chinese[N], char english[N], int change[N/10], int time, int door);//添加车站信息
Station *Line_Search(Line *line, int station_num);//查找站点
void *Line_Updata(Line *line, int station_num);//修改站点
void Line_Show(Line *line);//打印路线信息
void Line_Destory(Line **line);//销毁路线

#endif