#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    w.show();

    return a.exec();
}
