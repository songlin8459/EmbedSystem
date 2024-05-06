#ifndef DISPLAYHP_H
#define DISPLAYHP_H

#include <QPixmap>
#include "config.h"


class DisplayHP
{
public:
    DisplayHP();


public:
    QPixmap numImg; //设置图片
    int m_width;   //图片宽度
    int m_height;  //图片高度
    int numIndex;  //图片序号
};

#endif // DISPLAYHP_H
