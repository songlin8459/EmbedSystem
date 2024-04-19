#include "magazinedisplay.h"


MagazineDisplay::MagazineDisplay()
{
    m_img.load(MAGAZINE_PATH);
    m_bulletNum->setDigitCount(3);
    m_bulletNum->setMode(QLCDNumber::Dec);
    m_bulletNum->setSegmentStyle(QLCDNumber::Flat);
    m_bulletNum->resize(100, 40);
    m_bulletNum->move(GAME_WIDTH - 95, GAME_HEIGHT - 50);
    m_bulletNum->setStyleSheet("border: 0px;"
                               "color:white;");
}
