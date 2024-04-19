#include "mainwindow.h"
#include <QKeyEvent>
#include <ctime>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
   initStartScene();  // 初始化场景
   buttonAction();   // 按钮操作检测
}


MainWindow::~MainWindow()
{

}


void MainWindow::initStartScene()
{
   setWindowIcon(QIcon(GAME_ICON)); // 设定窗口 icon
   setFixedSize(GAME_WIDTH, GAME_HEIGHT);  // 设定窗口固定大小
   setWindowTitle(GAME_TITLE);  // 设定窗口标题

   initButton(); // 初始化各按钮

   // 添加背景图片
   pal.setBrush(QPalette::Background, QBrush(QPixmap(BG_IMG)));
   setPalette(pal);

   // 添加标题图片
   title->setPixmap(QPixmap(TITLE_IMG));
   title->move(B_MID_POSW - 185, B_MID_POSH - 300);

   /***** 键位介绍文本设置 *****/
   intro->setText("移动: WASD"
                  "\n\n"
                  "快速机动/加速: Shift"
                  "\n\n"
                  "射击: J"
                  "\n\n\n"
                  "松开射击键一段时间后会自动补充弹药");
   intro->setAlignment(Qt::AlignHCenter);
   intro->move(0, 200);
   intro->resize(512, 500);
   intro->setStyleSheet("font-family:微软雅黑;"
                        "font-size:24px;"
                        "color:white;"
                        "font:bold;");
   intro->hide();
   /**************************/

   // 定时器设置
   m_Timer.setInterval(GAME_RATE);

   // 敌机出场间隔记录器初始化
   enemySpaceRec = 0;
   enemy2SpaceRec = 0;

   // 随机数种子
   srand( (unsigned int)time(NULL) );

   // 英雄爆炸切图数据初始化
   initHeroBombAction();

   // 英雄生命值显示功能初始化
   initHPDisplay();

   // 设置计分板属性
   scoreBoard.m_des_text->setParent(this);
   scoreBoard.m_scoreLCD->setParent(this);
   scoreBoard.m_des_text->hide();
   scoreBoard.m_scoreLCD->hide();

   // 设置弹药显示属性
   magazineBoard.m_bulletNum->setParent(this);
   magazineBoard.m_bulletNum->hide();


   // 难度值
   normalMode = false;
   hardMode = false;
}


void MainWindow::initButton()
{
    ss_b1.setParent(this);
    ss_b1.setText(QString("开始游戏"));
    ss_b1.move(B_MID_POSW, B_MID_POSH - 20);

    ss_b2.setParent(this);
    ss_b2.setText(QString("退出"));
    ss_b2.move(B_MID_POSW, B_MID_POSH + 180);

    //键位介绍相关
    ss_b3.setParent(this);
    ss_b3.setText(QString("键位介绍"));
    ss_b3.move(B_MID_POSW, B_MID_POSH + 80);
    ss_b3_bk.setParent(this);
    ss_b3_bk.setText(QString("返回"));
    ss_b3_bk.move(B_MID_POSW, B_MID_POSH + 200);
    ss_b3_bk.hide();

    //返回按钮
    bk.setParent(this);
    bk.resize(110, 55);
    bk.move(400, 10);
    bk.setText(QString("返回"));
    bk.hide();

    //暂停按钮样式设置(特殊，不在GameButton类中)
    pause.setParent(this);
    pause.resize(45, 45);
    pause.move(10, 10);
    pause.setStyleSheet("QPushButton{"
                        "border-image:url(://res/img/game_pause_nor.png);"
                        "}"
                        "QPushButton:pressed{"
                        "border-image:url(://res/img/game_pause_pressed.png);"
                        "}"
                        );
    pause.hide();

    //继续按钮样式设置(特殊，不在GameButton类中)
    goon.setParent(this);
    goon.resize(45, 45);
    goon.move(10, 10);
    goon.setStyleSheet("QPushButton{"
                       "border-image:url(://res/img/game_resume_nor.png);"
                       "}"
                       "QPushButton:pressed{"
                       "border-image:url(://res/img/game_resume_pressed.png);"
                       "}"
                        );
    goon.hide();

    //选择难度按钮
    diff_Easy.setParent(this);
    diff_Easy.move(B_MID_POSW, B_MID_POSH - 100);
    diff_Easy.setText(QString("简单"));
    diff_Easy.hide();
    diff_Normal.setParent(this);
    diff_Normal.move(B_MID_POSW, B_MID_POSH);
    diff_Normal.setText(QString("普通"));
    diff_Normal.hide();
    diff_Hard.setParent(this);
    diff_Hard.move(B_MID_POSW, B_MID_POSH + 100);
    diff_Hard.setText(QString("困难"));
    diff_Hard.hide();
}


