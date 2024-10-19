#ifndef MEMORYBROWSERWIDGET_H
#define MEMORYBROWSERWIDGET_H

#include "assembly.h"

#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QWidget>

namespace Ui {
class MemoryBrowserWidget;
}

class MemoryBrowserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MemoryBrowserWidget(QWidget *parent = nullptr);
    ~MemoryBrowserWidget();

    void setup(Assembly* a);

protected:
    void reset();

private:
    Ui::MemoryBrowserWidget *ui;

    QStandardItemModel    model;
    QSortFilterProxyModel proxy;

    QMap<uint64_t, uint8_t> persistentOverrides;

    Assembly* curAssembly;
};

#endif // MEMORYBROWSERWIDGET_H
