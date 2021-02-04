#include "helpwidget.h"
#include "ui_helpwidget.h"
#include "QCloseEvent"

helpWidget::helpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::helpWidget)
{
    ui->setupUi(this);
}

helpWidget::~helpWidget()
{
    delete ui;
}

void helpWidget::show_help(QWidget* parent){

    static helpWidget * hw = new helpWidget(parent);
    hw->ui->output_fullVer->scroll(1,1);
    hw->show();
}

void helpWidget::end_help(helpWidget* hw){
    hw->hide();
}

void helpWidget::closeEvent(QCloseEvent * event){
    this->hide();
    event->ignore();
}
