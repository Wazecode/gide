#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->centralWidget()->setStyleSheet("background-image:url(\"/home/shuwais/Documents/Projects/gide/img/gideLogo.svg\"); background-position: center; ");

    setWindowTitle("GIDE");

    // ------Signals------------

    connect(ui->actionFull_Screen, &QAction::triggered, this, &MainWindow::onActionFullScreenTriggered);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::onActionExitTriggered);
    connect(ui->actionShow_Menu_Bar, &QAction::triggered, this, &MainWindow::onActionShowMenuBarTriggered);

    tabs = new GTabs(this);
    this->setCentralWidget(tabs);
    this->adjustSize();

    connect(ui->actionNew, &QAction::triggered, tabs, &GTabs::newTextEditTab);

    // tabs = new QTabWidget(this);
    // this->setCentralWidget(tabs);
    // tabs->resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    // tabs->setTabBarAutoHide(true);

    // TextEditor *t= new TextEditor(this);
    // TextEditor *t2= new TextEditor(this);
    // tabs->addTab(t,"Lorme");
    // tabs->addTab(t2,"ispum");

    //TextEditor Shortcuts
    // connect(ui->actionNew, &QAction::triggered, t, &TextEditor::newFile);
    // connect(ui->actionOpen, &QAction::triggered, t, &TextEditor::openFile);
    // connect(ui->actionSave, &QAction::triggered, t, &TextEditor::saveFile);
    // connect(ui->actionSave_As, &QAction::triggered, t, &TextEditor::saveFileAs);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::onActionShowMenuBarTriggered()
{
    if(ui->menubar->isVisible())
        ui->menubar->hide();
}

// void MainWindow::initializeShortcuts()
// {
//     new QShortcut(QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_Q), this, &MainWindow::onActionShowMenuBarTriggered);
// }
