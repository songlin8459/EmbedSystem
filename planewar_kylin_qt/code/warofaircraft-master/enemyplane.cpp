#include "enemyplane.h"
#include <ctime>
#include <QDebug>


EnemyPlane::EnemyPlane()
{
    m_X = 0;
    m_Y = 0;
    m_hitState = false;    // false为未被击中
    m_hitRecorder = 0;
    m_dirChangeRec = 0;
    m_hon_speed = 0;
    m_state = true;    // true为空闲未出场状态
    m_enemy_type = 0;

    srand( (unsigned int)time(NULL) );  //随机数种子
}


void EnemyPlane::updatePosition()
{
    if (m_state)
    {
        return;
    }

    m_Y += m_speed;

    if (m_enemy_type == 1)
    {
        m_dirChangeRec++;
        m_X += m_hon_speed;

        if (m_dirChangeRec > DIR_CHANGE_LIMIT)
        {
            int tmp = rand()%2;
            //qDebug() << tmp;
            if (tmp)
            {
                m_hon_speed = 1;
            }
            else
            {
                m_hon_speed = -1;
            }
            m_dirChangeRec = 0;
        }

        if (m_X < 0 || m_X >= GAME_WIDTH - m_img.width())
        {
            m_hon_speed *= -1;
        }
    }

    m_rect.moveTo(m_X + m_img.width() * 0.1, m_Y + m_img.width() * 0.1);

    // 超出屏幕后重置为空闲状态，并重置血量
    if (m_Y >= GAME_HEIGHT + 5)
    {
        m_state = true;
        m_HP = m_fullHP;    // 不同类型敌机的 fullHP 不同，所以不能将其设为一个常量
    }
}


void EnemyPlane::setAttribute(QString imgDir, int hp, int colAtk, int scoreVal, int speed, int type)
{
    m_img.load(imgDir);
    m_fullHP = hp;
    m_HP = m_fullHP;
    m_col_Atk = colAtk;
    m_scoreValue = scoreVal;
    m_speed = speed;
    m_enemy_type = type;

    m_rect.setWidth(m_img.width() * 0.8);
    // 特殊：高度 * 0.2 才能保证子弹看上去碰到飞机再爆炸，优化观感
    m_rect.setHeight(m_img.height() * 0.2);
    m_rect.moveTo(m_X + m_img.width() * 0.1, m_Y + m_img.width() * 0.4);
}


EnemyBoss::EnemyBoss()
{
    // 设置 BOSS 飞机属性
    EnemyPlane::setAttribute(BOSS_PATH, BOSS_HP, BOSS_COL_ATK, BOSS_VALUE, BOSS_SPEED, 3);

    m_X = (GAME_WIDTH - m_img.width()) / 2;
    m_Y = - m_img.height();

    // 设置 BOSS 子弹属性
    bullets_num_now = 0;
    for (int i = 0; i < BOSS_BULLET_NUM; i++)
    {
        m_bullets[i].setAttribute(BOSS_BULLET_PATH, BOSS_BULLET_DMG, BOSS_BULLET_SPEED);
    }

    // 设置 BOSS 炸弹属性
    m_missile.setAttribute(BOSS_MISSILE_PATH, BOSS_MISSILE_DMG, BOSS_MISSILE_SPEED);

    m_show_interval = 0;
    m_death_time = 0;

    m_show_time_rec = 0;
    m_show_round = 0;

    m_shoot_rec = 0;

    shootState = false;
    bullet_rec = 0;
    bullet_round = 0;
}


void EnemyBoss::bossAction()
{
    m_show_time_rec = m_current_time - m_showup_time;
    //qDebug() << "Show time: " << m_show_time_rec;

    if (m_Y < 50)
    {
        m_Y += BOSS_SPEED;
        m_rect.moveTo(m_X + m_img.width() * 0.1, m_Y + m_img.width() * 0.4);
    }
    else
    {
        m_shoot_rec++;

        if (m_shoot_rec >= BOSS_SHOOT_INTERVAL)
        {
            shootControl();
            //qDebug() << "shootControl on";

            if(shootState == false)
            {
                m_shoot_rec = 0;
            }
        }
    }
}


void EnemyBoss::shootControl()
{
    shootState = true;  // 开启射击状态
    bullet_rec++;

    if (bullet_rec >= BOSS_BULLET_INTERVAL)
    {
        bullet_rec = 0;
        bullet_round++;

        if (bullet_round <= BOSS_BULLET_ROUND - 1)
        {
            shoot();
            QSound::play(BOSS_BULLET_OUT_SND);
        }

        if (bullet_round >= BOSS_BULLET_ROUND)
        {
            throwBomb();
        }

        if (bullet_round >= BOSS_BULLET_ROUND)
        {
            bullet_round = 0;
            shootState = false;  // 达到射击次数上限，关闭射击状态
        }
    }
}


void EnemyBoss::shoot()
{
    //qDebug() << "boss shoot";
    int offsetX = 0;

    for (int i = 0; i < BOSS_BULLET_NUM; i++)
    {
        if (m_bullets[i].m_state == false)
        {
            continue;
        }

        m_bullets[i].m_state = false;
        m_bullets[i].m_X = m_X + (m_img.width() - m_bullets[i].m_img.width()) * 0.5 + offsetX;
        m_bullets[i].m_Y = m_Y + m_img.height() - 20;
        bullets_num_now++;

        // 偏移量调整
        offsetX = (bullets_num_now > 1) ? 150 : -150;

        // 一次同时射出 3 发子弹
        if (bullets_num_now >= 3)
        {
            bullets_num_now = 0;
            break;
        }
    }
}


void EnemyBoss::throwBomb()
{
    if (m_missile.m_state)
    {
        m_missile.m_state = false;
        m_missile.m_X = heroXget + (heroImgWidth - m_missile.m_img.width()) / 2;
        m_missile.m_Y = -m_missile.m_img.height();
    }
}


void EnemyBoss::afterDeath()
{
    m_state = true;
    m_death_time = m_current_time;
    m_HP = m_fullHP;    // 重置血量
    m_shoot_rec = 0;
    bullet_rec = 0;
    bullet_round = 0;

    // 重置位置
    m_X = (GAME_WIDTH - m_img.width()) / 2;
    m_Y = - m_img.height();
}
