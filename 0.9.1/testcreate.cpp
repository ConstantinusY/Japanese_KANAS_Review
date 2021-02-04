#include "testcreate.h"
#include "ui_testcreate.h"

#include "bgmsetting.h"
using namespace std;

//问卷样式枚举
enum TestStyles {
    style1,  // あ____ い____ う____ え____ お____
    style2,  // あ(     ) い(     ) う(     ) え(     ) お(     )
    style3   // あ:       い:     う:      え:       お:
};

class TestUnit{
private:
    string unit_data;
public:
    TestUnit(string ud, enum TestStyles s){
        unit_data=ud;
        switch (s) {
        case TestStyles::style1:  {
            unit_data+= "________   ";
            break;
        }
        case TestStyles::style2:  {
            unit_data += "(      )   ";
            break;
        }
        case TestStyles::style3:  {
            unit_data += ":       |   ";
            break;
        }}
    }
    string getUnit(){
        string res;
        res+="<td>";
        res+=unit_data;
        res+="</td>";
        return res;

    }
};

//生成问卷函数
string makeTest(map<string,string>kanas,enum TestStyles style,int kanaNumPerLine,bool addAnswer){
    string result;
    result+="<html> <head><meta charset='utf-8' /></head> <body> <table border='0px' cellspacing='3px' cellpadding='3px'>";

    //将假名取出来
    vector<string>items;
    for(auto it = kanas.begin() ; it != kanas.end() ; it++){
        items.push_back(it->first);
    }
    //打乱假名
    random_shuffle(items.begin(),items.end());


    //开始写入问题

    int usedItemNum = 0;
    while (usedItemNum < (int)items.size()) {
        result += "<tr>";
        //如果不够用了
        if(usedItemNum >= (int)items.size()-kanaNumPerLine)  {
            for(int i = usedItemNum ; i <  (int)items.size() ; i++)  {

                result += TestUnit((to_string(usedItemNum + 1)+"."+items.at(usedItemNum)),style).getUnit();

                usedItemNum++;
            }
            result += "</tr>";
            break;
        }
        for(int i = 0 ; i < kanaNumPerLine ; i++)  {

            result += TestUnit((to_string(usedItemNum + 1)+"."+items.at(usedItemNum)),style).getUnit();

            usedItemNum++;
        }
        result += "</tr>";
    }

    //写入答案
    if(addAnswer)  {

        result += (" <tr><td colspan='"+to_string(kanaNumPerLine)+"' align='center'>答案<td>");
        int usedItemNum = 0;
        while (usedItemNum < (int)items.size()) {
            result+="<tr>";
            //如果不够用了
            if(usedItemNum >= (int)items.size()-kanaNumPerLine)  {

                for(int i = usedItemNum ; i <  (int)items.size() ; i++)  {

                    result += TestUnit(to_string(usedItemNum + 1)+"."+kanas.find(items.at(usedItemNum))->second,style).getUnit();

                    usedItemNum++;
                }
                result+="</tr>";
                break;
            }
            for(int i = 0 ; i < kanaNumPerLine ; i++)  {

                result += TestUnit(to_string(usedItemNum + 1)+"."+kanas.find(items.at(usedItemNum))->second,style).getUnit();
                usedItemNum++;
            }
            result += "</tr>";
        }
    }

    result+="</body> </html>";


    return result;
}