void MainWindow::buttonAction()
{
   // 点击开始游戏
   connect(&ss_b1, &QPushButton::released,
           [=]()
           {
               startHide();  // 隐藏开始界面
               diffButtonShow();
           });

   // 点击退出游戏
   connect(&ss_b2, &QPushButton::released, [=](){ close(); });

   // 点击打开键位介绍
   connect(&ss_b3, &QPushButton::released,
           [=](){
               startHide();
               intro->show();
               ss_b3_bk.show();
           });

   // 点击离开键位介绍界面，返回主菜单
   connect(&ss_b3_bk, &QPushButton::released,
           [=](){
               intro->hide();
               ss_b3_bk.hide();
               startShow();
           });

   /********** 难度选择 **********/
   // 简单
   connect(&diff_Easy, &QPushButton::released,
           [=](){
               // 设定难度系数
               enemy_interval_index = 1;
               enemy_speed_index = 1;

               // 初始化敌机
               initEnemyPlane();

               GameStart();
           });
   // 普通
   connect(&diff_Normal, &QPushButton::released,
           [=](){
               // 设定难度系数
               normalMode = true;
               enemy_interval_index = 0.8;
               enemy_speed_index = 1.3;

               // 初始化敌机 (必须在设定难度系数之后！)
               initEnemyPlane();

               GameStart();
           });

   // 困难
   connect(&diff_Hard, &QPushButton::released,
           [=](){
               normalMode = true;
               hardMode = true;
               enemy_interval_index = 0.8;
               enemy_speed_index = 1.3;

               initEnemyPlane();

               GameStart();
           });
   /*****************************/

   // 返回主菜单
   connect(&bk, &QPushButton::released,
           [=](){
                   // 返回主菜单对话框，如果英雄已经死了就直接退出，不弹出对话框
                   if(myHero.m_state == 1)
                   {
                       qApp->exit(RESTART_CODE);
                       return;
                   }

                   int ret = QMessageBox::question(this, "返回",
                                                   "你确定要回到主菜单吗？",
                                                   QMessageBox::Yes, QMessageBox::No);
                                             // 按钮可自定义, 在 StandardButton 词条中查询

                   switch(ret)
                   {
                       case QMessageBox::Yes:
                           //qDebug() << "Exit";
                           qApp->exit(RESTART_CODE);
                           break;

                       case QMessageBox::No:
                           //qDebug() << "Continue";
                           break;

                       default:
                           break;
                   }
                }
          );

   // 暂停按钮
   connect(&pause, &QPushButton::released,
           [=](){
                    m_Timer.stop();  // 计时器停止
                    bk.show();
                    scoreBoard.m_des_text->hide();
                    scoreBoard.m_scoreLCD->hide();
                    pause.hide();
                    goon.show();
                }
          );

   // 继续按钮
   connect(&goon, &QPushButton::released,
           [=](){
                    m_Timer.start();  // 计时器继续
                    bk.hide();
                    scoreBoard.m_des_text->show();
                    scoreBoard.m_scoreLCD->show();
                    goon.hide();
                    pause.show();
                    heroVector.setKeyInputZero(); // 所有按键状态设置为未按下，防止出现按不了键的bug
                }
          );
}


void MainWindow::startHide()
{
   ss_b1.hide();
   ss_b2.hide();
   ss_b3.hide();
   title->hide();
}


void MainWindow::startShow()
{
   ss_b1.show();
   ss_b2.show();
   ss_b3.show();
   title->show();
}


void MainWindow::diffButtonShow()
{
    diff_Easy.show();
    diff_Normal.show();
    diff_Hard.show();
}


void MainWindow::GameStart()
{
    // 隐藏按钮
    diff_Easy.hide();
    diff_Normal.hide();
    diff_Hard.hide();

    // 关键数据处理
    startFlag = 1;    // 重写 paintEvent事件开始绘制
    timerUpdate();    // 进行游戏画面的更新
    m_Timer.start();  // 计时器启动
    bg_music->play();
    bg_music->setLoops(QSound::Infinite);  // 背景音乐循环播放
    scoreBoard.m_scoreLCD->show();
    scoreBoard.m_des_text->show();
    magazineBoard.m_bulletNum->show();
    pause.show();

    //记录运行时间
    start_time = clock();
    end_time = clock();
    current_time = 0;
}


void MainWindow::initEnemyPlane()
{
    // 初始化I型飞机
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        enemys[i].setAttribute(QString(ENEMY_PATH), ENEMY_HP, ENEMY_COL_ATK,
                               ENEMY_VALUE, ENEMY_SPEED * enemy_speed_index, 1);
    }

    for (int i = 0; i < BOMB_NUM; i++)
    {
        bombs[i].setBombImg(QString(BOMB_PATH));
    }

    // 初始化II型飞机
    for (int i = 0; i < ENEMY2_NUM; i++)
    {
        enemys2[i].setAttribute(QString(ENEMY2_PATH), ENEMY2_HP, ENEMY2_COL_ATK,
                                ENEMY2_VALUE, ENEMY2_SPEED * enemy_speed_index, 2);
    }

    for (int i = 0; i < BOMB2_NUM; i++)
    {
        bombs2[i].setBombImg(QString(BOMB2_PATH));
    }

    // 初始化 BOSS 的爆炸
    bombBoss.setBombImg(QString(BOSS_EXPLODE_PATH));

    // 初始化小炸弹爆炸
    for (int i = 0; i < BOSS_BULLET_NUM; i++)
    {
        bombBullet[i].setBombImg(BOMB_BOSS_BULLET);
    }

    // 初始化导弹爆炸
    bombMissile.setBombImg(BOMB_BOSS_MISSILE);

    // 传个参
    boss.heroImgWidth = myHero.m_img.width();
}


