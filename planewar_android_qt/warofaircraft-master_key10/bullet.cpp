#include "bullet.h"


Bullet::Bullet()
{
    //初始化子弹图片
    m_img.load(BULLET_PATH);

    //初始化子弹坐标
    m_X = GAME_WIDTH *0.5 ;
    m_Y = GAME_HEIGHT;

    //子弹状态
    m_state = true;

    //子弹伤害
    m_damage = BULLET_DAMAGE;

    //子弹速度
    m_speed = BULLET_SPEED;

    //初始化子弹边框
    m_rect.setWidth(m_img.width());
    m_rect.setHeight(m_img.height());
    m_rect.moveTo(m_X, m_Y);
}


void Bullet::setAttribute(QString img, int dmg, int speed)
{
    m_img.load(img);
    m_damage = dmg;
    m_speed = speed;

    m_rect.setWidth(m_img.width());
    m_rect.setHeight(m_img.height());
    m_rect.moveTo(m_X, m_Y);
}


void Bullet::updatePosition()
{
    //待发射子弹无需计算，直接返回
    if (m_state)
    {
        return;
    }

    m_Y -= BULLET_SPEED;    //发射出的子弹向上移动
    m_rect.moveTo(m_X,m_Y);

    if (m_Y <= -m_img.height())
    {
        m_state = true;
    }
}

void Bullet::bUpdatePosition()
{
    if (m_state)
    {
        return;
    }

    m_Y += BOSS_BULLET_SPEED;
    m_rect.moveTo(m_X, m_Y);

    if (m_Y >= GAME_HEIGHT + m_img.height())
    {
        m_state = true;
    }
}

void Bullet::bombUpdatePosition()
{
    if (m_state)
    {
        return;
    }

    m_Y += BOSS_MISSILE_SPEED;
    m_rect.moveTo(m_X, m_Y);

    if (m_Y > GAME_HEIGHT || m_X > GAME_WIDTH || m_X < -m_img.width())
    {
        m_state = true;
    }
}


