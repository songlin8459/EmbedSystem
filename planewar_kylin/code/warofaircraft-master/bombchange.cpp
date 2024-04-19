#include "bombchange.h"


BombChange::BombChange()
{
    m_X = 0;
    m_Y = 0;
    m_state = true;
    m_imgIndex = 0;
    m_spaceRec = 0;
}


void BombChange::setBombImg(QString img)
{
    for (int i = 1; i <= BOMB_MAX; i++)
    {
        //这一句利用了占位符和拼接字符串 比较重要，以后切换飞机种类和爆炸效果会用到，比较便捷
        QString str = QString (img).arg(i);
        m_imgArray.push_back(QPixmap(str));
    }
}


void BombChange::updateInfo()
{
    //空闲状态下爆炸直接return
    if (m_state)
    {
        return;
    }

    m_spaceRec++;

    //如果爆炸时间间隔未达预设时间，则不需切图，直接return
    if (m_spaceRec < BOMB_INTERVAL)
    {
        return;
    }

    m_spaceRec = 0; //计数器重置
    m_imgIndex++;   //切换爆炸图片下标

    if (m_imgIndex > BOMB_MAX - 1)
    {
        m_imgIndex = 0;
        m_state = true;
    }
}

