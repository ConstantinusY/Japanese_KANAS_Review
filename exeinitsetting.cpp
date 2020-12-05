#include "exeinitsetting.h"
#include "ui_exeinitsetting.h"
#include <sstream>

bool isNum(string str)
{
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d))
    {
        return false;
    }
    if (sin >> c)
    {
        return false;
    }
    return true;
}

exeInitSetting::exeInitSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::exeInitSetting)
{
    ui->setupUi(this);

    //创建练习场景
    this->exeScene = new ExerciseScene;

    //返回按钮
    _PushButton * backBtn = new _PushButton(":/res/BackButton.png",":/res/BackButtonSelected");
    backBtn->setParent(this);
    backBtn->move(290,390);

    connect(backBtn,&_PushButton::clicked,[=](){
        //延时切换窗口
        QTimer::singleShot(500,[=](){
            this->hide();
            giveLog("ExerciseInitSetting","设置练习窗口成功隐藏","yellow","window_change");
            emit back_to_chooseScene();
        });
    });

    //设置强制提交等待时间限制

    QRegExp rx("^(60|[1-8]?\\d(\\.\\d{1,4})?)$");
    QRegExpValidator *pReg = new QRegExpValidator(rx, this);
    ui->FGAwaitTimeInput->setValidator(pReg);

    //当按下确认按钮时进行初始化
    connect(ui->confirm,&QPushButton::clicked,[=](){

       int exeTime = -1;
       if(ui->exeTimeInput->text() != "" && isNum(ui->exeTimeInput->text().toStdString())){
           if(stoi(ui->exeTimeInput->text().toStdString()) > 0 ){
               exeTime = stoi((ui->exeTimeInput->text()).toStdString());
           }
       }


       map<string,string>*temp_kanas = nullptr;
       bool RUT = ui->recordUsedTime->checkState() == Qt::Checked;
       bool FGA = ui->FGA->checkState() == Qt::Checked;
       float FGAWT = stof((ui->FGAwaitTimeInput->text()).toStdString());


       //完成假名列表
       string kanaScopeConfig = ""; //选择的假名

       vector<map<string,string>>*kanaVec= new vector<map<string,string>>;

       if(ui->A1->checkState() == Qt::Checked) {
           kanaScopeConfig += "平假名清音部分  ";
           kanaVec->push_back(*AllKanas::A1);
       }
       if(ui->A2->checkState() == Qt::Checked) {
           kanaScopeConfig += "平假名浊音部分  ";
           kanaVec->push_back(*AllKanas::A2);
       }
       if(ui->A3->checkState() == Qt::Checked) {
           kanaScopeConfig += "平假名拗音部分  ";
           kanaVec->push_back(*AllKanas::A3);
       }
       if(ui->B1->checkState() == Qt::Checked) {
           kanaScopeConfig += "片假名清音部分  ";
           kanaVec->push_back(*AllKanas::B1);
       }
       if(ui->B2->checkState() == Qt::Checked) {
           kanaScopeConfig += "片假名浊音部分  ";
           kanaVec->push_back(*AllKanas::B2);
       }
       if(ui->B3->checkState() == Qt::Checked) {
           kanaScopeConfig += "片假名拗音部分  ";
           kanaVec->push_back(*AllKanas::B3);
       }

       COMBINE_KANA_LIST:

       temp_kanas = new map<string,string>(AllKanas::combineMaps(*kanaVec));

       map<bool,string>boolToStr = {
           {true,"√"}, {false,"×"}
       };

       vector<string>randKanas = {};
       for(auto it = temp_kanas->begin() ; it != temp_kanas->end() ; it++){
           randKanas.push_back(it->first);
       }
       random_shuffle(randKanas.begin(),randKanas.end());

       CONFIRM_SETTING:

       if (QMessageBox::question(this,"确认设置？",QString("您的设置：\n练习轮数：%1\n假名范围：%2\n是否记录用时：%3\n是否强制提交答案：%4\n强制提交等待时间：%5秒").arg(exeTime).arg(kanaScopeConfig.data()).arg(boolToStr.find(RUT)->second.data()).arg(boolToStr.find(FGA)->second.data()).arg(FGAWT)) == QMessageBox::Yes){

           //首先判断是否有违规输入
           if(exeTime < 1 ){
               QMessageBox::warning(this,"输入违规","您输入的轮数小于1\n已设置为1轮");
               exeTime = 1;
               ui->exeTimeInput->setText(QString::number(1));
               goto CONFIRM_SETTING;
           }
           if(temp_kanas->empty()){
               QMessageBox::warning(this,"范围违规","您未选择假名范围\n已设置为平假名清音部分");
               kanaVec->push_back(*AllKanas::A1);
               ui->A1->setCheckState(Qt::Checked);
               goto COMBINE_KANA_LIST;
           }
           if(FGA){
               if(FGAWT <= 0 ){
                   QMessageBox::warning(this,"输入违规","您输入的强制提交等待时间小于0秒\n已设置为5秒");
                   FGAWT = 5;
                   ui->FGAwaitTimeInput->setText(QString::number(5));
                   goto CONFIRM_SETTING;
               }
           }

           this->exeScene->exeInfo = new KanasExercise( exeTime,temp_kanas,&randKanas,getTime("hr-min-sec"),RUT,FGA,FGAWT );

           giveLog("ExersiceInitSetting","成功设定练习属性！","green");

           this->hide();
           giveLog("ExersiceInitSetting","成功隐藏设置窗口！","yellow","window_change");
           QTimer::singleShot(300,[=](){
               exeScene->move(this->x(),this->y());
               this->exeScene->show();
               giveLog("ExersiceInitSetting","成功显示练习场景！","yellow","window_change");
           });




           //开始练习前给出本次练习属性报告：
           giveLog("ExerciseScene",QString("本次练习属性：练习轮数：%1  假名范围：%2  是否记录用时：%3  是否强制提交答案：%4  强制提交等待时间：%5秒").arg(exeScene->exeInfo->exeTime).arg(kanaScopeConfig.data()).arg(exeScene->exeInfo->recordTime).arg(exeScene->exeInfo->giveAnswerForcefully).arg(exeScene->exeInfo->fGAwaitTime).toStdString(),"green","exe_config");

           //激活开始练习信号
           exeScene->StartEXE();
       }

    });
}

