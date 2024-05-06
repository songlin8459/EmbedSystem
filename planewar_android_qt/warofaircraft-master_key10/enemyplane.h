#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "config.h"
#include "bullet.h"
#include <QPixmap>
#include <QSound>


class EnemyPlane
{
public:
    EnemyPlane();

    void updatePosition();

    // 初始化属性依次为：图片路径，血量，碰撞伤害，被摧毁得分，移动速度
    void setAttribute(QString imgDir, int hp, int colAtk, int scoreVal, int speed, int type);


public:
    QPixmap m_img;
    int m_X;
    int m_Y;
    QRect m_rect;

    bool m_state;       // true为空闲未出场状态
    int m_speed;
    int m_HP;           // 当前血量
    int m_col_Atk;      // 飞机碰撞造成的伤害
    int m_scoreValue;   // 该飞机被击落后获得分数
    bool m_hitState;    // 用于切换被击中但未被摧毁时的受损图片
    int m_hitRecorder;  // 计时器，两次出现受损切图效果之间的最大间隔
    int m_dirChangeRec;
    int m_hon_speed;    // 横向速度
    int m_enemy_type;   // 飞机种类
    int m_fullHP;   // 不可更改！用于更新血量
};


class EnemyBoss : public EnemyPlane
{
public:
    EnemyBoss();

    void bossAction();   // BOSS行为，包括出场后的短距离移动和射击

    void shootControl();  // 控制子弹发射

    void shoot();  // 实现子弹发射

    void throwBomb();  // 实现炸弹投掷

    void afterDeath();   // BOSS死亡后执行的指令


public:
    Bullet m_bullets[BOSS_BULLET_NUM];  // BOSS的子弹数组
    Bullet m_missile;  // BOSS的炸弹

    int heroXget;   // 得到英雄的横坐标
    int heroImgWidth;   // 得到英雄图片的横坐标

    int m_current_time;   // 游戏已运行时间
    int m_showup_time;    // 记录 BOSS 出场的时刻
    int m_show_time_rec;  // 记录 BOSS 已出场时间
    int m_death_time;     // 记录 BOSS 死亡的时刻
    int m_show_round;     // 记录 BOSS 已出现次数

    int m_shoot_rec;      // 发射子弹间隔
    int bullets_num_now;  // 一次同时发射的子弹数量
    int m_show_interval;  // 记录上次 BOSS 死亡后已进行的时间，首次出场前默认为游戏开始到当前的时间

    bool shootState;   // 控制开关 BOSS 的一轮射击
    int bullet_rec;    // 每轮中各子弹的发射间隔记录
    int bullet_round;  // 每轮发射的子弹次数
};

#endif // ENEMYPLANE_H