void MainWindow::initHeroBombAction()
{
    heroBombSpcRec = 0;
    heroBombX = 0;
    heroBombY = 0;
    heroBombImgIndex = 0;

    for (int i = 1; i <= BOMB_MAX; i++)
    {
        QString hstr = QString (HERO_BOMB_PATH).arg(i);  // 拼接字符串
        heroBombImgArr.push_back(QPixmap(hstr));
    }
}


void MainWindow::initHPDisplay()
{
    for (int i = 0; i <= 9; i++)
    {
        QString hpstr = QString (NUMBER_IMG).arg(i);  // 拼接字符串
        heroHPDisp[i].numImg.load(hpstr);
        heroHPDisp[i].numIndex = i;
        heroHPDisp[i].m_height = heroHPDisp[i].numImg.height();
        heroHPDisp[i].m_width = heroHPDisp[i].numImg.width();
    }

    healthIcon.load(MYHERO_HPICON);

    for (int i = 0; i < 3; i++)
    {
        toDisplay[i] = 0;
    }
}


void MainWindow::timerUpdate()
{
   /* 以下所有操作在定时器启动时才会开始
    * 以下的函数最好不要调换顺序！容易出现致命错误！！
    */

   // 监听定时器发送的信号
   connect(&m_Timer,&QTimer::timeout,[=](){
       // 敌机出场
       if (myHero.m_state == 0)
       {
           enemyToSceneManager();

           end_time = clock();
           current_time = end_time - start_time;  // 单位: 毫秒
           //qDebug() << current_time;
       }

       // 更新游戏中元素的坐标
       updatePosition();

       // 将英雄血量转换成可显示的模式
       hpFeedback();

       // 将得分反馈在屏幕上
       /* 在这里的 arg 中
        * 第一个参数表示要转换为字符串的整形数
        * 第二个"6"表示位宽
        * 第三个"10"表示十进制
        * 第四个参数表示位数不足时用"0"填充
        */
       scoreBoard.m_scoreLCD->display(QString("%1").arg(myHero.m_score, 6, 10, QChar('0')));

       // 绘制到屏幕中
       update();

       if (myHero.m_state == 0)
       {
           // 碰撞检测
           collideCheck();

           // 将弹药数量反馈在屏幕上
           magazineBoard.m_bulletNum->display(myHero.m_magazine_capacity);
           //qDebug() << myHero.Magazine;
       }

       // 英雄被摧毁后需要进行的操作
       if (myHero.m_state)
       {
           afterHeroBoom();
       }
   });
}


