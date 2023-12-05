#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextEdit>

class TextEditor : public QTextEdit
{
    Q_OBJECT
private:
    QString currfile;
public:
    explicit TextEditor(QWidget *parent = nullptr);

    void openFile();
    void newFile();
    void saveFile();
    void saveFileAs();
    QString currentFilename();

signals:
};

#endif // TEXTEDITOR_H
