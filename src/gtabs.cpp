#include "gtabs.h"

GTabs::GTabs(QWidget *parent)
    :QTabWidget{parent}
{
    setTabsClosable(true);
    connect(this, &QTabWidget::tabCloseRequested, this , []() {
        qDebug() << "Hello";
    });
    initShortcuts();
}

void GTabs::setWindowTitle(const QString &t)
{
    this->parentWidget()->setWindowTitle(t);
    setTabText(currentIndex(), t);
    qDebug() << "GTabs\n";
}

void GTabs::newTextEditTab()
{
    this->addTab(new GTextEditor(this), "Untitled");
    this->setCurrentIndex(this->count() - 1);
}

void GTabs::deleteCurrentTab()
{
    this->removeTab(this->currentIndex());
}

void GTabs::initShortcuts()
{
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
}
