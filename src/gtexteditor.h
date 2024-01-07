#ifndef GTEXTEDITOR_H
#define GTEXTEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>

class GTextEditor : public QTextEdit
{
private:
    QString currfile;

public:
    explicit GTextEditor(QWidget *parent = nullptr);
    void setWindowTitle(QString t);

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
};

#endif // GTEXTEDITOR_H
