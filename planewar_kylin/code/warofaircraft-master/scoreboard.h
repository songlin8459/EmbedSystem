#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QLCDNumber>
#include <QLabel>
#include "config.h"


class ScoreBoard
{
public:
    ScoreBoard();


public:
    // 描述文字
    QLabel *m_des_text = new QLabel;

    // 计分板
    QLCDNumber *m_scoreLCD = new QLCDNumber;
};

#endif // SCOREBOARD_H
