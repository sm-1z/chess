QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += serialport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chess.cpp \
    chess_move_generator.cpp \
    chessengine.cpp \
    chessimages.cpp \
    chesspoint.cpp \
    chessvariate.cpp \
    engine.cpp \
    front.cpp \
    hyperai.cpp \
    main.cpp \
    mainwindow.cpp \
    networker.cpp \
    ocr.cpp \
    port.cpp

HEADERS += \
    chess.h \
    chess_move_generator.h \
    chessengine.h \
    chessimages.h \
    chesspoint.h \
    chessvariate.h \
    engine.h \
    front.h \
    hyperai.h \
    mainwindow.h \
    networker.h \
    ocr.h \
    port.h

FORMS += \
    chess.ui \
    engine.ui \
    front.ui \
    mainwindow.ui \
    ocr.ui \
    port.ui

LIBS     += -L$$quote(C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\um\arm64\User32.Lib)


TRANSLATIONS += \
    untitled_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images/res.qrc
