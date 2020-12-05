#ifndef EXEINITSETTING_H
#define EXEINITSETTING_H

#include <QWidget>
#include "WindowIncludes.h"
#include "exercisescene.h"

using namespace std;

namespace Ui {
class exeInitSetting;
}

class exeInitSetting : public QWidget
{
    Q_OBJECT

public:
    explicit exeInitSetting(QWidget *parent = nullptr);
    ~exeInitSetting();

    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *event);

    ExerciseScene* get_exeScene();
private:

    ExerciseScene * exeScene;

    Ui::exeInitSetting *ui;

signals:
    void back_to_chooseScene();

    void start_exe();
};

#endif // EXEINITSETTING_H
