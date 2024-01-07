#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QShortcut>
#include <QKeySequence>
#include <QTabBar>
#include <QPixmap>

#include "gtexteditor.h"
#include "gtabs.h"

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
    void onActionFullScreenTriggered();

    void onActionExitTriggered();

    void onActionShowMenuBarTriggered();

private:
    Ui::MainWindow *ui;
    GTextEditor *t; //Temp

    GTabs *tabs;

    void initializeShortcuts();
};
#endif // MAINWINDOW_H
