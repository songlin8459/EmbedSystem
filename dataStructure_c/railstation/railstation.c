#include "railstation.h"
/*==============================创建路线=============================*/
Line *Line_Create(void)
{
    Line *line = (Line *)malloc(sizeof(Line));
    if(line = NULL)
    {
        printf("line malloc failed!\n");
        return NULL;
    }
    //站点序号初始为-1
    line->station_num = -1;
    return line;
}
/*==============================添加车站信息=============================*/
void Line_Inser(Line *line, char chinese[N], char english[N], int change[N/10], int time, int door)
{
    //判满
    if(line->station_num == N - 1)
    {
        printf("line is full");
        return ;
    }
    //站点序号+1
    line->station_num++;
    //添加车站信息
    strcpy(line->station[line->station_num].name_chinese, chinese);
    strcpy(line->station[line->station_num].name_english, english);
    int change_arr_length = 0;
    while(change[change_arr_length++])line->station[line->station_num].change_line[change_arr_length] = change[change_arr_length];
    line->station[line->station_num].arrive_time = time;
    line->station[line->station_num].door = door;
    return ;
} 

/*==============================打印路线信息=============================*/
void Line_Show(Line *line)
{
    //判空
    if(line->station_num = -1)
    {
        printf("line is empty!\n");
        return ;
    }
    int i = 0;
    for(i; i <= line->station_num; i++)
    {
        printf("station_num:%d\n", line->station_num);
        printf("station_chinese_name:");
        puts(line->station[line->station_num].name_chinese);
        puts("");
        printf("station_english_name:");
        puts(line->station[line->station_num].name_english);
        puts("");
        printf("station_change_line:");
        puts(line->station[line->station_num].change_line);
        puts("");
        printf("arrive_time:%d\n", line->station[line->station_num].arrive_time);
        printf("station_open_door:%d\n", line->station[line->station_num].door);
        printf("------------------------------");
    }
    return ;
}
/*==============================销毁路线=============================*/
void Line_Destory(Line **line)
{
       free(*line);
       *line = NULL;
}