void MainWindow::updatePosition()
{
   if (myHero.m_state == 0)
   {
       // 更新地图坐标
       gameMap.mapPosition();

       // 不发射子弹时也要叠加时间，以实现第一发子弹立即射出
       if (myHero.m_spaceRec < BULLET_SPACE)
       {
           myHero.m_spaceRec++;
           //qDebug() << myHero.SpaceRecord;
       }

       // 实时弹药补充
       myHero.MagazineSupply();

       // 如果发射键被按下，则发射子弹，并且按下时无法补充弹药
       if (heroVector.m_shootState)
       {
           myHero.isShooting = 1;
           myHero.shoot();
           //qDebug() << "shootSend";
       }
       else
       {
           myHero.isShooting = 0;
       }
   }

   // 更新飞机位置
   if (myHero.m_state == 0)
   {
       // 处理移动信息
       heroVector.GenerateVector();
       // 设置飞机移动到的位置
       myHero.setPosition(heroVector.Vx * (heroVector.keyMoveState[4]?2.5:1),
                          heroVector.Vy * (heroVector.keyMoveState[4]?2.5:1));
                          // 2.5为加速参数，意为机动时速度为原速度的2.5倍
   }

   // 遍历找出英雄发射的所有在场子弹，然后进行位置更新实现移动
   for (int i = 0; i < BULLET_NUMBER; i++)
   {
       // 如果非空闲，计算发射位置
       if (myHero.m_bullets[i].m_state == false)
       {
           myHero.m_bullets[i].updatePosition();
       }
   }

   // 遍历找出 BOSS 发射的所有在场子弹，然后进行位置更新实现移动
   for (int i = 0; i < BOSS_BULLET_NUM; i++)
   {
       // 如果非空闲，计算发射位置
       if (boss.m_bullets[i].m_state == false)
       {
           boss.m_bullets[i].bUpdatePosition();
       }
   }

   // 更新 BOSS 的炸弹移动
   if (boss.m_missile.m_state == false)
   {
       boss.m_missile.bombUpdatePosition();
   }

   // 遍历找出所有在场I型敌机，然后进行位置更新实现移动
   for (int i = 0; i < ENEMY_NUM; i++)
   {
       if (enemys[i].m_state == false)
       {
           enemys[i].updatePosition();
       }
   }

   // 进行I型敌机爆炸时的图片切换操作
   for (int i = 0; i < BOMB_NUM; i++)
   {
       if (bombs[i].m_state == false)
       {
           bombs[i].updateInfo();
       }
   }

   // 普通难度打开之后的操作
   if (normalMode)
   {
       // 遍历找出所有在场II型敌机，然后进行位置更新实现移动
       for (int i = 0; i < ENEMY2_NUM; i++)
       {
           if(enemys2[i].m_state == false)
           {
               enemys2[i].updatePosition();
           }
       }

       // 进行II型敌机爆炸时的图片切换操作
       for (int i = 0; i < BOMB2_NUM; i++)
       {
           if (bombs2[i].m_state == false)
           {
               bombs2[i].updateInfo();
           }
       }

       // 进行II型敌机被击中时的图片切换操作
       for (int i = 0; i < ENEMY2_NUM; i++)
       {
           if (enemys2[i].m_hitState)
           {
               enemys2[i].m_hitRecorder++;
               if (enemys2[i].m_hitRecorder >= HIT_INTERVAL)
               {
                   enemys2[i].m_img.load(ENEMY2_PATH);
                   enemys2[i].m_hitRecorder = 0;
                   enemys2[i].m_hitState = false;
               }
           }
       }
   }

   // 困难难度打开之后的操作
   if (hardMode)
   {
       // BOSS 爆炸时的切图操作
       if (bombBoss.m_state == false)
       {
           bombBoss.updateInfo();
           //qDebug() << "booming";
       }

       // BOSS 小炸弹爆炸时的切图操作
       for(int i = 0; i < BOSS_BULLET_NUM; i++)
       {
           if (bombBullet[i].m_state == false)
           {
               bombBullet[i].updateInfo();
           }
       }

       // BOSS 导弹爆炸时的切图操作
       if (bombMissile.m_state == false)
       {
           bombMissile.updateInfo();
       }

       // 进行 BOSS 被击中时的图片切换操作
       if (boss.m_hitState)
       {
           boss.m_hitRecorder++;

           if (boss.m_hitRecorder >= BOSS_HIT_INTERVAL)
           {
               boss.m_img.load(BOSS_PATH);
               boss.m_hitRecorder = 0;
               boss.m_hitState = false;
               //qDebug() << "img back";
           }
       }
   }
}


