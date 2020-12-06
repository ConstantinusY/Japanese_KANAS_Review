QT       += core gui
QT       += multimediawidgets
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += resources_big

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    LogOperation.cpp \
    _pushbutton.cpp \
    allkanas.cpp \
    bgmsetting.cpp \
    choosescene.cpp \
    exeinitsetting.cpp \
    exercisereport.cpp \
    exercisescene.cpp \
    helpwidget.cpp \
    kanasexercise.cpp \
    main.cpp \
    startscene.cpp \
    testcreate.cpp

HEADERS += \
    LogOperation.h \
    WindowIncludes.h \
    _pushbutton.h \
    allkanas.h \
    bgmsetting.h \
    choosescene.h \
    exeinitsetting.h \
    exercisereport.h \
    exercisescene.h \
    helpwidget.h \
    kanasexercise.h \
    startscene.h \
    testcreate.h

FORMS += \
    bgmsetting.ui \
    choosescene.ui \
    exeinitsetting.ui \
    exercisereport.ui \
    exercisescene.ui \
    helpwidget.ui \
    startscene.ui \
    testcreate.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

# -----------------------------------------------
# program designed by Constantinus_Yang(YANG MING LIN)
# program finished on 2020/11/19
# License: MIT license
# -----------------------------------------------
