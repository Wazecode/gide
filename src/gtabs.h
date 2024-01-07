#ifndef GTABS_H
#define GTABS_H

#include <QTabWidget>
#include <QWidget>
#include <QVector>

#include "gtexteditor.h"

class GTabs : public QTabWidget
{
private:
public:
    explicit GTabs(QWidget *parent = nullptr);
public slots:
    void newTextEditTab();
};

#endif // GTABS_H
