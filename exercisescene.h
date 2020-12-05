#ifndef EXERCISESCENE_H
#define EXERCISESCENE_H

#include "WindowIncludes.h"

#include  "LogOperation.h"
#include "_pushbutton.h"
#include "exercisereport.h"

namespace Ui {
class ExerciseScene;
}

class ExerciseScene : public QMainWindow
{
    Q_OBJECT

public:
    void initExe();

    explicit ExerciseScene(QWidget *parent = nullptr);
    ~ExerciseScene();

    void closeEvent(QCloseEvent * ev);

    _PushButton * giveAnswerBtn;

    void StartEXE();

    void start_time();

    void start_group();

    void randomSort_Put();

    void answer_given_operate();

    void refresh_output();

    int exeTime; //进行轮数
    int groupNum; //进行组数

    KanasExercise * exeInfo;

    void set_exeReport(ExerciseReport *er);

    void give_value_to_exeReport();

    void setBg(QString filePath);


private:
    ExerciseReport * exeReport;
    Ui::ExerciseScene *ui;
signals:
    void DOEXE();
    void FGA();
    void open_setting();
public slots:
    void forcefullyGiveAnswer();
    void updateTimer();
    void TimerSetToZero();

};

#endif // EXERCISESCENE_H
