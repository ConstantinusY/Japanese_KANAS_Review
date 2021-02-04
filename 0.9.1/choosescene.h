#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H

#include <QWidget>
#include "WindowIncludes.h"
#include "testcreate.h"
#include "exeinitsetting.h"

namespace Ui {
class ChooseScene;
}

class ChooseScene : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseScene(QWidget *parent = nullptr);
    ~ChooseScene();

    void paintEvent(QPaintEvent *);

    void closeEvent(QCloseEvent *event);

    TestCreate * _testCreateScene();

    exeInitSetting * _exeInitSetting();

    ExerciseReport * _exeReport();
private:
    Ui::ChooseScene *ui;

    exeInitSetting * exeInit;

    TestCreate * testCreateScene;

    ExerciseReport * exeReport;
signals:
    void back_to_start();
};

#endif // CHOOSESCENE_H