exeInitSetting::~exeInitSetting()
{
    delete ui;
}

void exeInitSetting::paintEvent(QPaintEvent *){
    static bool first_load = true;

    //创建位图
    QPixmap * pix = new QPixmap(":/res/settingBg.jpg");
    //创建画家
    QPainter * painter = new QPainter(this);
    //画背景
    painter->drawPixmap(0,0,this->width(),this->height(),*pix);

    if(first_load) { giveLog("ExerciseInitSetting","成功加载背景！"); }

    //释放内存
    delete pix;
    pix = nullptr;
    delete painter;
    painter = nullptr;

    if(first_load) { giveLog("ExerciseInitSetting","成功释放内存！","black","heap"); }

    first_load  = false;
}

void exeInitSetting::closeEvent(QCloseEvent *event){
    giveLog("ExerciseInitSetting","拦截到退出信号");

    //使用messagebox询问是否退出
    if(QMessageBox::question(this,"Are u sure to leave?","欧尼酱不再享受一下日本语给您带来的放松么") == QMessageBox::Yes)  {
        giveLog("ExerciseInitSetting","放弃退出程序","yellow");
        event->ignore();//忽略信号，不退出
    }
    else  {
        giveLog("ExerciseInitSetting","成功退出程序","cyan","system");
        event->accept();//接受，退出
        exit(EXIT_SUCCESS);
    }
}

ExerciseScene* exeInitSetting::get_exeScene(){
    return this->exeScene;
}
