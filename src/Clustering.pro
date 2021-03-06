QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clustering/dbscannote.cpp \
    clustering/hierarchical.cpp \
    clustering/hierarchicalnotes.cpp \
    clustering/kmeannotes.cpp \
    clustering/kmediannotes.cpp \
    clustering/kmedians.cpp \
    clustering/dbscan.cpp \
    clustering/pam.cpp \
    core/note.cpp \
    core/notes.cpp \
    clustering/kmeans.cpp \
    core/distance.cpp \
    core/donnees.cpp \
    core/main.cpp \
    core/sommet.cpp \
    data_science/acp.cpp \
    data_science/acpNotes.cpp \
    data_science/analysecleandata.cpp \
    gui/mainwindow.cpp \
    gui/scene.cpp \
    matrice/matrice.cpp \
    matrice/vecteur.cpp \

HEADERS += \
    clustering/dbscannote.h \
    clustering/hierarchical.h \
    clustering/hierarchicalnotes.h \
    clustering/kmeannotes.h \
    clustering/kmediannotes.h \
    clustering/kmedians.h \
    clustering/dbscan.h \
    clustering/pam.h \
    core/note.h \
    core/notes.h \
    clustering/kmeans.h \
    core/distance.h \
    core/donnees.h \
    core/sommet.h \
    data_science/acp.h \
    data_science/acpNotes.h \
    data_science/analysecleandata.h \
    gui/mainwindow.h \
    gui/scene.h \
    matrice/matrice.h \
    matrice/vecteur.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