void MainWindow::paintEvent(QPaintEvent *)
{
   // startFlag 为 1 时开始绘制
   if (startFlag == 1)
   {
       QPainter painter(this);

       // 绘制地图
       painter.drawPixmap(0,gameMap.m_map1_posY,gameMap.m_map1);
       painter.drawPixmap(0,gameMap.m_map2_posY,gameMap.m_map2);

       // 绘制英雄飞机，如果没死的话
       if(myHero.m_state == 0){
           if(heroVector.keyMoveState[4] || heroVector.keyMoveState[0]){
               painter.drawPixmap(myHero.m_X, myHero.m_Y,
                                  myHero.m_img_speedup.width()/1.2, myHero.m_img_speedup.height()/1.2,
                                  myHero.m_img_speedup);
           }
           else{
               painter.drawPixmap(myHero.m_X, myHero.m_Y,
                                  myHero.m_img.width()/1.2,myHero.m_img.height()/1.2,
                                  myHero.m_img);
           }
       }

       // 绘制所有在场子弹
       for (int i = 0;i < BULLET_NUMBER;i++)
       {
           if (myHero.m_bullets[i].m_state == false)
           {
              painter.drawPixmap(myHero.m_bullets[i].m_X,
                                 myHero.m_bullets[i].m_Y,
                                 myHero.m_bullets[i].m_img.width()/1.5,
                                 myHero.m_bullets[i].m_img.height()/1.5,
                                 myHero.m_bullets[i].m_img);
           }
       }

       // 绘制所有在场I型敌机
       for (int i = 0;i < ENEMY_NUM;i++)
       {
           if (enemys[i].m_state == false)
           {
              painter.drawPixmap(enemys[i].m_X, enemys[i].m_Y,enemys[i].m_img.width() /1.5,
                                 enemys[i].m_img.height() / 1.5,enemys[i].m_img);


           }
       }

       // 绘制I型敌机爆炸
       for (int i = 0; i < BOMB_NUM; i++)
       {
           if (bombs[i].m_state == false)
           {
               painter.drawPixmap(bombs[i].m_X, bombs[i].m_Y,
                                  bombs[i].m_imgArray[bombs[i].m_imgIndex]);
                              /* 注意这里是播放 bombImgArr数组中下标为 bombImgIndex的图片，
                               * 下标在 Bomb类的 updateInfo()函数里进行更新
                               */
           }
       }

       // 普通难度打开之后的操作
       if (normalMode)
       {
           // 绘制所有在场II型敌机
           for (int i = 0;i < ENEMY2_NUM;i++)
           {
               if (enemys2[i].m_state == false)
               {
                  painter.drawPixmap(enemys2[i].m_X, enemys2[i].m_Y, enemys2[i].m_img);
               }
           }
           // 绘制II型敌机爆炸
           for (int i = 0; i < BOMB2_NUM; i++)
           {
               if (bombs2[i].m_state == false)
               {
                   painter.drawPixmap(bombs2[i].m_X, bombs2[i].m_Y,
                                      bombs2[i].m_imgArray[bombs2[i].m_imgIndex]);
               }
           }
       }

       // 绘制与 BOSS 相关的图像
       if (hardMode)
       {
           // 绘制 BOSS 与它的弹药
           for (int i = 0; i < BOSS_BULLET_NUM; i++)
           {
               if (boss.m_bullets[i].m_state == false)
               {
                   painter.drawPixmap(boss.m_bullets[i].m_X, boss.m_bullets[i].m_Y, boss.m_bullets[i].m_img);
               }
           } 

           if (boss.m_state == false)
           {
               painter.drawPixmap(boss.m_X, boss.m_Y, boss.m_img);
           }

           if (boss.m_missile.m_state == false)
           {
               painter.drawPixmap(boss.m_missile.m_X, boss.m_missile.m_Y, boss.m_missile.m_img);
           }


           // 爆炸切图操作
           for (int i = 0; i < BOSS_BULLET_NUM; i++)
           {
               if (bombBullet[i].m_state== false)
               {
                   painter.drawPixmap(bombBullet[i].m_X, bombBullet[i].m_Y, bombBullet[i].m_imgArray[bombBullet[i].m_imgIndex]);
               }

           }

           if (bombBoss.m_state == false)
           {
               painter.drawPixmap(bombBoss.m_X, bombBoss.m_Y, bombBoss.m_imgArray[bombBoss.m_imgIndex]);
           }

           if (bombMissile.m_state == false)
           {
               painter.drawPixmap(bombMissile.m_X, bombMissile.m_Y, bombMissile.m_imgArray[bombMissile.m_imgIndex]);
           }
       }

       // 绘制英雄爆炸
       if (myHero.m_state && heroBombImgIndex < BOMB_MAX)
       {
           /* 这个 heroBombImgIndex < BOMB_MAX 条件必须加！
            * 因为这个index之后会累加到 BOMB_MAX，已经超出容器容量，这时候再绘制会报错
           */
           painter.drawPixmap(heroBombX, heroBombY, heroBombImgArr[heroBombImgIndex]);
       }

       // 绘制英雄血量
       painter.drawPixmap(6, GAME_HEIGHT - 53, healthIcon.width() / 1.3,
                          healthIcon.height() / 1.3, healthIcon);

       painter.drawPixmap(100,
                          GAME_HEIGHT - 50,
                          heroHPDisp[toDisplay[2]].m_width  / 6,
                          heroHPDisp[toDisplay[2]].m_height / 6,
                          heroHPDisp[toDisplay[2]].numImg);

       painter.drawPixmap(100 - heroHPDisp[toDisplay[2]].m_width / 6 - 3,
                          GAME_HEIGHT - 50,
                          heroHPDisp[toDisplay[1]].m_width / 6,
                          heroHPDisp[toDisplay[1]].m_height / 6,
                          heroHPDisp[toDisplay[1]].numImg);

       painter.drawPixmap(100 - heroHPDisp[toDisplay[2]].m_width / 6
                              - heroHPDisp[toDisplay[1]].m_width / 6 - 6,
                          GAME_HEIGHT - 50,
                          heroHPDisp[toDisplay[0]].m_width / 6,
                          heroHPDisp[toDisplay[0]].m_height / 6,
                          heroHPDisp[toDisplay[0]].numImg);

       // 绘制弹匣
       painter.drawPixmap(GAME_WIDTH - magazineBoard.m_bulletNum->width() + 8,
                          GAME_HEIGHT - magazineBoard.m_bulletNum->height() - 28,
                          magazineBoard.m_img.width() * 1.2,
                          magazineBoard.m_img.height() * 1.2,
                          magazineBoard.m_img);
   }
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W)
    {
        heroVector.keyMoveState[0] = 1;
        //qDebug() << "UP";
    }

    if (event->key() == Qt::Key_D)
    {
        heroVector.keyMoveState[1] = 1;
    }

    if (event->key() == Qt::Key_S)
    {
        heroVector.keyMoveState[2] = 1;
    }

    if (event->key() == Qt::Key_A)
    {
        heroVector.keyMoveState[3] = 1;
    }

    if (event->key() == Qt::Key_Shift)
    {
        heroVector.keyMoveState[4] = 1;
    }

    if (event->key() == Qt::Key_J)
    {
        heroVector.m_shootState = true;
    }
    // ...添加更多按键，方法类似以上所写
}


