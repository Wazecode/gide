#include "gtabs.h"

GTabs::GTabs(QWidget *parent)
    :QTabWidget{parent}
{
    //Shorcuts
}

void GTabs::newTextEditTab()
{
    this->addTab(new GTextEditor, "Untitled");
}
