QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    eat.cpp \
    main.cpp \
    dialog.cpp \
    pairpal.cpp \
    play.cpp \
    registerpage.cpp \
    self.cpp \
    sport.cpp \
    study.cpp

HEADERS += \
    dialog.h \
    eat.h \
    pairpal.h \
    play.h \
    registerpage.h \
    self.h \
    sport.h \
    study.h

FORMS += \
    dialog.ui \
    eat.ui \
    pairpal.ui \
    play.ui \
    registerpage.ui \
    self.ui \
    sport.ui \
    study.ui

TRANSLATIONS += \
    page1_zh_CN.ts


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
