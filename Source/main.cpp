#include "fileparser.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FileParser fparser;
    CIEVector cieVector = fparser.Read();
    MainWindow w(cieVector);
    w.show();
    return a.exec();
}
