#include "bgmsetting.h"
#include "ui_bgmsetting.h"

//定义音乐播放器
using namespace std;

struct _Music
{
    string musicName;
    string musicAuther;
    string musicAlbum;

    QUrl fileUrl;

    _Music(QUrl fileUrl,string musicName,string mau,string mal){
        this->musicName = musicName;
        this->musicAuther = mau;
        this->musicAlbum = mal;
        this->fileUrl = fileUrl;
};
};

enum MusicPlayMode{
    list = 0,    //列表循环
    random = 1,  //随机播放
    loop = 2,    //单曲循环
};

class music_vec_url_finder{
private:
    QUrl target;
public:
    music_vec_url_finder(QUrl url){
        this->target = url;
    }
    bool operator()(_Music m){
        return m.fileUrl == target;
    }
};

class MusicPlayer
{
private:

    QString PM_FilePath;

    vector<_Music> * musics;
    QMediaPlayer * player;
    QMediaPlaylist * playlist;
    MusicPlayMode playMode;

public:

    float PM_TimeLen;
    string PM_Name;
    string PM_Auther;
    string PM_Album;

    _Music  at(QUrl target){
        return *find_if(musics->begin(),musics->end(),music_vec_url_finder(target));
    }

    MusicPlayer(vector<_Music>*musics, MusicPlayMode mode,QWidget * parent = nullptr){

        this->musics = musics;

        this->playMode = mode;

        this->player = new QMediaPlayer();

        this->playlist = new QMediaPlaylist();

        this->player->setParent(parent);
        this->playlist->setParent(parent);

        refresh_info();

        player->setPlaylist(playlist);
    }

    ~MusicPlayer(){
        delete musics;
        musics = nullptr;
        delete player;
        player = nullptr;
        delete playlist;
        playlist = nullptr;
    }

    void appendMusic(_Music m){

        this->musics->push_back(m);

        this->playlist->addMedia(m.fileUrl);

        this->refresh_info();

        giveLog("musicPLayer","成功加载音乐");
    }

    void set_playMode(MusicPlayMode playMode){
        this->playMode = playMode;
        refresh_info();
    }

    void clearMusic(){
        playlist->clear();
        this->musics->clear();
    }

    void refresh_info(){


        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        player->setPlaylist(playlist);

        switch (this->playMode) {
        case MusicPlayMode::list:
            playlist->setPlaybackMode(QMediaPlaylist::Loop);
            giveLog("MusicPlayer","成功设置播放模式为列表循环");
            break;
        case MusicPlayMode::random:
            playlist->setPlaybackMode(QMediaPlaylist::Random);
            giveLog("MusicPlayer","成功设置播放模式为随机播放");
            break;
        case MusicPlayMode::loop:
            playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            giveLog("MusicPlayer","成功设置播放模式为单曲循环");
            break;
        }

        player->play();
    }

    QMediaPlayer* _player(){
         return this->player;
    }

    static QString Time(qint64 time){
        qint64 seconds = time / 1000;
        const qint64 minutes = seconds / 60;
        seconds -= minutes*60;
        return QString("%1：%2").arg(minutes).arg(seconds);
    }

    void refresh_play_list(QListWidget* a){
        a->clear();
        int m = 1;
        for(vector<_Music>::iterator it = musics->begin(); it != musics->end() ; it++){
            a->addItem(QString("%1.%2 by %3").arg(m).arg(it->musicName.data()).arg(it->musicAuther.data()));
            m++;
        }
    }
};


