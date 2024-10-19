#include "memorybrowserwidget.h"
#include "ui_memorybrowserwidget.h"

MemoryBrowserWidget::MemoryBrowserWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MemoryBrowserWidget)
{
    ui->setupUi(this);
}

MemoryBrowserWidget::~MemoryBrowserWidget()
{
    delete ui;
}
