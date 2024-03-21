#include "runner.h"
#include "ui_runner.h"

Runner::Runner(QWidget *parent, QString file)
    : QDialog(parent)
    , ui(new Ui::Runner)
    , fileinfo(file)
{
    ui->setupUi(this);
    setCurrLang();

    shell = new QProcess(this);

    shell->setWorkingDirectory(fileinfo.absolutePath());

    switch(currLang) {
    case language::cpp : cppInit();
        break;
    case language::py : pyInit();
        break;
    case language::java : javaInit();
        break;
    }

    connect(ui->runButton, &QPushButton::clicked, this, &Runner::onRunPressed);
    connect(ui->compileButton, &QPushButton::clicked, this, &Runner::onCompilePressed);
    connect(ui->closeButton, &QPushButton::clicked, this, &Runner::onClosePressed);

    connect(shell, &QProcess::readyReadStandardOutput, this, &Runner::updateText);
    connect(shell, &QProcess::readyReadStandardError, this, &Runner::updateError);

    log("Greetings from the console", "blue");

}

Runner::~Runner()
{
    delete ui;
    delete shell;
}

void Runner::onRunPressed()
{
    switch(currLang) {
    case language::cpp : cppRun();
        break;
    case language::py : pyRun();
        break;
    case language::java : javaRun();
        break;
    }
}

void Runner::onCompilePressed()
{
    switch (currLang) {
    case language::cpp: cppCompile();
        break;
    case language::java: javaCompile();
    default:
        break;
    }
}

void Runner::onClosePressed()
{
    this->close();
}

void Runner::updateText()
{
    QByteArray b = shell->readAllStandardOutput();
    log(QString(b), "white");
}

void Runner::updateError()
{
    QByteArray b = shell->readAllStandardError();
    log(QString(b), "white");
}

void Runner::setCurrLang()
{
    if(fileinfo.suffix() == "cpp")
        currLang = language::cpp;
    else if(fileinfo.suffix() == "py")
        currLang = language::py;
    else if(fileinfo.suffix() == "java")
        currLang = language::java;
}

void Runner::cppInit()
{
    ui->compileLineEdit->setText("g++");
    ui->sourceLineEdit->setText(fileinfo.fileName());
    ui->runLineEdit->setText("./" + fileinfo.fileName() + ".out");
}

void Runner::cppCompile()
{
    QString compiler = ui->compileLineEdit->text();
    QStringList args;
    args << ui->sourceLineEdit->text();
    QString output = "-o" + fileinfo.fileName() + ".out";
    args << output;

    //run
    shell->start(compiler, args);
    shell->waitForFinished();
    if(shell->exitCode() == 0)
        log("Compiled Successfully", "green");
    else
        log("Compilation Falied", "red");
}

void Runner::cppRun()
{
    shell->start(ui->runLineEdit->text());
    logExit();
}

void Runner::pyInit()
{
    ui->compileButton->hide();
    ui->runLabel->hide();
    ui->runLineEdit->hide();
    ui->compileLineEdit->setText("python");
    ui->sourceLineEdit->setText(fileinfo.fileName());
}

void Runner::pyRun()
{
    QStringList args;
    const QString compiler = ui->compileLineEdit->text();
    args << ui->sourceLineEdit->text();
    shell->start(compiler, args);
    logExit();
}

void Runner::javaInit()
{
    ui->compileLineEdit->setText("javac");
    ui->sourceLineEdit->setText(fileinfo.fileName());
}

void Runner::javaCompile()
{
    QString compiler = ui->compileLineEdit->text();
    QStringList args;
    args << ui->sourceLineEdit->text();

    shell->start(compiler, args);
    shell->waitForFinished();
    if(shell->exitCode() == 0)
        log("Compiled Successfully", "green");
    else
        log("Compilation Falied", "red");
}

void Runner::javaRun()
{
    QStringList args;
    const QString jvm = "java";
    args << fileinfo.baseName();
    shell->start(jvm, args);
    logExit();
}

void Runner::log(QString text, QString color)
{
    ui->console->setTextColor(QColor(color));
    ui->console->append(text);
}

void Runner::logExit()
{
    shell->waitForFinished();
    const QString consoleOut = "Exit code:" + QString::number(shell->exitCode());
    log(consoleOut, "gray");
}
