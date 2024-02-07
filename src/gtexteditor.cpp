#include "gtexteditor.h"

GTextEditor::GTextEditor(QWidget *parent)
    :QTextEdit{parent}
{
    int fontWidth = QFontMetrics(this->currentCharFormat().font()).averageCharWidth();
    this->setTabStopDistance(3* fontWidth);
    initShortcuts();
}

void GTextEditor::newFile()
{
    _currfile.clear();
    this->setText(QString());
    setWindowTitle("Untitled");
}

void GTextEditor::openFile()
{

    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    if(filename.isEmpty())
        return;

    QFile file(filename);
    _currfile = filename;


    emit fileNameChanged(getFilenameFromPath());

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
    if(_currfile.isEmpty()) {
        filename = QFileDialog::getSaveFileName(this, "Save");
        _currfile = filename;
        // setWindowTitle(filename);
    }
    else {
        filename = _currfile;
    }

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannont save file: " + file.errorString());
    }
    emit fileNameChanged(getFilenameFromPath());

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
    file.symLinkTarget();

    _currfile = filename;
    // setWindowTitle(filename);
    emit fileNameChanged(getFilenameFromPath());

    QTextStream out(&file);
    QString text = this->toPlainText();
    out << text;
    file.close();
}


void GTextEditor::initShortcuts()
{
    //Save File
    {
        QShortcut *s = new QShortcut(QKeySequence(tr("Ctrl+S", "File|Save")), this);
        connect(s, &QShortcut::activated, this, &GTextEditor::saveFile);
    }

    //Save File as
    {
        QShortcut *s = new QShortcut(QKeySequence(tr("Ctrl+Shift+S", "File|Save as")), this);
        connect(s, &QShortcut::activated, this, &GTextEditor::saveFileAs);
    }
}

const QString GTextEditor::getFilenameFromPath()
{
    if(_currfile.isEmpty()) {
        return "Untitled";
    }
    else {
        QFileInfo fileInfo(_currfile);
        return fileInfo.fileName();
    }
}
