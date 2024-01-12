QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/src/command
INCLUDEPATH += $$PWD/src/core
INCLUDEPATH += $$PWD/src/preferences

SOURCES += \
    $$PWD/src/command/*.cpp \
	$$PWD/src/core/*.cpp \
	$$PWD/src/preferences/*.cpp \

HEADERS += \
    $$PWD/src/command/*.h \
	$$PWD/src/core/*.h \
	$$PWD/src/preferences/*.h \

FORMS += \
    # $$PWD/src/command/*.ui \
	$$PWD/src/core/*.ui \
	$$PWD/src/preferences/*.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    $$PWD/build-assets/caspian.png

DESTDIR = $$PWD
