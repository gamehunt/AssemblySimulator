#ifndef MEMORYBROWSERWIDGET_H
#define MEMORYBROWSERWIDGET_H

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

private:
    Ui::MemoryBrowserWidget *ui;
};

#endif // MEMORYBROWSERWIDGET_H
