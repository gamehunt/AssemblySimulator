#include "memorybrowserwidget.h"
#include "ui_memorybrowserwidget.h"

#include <QMessageBox>
#include <memoryeditdialog.h>

MemoryBrowserWidget::MemoryBrowserWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MemoryBrowserWidget)
{
    ui->setupUi(this);

    QObject::connect(ui->addButton, &QPushButton::clicked, this, &MemoryBrowserWidget::addData);
    QObject::connect(ui->memoryTableView, &QTableView::doubleClicked, this, &MemoryBrowserWidget::editData);
    QObject::connect(ui->removeButton, &QPushButton::clicked, this, [this]() {
        if(ui->memoryTableView->selectionModel()->hasSelection()) {
            removeData(ui->memoryTableView->selectionModel()->selectedRows().first());
        }
    });

    reset();

    QObject::connect(ui->memoryTableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MemoryBrowserWidget::updateButtonStates);
    updateButtonStates();
}

MemoryBrowserWidget::~MemoryBrowserWidget()
{
    delete ui;
}

void MemoryBrowserWidget::updateButtonStates() {
    if(ui->memoryTableView->selectionModel() == nullptr) {
        ui->removeButton->setEnabled(false);
        return;
    }
    ui->removeButton->setEnabled(ui->memoryTableView->selectionModel()->hasSelection());
}

void MemoryBrowserWidget::reset() {
    model.clear();
    refreshTable();
}

void MemoryBrowserWidget::refreshTable() {
    proxy.setSourceModel(&model);
    ui->memoryTableView->setModel(&proxy);
    ui->memoryTableView->resizeColumnsToContents();
}

void MemoryBrowserWidget::setup(Assembly* a) {
    curAssembly = a;
    model.clear();

    if(!curAssembly) {
        goto end;
    }

    QMap<uint64_t, uint8_t>& mem = curAssembly->getMemory()->getRaw();

    int w = curAssembly->getState()->getWidth();

    QMap<uint64_t, uint64_t> values;

    QList addresses = mem.keys().toList();
    std::sort(addresses.begin(), addresses.end());

    for(int i = 0; i < addresses.size(); i++) {
        uint64_t addr = addresses[i];
        uint64_t v = mem[addr];
        int skip = 0;
        for(int j = 1; j < 4; j++) {
            uint8_t sv = mem.value(addr + j, 0);
            v |= (sv << j * 8);
            if(addresses[i + j] == addr + j) {
                skip++;
            }
        }
        i += skip;
        values[addr] = v;
    }

end:
    for(auto key: persistentData.keys()) {
        addresses.append(key);
        uint64_t v = persistentData[key];
        if(v) {
            values[key] = v;
        }
    }

    std::sort(addresses.begin(), addresses.end());
    for(auto addr: addresses) {
        model.appendRow({
            new QStandardItem(toHex(addr, w)),
            new QStandardItem(toHex(values[addr], w)),
        });
    }


    refreshTable();
}

void MemoryBrowserWidget::addData() {
    MemoryEditDialog dial;
    if(dial.exec() == QDialog::Accepted) {
        try {
            auto r = dial.getValues();
            persistentData[r.first] = r.second;
            setup(curAssembly);
        } catch(std::exception& e) {
            QMessageBox::critical(this, "Error", "Invalid values");
        }
    }
}

void MemoryBrowserWidget::editData(QModelIndex index) {
    MemoryEditDialog dial;
    dial.setValues(index.siblingAtColumn(0).data().toULongLong(),
                   index.siblingAtColumn(1).data().toULongLong());
    if(dial.exec() == QDialog::Accepted) {
        try {
            auto r = dial.getValues();
            persistentData[r.first] = r.second;
        } catch(std::exception& e) {
            QMessageBox::critical(this, "Error", "Invalid values");
        }
    }
}

void MemoryBrowserWidget::removeData(QModelIndex index) {
    persistentData.remove(index.siblingAtColumn(0).data().toULongLong());
    setup(curAssembly);
}

void MemoryBrowserWidget::push() {

}

void MemoryBrowserWidget::pop() {

}

void MemoryBrowserWidget::injectMemory() {
    for(auto [k, v] : persistentData.asKeyValueRange()) {
        qDebug() << k << v;
        curAssembly->getMemory()->set<uint64_t>(k, v);
    }
}
