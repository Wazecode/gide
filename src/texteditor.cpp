#include "texteditor.h"

TextEditor::TextEditor(QWidget *parent)
    : QTextEdit{parent}
{

}

void TextEditor::newFile()
{

}

void TextEditor::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    if(filename.isEmpty())
        return;

    QFile file(filename);
    currfile = filename;

    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot Open file: ", file.errorString());
    }

    QTextStream in(&file);
    QString text = in.readAll();
    this->setText(text);
    file.close();
}
