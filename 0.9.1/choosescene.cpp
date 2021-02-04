#include "choosescene.h"
#include "ui_choosescene.h"

ChooseScene::ChooseScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseScene)
{
    ui->setupUi(this);


    //创建练习设置场景
    this->exeInit = new exeInitSetting;

    //创建问卷场景
    this->testCreateScene = new TestCreate;

    //创建报告窗口并设定
    this->exeReport = new ExerciseReport;
    exeInit->get_exeScene()->set_exeReport(this->exeReport);

    //选择练习
    connect(ui->exercise_mode,&QCommandLinkButton::clicked,[=](){
        //延时切换窗口
        QTimer::singleShot(300,[=](){
            this->hide();
            giveLog("ChooseScene","选择窗口成功隐藏","yellow","window_change");
            exeInit->move(this->x(),this->y());
            this->exeInit->show();
            giveLog("ChooseScene","成功显示练习场景","yellow","window_change");
        });
    });

    //选择问卷
    connect(ui->test_create_mode,&QCommandLinkButton::clicked,[=](){
        //延时切换窗口
        QTimer::singleShot(300,[=](){
            this->hide();
            giveLog("ChooseScene","选择窗口成功隐藏","yellow","window_change");
            testCreateScene->move(this->x(),this->y());
            this->testCreateScene->show();
            giveLog("ChooseScene","成功显示问卷生成场景","yellow","window_change");
        });
    });

    //返回按钮
    _PushButton * backBtn = new _PushButton(":/res/BackButton.png",":/res/BackButtonSelected");
    backBtn->setParent(this);
    backBtn->move(350,250);

    connect(backBtn,&_PushButton::clicked,[=](){
        //延时切换窗口
        QTimer::singleShot(500,[=](){
            this->hide();
            giveLog("ChooseScene","选择窗口成功隐藏","yellow","window_change");
            emit back_to_start();
        });
    });

    //监听问卷场景的返回信号
    connect(testCreateScene,&TestCreate::back_to_chooseScene,[=](){
        QTimer::singleShot(300,[=](){
            this->move(testCreateScene->x(),testCreateScene->y());
            this->show();
            giveLog("ChooseScene","成功返回到选择场景","yellow","window_change");
        });
    });

    //监听设置练习场景的返回信号
    connect(exeInit,&exeInitSetting::back_to_chooseScene,[=](){
        QTimer::singleShot(300,[=](){
            this->move(exeInit->x(),exeInit->y());
            this->show();
            giveLog("ChooseScene","成功返回到选择场景","yellow","window_change");
        });
    });

    //监听练习报告的返回信号
    connect(exeReport,&ExerciseReport::back_to_choose,[=](){
        QTimer::singleShot(300,[=](){
            this->move(exeReport->x(),exeReport->y());
            this->show();
            giveLog("ChooseScene","成功返回到选择场景","yellow","window_change");
        });
    });
}

ChooseScene::~ChooseScene()
{
    delete ui;
}

void ChooseScene::paintEvent(QPaintEvent *)  {
    static bool first_load = true;

    //创建位图
    QPixmap * pix = new QPixmap(":/res/bg.jpg");
    //创建画家
    QPainter * painter = new QPainter(this);
    //画背景
    painter->drawPixmap(0,0,this->width(),this->height(),*pix);

    if(first_load) { giveLog("ChooseScene","成功加载背景！"); }

    //释放内存
    delete pix;
    pix = nullptr;
    delete painter;
    painter = nullptr;

    if(first_load) { giveLog("ChooseScene","成功释放内存！","black","heap"); }

    first_load  = false;
}

void ChooseScene::closeEvent(QCloseEvent *event)  {
    giveLog("ChooseScene","拦截到退出信号");

    //使用messagebox询问是否退出
    if(QMessageBox::question(this,"Are u sure to leave?","欧尼酱不再享受一下日本语给您带来的放松么") == QMessageBox::Yes)  {
        giveLog("ChooseScene","放弃退出程序","yellow");
        event->ignore();//忽略信号，不退出
    }
    else  {
        giveLog("ChooseScene","成功退出程序","cyan","system");
        event->accept();//接受，退出
        exit(EXIT_SUCCESS);
    }
}

TestCreate * ChooseScene::_testCreateScene(){
    return this->testCreateScene;
}

exeInitSetting * ChooseScene::_exeInitSetting(){
    return this->exeInit;
}

ExerciseReport * ChooseScene::_exeReport(){
    return this->exeReport;
}
