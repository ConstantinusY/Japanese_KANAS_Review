#pragma once

#include <QPushButton>
#include <QAnimationDriver>
#include <QPropertyAnimation>

class _PushButton : public QPushButton
{
    Q_OBJECT
public:

    QString normalImagePath;
    QString pressedImagePath;

    _PushButton( QString normalImage, QString PressedImage = "");

    void setImagePath( QString np, QString pp = "");
    void effect_down(); //向下弹
    void effect_up();   //向上弹

    void mousePressEvent(QMouseEvent * e);

    void mouseReleaseEvent(QMouseEvent * e);
};
