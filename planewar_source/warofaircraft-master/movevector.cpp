#include "movevector.h"


MoveVector::MoveVector()
{
    for (int i = 0; i < 5; i++)
    {
        keyMoveState[i] = 0;
    }

    setVectorZero();
    m_shootState = 0;  // 初始化子弹发射状态
}


void MoveVector::setVectorZero()
{
    Vx = 0;
    Vy = 0;
}


void MoveVector::GenerateVector()
{
    setVectorZero();

    if (keyMoveState[0])
    {
        Vy -= qreal(1.0);
    }
    if (keyMoveState[1])
    {
        Vx += qreal(1.0);
    }
    if (keyMoveState[2])
    {
        Vy += qreal(1.0);
    }
    if (keyMoveState[3])
    {
        Vx -= qreal(1.0);
    }

    qreal len = sqrt(Vx * Vx + Vy * Vy);

    // 向量归一化
    if (len != qreal(0.0))
    {
        Vx = Vx / len;
        Vy = Vy / len;
    }
}

void MoveVector::setKeyInputZero()
{
    for (int i = 0; i < 5; i++)
    {
        keyMoveState[i] = 0;
    }

    m_shootState = 0;
}
