#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    t = new TextEditor(this);
    this->setCentralWidget(t);
    t->resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    this->adjustSize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionopen_triggered()
{
    t->openFile();
    t->show();
}

