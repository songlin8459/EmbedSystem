#ifndef BULLET_H
#define BULLET_H

#include "config.h"
#include <QPixmap>


class Bullet
{
public:
    Bullet();

    // 设置子弹属性
    void setAttribute(QString img, int dmg, int speed);

    // 刷新子弹位置
    void updatePosition();

    // 刷新 BOSS 子弹位置
    void bUpdatePosition();
    
    // 刷新 BOSS 炸弹位置
    void bombUpdatePosition();


public:
    QPixmap m_img;  // 子弹资源对象

    // 坐标
    int m_X;
    int m_Y;

    int m_speed;    // 子弹速度
    int m_damage;   // 子弹伤害
    bool m_state;   // 子弹状态，1为空闲待发射，0为正处于发射状态
    QRect m_rect;   // 子弹边框
};

#endif // BULLET_H