BgmSetting::BgmSetting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BgmSetting)
{
    ui->setupUi(this);

    ui->widgets->setCurrentIndex(0);

    connect(ui->actionExit,&QAction::triggered,[=](){
        this->close();
    });

    connect(ui->actionBack,&QAction::triggered,[=](){
        this->hide();
    });

    MusicPlayer* Player = new MusicPlayer(new vector<_Music>(),MusicPlayMode::list,this);

    //连接播放方式更换
    connect(ui->changePlayMode,&QPushButton::clicked,[=](){
        static bool first = true;
        if(first){Player->set_playMode(MusicPlayMode::list);}
        first = false;

        static short index = 0; //index = 0:顺序播放,index = 1:随机播放,index = 2:单曲循环
        switch(index){
        case 0:
            Player->set_playMode(MusicPlayMode::list);
            ui->changePlayMode->setText("顺序播放");
            index = 1;
            break;
        case 1:
            Player->set_playMode(MusicPlayMode::random);
            ui->changePlayMode->setText("随机播放");
            index = 2;
            break;
        case 2:
            Player->set_playMode(MusicPlayMode::loop);
            ui->changePlayMode->setText("单曲循环");
            index = 0;
        }
    });

    Player->set_playMode(MusicPlayMode::list);

    //将歌曲加入列表
    Player->appendMusic(_Music(QUrl("qrc:/res/music/music1.mp3"),"现实.V1","ZaTAR_Official","现实"));
    Player->appendMusic(_Music(QUrl("qrc:/res/music/music2.mp3"),"苦涩","RRAN","苦涩"));
    Player->appendMusic(_Music(QUrl("qrc:/res/music/music3.mp3"),"夏日、教室与望着窗外的我","Candy_Wind","雨之翼"));
    Player->appendMusic(_Music(QUrl("qrc:/res/music/music4.mp3"),"情书","Candy_Wind","拂晓车站"));
    Player->appendMusic(_Music(QUrl("qrc:/res/music/music5.mp3"),"mopemope","LeaF","《mopemope》"));
    Player->appendMusic(_Music(QUrl("qrc:/res/music/music6.mp3"),"高潔なる教皇","菅野祐悟","ジョジョの奇妙な冒険..."));
    Player->appendMusic(_Music(QUrl("qrc:/res/music/music7.mp3"),"Flemington","Tom Day","Flemington"));
    Player->appendMusic(_Music(QUrl("qrc:/res/music/music8.mp3"),"復讐の行方","藤澤健至","地獄少女 OST"));
    Player->appendMusic(_Music(QUrl("qrc:/res/music/music9.mp3"),"桜廻廊","A_Hisa","桜廻廊"));
    Player->appendMusic(_Music(QUrl("qrc:/res/music/music10.mp3"),"海の涙","出羽良彰","風のあすから"));

    Player->refresh_play_list(ui->playList);
    Player->_player()->play();

    //开始播放按钮
    connect(ui->continueSong,&QPushButton::clicked,[=](){
        if(Player->_player()->state() == QMediaPlayer::PausedState){
            Player->_player()->play();
            giveLog("BgmSetting","已发出开始播放信号");
        }
    });

    //暂停播放按钮
    connect(ui->pauseSong,&QPushButton::clicked,[=](){
        if(Player->_player()->state() == QMediaPlayer::PlayingState){
            Player->_player()->pause();
            giveLog("BgmSetting","已发出暂停播放信号");
        }
    });

    //下一首按钮
    connect(ui->nextSong,&QPushButton::clicked,[=](){
        Player->_player()->playlist()->next();
    });

    //上一首按钮
    connect(ui->lastSong,&QPushButton::clicked,[=](){
        Player->_player()->playlist()->previous();
    });

    ui->musicSlider->hide();//实在修不明白了

    //开始先刷新一次
    _Music temp = Player->at(Player->_player()->playlist()->currentMedia().request().url());
    ui->playingMusicName->setText(QString::fromStdString(temp.musicName));
    ui->playingMusicAuther->setText(QString::fromStdString(temp.musicAuther));
    ui->playingMusicSpecialEdition->setText(QString::fromStdString(temp.musicAlbum));
    ui->volumeOutput->setText(QString("%1%").arg(Player->_player()->volume()));//音量也刷新
    ui->musicSlider->setMinimum(0);

    //切换媒体时刷新信息
    connect(Player->_player(),QOverload<const QMediaContent&>::of(&QMediaPlayer::currentMediaChanged),[=](const QMediaContent& media){
        _Music temp = Player->at(media.request().url());
        ui->playingMusicName->setText(QString::fromStdString(temp.musicName));
        ui->playingMusicAuther->setText(QString::fromStdString(temp.musicAuther));
        ui->playingMusicSpecialEdition->setText(QString::fromStdString(temp.musicAlbum));
    });

//    connect(Player->_player(),&QMediaPlayer::durationChanged,this,&BgmSetting::updateduration);

    //更新歌曲进度条 & 时间
    connect(Player->_player(),&QMediaPlayer::positionChanged,[=](){

//        ui->musicSlider->setValue(Player->_player()->position());
        //更新时间
        auto a = MusicPlayer::Time(Player->_player()->position());
        ui->timeOutput->setText(a);
    });




    //更新音量
    connect(Player->_player(),&QMediaPlayer::volumeChanged,[=](){
        ui->volumeOutput->setText(QString("%1%").arg(Player->_player()->volume()));
    });

    //滚动QDial更新音量
    connect(ui->volumeDial,QOverload<int>::of(&QDial::valueChanged),[=](int v){
        Player->_player()->setVolume(v);
    });

    //帮助窗口
    connect(ui->actionhelp_musicPlayer,&QAction::triggered,[=](){
        helpWidget::show_help(nullptr);
    });

    //翻页操作
    connect(ui->gotoBgSetting,&QPushButton::clicked,[=](){
        ui->widgets->setCurrentIndex(1);
    });
    connect(ui->gotoMusicPlayer,&QPushButton::clicked,[=](){
        ui->widgets->setCurrentIndex(0);
    });

    //放入背景预览
    QMovie *bg1 = new QMovie(":/res/exeBg.gif");
    bg1->start();
    ui->bg_1display->setMovie(bg1);
    ui->bg_1display->setScaledContents(true);
    QMovie *bg2 = new QMovie(":/res/exeBg_2.gif");
    bg2->start();
    ui->bg_2display->setMovie(bg2);
    ui->bg_2display->setScaledContents(true);
    QMovie *bg3 = new QMovie(":/res/exeBg_3.gif");
    bg3->start();
    ui->bg_3display->setMovie(bg3);
    ui->bg_3display->setScaledContents(true);

    //当按下应用按钮时进行操作
    connect(ui->confirmBtn,&QPushButton::clicked,[=](){
       Backgrounds chosenBg = Backgrounds::bg1;
       if(ui->bg1Btn->isChecked()){
           chosenBg = Backgrounds::bg1;
       }
       else if(ui->bg2Btn->isChecked()){
           chosenBg = Backgrounds::bg2;
       }
       else if(ui->bg3Btn->isChecked()){
           chosenBg = Backgrounds::bg3;
       }
       else if(ui->bg4Btn->isChecked()){
           chosenBg = Backgrounds::bg4;
       }

       chooseBg(chosenBg);

       giveLog("bgSetting","成功发出切换背景信号");
    });


}

