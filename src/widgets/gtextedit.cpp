#include "gtextedit.h"
#include "linenumberarea.h"

GTextEdit::GTextEdit(QWidget *parent) :
    QPlainTextEdit(parent)
{
    filepath = "";
    fileType = "";
    highlighter = NULL;

    lineNumberArea = new LineNumberArea(this);

    connect(this, &GTextEdit::blockCountChanged, this, &GTextEdit::updateLineNumberAreaWidth);
    connect(this, &GTextEdit::updateRequest, this, &GTextEdit::updateLineNumberArea);
    updateLineNumberAreaWidth(0);
}

/*
 *****************************
 *        Editing            *
 *****************************
*/

// Selects Current Line Where Cursor Is Positioned
void GTextEdit::selectLine(){
    QTextCursor cur = this->textCursor();
    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    this->setTextCursor(cur);
}

// Selects Current Word Where Cursor Is Positioned
void GTextEdit::selectWord(){
    QTextCursor cur = this->textCursor();
    cur.movePosition(QTextCursor::StartOfWord, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
    this->setTextCursor(cur);
}

// Returns Word Under Cursor
QString GTextEdit::lineUnderCursor(){
    selectLine();
    QTextCursor cur = this->textCursor();
    QString line = cur.selectedText();
    cur.clearSelection();
    this->setTextCursor(cur);
    return line;
}

// Returns Word Under Cursor
QString GTextEdit::wordUnderCursor(){
    selectWord();
    QTextCursor cur = this->textCursor();
    QString word = cur.selectedText();
    cur.clearSelection();
    this->setTextCursor(cur);
    return word;
}

// Deletes Current Line Where Cursor Is Positioned
void GTextEdit::deleteLine(){
    selectLine();
    QTextCursor cur = this->textCursor();
    if(cur.selectedText() != ""){
        cur.removeSelectedText();
    }
    this->setTextCursor(cur);
}

// Deletes Current Word Where Cursor Is Positioned
void GTextEdit::deleteWord(){
    selectWord();
    QTextCursor cur = this->textCursor();

    if (cur.selectedText() != ""){
        cur.removeSelectedText();
    }

    this->setTextCursor(cur);
}

// Joins Line Where Cursor Is Currently Positioned With The Line Below It
void GTextEdit::joinLines(){
    QTextCursor cur = this->textCursor();

    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
    cur.deleteChar();

    this->setTextCursor(cur);
}

// Swaps Line Where Cursor Is Currently Positioned With The Line Above It
void GTextEdit::swapLineUp(){
    QTextCursor cur = this->textCursor();
    //  Select Current Line And Store Value
    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    QString newTop = cur.selectedText();
    cur.removeSelectedText();
    // Select Line Above And Store Value
    cur.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    QString newBottom = cur.selectedText();
    cur.removeSelectedText();
    // Insert New Values
    cur.insertText(newTop);
    cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
    cur.insertText(newBottom);
    // Position Cursor
    cur.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);

    this->setTextCursor(cur);
}

// Swaps Line Where Cursor Is Currently Positioned With The Line Below It
void GTextEdit::swapLineDown(){
    QTextCursor cur = this->textCursor();
    //  Select Current Line And Store Value
    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    QString newBottom = cur.selectedText();
    cur.removeSelectedText();
    // Select Line Below And Store Value
    cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    QString newTop = cur.selectedText();
    cur.removeSelectedText();
    // Insert New Values
    cur.insertText(newBottom);
    cur.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
    cur.insertText(newTop);
    // Position Cursor
    cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);

    this->setTextCursor(cur);
}



