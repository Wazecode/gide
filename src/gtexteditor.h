#ifndef GTEXTEDITOR_H
#define GTEXTEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QShortcut>
#include <QKeySequence>

class GTextEditor : public QTextEdit
{
private:
    QString currfile;
    void initShortcuts();

public:
    explicit GTextEditor(QWidget *parent = nullptr);
    void setWindowTitle(const QString &t);

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
};

#endif // GTEXTEDITOR_H
