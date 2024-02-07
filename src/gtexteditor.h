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
    Q_OBJECT
private:
    QString _currfile;
    QString _filename;
    void initShortcuts();

public:
    explicit GTextEditor(QWidget *parent = nullptr);
    const QString getFilenameFromPath();

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
signals:
    void fileNameChanged(const QString &newFilename);
};

#endif // GTEXTEDITOR_H
