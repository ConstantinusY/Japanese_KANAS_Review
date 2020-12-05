#include "_pushbutton.h"
#include "LogOperation.h"


_PushButton::_PushButton( QString normalImage, QString PressedImage)
{
    //保存住正常显示路径和选中显示路径
    this->normalImagePath = normalImage;
    this->pressedImagePath = PressedImage;

    QPixmap pix;
    if(!pix.load( this->normalImagePath ))  {
        giveLog( "_PushButton",(((QString("error: 图片加载失败！ path:%1")).arg(this->normalImagePath)).toUtf8().data()));
        return;
    }

    this->setFixedSize(pix.width(),pix.height());

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图片
    this->setIcon(pix);

    //设置图片大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}

void _PushButton::effect_down(){
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    //设定时间间隔
    animation->setDuration(200);

    //设置动态对象起始位置
    animation->setStartValue(QRect( this->x(),this->y(),this->width(),this->height() ));

    //设置动画对象结束位置
    animation->setEndValue(QRect( this->x(),this->y() + 10,this->width(),this->height() ));

    //设置缓和曲线，弹跳效果
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}

void _PushButton::effect_up(){
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    //设定时间间隔
    animation->setDuration(200);

    //设置动态对象起始位置
    animation->setStartValue(QRect( this->x(),this->y()+10,this->width(),this->height() ));

    //设置动画对象结束位置
    animation->setEndValue(QRect( this->x(),this->y(),this->width(),this->height() ));

    //设置缓和曲线，弹跳效果
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();
}

void _PushButton::mousePressEvent(QMouseEvent * e)
{
    if(this->pressedImagePath != "") //传入选中后路径不为空，选中后进行图片切换
    {
        QPixmap pix;
        if(!pix.load(this->pressedImagePath))
        {
            giveLog("_PushButton","图片加载失败","red","error");
            return;
        }

        this->setFixedSize(pix.width(),pix.height());

        this->setStyleSheet("QPushButton{border:0px}");

        this->setIcon(pix);

        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    QPushButton::mousePressEvent(e);

}

void _PushButton::mouseReleaseEvent(QMouseEvent * e)
{
    if(this->pressedImagePath != "") //传入选中后路径不为空，选中后进行图片切换
    {
        QPixmap pix;
        if(!pix.load(this->normalImagePath))
        {
            giveLog("_PushButton","图片加载失败","red","error");
            return;
        }

        this->setFixedSize(pix.width(),pix.height());

        this->setStyleSheet("QPushButton{border:0px}");

        this->setIcon(pix);

        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    QPushButton::mouseReleaseEvent(e);
}

void _PushButton::setImagePath( QString np, QString pp)  {
    this->normalImagePath = np;
    this->pressedImagePath = pp;

    QPixmap pix;
    if(!pix.load( this->normalImagePath ))  {
        giveLog( "_PushButton",(((QString("error: 图片加载失败！ path:%1")).arg(this->normalImagePath)).toUtf8().data()));
        return;
    }

    this->setIcon(pix);

}
