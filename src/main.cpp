#include "mainwindow.h"
#include "texteditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    TextEditor t;
    t.show();
    return a.exec();
}
