#include "mainwindow.h"

#include <QApplication>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Connection c("airport");

    w.show();
    return a.exec();
}