/*
 *  Toggles currently selected line(s) between commented out and uncommented
 *  Comments based on language of file type
 *  If no text is selected then it selects the current line
*/
void GTextEdit::toggleComment(){
    QTextCursor cur = this->textCursor();
    if (!cur.hasSelection()){
        selectLine();
    }

    int endSelection = cur.selectionEnd();
    cur.setPosition(cur.selectionStart());
    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    this->setTextCursor(cur);

    QString line = lineUnderCursor();

    QString commentStart;
    QString commentEnd;

    if(fileType == "html" or fileType == "css"){

        if(fileType == "html"){
            commentStart = "<!--";
            commentEnd = "-->";
        }else{
            commentStart = "/*";
            commentEnd = "*/";
        }

        if(line.startsWith(commentStart)){
            for(int i=0; i < commentStart.length(); i++){
                cur.deleteChar();
            }
            endSelection -= commentStart.length();

            cur.setPosition(endSelection);
            cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
            this->setTextCursor(cur);
            QString line = lineUnderCursor();

            if(line.endsWith(commentEnd)){
                for(int i=0; i < commentEnd.length(); i++){
                    cur.deletePreviousChar();
                }
            }
        }else{
            cur.insertText(commentStart);
            endSelection += commentStart.length();

            cur.setPosition(endSelection);
            cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
            this->setTextCursor(cur);
            QString line = lineUnderCursor();

            if(!line.endsWith(commentEnd)){
                cur.insertText(commentEnd);
            }
        }

    }else{
        if(fileType == "py"){
            commentStart = "#";
        }else{
            commentStart = "//";
        }

        if(line.startsWith(commentStart)){
            for(int i=0; i < commentStart.length(); i++){
                cur.deleteChar();
            }
            endSelection -= commentStart.length();
            cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);

            while(cur.position() < endSelection){
                cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
                this->setTextCursor(cur);
                line = lineUnderCursor();

                if(line.startsWith(commentStart)){
                    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
                    for(int i=0; i < commentStart.length(); i++){
                        cur.deleteChar();
                    }
                    endSelection -= commentStart.length();

                }
                cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);

            }

        }else{
            cur.insertText(commentStart);
            endSelection += commentStart.length();
            cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);

            while(cur.position() < endSelection){
                cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
                this->setTextCursor(cur);
                line = lineUnderCursor();

                if(!line.startsWith(commentStart)){
                    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
                    cur.insertText(commentStart);
                    endSelection += commentStart.length();
                }

                cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
            }
        }

    }

    this->setTextCursor(cur);
}

void GTextEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::black);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::lightGray);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

int GTextEdit::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void GTextEdit::setHighlighterTheme(QString theme){
    if (highlighter != NULL){
        highlighter->setTheme(fileType, theme);
    }
}

void GTextEdit::setHighlighter(Highlighter * h){
    if(highlighter != NULL){
        delete highlighter;
    }

    highlighter = h;
}

/*
 *****************************
 *         File Info         *
 *****************************
*/
QString GTextEdit::getFilepath(){
    return filepath;
}

QString GTextEdit::getFileType(){
    return fileType;
}

void GTextEdit::setFilePath(QString newFilepath){
    filepath = newFilepath;
}
void GTextEdit::setFileType(QString newFileType){
    fileType = newFileType;
}

/*
 *****************************
 *         Virtual functions *
 *****************************
*/

void GTextEdit::keyPressEvent ( QKeyEvent * e ){
    // Indent Selection On Tab
    if(e->key() == 16777217){
        QTextCursor cur = this->textCursor();
        if (cur.hasSelection()){
            int endSelection = cur.selectionEnd();
            cur.setPosition(cur.selectionStart());
            cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
            cur.insertText("\t");
            endSelection++;
            cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
            while(cur.position() < endSelection){
                cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
                cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
                cur.insertText("\t");
                endSelection++;
                cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
            }

            this->setTextCursor(cur);

        }else{
            QPlainTextEdit::keyPressEvent(e);
        }

    }else if(e->key() == 16777218){
        // Unindent Selection On Backtab
        QTextCursor cur = this->textCursor();
        if (!cur.hasSelection()){
            selectLine();
        }
        int endSelection = cur.selectionEnd();
        cur.setPosition(cur.selectionStart());
        cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
        cur.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
        QString line = cur.selectedText();
        cur.clearSelection();
        if(line.startsWith("\t")){
            cur.deleteChar();
            endSelection -= 1;
        }

        cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
        while(cur.position() < endSelection){
            cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
            cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
            cur.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
            QString line = cur.selectedText();
            cur.clearSelection();
            if(line.startsWith("\t")){
                cur.deleteChar();
                endSelection -= 1;
            }
            cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
        }

        this->setTextCursor(cur);

    }else{
        QPlainTextEdit::keyPressEvent(e);
    }
}

void GTextEdit::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void GTextEdit::updateLineNumberAreaWidth(int newBlockCount)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void GTextEdit::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}
