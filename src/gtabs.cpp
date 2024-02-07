#include "gtabs.h"

GTabs::GTabs(QWidget *parent)
    :QTabWidget{parent}
{
    setTabsClosable(true);
    initShortcuts();

}

void GTabs::changeTabName(const QString &t)
{
    parentWidget()->setWindowTitle(t);
    setTabText(currentIndex(), t);
}

void GTabs::newTextEditTab()
{
    GTextEditor *t = new GTextEditor(this);
    this->addTab(t, "Untitled");
    this->setCurrentIndex(this->count() - 1);
    connect(t, SIGNAL(fileNameChanged(QString)), this, SLOT(changeTabName(QString)));
    t->setFocus();
}

void GTabs::deleteCurrentTab()
{
    this->removeTab(this->currentIndex());
}

void GTabs::openTextFile()
{
    GTextEditor *t = new GTextEditor(this);
    this->addTab(t, "");
    this->setCurrentIndex(this->count() - 1);
    t->openFile();
    changeTabName(t->getFilenameFromPath());
    t->setFocus();
}

void GTabs::initShortcuts()
{

    //Open File
    {
        QShortcut *s = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")), this);
        connect(s, &QShortcut::activated, this, &GTabs::openTextFile);
    }

    //Add tab or New File
    {
        QShortcut *s = new QShortcut(QKeySequence(tr("Ctrl+T", "Tabs|add")), this);
        connect(s, &QShortcut::activated, this, &GTabs::newTextEditTab);
    }

    //delete tab
    {
        QShortcut *s = new QShortcut(QKeySequence(tr("Ctrl+W", "Tabs|delete")), this);
        connect(s, &QShortcut::activated, this, &GTabs::deleteCurrentTab);
    }

    //Got to tab i
    for(int i=1; i <= 10; i++)
    {
        std::string str = "Alt+" + std::to_string(i);
        QShortcut *s = new QShortcut(QKeySequence(tr(str.c_str())), this);
        connect(s, &QShortcut::activated, this, [this, i](){
            setCurrentIndex(i-1);
        });
    }

    //When Tab Close button is pressed
    connect(this, &GTabs::tabCloseRequested, this , &GTabs::removeTab);

    //Test
    {
        QShortcut *s = new QShortcut(QKeySequence(tr("Ctrl+K", "Tabs|delete")), this);
        connect(s, &QShortcut::activated, this, [this]() {
            setWindowTitle("Testing Change");
        });
    }


}
