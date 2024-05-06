#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include "config.h"
#include <QPushButton>


// 标准化按钮的样式，后续也许会添加其他效果
class GameButton : public QPushButton
{
    Q_OBJECT

public:
    GameButton(QPushButton *parent = 0);
    ~GameButton();
};

#endif // GAMEBUTTON_H
