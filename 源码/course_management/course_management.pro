QT       += core gui charts network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    charttable.cpp \
    coursenode.cpp \
    listtable.cpp \
    main.cpp \
    mainwindow.cpp \
    netwidget.cpp \
    searchwidget.cpp \
    sortwidget.cpp

HEADERS += \
    charttable.h \
    coursenode.h \
    listtable.h \
    mainwindow.h \
    netwidget.h \
    searchwidget.h \
    sortm.h \
    sortwidget.h\
    ConnectStatus.h

FORMS += \
    charttable.ui \
    listtable.ui \
    mainwindow.ui \
    netwidget.ui \
    searchwidget.ui \
    sortwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
