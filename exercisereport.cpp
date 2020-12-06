#include "exercisereport.h"
#include "ui_exercisereport.h"

ExerciseReport::ExerciseReport(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExerciseReport)
{
    ui->setupUi(this);

    usedTime = -1;

    //帮助窗口
    connect(ui->actionHelp,&QAction::triggered,[=](){
        helpWidget::show_help(nullptr);
    });

    //退出
    connect(ui->actionExit,&QAction::triggered,[=](){
        this->close();
    });


    //显示背景
    QMovie * movie = new QMovie(":/res/exeBg.gif");
    ui->showBg->setWindowFlag(Qt::WindowStaysOnBottomHint);
    ui->showBg->setMovie(movie);
    ui->showBg->setScaledContents(true);
    movie->start();
    //设置背景模糊
    auto blurEft = new QGraphicsBlurEffect(ui->showBg);
    blurEft->setBlurRadius(7);
    blurEft->setBlurHints(QGraphicsBlurEffect::QualityHint);
    ui->showBg->setGraphicsEffect(blurEft);
    giveLog("ExerciseReport","成功显示背景并设置模糊");

    //返回按钮
    _PushButton * backBtn = new _PushButton(":/res/BackButton.png",":/res/BackButtonSelected");
    backBtn->setParent(this);
    backBtn->move(580,370);

    connect(backBtn,&_PushButton::clicked,[=](){
        //延时切换窗口
        QTimer::singleShot(500,[=](){
            this->hide();
            giveLog("ExerciseReport","选择窗口成功隐藏","yellow","window_change");
            emit back_to_choose();
        });
    });

    //设置窗口
    connect(ui->actionSetting,&QAction::triggered,[=](){
        emit open_setting();
    });


}

ExerciseReport::~ExerciseReport()
{
    delete ui;
}

void ExerciseReport::closeEvent(QCloseEvent *event){
    giveLog("ExerciseReport","拦截到退出信号");

    //使用messagebox询问是否退出
    if(QMessageBox::question(this,"Are u sure to leave?","欧尼酱不再享受一下日本语给您带来的放松么") == QMessageBox::Yes)  {
        giveLog("ExerciseReport","放弃退出程序","yellow");
        event->ignore();//忽略信号，不退出
    }
    else  {
        giveLog("ExerciseReport","成功退出程序","cyan","system");
        event->accept();//接受，退出
        exit(EXIT_SUCCESS);
    }
}

void ExerciseReport::showInfo(){
    ui->outputArea1->clear();
    ui->outputArea2->clear();
    //显示内容
    ui->allKanaNumOutput->setText(QString("%1个").arg(allKanaNum));
    ui->allFalseAnsNumOutput->setText(QString("%1个").arg(allFalseKanaNum));
    ui->allRightAnsNumOutput->setText(QString("%1个").arg(allRightKanaNum));
    ui->rightAnsPercentOutput->setText(QString("%1%").arg(QString::number((float)((float)allRightKanaNum / (float)allKanaNum)*100,'f',2)));
    ui->falseAnsPercentOutput->setText(QString("%1%").arg(QString::number((float)((float)allFalseKanaNum / (float)allKanaNum)*100,'f',2)));
    for(int i = 0;i<allFalseKanaNum;i++){
        ui->outputArea1->addItem(QString("%1. %2").arg(i+1).arg(falseKanaList[i].data()));
        ui->outputArea2->addItem(QString("%1. %2：%3").arg(i+1).arg(falseKanaList[i].data()).arg(this->kana_dict.find(falseKanaList[i])->second.data()));
    }
    if(usedTime == -1){
        ui->usedTimeOutput->setText("未记录");
    }
    else{
        ui->usedTimeOutput->setText(QString("%1秒").arg(QString::number(usedTime,'f',2)));
    }
}

void ExerciseReport::setBg(QString filePath){

    ui->showBg->clear();
    QMovie * movie = new QMovie(filePath);
    ui->showBg->setMovie(movie);
    movie->start();
}