void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        heroVector.keyMoveState[0] = 0;
    }

    if (event->key() == Qt::Key_D)
    {
        heroVector.keyMoveState[1] = 0;
    }

    if (event->key() == Qt::Key_S)
    {
        heroVector.keyMoveState[2] = 0;
    }

    if (event->key() == Qt::Key_A)
    {
        heroVector.keyMoveState[3] = 0;
    }

    if (event->key() == Qt::Key_Shift)
    {
        heroVector.keyMoveState[4] = 0;
    }

    if (event->key() == Qt::Key_J)
    {
        heroVector.m_shootState = false;
    }
    //...添加更多按键，方法类似以上所写
}


// 单独建立一个函数管理的原因是，若以后有特殊敌机的操作，则更方便配置
void MainWindow::enemyToSceneManager()
{
    if (boss.m_state)
    {
        enemyToScene();
    }

    if (normalMode && boss.m_state)
    {
        enemy2ToScene();
    }

    if (hardMode)
    {
        bossToScene();
    }
}


void MainWindow::enemyToScene()
{
    enemySpaceRec++;

    if (enemySpaceRec < ENEMY_INTERVAL * enemy_interval_index)
    {
        return;
    }

    enemySpaceRec = 0;

    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (enemys[i].m_state)
        {
            enemys[i].m_state = false;
            enemys[i].m_X = rand()%(GAME_WIDTH - enemys[i].m_rect.width());
            enemys[i].m_Y = -enemys[i].m_rect.height() - 5;
            //qDebug() << enemys[i].m_speed;
            break;
        }
    }
}


void MainWindow::enemy2ToScene()
{
    enemy2SpaceRec++;

    if (enemy2SpaceRec < ENEMY2_INTERVAL * enemy_interval_index)
    {
        return;
    }

    enemy2SpaceRec = 0;

    for (int i = 0; i < ENEMY2_NUM; i++)
    {
        if (enemys2[i].m_state)
        {
            enemys2[i].m_state = false;
            enemys2[i].m_X = rand()%(GAME_WIDTH - enemys2[i].m_rect.width());
            enemys2[i].m_Y = -enemys2[i].m_rect.height() - 5;
            break;
        }
    }
}

void MainWindow::bossToScene()
{
    // BOSS未出场时，持续更新 m_show_interval 记录间隔
    if (boss.m_state)
    {
        boss.m_show_interval = current_time - boss.m_death_time;
        //qDebug() << "Show interval: " << boss.m_show_interval;
    }

    // 达到规定时间后执行以下语句，使 BOSS 出场
    if (current_time >= BOSS_SHOW_TIME && boss.m_show_interval >= BOSS_SHOW_TIME)
    {
        if (boss.m_state)
        {
            boss.m_state = false;
            boss.m_showup_time = current_time;  // 记录 BOSS 出场时刻
            //qDebug() << "Show up: " << boss.m_showup_time;
            boss.m_show_round++;   // 已出现次数加一
            //qDebug() << "boss out, round: " << boss.m_show_round++;
        }
        boss.heroXget = myHero.m_X;
        boss.m_current_time = current_time;
        boss.bossAction();
    }
}


void MainWindow::collideCheck()
{
    // 与I型敌机发生碰撞的处理方法
    enemy1Feedback();

    if (normalMode)
    {
        // 与II型敌机发生碰撞的处理方法
        enemy2Feedback();
    }

    if (hardMode)
    {
        bossFeedback();
    }

    // 播放英雄爆炸效果
    if (myHero.m_HP <= 0)
    {
        QSound::play(SND_HERO_BLOWUP);
        myHero.m_state = 1;    // 设置状态为死亡
        heroBombX = myHero.m_X - 20;
        heroBombY = myHero.m_Y - 40;
    }
}


