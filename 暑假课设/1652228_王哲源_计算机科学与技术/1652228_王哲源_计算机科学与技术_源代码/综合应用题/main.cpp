#include "mapwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MapWindow mapW;
    mapW.show();

    return a.exec();
}
