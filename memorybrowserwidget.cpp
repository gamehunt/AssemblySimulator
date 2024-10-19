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

void MemoryBrowserWidget::reset() {
    model.clear();
    proxy.setSourceModel(&model);
    ui->memoryTableView->setModel(&proxy);
}

void MemoryBrowserWidget::setup(Assembly* a) {
    curAssembly = a;

    QMap<uint64_t, uint8_t>& mem = curAssembly->getMemory()->getRaw();

    int w = curAssembly->getState()->getWidth();

    for(auto key : mem.keys()) {
        uint64_t v = mem[key];
        if(v) {
            model.appendRow({
                new QStandardItem(toHex(key, w)),
                new QStandardItem(toHex(v, w)),
            });
        }
    }

    proxy.setSourceModel(&model);
    ui->memoryTableView->setModel(&proxy);
}