void MainWindow::enemy1Feedback()
{
    // 遍历非空闲敌机
    for (int i = 0; i<ENEMY_NUM; i++)
    {
        // 如果英雄被摧毁 直接跳出该函数
        if (myHero.m_HP <= 0)
        {
            return;
        }

        if (enemys[i].m_state)
        {
            continue;
        }

        // 遍历非空闲子弹
        for (int j = 0; j<BULLET_NUMBER; j++)
        {
            if (myHero.m_bullets[j].m_state)
            {
                continue;
            }

            // 若发生碰撞，则将子弹空闲状态设置为真
            if (enemys[i].m_rect.intersects(myHero.m_bullets[j].m_rect))
            {
                myHero.m_bullets[j].m_state = true;
                enemys[i].m_HP -= myHero.m_bullets[j].m_damage;
                QSound::play(SND_ENEMY_BLOWUP);

                // 敌机被摧毁后进行以下操作
                if (enemys[i].m_HP <= 0)
                {
                    enemys[i].m_state = true;
                    enemys[i].m_HP = ENEMY_HP;   // 血量重置
                    myHero.m_score += enemys[i].m_scoreValue;

                    // 播放爆炸效果
                    for (int k = 0; k < BOMB_NUM; k++)
                    {
                        if (bombs[k].m_state)  // 寻找一个空闲的爆炸
                        {
                            bombs[k].m_state = false;
                            // 更新爆炸坐标
                            bombs[k].m_X = enemys[i].m_X +
                                          (enemys[i].m_img.width()
                                           - bombs[k].m_imgArray[bombs[k].m_imgIndex].width()) / 2 - 20;
                            bombs[k].m_Y = enemys[i].m_Y +
                                          (enemys[i].m_img.height()
                                           - bombs[k].m_imgArray[bombs[k].m_imgIndex].height()) / 2 + 10;
                            break;
                        }
                    }
                }
            }
        }

        // 敌机和英雄碰撞后英雄扣血
        if (enemys[i].m_rect.intersects(myHero.m_rect) && myHero.m_state == 0)
        {
            enemys[i].m_state = true;
            myHero.m_HP -= enemys[i].m_col_Atk; // 英雄扣血
            //qDebug() << "-20HP";

            // 敌机撞到英雄后爆炸
            for (int k = 0; k < BOMB_NUM; k++)
            {
                if (bombs[k].m_state)  // 寻找一个空闲的爆炸
                {
                    QSound::play(SND_ENEMY_BLOWUP);
                    bombs[k].m_state = false;
                    // 更新爆炸坐标
                    bombs[k].m_X = enemys[i].m_X;
                    bombs[k].m_Y = enemys[i].m_Y;
                    break;
                }
            }
        }
    }
}


void MainWindow::enemy2Feedback()
{
    // 遍历非空闲敌机
    for (int i = 0; i<ENEMY2_NUM; i++)
    {
        //如果英雄被摧毁 直接跳出该函数
        if (myHero.m_HP <= 0)
        {
            return;
        }

        if (enemys2[i].m_state)
        {
            continue;
        }

        // 遍历非空闲子弹
        for (int j = 0; j<BULLET_NUMBER;j++)
        {
            if (myHero.m_bullets[j].m_state)
            {
                continue;
            }

            // 若发生碰撞，则将子弹空闲状态设置为真
            if (enemys2[i].m_rect.intersects(myHero.m_bullets[j].m_rect))
            {
                myHero.m_bullets[j].m_state = true;
                enemys2[i].m_HP -= myHero.m_bullets[j].m_damage;
                QSound::play(SND_ENEMY_BLOWUP);

                // 敌机被摧毁后进行以下操作
                if (enemys2[i].m_HP <= 0)
                {
                    enemys2[i].m_state = true;
                    enemys2[i].m_HP = ENEMY2_HP;   // 血量重置
                    myHero.m_score += enemys2[i].m_scoreValue;
                    // 播放爆炸效果
                    for (int k = 0; k < BOMB_NUM; k++)
                    {
                        if (bombs2[k].m_state)  // 寻找一个空闲的爆炸
                        {
                            bombs2[k].m_state = false;
                            // 更新爆炸坐标
                            bombs2[k].m_X = enemys2[i].m_X;
                            bombs2[k].m_Y = enemys2[i].m_Y;
                            break;
                        }
                    }
                }
                // 若这一发子弹未摧毁，则播放被击中动画
                else
                {
                    enemys2[i].m_img.load(ENEMY2_HIT_PATH);
                    enemys2[i].m_hitState = true;
                    enemys2[i].m_hitRecorder = 0;   // 细节，每次被打中计时器都要清零！
                }
            }
        }

        // 敌机和英雄碰撞后英雄扣血
        if (enemys2[i].m_rect.intersects(myHero.m_rect) && myHero.m_state == 0)
        {
            enemys2[i].m_state = true;
            myHero.m_HP -= enemys2[i].m_col_Atk; // 英雄扣血
            //qDebug() << "-50HP";

            // 敌机撞到英雄后爆炸
            for (int k = 0; k < BOMB2_NUM; k++)
            {
                if (bombs2[k].m_state)  // 寻找一个空闲的爆炸
                {
                    QSound::play(SND_ENEMY_BLOWUP);
                    bombs2[k].m_state = false;
                    // 更新爆炸坐标
                    bombs2[k].m_X = enemys2[i].m_X +
                                   (enemys2[i].m_img.width()
                                    - bombs2[k].m_imgArray[bombs2[k].m_imgIndex].width()) / 2;
                    bombs2[k].m_Y = enemys2[i].m_Y +
                                   (enemys2[i].m_img.height()
                                    - bombs2[k].m_imgArray[bombs2[k].m_imgIndex].height()) / 2;;
                    break;
                }
            }
        }
    }
}

