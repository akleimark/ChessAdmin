QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    MVC.cpp \
    MemberListView.cpp \
    MemberModel.cpp \    
    Database.cpp \
    Table.cpp \
    MemberListController.cpp \
    Dialog.cpp \
    ListModel.cpp


HEADERS += \
    MainWindow.h \
    MVC.h \
    MemberListView.h \
    MemberModel.h \
    Misc.h \
    Database.h \
    Table.h \
    MemberListController.h \
    Dialog.h \
    ListModel.h



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
