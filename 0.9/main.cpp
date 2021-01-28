#include "startscene.h"
#include "WindowIncludes.h"
#include <QApplication>


void delTempDirBeforeExit(){
    QDir * a =  new QDir;
    a->setPath(".\\TEMP");
    a->removeRecursively();
}

int main(int argc, char *argv[])
{
    atexit(delTempDirBeforeExit);
    QDir *tempFolder = new QDir;
    tempFolder->mkdir(".\\TEMP");

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QApplication a(argc, argv);
    StartScene w;
    w.show();
    return a.exec();
}
