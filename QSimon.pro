QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Objects/button.cpp \
    Objects/movescontainer.cpp \
    Visitors/graphicvisitor.cpp \
    gamewidget.cpp \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    Objects/button.h \
    Objects/downbutton.h \
    Objects/leftbutton.h \
    Objects/movescontainer.h \
    Objects/rightbutton.h \
    Objects/upbutton.h \
    Visitors/equalityvisitor.h \
    Visitors/graphicvisitor.h \
    Visitors/visitor.h \
    gamewidget.h \
    mainwindow.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
