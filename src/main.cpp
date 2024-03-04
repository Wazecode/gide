#include <QApplication>
#include "mainwindow.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("GIDE");
    a.setOrganizationName("GIDE");

    MainWindow w;
    w.show();
    if(argc > 1){
        w.openWith(QString::fromStdString(argv[1]));
    }
    
    return a.exec();
}
