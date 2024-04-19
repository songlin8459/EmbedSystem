#ifndef MYHERO_H
#define MYHERO_H

#include <QPixmap>
#include "bullet.h"


class MyHero
{
public:
    MyHero();

    // 改变飞机和其碰撞边框的位置
    void setPosition(qreal x, qreal y);

    // 发射子弹
    void shoot();

    // 弹药补充
    void MagazineSupply();


public:
    // 飞机图像
    QPixmap m_img;
    QPixmap m_img_speedup;

    // 飞机坐标 速度
    qreal m_X;
    qreal m_Y;
    qreal m_speed;

    // 飞机得分
    int m_score;

    // 飞机血量
    int m_HP;

    // 飞机状态，为 1 时代表死亡
    bool m_state;

    // 飞机边框
    QRect m_rect;

    // 子弹数组
    Bullet m_bullets[BULLET_NUMBER];

    // 当前弹匣中子弹数量
    int m_magazine_capacity;

    // 间隔记录
    int m_spaceRec;

    // 为 1 时表示发射键被按下
    bool isShooting;

    // 补充弹药阈值间隔记录
    int m_supplyRec;

    // 控制弹药补充速度
    int m_supply_limit;
};

#endif // MYHERO_H
