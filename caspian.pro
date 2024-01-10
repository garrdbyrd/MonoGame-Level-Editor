QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    config.cpp \
    customtoolbar.cpp \
    doublespinboxwidget.cpp \
    filebrowsewidget.cpp \
    main.cpp \
    caspian.cpp \
    maingraphicsview.cpp \
    preferencesdialog.cpp \
	selectablelabel.cpp \
    spinboxwidget.cpp

HEADERS += \
    caspian.h \
    config.h \
    customtoolbar.h \
    doublespinboxwidget.h \
    filebrowsewidget.h \
    maingraphicsview.h \
    preferencesdialog.h \
	selectablelabel.h \
    spinboxwidget.h

FORMS += \
    caspian.ui \
    preferencesdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    caspian.png

DESTDIR = $$PWD
