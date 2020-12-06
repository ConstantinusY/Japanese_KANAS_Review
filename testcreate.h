#ifndef TESTCREATE_H
#define TESTCREATE_H

#include <QMainWindow>
#include "WindowIncludes.h"

namespace Ui {
class TestCreate;
}

class TestCreate : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestCreate(QWidget *parent = nullptr);
    ~TestCreate();

    string filePath;

    string test;

    void closeEvent(QCloseEvent * ev);

    void setBg(QString filePath);

private:
    Ui::TestCreate *ui;

signals:
    void back_to_chooseScene();

    void open_setting();

};

#endif // TESTCREATE_H