void MainWindow::bossFeedback()
{
    //如果英雄或者 BOSS 被摧毁 直接跳出该函数
    if (myHero.m_HP <= 0 || boss.m_state)
    {
        return;
    }

    /************* 英雄子弹打到 BOSS 的处理方法 *************/
    // 遍历非空闲子弹
    for (int j = 0; j < BULLET_NUMBER; j++)
    {
        if (myHero.m_bullets[j].m_state)
        {
            continue;
        }

        // 若发生碰撞，则将子弹空闲状态设置为真
        if (boss.m_rect.intersects(myHero.m_bullets[j].m_rect))
        {
            myHero.m_bullets[j].m_state = true;
            boss.m_HP -= myHero.m_bullets[j].m_damage;
            QSound::play(SND_ENEMY_BLOWUP);

            // BOSS 被摧毁后进行以下操作
            if (boss.m_HP <= 0)
            {
                myHero.m_score += boss.m_scoreValue;

                // 播放爆炸效果
                bombBoss.m_state = false;
                // 更新爆炸坐标
                bombBoss.m_X = boss.m_X;
                bombBoss.m_Y = boss.m_Y;

                boss.afterDeath();
            }
            // 若这一发子弹未摧毁，则播放被击中动画
            else
            {
                boss.m_img.load(BOSS_HIT_PATH);
                boss.m_hitState = true;
                boss.m_hitRecorder = 0;
            }
        }
    }

    /************* BOSS 子弹 和 导弹打到英雄的处理方法 *************/
    // 遍历 BOSS 发射的子弹
    for (int i = 0; i < BOSS_BULLET_NUM; i++)
    {
        if (boss.m_bullets[i].m_state)
        {
            continue;
        }

        if (boss.m_bullets[i].m_rect.intersects(myHero.m_rect))
        {
            //qDebug() << "crashed";
            boss.m_bullets[i].m_state = true;
            bombBullet[i].m_state = false;
            bombBullet[i].m_X = boss.m_bullets[i].m_X;
            bombBullet[i].m_Y = boss.m_bullets[i].m_Y;
            myHero.m_HP -= boss.m_bullets[i].m_damage;
            QSound::play(BOSS_BULLET_COL_SND);
        }
    }

    if (boss.m_missile.m_state == false)
    {
        if (boss.m_missile.m_rect.intersects(myHero.m_rect))
        {
            boss.m_missile.m_state = true;
            bombMissile.m_state = false;
            bombMissile.m_X = boss.m_missile.m_X;
            bombMissile.m_Y = boss.m_missile.m_Y;
            myHero.m_HP -= boss.m_missile.m_damage;
            QSound::play(BOSS_MISSILE_COL_SND);
        }
    }

}

void MainWindow::afterHeroBoom()
{
    heroBombSpcRec++;

    // 如果爆炸时间间隔未达预设时间，则不需切图，直接return
    if (heroBombSpcRec < HERO_BOMB_INTERVAL)
    {
        return;
    }

    heroBombSpcRec = 0;  // 计数器重置
    heroBombImgIndex++;

    if (heroBombImgIndex > BOMB_MAX - 1)
    {
        bg_music->stop();   // 英雄飞机摧毁后停止音乐
        m_Timer.stop();
        bk.show();  // 返回按钮显示

        /****** 显示最终得分 ******/
        scoreBoard.m_des_text->setText("最终得分");
        scoreBoard.m_des_text->setStyleSheet("font-family:幼圆;color:white;"
                                             "font-size:32px; font:bold;");
        scoreBoard.m_des_text->move((GAME_WIDTH - scoreBoard.m_des_text->width()) / 2,
                                    (GAME_HEIGHT - scoreBoard.m_des_text->height()) / 2 - 60);
        scoreBoard.m_scoreLCD->resize(250, 120);
        scoreBoard.m_scoreLCD->move((GAME_WIDTH - scoreBoard.m_scoreLCD->width()) / 2,
                                    (GAME_HEIGHT - scoreBoard.m_scoreLCD->height()) / 2 + 20);
        /*************************/

    }

    // 暂停/继续按钮隐藏
    pause.hide();
    goon.hide();
}


void MainWindow::hpFeedback()
{
    if (myHero.m_HP < 0)
    {
        myHero.m_HP = 0;
    }

    int HP = myHero.m_HP;
    int i = 2;   // 当前位数，从左往右递增，有第0 1 2位

    // 将整形数HP转化为字符串 并找到所需显示的三个数字对象
    while (i >= 0) // !!!控制条件必须是i>=0而不是HP>0，因为HP只有两位数时只会循环两次 百位数不会更新！
    {
        for (int k = 0; k <= 9; k++)
        {
            if (HP % 10 == heroHPDisp[k].numIndex)
            {
                toDisplay[i--] = heroHPDisp[k].numIndex;
            }
        }
        HP /= 10;
    }
}








