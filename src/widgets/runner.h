#ifndef RUNNER_H
#define RUNNER_H

#include <QDialog>
#include <QProcess>
#include <QFileInfo>
#include <QThread>

namespace Ui {
class Runner;
}

class Runner : public QDialog
{
    Q_OBJECT

public:
    explicit Runner(QWidget *parent = nullptr, QString file = "");
    ~Runner();

    enum language {
        cpp,
        py,
        java
    };

    language currLang;

private:
    Ui::Runner *ui;

    void onRunPressed();
    void onCompilePressed();
    void onClosePressed();

    void updateText();
    void updateError();

    //Languages Config

    void setCurrLang();

    void cppInit();
    void cppCompile();
    void cppRun();

    void pyInit();
    void pyRun();

    void javaInit();
    void javaCompile();
    void javaRun();

    void log(QString text, QString color);
    void logExit();

    QFileInfo fileinfo;
    QProcess *shell;

};

#endif // RUNNER_H
