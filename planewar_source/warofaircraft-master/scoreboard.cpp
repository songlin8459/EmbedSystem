#include "scoreboard.h"


ScoreBoard::ScoreBoard()
{
    // 描述文字
    m_des_text->setText("得分: ");
    m_des_text->resize(135, 40);
    m_des_text->move(GAME_WIDTH - 200, 10);
    m_des_text->setStyleSheet("font-family:幼圆;"
                            "font-size:24px;"
                            "color:white;"
                            "font:bold;");

    // 设置计分板参数
    m_scoreLCD->setDigitCount(6);
    m_scoreLCD->setMode(QLCDNumber::Dec);
    m_scoreLCD->setSegmentStyle(QLCDNumber::Flat);
    m_scoreLCD->resize(120, 40);
    m_scoreLCD->move(GAME_WIDTH - 130, 10);
    m_scoreLCD->setStyleSheet("border: 0px;"
                              "color:white;");
}
