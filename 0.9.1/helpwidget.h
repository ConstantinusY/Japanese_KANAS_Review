#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>

namespace Ui {
class helpWidget;
}

class helpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit helpWidget(QWidget *parent = nullptr);
    ~helpWidget();

    static void show_help(QWidget* parent);

    static void end_help(helpWidget* hw);

    void closeEvent(QCloseEvent *event);

private:
    Ui::helpWidget *ui;
};

#endif // HELPWIDGET_H
