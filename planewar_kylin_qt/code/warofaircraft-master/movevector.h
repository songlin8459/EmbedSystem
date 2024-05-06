#ifndef MOVEVECTOR_H
#define MOVEVECTOR_H

#include "config.h"
#include <QtMath>


class MoveVector
{
public:
    MoveVector();

    void setVectorZero();

    void GenerateVector();

    // 返回菜单用，防止出现一些已知的bug
    void setKeyInputZero();


public:
    bool keyMoveState[5];
    /* 下标:  0:Up  1:Right  2:Down  3:Left  4:快速机动
     * 值:  0:未按下  1:按下
    */

    bool m_shootState; // 由键盘控制的射击状态

    qreal Vx;
    qreal Vy;
};

#endif // MOVEVECTOR_H
