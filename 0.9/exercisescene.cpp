#include "exercisescene.h"
#include "ui_exercisescene.h"
using namespace std;

class map_value_finder
{
public:
       map_value_finder( const string &cmp_string):m_s_cmp_string(cmp_string){}
        bool  operator ()( const map< string, string>::value_type &pair)
       {
             return pair.second == m_s_cmp_string;
       }
private:
         const  string &m_s_cmp_string;
};

template<class T>
class vec_smaller_len_finder
{
public:
        vec_smaller_len_finder( int len){
            this->len = len;
        }

        bool  operator ()( const vector<T> v)
       {
             return (int)v.size() < len;
       }
private:
       int len;
};


QString vector_mapStringStringToQString(vector<map<string,string>> * v)  {
    string res = "";

    for(auto it = v->begin(); it != v->end(); it++)  {
        string temp = "";
        temp += (it->begin()->first);
        temp += "->";
        temp += (it->begin()->second);
        temp += "\n";

        it->erase(it->begin());
    }

    return QString::fromStdString(res);
}

ExerciseScene::ExerciseScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExerciseScene)
{
    ui->setupUi(this);


    //帮助窗口
    connect(ui->actionHelp,&QAction::triggered,[=](){
        helpWidget::show_help(nullptr);
    });

    //退出
    connect(ui->actionExit,&QAction::triggered,[=](){
        this->close();
    });

    //设置窗口
    connect(ui->actionSetting,&QAction::triggered,[=](){
        emit open_setting();
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
    giveLog("ExerciseScene","成功显示背景并设置模糊");

    //创建提交答案按钮
    //如果不强制提交答案，则显示提交答案按钮，否则显示强制提交答案限时

    giveAnswerBtn = new _PushButton(":/res/giveAnswerBtn.png");

    giveAnswerBtn->setParent(this);
    giveAnswerBtn->move(210,175);
    giveAnswerBtn->setFocusPolicy(Qt::ClickFocus);

    //设置五个输入框的tab顺序以方便切换
    setTabOrder(ui->input,ui->input_2);
    setTabOrder(ui->input_2,ui->input_3);
    setTabOrder(ui->input_3,ui->input_4);
    setTabOrder(ui->input_4,ui->input_5);
    setTabOrder(ui->input_5,ui->input);

    ui->remainTime->hide();
    ui->remainTime->setWindowFlags(Qt::WindowStaysOnTopHint);
    connect(this,&ExerciseScene::DOEXE,[=]()  {

        initExe();

        //状态栏显示记录时间
        QLabel *timeOutput = new QLabel(this);//标签显示已用时间
        ui->statusBar->addWidget(timeOutput);
        if(exeInfo->recordTime){
            exeInfo->usedTime = 0;
            QTimer * recordTimeTimer = new QTimer();
            recordTimeTimer->setTimerType(Qt::PreciseTimer);
            connect(recordTimeTimer,&QTimer::timeout,[=](){
                exeInfo->usedTime += 100;//如果报告窗口已显示，我们停止计时
                if(!exeReport->isHidden() ){
                    recordTimeTimer->stop();
                    ui->statusBar->removeWidget(timeOutput);
                }
                //显示信息
                timeOutput->setText(QString("正在记录练习用时！ 已用时间：%1秒！").arg(QString::number(exeInfo->usedTime/1000,'f',2)));
            });
            recordTimeTimer->start(100);
        }

        if(exeInfo->giveAnswerForcefully == true)  {  //强制提交答案部分代码

            giveAnswerBtn->hide();

            ui->remainTime->show();

            exeInfo->set_GRSK();

            //开始第一轮练习并开始第一组
            exeTime = 0; //进行了几轮
            groupNum = 0;//进行了几组

            exeTime += 1;
            start_time();

            groupNum += 1;
            start_group();

            randomSort_Put();

            connect(this,&ExerciseScene::FGA,[=](){

                groupNum+=1;
                answer_given_operate();

                if(groupNum > (exeInfo->allKanaNum / 5 + 1)) { //本组练习完成
                    groupNum = 1;
                    exeTime ++;

                    if(exeTime > exeInfo->exeTime){
                        //结束练习
                        ui->thisGroupFalseAnsOutPut->clear();
                        ui->thisTimeFalseAnsOutPut->clear();
                        this->hide();
                        give_value_to_exeReport();
                        QTimer::singleShot(300,[=](){
                            exeReport->move(this->x(),this->y());
                            exeReport->show();
                        });
                        exeReport->showInfo();
                        disconnect(giveAnswerBtn,NULL,NULL,NULL);
                        return;
                    }

                    start_time();

                    randomSort_Put();

                    start_group();

                }
                else{
                    randomSort_Put();

                    start_group();

                }
            });


            QTimer * timer = new QTimer(this);
            QTimer * timer_2 = new QTimer(this);

            timer->setTimerType(Qt::PreciseTimer);
            connect(timer,SIGNAL(timeout()),this,SLOT(forcefullyGiveAnswer()));
            connect(timer,SIGNAL(timeout()),this,SLOT(TimerSetToZero()));


            timer_2->setTimerType(Qt::PreciseTimer);
            connect(timer_2,SIGNAL(timeout()),this,SLOT(updateTimer()));

            timer->start(exeInfo->fGAwaitTime*1000);
            timer_2->start(100);

            //如果停止了练习，就停止计时
            connect(timer,&QTimer::timeout,[=](){
                if(exeTime > exeInfo->exeTime){
                    timer->stop();
                }
            });
            connect(timer_2,&QTimer::timeout,[=](){
                if(exeTime > exeInfo->exeTime){
                    timer_2->stop();
                }
            });

            return;

        }
        else if(exeInfo->giveAnswerForcefully == false)  { //非强制提交答案部分代码

            ui->remainTime->hide();
            giveAnswerBtn->show();

            exeInfo->set_GRSK();

            //开始第一轮练习并开始第一组
            exeTime = 0; //进行了几轮
            groupNum = 0;//进行了几组

            exeTime += 1;
            start_time();

            groupNum += 1;
            start_group();

            randomSort_Put();

            //点击按钮时进行一系列刷新
            connect(giveAnswerBtn,&_PushButton::clicked,[=](){
                groupNum+=1;
                answer_given_operate();

                if(groupNum > (exeInfo->allKanaNum / 5 + 1)) { //本组练习完成
                    groupNum = 1;
                    exeTime ++;

                    if(exeTime > exeInfo->exeTime){
                        //结束练习
                        ui->thisGroupFalseAnsOutPut->clear();
                        ui->thisTimeFalseAnsOutPut->clear();
                        this->hide();
                        give_value_to_exeReport();
                        QTimer::singleShot(300,[=](){
                            exeReport->move(this->x(),this->y());
                            exeReport->show();
                        });
                        exeReport->showInfo();
                        disconnect(giveAnswerBtn,NULL,NULL,NULL);
                        return;
                    }

                    start_time();

                    randomSort_Put();

                    start_group();

                }
                else{
                    randomSort_Put();

                    start_group();

                }
            });

        }

    });

}

void ExerciseScene::start_time(){
    //初始化
    delete exeInfo->thisTimeFalseAnswer;

    exeInfo->thisTimeFalseAnswer = new vector<string>();

    ui->thisTimeFalseAnsOutPut->clear();

    exeInfo->thisTimeCorrectAnsNum = 0;



    giveLog("","进入新一轮练习");



    random_shuffle(exeInfo->GRSK->begin(),exeInfo->GRSK->end());

    vector<string>shortOne = *find_if(exeInfo->GRSK->begin(),exeInfo->GRSK->end(),vec_smaller_len_finder<string>(5));

    exeInfo->GRSK->erase(std::find(exeInfo->GRSK->begin(),exeInfo->GRSK->end(),shortOne));

    exeInfo->GRSK->push_back(shortOne);

    refresh_output();
}

void ExerciseScene::start_group(){
    refresh_output();
    ui->input->setFocus();
}

void ExerciseScene::randomSort_Put(){

    static int p = 0;
    if(p >= exeInfo->allKanaNum / 5 + 1){
        p = 0;

    }
    //打乱本组假名
    vector<string> TGKL = exeInfo->GRSK->at(p);


    //把假名放进标签
    if(TGKL.size() >= 1)
    {
        ui->output->show();
        ui->input->show();
        ui->output->setText(QString::fromStdString(TGKL[0]));
    }
    else{
        ui->output->setText("");
        ui->output->hide();
        ui->input->hide();
    }

    if(TGKL.size() >= 2)
    {
        ui->output_2->show();
        ui->input_2->show();
        ui->output_2->setText(QString::fromStdString(TGKL[1]));
    }
    else {
        ui->output_2->setText("");
        ui->output_2->hide();
        ui->input_2->hide();
    }

    if(TGKL.size() >= 3)
    {
        ui->output_3->show();
        ui->input_3->show();
        ui->output_3->setText(QString::fromStdString(TGKL[2]));
    }
    else {
        ui->output_3->setText("");
        ui->output_3->hide();
        ui->input_3->hide();
    }

    if(TGKL.size() >= 4)
    {
        ui->output_4->show();
        ui->input_4->show();
        ui->output_4->setText(QString::fromStdString(TGKL[3]));
    }
    else {
        ui->output_4->setText("");
        ui->output_4->hide();
        ui->input_4->hide();
    }

    if(TGKL.size() >= 5)
    {
        ui->output_5->show();
        ui->input_5->show();
        ui->output_5->setText(QString::fromStdString(TGKL[4]));
    }
    else {
        ui->output_5->setText("");
        ui->output_5->hide();
        ui->input_5->hide();
    }

    p += 1;
}

void ExerciseScene::StartEXE(){

    emit DOEXE();

}

void ExerciseScene::answer_given_operate(){
    //初始化
    exeInfo->thisGroupRightAnsNum = 0;
    delete exeInfo->thisGroupFalseAnswer;
    exeInfo->thisGroupFalseAnswer = new vector<string>();
    delete exeInfo->thisGroupGivenAnswer;
    exeInfo->thisGroupGivenAnswer = new vector<string>();

    //收集回答并生成答案
    vector<string>Ans = {};
    if(ui->output->text() != ""){
        exeInfo->thisGroupGivenAnswer->push_back(ui->input->text().toStdString());

        Ans.push_back(exeInfo->kanas->find(ui->output->text().toStdString())->second);
    }
    if(ui->output_2->text() != ""){
        exeInfo->thisGroupGivenAnswer->push_back(ui->input_2->text().toStdString());

        Ans.push_back(exeInfo->kanas->find(ui->output_2->text().toStdString())->second);
    }
    if(ui->output_3->text() != ""){
        exeInfo->thisGroupGivenAnswer->push_back(ui->input_3->text().toStdString());

        Ans.push_back(exeInfo->kanas->find(ui->output_3->text().toStdString())->second);
    }
    if(ui->output_4->text() != ""){
        exeInfo->thisGroupGivenAnswer->push_back(ui->input_4->text().toStdString());

        Ans.push_back(exeInfo->kanas->find(ui->output_4->text().toStdString())->second);
    }
    if(ui->output_5->text() != ""){
        exeInfo->thisGroupGivenAnswer->push_back(ui->input_5->text().toStdString());

        Ans.push_back(exeInfo->kanas->find(ui->output_5->text().toStdString())->second);
    }

    vector<string>thisGroupFalseAnsCorrect;

    //进行判断
    for(short i = 0; i < (int)exeInfo->thisGroupGivenAnswer->size() ; i++){
        if(exeInfo->thisGroupGivenAnswer->at(i) == Ans[i]){
            exeInfo->thisGroupRightAnsNum++;
        }
        else{
            exeInfo->thisGroupFalseAnswer->push_back(exeInfo->thisGroupGivenAnswer->at(i));
            thisGroupFalseAnsCorrect.push_back(Ans[i]);
            //把allFalseAnswer也插入一下
            exeInfo->allFalseAnswer->push_back(find_if(exeInfo->kanas->begin(), exeInfo->kanas->end(), map_value_finder(Ans[i]))->first);
        }
    }
    //进行输出

    ui->thisGroupCorrectNum->setText(QString("本组正确个数：%1个").arg(exeInfo->thisGroupRightAnsNum));

    ui->thisGroupIncorrectNum->setText(QString("本组错误假名：%1个").arg((int)exeInfo->thisGroupFalseAnswer->size()));

    ui->thisGroupFalseAnsOutPut->clear();

    for (short i = 0;i < (int)exeInfo->thisGroupFalseAnswer->size() ;  i++){
        ui->thisGroupFalseAnsOutPut->addItem(QString("%1.%2:%3 -> %4").arg(i+1).arg(find_if(exeInfo->kanas->begin(), exeInfo->kanas->end(), map_value_finder(thisGroupFalseAnsCorrect[i]))->first.data()).arg(exeInfo->thisGroupFalseAnswer->at(i).data()).arg(thisGroupFalseAnsCorrect[i].data()));
    }

    //更新各个全局数值
    exeInfo->thisTimeFalseAnswer->insert(exeInfo->thisTimeFalseAnswer->end(),exeInfo->thisGroupFalseAnswer->begin(),exeInfo->thisGroupFalseAnswer->end());
    exeInfo->thisTimeCorrectAnsNum+= exeInfo->thisGroupRightAnsNum;
    if(!exeInfo->thisTimeFalseAnswer->empty()){
            exeInfo->allIncorrectAnsNum += (int)exeInfo->thisTimeFalseAnswer->size();
    }
    for (short i = 0;i < (int)exeInfo->thisGroupFalseAnswer->size() ;  i++){
        ui->thisTimeFalseAnsOutPut->addItem(QString("%1%2:%3 -> %4").arg("_").arg(find_if(exeInfo->kanas->begin(), exeInfo->kanas->end(), map_value_finder(thisGroupFalseAnsCorrect[i]))->first.data()).arg(exeInfo->thisGroupFalseAnswer->at(i).data()).arg(thisGroupFalseAnsCorrect[i].data()));
    }

    //清空输入框
    ui->input->clear();
    ui->input_2->clear();
    ui->input_3->clear();
    ui->input_4->clear();
    ui->input_5->clear();



}

void ExerciseScene::refresh_output(){
    ui->exeTimeRemained->setText(QString("剩余练习轮数：%1轮").arg(exeInfo->exeTime-exeTime));

    float thisTimeCorrectPercent = 0.0;//本轮练习正确率
    {
        float correctAns = exeInfo->thisTimeCorrectAnsNum;
        float usedKana = exeInfo->thisTimeFalseAnswer->size() + exeInfo->thisTimeCorrectAnsNum;
        thisTimeCorrectPercent = correctAns / usedKana;
        if(thisTimeCorrectPercent < 0){
            thisTimeCorrectPercent = 0;
        }
        thisTimeCorrectPercent *= 100;
    }

    ui->thisTimeCorrectPercent->setText(QString("本轮练习正确率：%1%").arg(QString::number(thisTimeCorrectPercent,'f',2))); //更新数据

    float thisTimeIncorrectPercent = 0.0;
    {
        float incorrectAns = exeInfo->thisTimeFalseAnswer->size();
        float usedKana =  exeInfo->thisTimeFalseAnswer->size() + exeInfo->thisTimeCorrectAnsNum;
        thisTimeIncorrectPercent = incorrectAns / usedKana;
        thisTimeIncorrectPercent *= 100;
    }

    ui->thisTimeIncorrectPercent->setText(QString("本轮练习错误率：%1%").arg(QString::number(thisTimeIncorrectPercent,'f',2))); //更新数据

    int thisGroupRemainTime = ((exeInfo->allKanaNum / 5 + 1) - groupNum); //本组剩余轮数
    ui->kanaGroupRemained->setText(QString("本轮练习剩余组数：%1组").arg(thisGroupRemainTime));

    ui->allRightAnswer->setText(QString("总计正确个数:%1个").arg(exeInfo->thisTimeCorrectAnsNum));
    ui->allFalseAnswer->setText(QString("总计错误个数：%1个").arg(exeInfo->thisTimeFalseAnswer->size()));
    ui->allKanas->setText(QString("全部假名个数：%1个").arg(exeInfo->allKanaNum));
}

void ExerciseScene::forcefullyGiveAnswer(){
    emit FGA();
}

void ExerciseScene::updateTimer(){
    static float minusVal = 0;

    minusVal += 0.1;

    if(exeInfo->fGAwaitTime - minusVal<=0){
        minusVal = 0;
    }

    ui->remainTime->setText(QString("剩余时间:%1").arg(QString::number((exeInfo->fGAwaitTime - minusVal),'f',2)));

}

void ExerciseScene::TimerSetToZero(){
    ui->remainTime->setText(QString("剩余时间:%1").arg(0));

}

ExerciseScene::~ExerciseScene()
{
    delete ui;
}

void ExerciseScene::closeEvent(QCloseEvent * ev) {
    giveLog("ExerciseScene","拦截到退出信号");

    //使用messagebox询问是否退出
    if(QMessageBox::question(this,"Are u sure to leave?","欧尼酱不再享受一下日本语给您带来的放松么") == QMessageBox::Yes)
    {

        giveLog("ExerciseScene","放弃退出程序","yellow");

        ev->ignore();//忽略信号，不退出

    }
    else  {

        giveLog("ExerciseScene","成功退出程序","cyan","system");

        ev->accept();//接受，退出

        exit(EXIT_SUCCESS);

    }
}

void ExerciseScene::set_exeReport(ExerciseReport* er){
    this->exeReport = er;
}

void ExerciseScene::give_value_to_exeReport(){
    exeReport->allKanaNum = exeInfo->allKanaNum * exeInfo->exeTime;

    exeReport->allFalseKanaNum = (int)exeInfo->allFalseAnswer->size();

    exeReport->falseKanaList = *exeInfo->allFalseAnswer;

    exeReport->allRightKanaNum = exeReport->allKanaNum -  exeReport->allFalseKanaNum;

    exeReport->kana_dict = *exeInfo->kanas;

    if(exeInfo->recordTime){
        exeReport->usedTime = exeInfo->usedTime / 1000;
    }
    else
    {
        exeReport->usedTime = -1;
    }

}

void ExerciseScene::setBg(QString filePath){

    ui->showBg->clear();
    QMovie * movie = new QMovie(filePath);
    ui->showBg->setMovie(movie);
    movie->start();
}

void ExerciseScene::initExe(){
    this->exeTime = 0;
    this->groupNum = 0;
}


