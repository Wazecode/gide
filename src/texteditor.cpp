#include "texteditor.h"

TextEditor::TextEditor(QWidget *parent)
    : QTextEdit{parent}
{

}

void TextEditor::open()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(filename);
    currfile = filename;

    QTextStream in(&file);
    QString text = in.readAll();
    this->setText(text);
    file.close();
}
