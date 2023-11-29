#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "texteditor.h"

const int DEFAULT_WIDTH = 800;
const int DEFAULT_HEIGHT= 600;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionopen_triggered();

private:
    Ui::MainWindow *ui;
    TextEditor *t; //temporary
};
#endif // MAINWINDOW_H