BgmSetting::~BgmSetting()
{
    delete ui;
}

void BgmSetting::closeEvent(QCloseEvent * ev){
    ev->ignore();
    this->hide();
}

void BgmSetting::paintEvent(QPaintEvent *){
    static bool first_load = true;

    //创建位图
    QPixmap * pix = new QPixmap(":/res/settingBg_flower.png");
    //创建画家
    QPainter * painter = new QPainter(this);
    //画背景
    painter->drawPixmap(0,0,this->width(),this->height(),*pix);

    if(first_load) { giveLog("Bgm_Bg_Setting","成功加载背景！"); }

    //释放内存
    delete pix;
    pix = nullptr;
    delete painter;
    painter = nullptr;

    if(first_load) { giveLog("Bgm_Bg_Setting","成功释放内存！","black","heap"); }

    first_load  = false;
}

void BgmSetting::updateduration(qint64 d){
    ui->musicSlider->setRange(0,d);
    ui->musicSlider->setEnabled(d > 0);
    ui->musicSlider->setPageStep(d / 10);
}

void BgmSetting::chooseBg(Backgrounds bg){

    switch(bg)
    {
    case Backgrounds::bg1:
        testMake->setBg(":/res/exeBg.gif");
        exeScene->setBg(":/res/exeBg.gif");
        exeReport->setBg(":/res/exeBg.gif");
        break;
    case Backgrounds::bg2:
        testMake->setBg(":/res/exeBg_2.gif");
        exeScene->setBg(":/res/exeBg_2.gif");
        exeReport->setBg(":/res/exeBg_2.gif");
        break;
    case Backgrounds::bg3:
        testMake->setBg(":/res/exeBg_3.gif");
        exeScene->setBg(":/res/exeBg_3.gif");
        exeReport->setBg(":/res/exeBg_3.gif");
        break;
    case Backgrounds::bg4:
        testMake->setBg(":/res/exeBg_4.gif");
        exeScene->setBg(":/res/exeBg_4.gif");
        exeReport->setBg(":/res/exeBg_4.gif");
        break;
    }

}
