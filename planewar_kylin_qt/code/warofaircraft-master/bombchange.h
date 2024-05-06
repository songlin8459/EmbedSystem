#ifndef BOMBCHANGE_H
#define BOMBCHANGE_H

#include "config.h"
#include <QPixmap>
#include <QVector>


class BombChange
{
public:
    BombChange();

    //更新爆炸信息
    void updateInfo();

    //设置爆炸图片
    void setBombImg(QString img);


public:
    QVector<QPixmap> m_imgArray;   //爆炸图片数组
    int m_X;
    int m_Y;
    bool m_state;
    int m_spaceRec;    //爆炸切图时间间隔
    int m_imgIndex;    //爆炸时加载的图片下标
};

#endif // BOMBCHANGE_H
