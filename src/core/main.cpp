#include "../gui/mainwindow.h"

#include <QApplication>
#include "donnees.h"

int main(int argc, char *argv[])
{
    Donnees* d = new Donnees();
    QApplication a(argc, argv);
    MainWindow w ( d );
    w.show();
    return a.exec();
}
