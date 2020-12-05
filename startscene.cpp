#include "startscene.h"
#include "ui_startscene.h"

using namespace std;

StartScene::StartScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartScene)
{
    ui->setupUi(this);

    //创建选择窗口
    this->chooseScene = new ChooseScene;

    connect(ui->actionExit,&QAction::triggered,[=](){
        this->close();
    });

    //创建设置窗口
    this->setting = new BgmSetting(this);
    //将各个能打开设置窗口的窗口与设置窗口绑起来
    setting->testMake = chooseScene->_testCreateScene();
    setting->exeScene = chooseScene->_exeInitSetting()->get_exeScene();
    setting->exeReport = chooseScene->_exeReport();
    //监听信号
    connect(setting->exeScene,&ExerciseScene::open_setting,[=](){
        setting->show();
    });
    connect(setting->exeReport,&ExerciseReport::open_setting,[=](){
        setting->show();
    });
    connect(setting->testMake,&TestCreate::open_setting,[=](){
        setting->show();
    });


    connect(ui->actionBgm_Bg_Setting,&QAction::triggered,[=](){
        setting->show();
    });



    //创建开始按钮
    _PushButton * startBtn = new _PushButton(":/res/MenuSceneStartButton.png");

    startBtn->setParent(this);
    startBtn->move(this->width()*0.4,this->height()*0.6);


    //连接信号
    connect(startBtn,&_PushButton::clicked,[=](){
        startBtn->effect_up();

        QTimer::singleShot(500,[=](){

            startBtn->effect_down();

            this->hide();
            giveLog("StartScene","成功隐藏开始场景","yellow","window_change");

            chooseScene->move(this->x(),this->y());
            chooseScene->show();

            giveLog("StartScene","成功显示选择场景","yellow","window_change");

        });
    });

    //监听选择场景的返回信号
    connect(chooseScene,&ChooseScene::back_to_start,[=](){
        this->move(chooseScene->x(),chooseScene->y());
        this->show();

        giveLog("StartScene","成功返回到开始场景","yellow","window_change");
    });

    //帮助窗口
    connect(ui->actionHelp,&QAction::triggered,[=](){
        helpWidget::show_help(nullptr);
    });
}

StartScene::~StartScene()
{
    delete ui;
}

void StartScene::paintEvent(QPaintEvent *){
    static bool first_load = true;

    //创建位图
    QPixmap * pix = new QPixmap(":/res/bg.jpg");
    //创建画家
    QPainter * painter = new QPainter(this);
    //画背景
    painter->drawPixmap(0,0,this->width(),this->height(),*pix);

    if(first_load) { giveLog("StartScene","成功加载背景！"); }


    //创建字体
    QFont * font =  new QFont("黑体",18,QFont::Bold,true);
    font->setUnderline(true);
    font->setOverline(true);
    font->setLetterSpacing(QFont::AbsoluteSpacing,5);
    //写文字
    painter->setFont(*font);
    painter->setPen(Qt::darkCyan);
    painter->drawText(30,60,QString("ENJOY JAPANESE"));

    if(first_load) { giveLog("ChooseScene","成功加载标题！"); }


    //释放内存
    delete pix;
    pix = nullptr;
    delete painter;
    painter = nullptr;

    if(first_load) { giveLog("StartScene","成功释放内存！","black","heap"); }

    first_load  = false;
}

void StartScene::closeEvent(QCloseEvent * ev) {
    giveLog("StartScene","拦截到退出信号");

    if(QMessageBox::question(this,"Are u sure to leave?","欧尼酱不再享受一下日本语给您带来的放松么") == QMessageBox::Yes)  {
        giveLog("StartScene","放弃退出程序","yellow");
        ev->ignore();
    }
    else  {
        giveLog("StartScene","成功退出程序","cyan","system");
        ev->accept();
        exit(EXIT_SUCCESS);
    }
}

