#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QPalette>
#include <QLabel>
#include <QIcon>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <QApplication>
#include <QSound>
#include <QLCDNumber>
#include <QSocketNotifier>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include "config.h"
#include "gamebutton.h"
#include "map.h"
#include "myhero.h"
#include "bullet.h"
#include "enemyplane.h"
#include "bombchange.h"
#include "movevector.h"
#include "displayhp.h"
#include "scoreboard.h"
#include "magazinedisplay.h"


class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(char *argv[], QWidget *parent = nullptr);
    ~MainWindow();
    //初始化摇杆和物理按键
    void initJoyStick();

    // 初始化游戏的一些必要属性
    void initStartScene();

    // 初始化按钮形态
    void initButton();

    // 控制各按钮按下后所需执行的操作
    void buttonAction();

    // 控制开始菜单的显示和隐藏
    void startHide();
    void startShow();

    // 显示控制难度的开关
    void diffButtonShow();

    // 初始化各敌机属性
    void initEnemyPlane();

    /*** !!控制游戏正式开始!! ***/
    void GameStart();

    // 基于定时器更新游戏画面
    void timerUpdate();

    // 更新所有游戏中元素的坐标
    void updatePosition();

    // 重写 paintEvent 函数
    void paintEvent(QPaintEvent *);

    // 重写这两个函数，使用键盘控制控制飞机
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    // 下列第一个函数管理所有敌机出场函数
    void enemyToSceneManager();
    void enemyToScene();
    void enemy2ToScene();
    void bossToScene();

    // 碰撞检测
    void collideCheck();

    // 英雄爆炸切图数据初始化
    void initHeroBombAction();

    // 英雄生命值显示功能初始化
    void initHPDisplay();

    // 反馈英雄生命值的变化
    void hpFeedback();

    // 与I型敌机发生交互的处理方法
    void enemy1Feedback();

    // 与II型敌机发生交互的处理方法
    void enemy2Feedback();

    // 与BOSS发生交互的处理方法
    void bossFeedback();

    // 英雄被摧毁后进行的操作
    void afterHeroBoom();


public:
    // 地图对象
    Map gameMap;

    // 英雄飞机对象
    MyHero myHero;

    // 英雄移动向量
    MoveVector heroVector;

    // 定时器
    QTimer m_Timer;

    // 敌机数组
    EnemyPlane enemys[ENEMY_NUM];
    EnemyPlane enemys2[ENEMY2_NUM];
    EnemyBoss boss;

    // 敌机出场时间间隔记录器
    int enemySpaceRec;
    int enemy2SpaceRec;

    /* 爆炸数组
     * 建立数组的好处是 如果同时有很多爆炸能应付得来，爆炸最大数量最好是飞机最大数量 */
    BombChange bombs[BOMB_NUM];
    BombChange bombs2[BOMB2_NUM];
    BombChange bombBoss;
    BombChange bombBullet[BOSS_BULLET_NUM];
    BombChange bombMissile;

/***** 实现英雄爆炸切图所需参数 *****/

    int heroBombX;
    int heroBombY;
    int heroBombSpcRec;
    QVector<QPixmap> heroBombImgArr;
    int heroBombImgIndex;

/**********************************/


/********** 生命值显示区域 **********/

    // 英雄生命值数字贴图数组
    DisplayHP heroHPDisp[10];
    // 存储三个要显示的数字对象的下标
    int toDisplay[3];
    // 生命值图标
    QPixmap healthIcon;

/***********************************/

    // 计分板对象
    ScoreBoard scoreBoard;

    // 弹匣显示
    MagazineDisplay magazineBoard;


private:
    GameButton ss_b1;  // 开始游戏按钮
    GameButton ss_b2;  // 退出按钮
    GameButton ss_b3;
    GameButton ss_b3_bk;
    GameButton bk;     // 回到主菜单按钮

    //选择难度按钮
    GameButton diff_Easy;
    GameButton diff_Normal;
    GameButton diff_Hard;

    QPushButton pause;  // 暂停按钮
    QPushButton goon;   // 继续按钮

    QLabel *title = new QLabel(this);   // 标题图片
    QLabel *intro = new QLabel(this);   // 键位介绍文字

    QPalette pal = this->palette();

    int startFlag = 0;  // 开始游戏时设置为 1

    //QSound *bg_music = new QSound(SND_BG, this);  // 背景音乐对象

    bool normalMode; // 普通难度开关
    bool hardMode;   // 困难难度开关

    qreal enemy_interval_index;   // 敌机出场间隔系数，受难度影响
    qreal enemy_speed_index;      // 敌机速度系数，受难度影响

    int start_time;
    int end_time;
    int current_time;

    int fd;
    QSocketNotifier *notifier;
    struct input_event ev;
    bool flag_stop;
    int loop_counter;
signals:
    void flag_stop_signal(bool flag_stop);
public slots:
    void joyCtlVector(void);
    void joyCtlVector_handle();

};

#endif // MAINWINDOW_H


