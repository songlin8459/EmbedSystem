#include "gamebutton.h"


GameButton::GameButton(QPushButton *parent) : QPushButton(parent)
{
    resize(BUTTON_W, BUTTON_H);

    // 设定按钮图
    this->setStyleSheet("QPushButton{"
                        "border-image:url(://res/img/button_nor.png);"
                        "font-family:幼圆;"
                        "font-size:24px;"
                        "font:bold;"
                        "color:white;"
                        "}"
                        "QPushButton:pressed{"
                        "border-image:url(://res/img/button_pressed.png);"
                        "}"
                        );
}


GameButton::~GameButton()
{

}
