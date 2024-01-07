#include "gtexteditor.h"

GTextEditor::GTextEditor(QWidget *parent)
    :QTextEdit{parent}
{
    int fontWidth = QFontMetrics(this->currentCharFormat().font()).averageCharWidth();
    this->setTabStopDistance(3* fontWidth);
}

void GTextEditor::setWindowTitle(QString t)
{
    this->parentWidget()->setWindowTitle(t);
}

void GTextEditor::newFile()
{
    currfile.clear();
    this->setText(QString());
    setWindowTitle("Untitled");
}

void GTextEditor::openFile()
{

    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    if(filename.isEmpty())
        return;

    QFile file(filename);
    currfile = filename;

    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot Open file: " + file.errorString());
    }

    setWindowTitle(filename);

    QTextStream in(&file);
    QString text = in.readAll();
    this->setText(text);
    file.close();
}

void GTextEditor::saveFile()
{
    QString filename;
    if(currfile.isEmpty()) {
        filename = QFileDialog::getSaveFileName(this, "Save");
        currfile = filename;
        setWindowTitle(filename);
    }
    else {
        filename = currfile;
    }

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannont save file: " + file.errorString());
    }

    QTextStream out(&file);
    QString text = this->toPlainText();
    out << text;
    file.close();
}

void GTextEditor::saveFileAs()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as");

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannont save file: " + file.errorString());
    }

    currfile = filename;
    setWindowTitle(filename);

    QTextStream out(&file);
    QString text = this->toPlainText();
    out << text;
    file.close();
}



