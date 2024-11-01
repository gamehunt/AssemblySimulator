#ifndef MEMORYBROWSERWIDGET_H
#define MEMORYBROWSERWIDGET_H

#include "libs/LibAssembly/assembly.h"

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
    void injectMemory();

public slots:
    void addData();
    void removeData(QModelIndex index);
    void editData(QModelIndex index);
    void push();
    void pop();
    void refresh();


protected slots:
    void updateButtonStates();
    void refreshTable();

protected:
    void reset();

private:
    Ui::MemoryBrowserWidget *ui;

    QStandardItemModel    model;
    QSortFilterProxyModel proxy;

    QMap<uint64_t, uint64_t> persistentData;

    Assembly* curAssembly;
};

#endif // MEMORYBROWSERWIDGET_H
