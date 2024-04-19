#ifndef CONFIG_H
#define CONFIG_H


/**** 游戏配置数据 ****/
//代码
#define RESTART_CODE 931


/*****游戏窗口大小和标题*****/
#define GAME_WIDTH  520
#define GAME_HEIGHT 854
#define GAME_TITLE  "War of Aircraft"


//button大小
#define BUTTON_W    200
#define BUTTON_H    60


//初始化在中心点的 button坐标
#define B_MID_POSW  (GAME_WIDTH-BUTTON_W)/2
#define B_MID_POSH  (GAME_HEIGHT-BUTTON_H)/2


//定时器刷新时间间隔 单位:毫秒
#define GAME_RATE   15


/*****图标加载路径*****/
#define GAME_ICON   ":/res/img/icon_launcher.png"

/*****界面图片路径*****/
#define NUMBER_IMG ":/res/img/NO%1.png"
#define TITLE_IMG ":/res/img/title.png"
#define BG_IMG ":/res/img/bg.jpg"


/**** 地图配置数据 ****/
#define MAP_PATH    ":/res/img/bg.jpg"
#define MAP_SCROLL_SPEED 2  // 滚动速度--2像素


/**** 玩家飞机配置数据 ****/
#define MYHERO_PATH ":/res/img/herostill.png"  // 静止的飞机路径
#define MYHERO_SPEEDUP_PATH ":/res/img/heromove.png"
#define MYHERO_HPICON ":/res/img/blood.png"
#define HERO_HP 100
#define HERO_SPEED 4  // 玩家飞机移动速度


/**** 子弹配置数据 ****/
#define BULLET_PATH ":/res/img/bullet.png"  // 子弹图片
#define BULLET_SPEED 6   // 子弹速度
#define BULLET_NUMBER 30  // 同时存在的子弹总数量
#define BULLET_SPACE 20  // 发射时间间隔(单位: 计时器)
#define BULLET_DAMAGE 25  // 子弹伤害
#define MAGAZINE_PATH ":/res/img/BulletCounterIcon.png" // 弹匣图片
#define HERO_MAGAZINE 40  // 弹匣中子弹数量
#define SUPPLY_INTERVAL 75  // 停止射击时间达到此间隔后才能开始补充弹药
#define SUP_SPEED_LMT 8  // 补充每发弹药的速度限制


/**** 敌机配置数据 ****/
#define ENEMY_PATH  ":/res/img/enemy1.png"
#define ENEMY_SPEED 4
#define ENEMY_NUM   20
#define ENEMY_INTERVAL 40
#define ENEMY_COL_ATK 20
#define ENEMY_VALUE 10
#define ENEMY_HP 20

#define ENEMY2_PATH ":/res/img/enemy2.png"
#define ENEMY2_HIT_PATH ":/res/img/enemy2_hit.png"
#define ENEMY2_SPEED 3
#define ENEMY2_NUM   5
#define ENEMY2_INTERVAL 200
#define ENEMY2_COL_ATK 50
#define ENEMY2_VALUE 25
#define ENEMY2_HP 50

#define BOSS_PATH   ":/res/img/enemy3.png"
#define BOSS_HIT_PATH ":/res/img/enemy3_hit.png"
#define BOSS_HIT_INTERVAL 10
#define BOSS_SPEED 2
#define BOSS_COL_ATK 1000
#define BOSS_VALUE 300
#define BOSS_HP 500
#define BOSS_SHOW_TIME 15000    // BOSS每次出场需间隔的时间(单位: 毫秒)
#define BOSS_SHOOT_INTERVAL 300    // BOSS发射子弹间隔(单位: 计时器)

#define BOSS_BULLET_INTERVAL 60    // BOSS每轮射击中子弹间隔(单位: 计时器)
#define BOSS_BULLET_NUM 20     // BOSS最多同时存在的子弹数量
#define BOSS_BULLET_ROUND 4    // BOSS每轮发射子弹次数，最后一次是炸弹投掷
#define BOSS_BULLET_PATH ":/res/img/boss_bullet.png"    // BOSS子弹图片
#define BOSS_BULLET_SPEED 3    // 子弹速度
#define BOSS_BULLET_DMG 25    // 子弹伤害
#define BOSS_BULLET_OUT_SND ":/res/sounds/boss_bullet_out.wav"
#define BOSS_BULLET_COL_SND ":/res/sounds/boss_bullet_collided.wav"

#define BOSS_MISSILE_PATH ":/res/img/boss_bomb.png"    // BOSS炸弹图片
#define BOSS_MISSILE_SPEED 4   // 炸弹速度
#define BOSS_MISSILE_DMG 80   // 炸弹伤害
#define BOSS_MISSILE_COL_SND ":/res/sounds/boss_bomb_collided.wav"

#define HIT_INTERVAL 20
#define DIR_CHANGE_LIMIT 50


/**** 爆炸配置数据 ****/
#define BOMB_PATH   ":/res/img/boom%1.png"      // 小飞机爆炸切图
#define BOMB2_PATH  ":/res/img/boom2_%1.png"    // 中飞机爆炸切图
#define BOSS_EXPLODE_PATH  ":/res/img/bossboom_%1.png"  // BOSS 爆炸切图
#define HERO_BOMB_PATH ":/res/img/heroboom%1.png"       // 英雄爆炸切图
#define BOMB_BOSS_BULLET  ":/res/img/bb_boom%1.png"    // BOSS 子弹爆炸切图
#define BOMB_BOSS_MISSILE ":/res/img/mis_boom%1.png"    // BOSS 导弹爆炸切图
#define BOMB_NUM    20  // 敌机同时可发生的爆炸数量
#define BOMB2_NUM   5
#define BOMB_MAX    10   // 即爆炸图片数量
#define BOMB_INTERVAL 10
#define HERO_BOMB_INTERVAL 10


/**** 音效配置数据 ****/
#define SND_BG    ":/res/sounds/bg_music.wav"
#define SND_ENEMY_BLOWUP ":/res/sounds/enemy_blowup.wav"
#define SND_HERO_BLOWUP ":/res/sounds/hero_blowup.wav"

#endif // CONFIG_H
