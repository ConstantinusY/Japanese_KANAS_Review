#ifndef EXERCISEREPORT_H
#define EXERCISEREPORT_H

#include <QMainWindow>
#include "WindowIncludes.h"
using namespace std;

namespace Ui {
class ExerciseReport;
}

class ExerciseReport : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExerciseReport(QWidget *parent = nullptr);
    ~ExerciseReport();

    void closeEvent(QCloseEvent * event);

    int allKanaNum;

    int allRightKanaNum;

    int allFalseKanaNum;

    float usedTime;
    vector<string>falseKanaList;

    map<string,string>kana_dict;

    void showInfo();

    void setBg(QString filePath);
private:
    Ui::ExerciseReport *ui;
signals:
    void back_to_choose();
    void open_setting();

};

#endif // EXERCISEREPORT_H
