#pragma once
#include <QWidget>
#include "gtextedit.h"

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(GTextEdit *editor) : QWidget(editor), codeEditor(editor)
    {}

    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    GTextEdit *codeEditor;
};
