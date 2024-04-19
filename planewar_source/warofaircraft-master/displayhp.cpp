#include "displayhp.h"


DisplayHP::DisplayHP()
{
    //这里的初始化没有意义
    m_width = 0;
    m_height = 0;
    numIndex = 0;
    numImg.load(":/res/img/NO0.png");
}
