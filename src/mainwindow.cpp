#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("GIDE");

    // ------Signals------------

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNewTriggered);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onActionOpenTriggered);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onActionSaveTriggered);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::onActionSaveAsTriggered);
    connect(ui->actionFull_Screen, &QAction::triggered, this, &MainWindow::onActionFullScreenTriggered);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::onActionExitTriggered);

    t = new TextEditor(this);
    this->setCentralWidget(t);
    t->resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    this->adjustSize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//--------------Files------------------------
void MainWindow::onActionNewTriggered() {
    t->newFile();
}
void MainWindow::onActionOpenTriggered()
{
    t->openFile();
    t->show();
}

void MainWindow::onActionSaveTriggered()
{
    t->saveFile();
}

void MainWindow::onActionSaveAsTriggered()
{
    t->saveFileAs();
}


//-----------Window---------------------------
void MainWindow::onActionFullScreenTriggered()
{
    if(isFullScreen())
        showNormal();
    else
        showFullScreen();

}


void MainWindow::onActionExitTriggered()
{
    QApplication::quit();
}