TestCreate::TestCreate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestCreate)
{
    ui->setupUi(this);

    //设置窗口
    connect(ui->actionSetting,&QAction::triggered,[=](){
        emit open_setting();
    });


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
    giveLog("TestCreate","成功显示背景并设置模糊");

    //返回按钮
    _PushButton * backBtn = new _PushButton(":/res/BackButton.png",":/res/BackButtonSelected");
    backBtn->setParent(this);
    backBtn->move(840,430);

    connect(backBtn,&_PushButton::clicked,[=](){
        //延时切换窗口
        QTimer::singleShot(500,[=](){
            this->hide();
            giveLog("TestCreate","选择窗口成功隐藏","yellow","window_change");
            emit back_to_chooseScene();
        });
    });

    //获取文件路径
    connect(ui->chooseFile,&QPushButton::clicked,[=](){
        this->filePath = QFileDialog::getOpenFileName(this,"选择文件",".","*.html").toUtf8().data();

        ui->openedFileOutput->setText(QString::fromStdString(filePath));

        giveLog("TestCreate",QString("成功打开文件：%1").arg(QString::fromStdString(filePath)).toStdString());
    });

    //实现功能
    connect(ui->create,&QPushButton::clicked,[=](){ //当按下生成按钮进行一系列判断
        giveLog("TestCreate","生成按钮被按下，生成开始！");

        //创建Map存放假名
        vector<map<string,string>> kanas = {};
        //确定范围
        if(ui->A1->checkState() == Qt::Checked){
            kanas.push_back(*AllKanas::A1);
        }
        if(ui->A2->checkState() == Qt::Checked){
            kanas.push_back(*AllKanas::A2);
        }
        if(ui->A3->checkState() == Qt::Checked){
            kanas.push_back(*AllKanas::A3);
        }
        if(ui->B1->checkState() == Qt::Checked){
            kanas.push_back(*AllKanas::B1);
        }
        if(ui->B2->checkState() == Qt::Checked){
            kanas.push_back(*AllKanas::B2);
        }
        if(ui->B3->checkState() == Qt::Checked){
            kanas.push_back(*AllKanas::B3);
        }

        auto allKanas = AllKanas::combineMaps(kanas);

        giveLog("TestCreate","成功确认生成范围！");

        //确认样式
        enum TestStyles style;

        if(ui->style1->isChecked()){
            style = TestStyles::style1;
        }
        if(ui->style2->isChecked()){
            style = TestStyles::style2;
        }
        if(ui->style3->isChecked()){
            style = TestStyles::style3;
        }

        giveLog("TestCreate","成功确认样式！");

        //获取每行假名数
        int kana_num_per_line = stoi(string(ui->KanaNumberPerLineInput->text().toUtf8().data()));
        if(kana_num_per_line > 10)  {        //不允许每行多于十个
            giveLog("TestCreate","假名数过多","yellow","warning");
            ui->KanaNumberPerLineInput->setText("10");
            kana_num_per_line = 10;
            QMessageBox::warning(this,"每行假名过多","您输入的每行假名数>10，超出范围，默认为10。");
        }
        if(kana_num_per_line < 1){
            giveLog("TestCreate","假名数过少","yellow","warning");
            ui->KanaNumberPerLineInput->setText("1");
            kana_num_per_line = 1;
            QMessageBox::warning(this,"每行假名过少","您输入的每行假名数<1，超出范围，默认为1。");
        }
        giveLog("TestCreate","成功确认每行假名数！");

        //确认是否添加答案
        bool addAnswer = ui->switch_addKeys->checkState() == Qt::Checked;
        giveLog("TestCreate","成功确认是否添加答案！");

        //产生结果

        this->test = (makeTest(allKanas,style,kana_num_per_line,addAnswer));
        ui->outPutArea->setHtml(QString::fromStdString(test));

        giveLog("TestCreate","成功生成！");



    });

    //写入文件
    connect(ui->saveToFile,&QPushButton::clicked,[=](){
        //如果文件路径为空
        if(this->filePath == ""){

            QMessageBox::warning(this,"警告","未选择文件");

        }
        else{

        ofstream ofs;
        ofs.open(filePath,ios::in);
        ofs.clear();

        ofs << this->test << endl;

        QMessageBox::information(this,"保存成功","问卷成功保存到文件");

        ofs.close();

        }
    });

    //样式预览
    connect(ui->stylePreview,&QPushButton::clicked,[=](){
        ui->outPutArea->setText("样式预览：\n样式1,   あ____ い____ う____ え____ お____\n样式2,   あ(     ) い(     ) う(     ) え(     ) お(     )\n样式3,   あ:       い:     う:      え:       お:      ");
    });

}

TestCreate::~TestCreate()
{
    delete ui;
}

void TestCreate::closeEvent(QCloseEvent * ev) {
    giveLog("TestCreate","拦截到退出信号");

    if(QMessageBox::question(this,"Are u sure to leave?","欧尼酱不再享受一下日本语给您带来的放松么") == QMessageBox::Yes)  {
        giveLog("TestCreate","放弃退出程序","yellow");
        ev->ignore();
    }
    else  {
        giveLog("TestCreate","成功退出程序","cyan","system");
        ev->accept();
        exit(EXIT_SUCCESS);
    }
}

void TestCreate::setBg(QString filePath){

    ui->showBg->clear();
    QMovie * movie = new QMovie(filePath);
    ui->showBg->setMovie(movie);
    movie->start();
}


