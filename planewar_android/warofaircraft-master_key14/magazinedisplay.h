#ifndef MAGAZINEDISPLAY_H
#define MAGAZINEDISPLAY_H

#include <QPixmap>
#include <QLCDNumber>
#include "config.h"


class MagazineDisplay
{
public:
    MagazineDisplay();


public:
    QPixmap m_img;
    QLCDNumber *m_bulletNum = new QLCDNumber;
};

#endif // MAGAZINEDISPLAY_H
