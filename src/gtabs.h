#ifndef GTABS_H
#define GTABS_H

#include <QDebug>
#include <QTabWidget>
#include <QWidget>
#include <QShortcut>
#include <QKeySequence>

#include "gtexteditor.h"
//#include "gsettings.h"

class GTabs : public QTabWidget
{
    Q_OBJECT
private:
public:
    explicit GTabs(QWidget *parent = nullptr);
public slots:
    void newTextEditTab();
    void deleteCurrentTab();
    void openTextFile();
    void changeTabName(const QString &tabName);

private:
    void initShortcuts();
};

#endif // GTABS_H
