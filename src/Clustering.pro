QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clustering/hierarchical.cpp \
    clustering/kmeannotes.cpp \
    clustering/kmedians.cpp \
    clustering/dbscan.cpp \
    clustering/pam.cpp \
    core/note.cpp \
    core/notes.cpp \
    data_science/acp.cpp \
    clustering/kmeans.cpp \
    core/distance.cpp \
    core/donnees.cpp \
    core/main.cpp \
    core/sommet.cpp \
    gui/mainwindow.cpp \
    gui/scene.cpp

HEADERS += \
    clustering/hierarchical.h \
    clustering/kmeannotes.h \
    clustering/kmedians.h \
    clustering/dbscan.h \
    clustering/pam.h \
    core/note.h \
    core/notes.h \
    data_science/acp.h \
    clustering/kmeans.h \
    core/distance.h \
    core/donnees.h \
    core/sommet.h \
    gui/mainwindow.h \
    gui/scene.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
