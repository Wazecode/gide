#pragma once

#include <QPlainTextEdit>
#include <QPainter>
#include "../utils/highlighter.h"

class GTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    GTextEdit(QWidget *parent = 0);
    QString getFilepath();
    QString getFileType();
    void setFilePath(QString newFilepath);
    void setFileType(QString newFileType);
    void setHighlighter(Highlighter * h);
    void setHighlighterTheme(QString theme);
    void selectLine();
    void selectWord();
    QString lineUnderCursor();
    QString wordUnderCursor();
    void deleteLine();
    void deleteWord();
    void joinLines();
    void swapLineUp();
    void swapLineDown();
    void toggleComment();
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    virtual void keyPressEvent(QKeyEvent * e) override;
    void resizeEvent(QResizeEvent *event) override;

public slots:

private:
    QString filepath;
    QString fileType;
    Highlighter * highlighter;
    QWidget *lineNumberArea;
private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &rect, int dy);

};

