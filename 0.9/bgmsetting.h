#ifndef BGMSETTING_H
#define BGMSETTING_H

#include <QMainWindow>
#include "WindowIncludes.h"

#include "testcreate.h"
#include "exercisereport.h"
#include "exercisescene.h"

enum Backgrounds{
    bg1 = 1,
    bg2 = 2,
    bg3 = 3,
    bg4 = 4,
};


namespace Ui {
class BgmSetting;
}

class BgmSetting : public QMainWindow
{
    Q_OBJECT

public:
    explicit BgmSetting(QWidget *parent = nullptr);
    ~BgmSetting();
    void closeEvent(QCloseEvent * ev);
    void paintEvent(QPaintEvent *);

    void chooseBg(Backgrounds bg);

    TestCreate * testMake;
    ExerciseReport * exeReport;
    ExerciseScene * exeScene;

private:

    Ui::BgmSetting *ui;

public slots:
    void updateduration(qint64 d);
};

#endif // BGMSETTING_H
