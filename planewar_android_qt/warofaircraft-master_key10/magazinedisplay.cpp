#include "magazinedisplay.h"


MagazineDisplay::MagazineDisplay()
{
    m_img.load(MAGAZINE_PATH);
    m_bulletNum->setDigitCount(3);
    m_bulletNum->setMode(QLCDNumber::Dec);
    m_bulletNum->setSegmentStyle(QLCDNumber::Flat);
    m_bulletNum->resize(190, 80);
    m_bulletNum->move(GAME_WIDTH - 205, GAME_HEIGHT - 150);
    m_bulletNum->setStyleSheet("border: 0px;"
                               "color:white;");
}
