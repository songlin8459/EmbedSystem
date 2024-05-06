#include "myhero.h"
#include "config.h"
#include <QDebug>

MyHero::MyHero()
{
    // 初始化飞机图片
    m_img.load(MYHERO_PATH);
    m_img_speedup.load(MYHERO_SPEEDUP_PATH);

    // 初始化飞机坐标
    m_X = (GAME_WIDTH - m_img.width()) / 2;
    m_Y = GAME_HEIGHT - m_img.height() - 50;

    // 初始化飞机血量 状态 速度
    m_HP = HERO_HP;
    m_state = 0;
    m_speed = HERO_SPEED;

    // 初始化矩形碰撞边框
    m_rect.setWidth(m_img.width() - 60);
    m_rect.setHeight(m_img.height() - 30);
    m_rect.moveTo(m_X + 30, m_Y + 15);

    m_spaceRec = 0;

    m_score = 0;

    m_magazine_capacity = HERO_MAGAZINE;
    isShooting = 0;
}

void MyHero::setPosition(qreal newx, qreal newy)
{
    qreal x, y;
    x = m_X + newx * m_speed;
    y = m_Y + newy * m_speed;

    // 侦测飞机是否超出窗口边界并且作出反应
    if (x <= -20)
    {
        x = -20;
    }
    if (y <= 300)
    {
        y = 300;
    }
    if (x >= GAME_WIDTH - m_img.width() + 40)
    {
        x = GAME_WIDTH - m_img.width() + 40;
    }
    if (y >= GAME_HEIGHT - m_img.height() + 20)
    {
        y = GAME_HEIGHT - m_img.height() + 20;
    }

    m_X = x;
    m_Y = y;
    m_rect.moveTo(m_X + 30, m_Y + 15);
}

void MyHero::shoot()
{
    // 未达到预定时间间隔 或弹匣中弹药不足，不发射子弹 直接return
    if (m_spaceRec < BULLET_SPACE || m_magazine_capacity <= 0)
    {
        return;
    }

    m_spaceRec = 0;

    // 遍历寻找一个处于空闲状态的子弹
    for (int i = 0; i < BULLET_NUMBER; i++)
    {
        if (m_bullets[i].m_state)
        {
            m_bullets[i].m_state = false; // 将其改为发射状态
            m_bullets[i].m_X = m_X + m_img.width() * 0.5 - 17;
            m_bullets[i].m_Y = m_Y - 30;
            m_magazine_capacity--; // 弹药减一
            break;                 // 已找到一个空闲子弹，发射后break终止循环
        }
    }
}

void MyHero::MagazineSupply()
{
    if (isShooting)
    {
        m_supplyRec = 0;
        return;
    }

    m_supplyRec++;
    
    if (m_supplyRec >= SUPPLY_INTERVAL)
    {
        m_supplyRec = SUPPLY_INTERVAL;
        m_supply_limit++;

        if ((m_magazine_capacity < HERO_MAGAZINE) && (m_supply_limit >= SUP_SPEED_LMT))
        {
            m_magazine_capacity++;
            m_supply_limit = 0;
        }
    }
}
