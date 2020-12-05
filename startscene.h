#ifndef STARTSCENE_H
#define STARTSCENE_H



#include "WindowIncludes.h"

#include  "LogOperation.h"
#include "_pushbutton.h"
#include  "choosescene.h"
#include "bgmsetting.h"

QT_BEGIN_NAMESPACE
namespace Ui { class StartScene; }
QT_END_NAMESPACE

class StartScene : public QMainWindow
{
    Q_OBJECT

public:
    StartScene(QWidget *parent = nullptr);
    ~StartScene();

    void paintEvent(QPaintEvent *);

    void closeEvent(QCloseEvent * ev);

    BgmSetting * setting;
private:

    Ui::StartScene *ui;

    ChooseScene * chooseScene;

};
#endif // STARTSCENE_H
