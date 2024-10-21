#include "memorybrowserwidget.h"
#include "ui_memorybrowserwidget.h"

#include <QMessageBox>
#include <memoryeditdialog.h>

MemoryBrowserWidget::MemoryBrowserWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MemoryBrowserWidget)
{
    ui->setupUi(this);

    curAssembly = nullptr;

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
    model.setHorizontalHeaderLabels({"Address", "Value", "+0", "+1", "+2", "+3", "+4", "+5", "+6", "+7"});
    proxy.setSourceModel(&model);
    ui->memoryTableView->setModel(&proxy);
    ui->memoryTableView->resizeColumnsToContents();
}

void MemoryBrowserWidget::refresh() {
    setup(curAssembly);
}

void MemoryBrowserWidget::setup(Assembly* a) {
    curAssembly = a;
    model.clear();

    QMap<uint64_t, uint64_t> values;
    int w = 16;

    if(curAssembly) {
        QMap<uint64_t, uint8_t>& mem = curAssembly->getMemory()->getRaw();
        w = curAssembly->getState()->getWidth();

        for(int i = 0; i < mem.size(); i++) {
            uint64_t addr = mem.keys()[i];
            uint64_t v = mem[addr];
            int skip = 0;
            for(int j = 1; j < 8; j++) {
                uint8_t sv = mem.value(addr + j, 0);
                v |= ((uint64_t) sv << j * 8);
                if(i + j < mem.size() && mem.keys()[i + j] == addr + j) {
                    skip++;
                } else {
                    break;
                }
            }
            i += skip;
            if(v) {
                values[addr] = v;
            }
        }
    }

    for(auto key: persistentData.keys()) {
        uint64_t v = persistentData[key];
        if(v) {
            values[key] = v;
        }
    }

    for(auto [a, v]: values.asKeyValueRange()) {
        model.appendRow({
            new QStandardItem(toHex(a, w)),
            new QStandardItem(toHex(v, w)),
            new QStandardItem(toHex((v >> 8 * 0) & 0xFF, 2)),
            new QStandardItem(toHex((v >> 8 * 1) & 0xFF, 2)),
            new QStandardItem(toHex((v >> 8 * 2) & 0xFF, 2)),
            new QStandardItem(toHex((v >> 8 * 3) & 0xFF, 2)),
            new QStandardItem(toHex((v >> 8 * 4) & 0xFF, 2)),
            new QStandardItem(toHex((v >> 8 * 5) & 0xFF, 2)),
            new QStandardItem(toHex((v >> 8 * 6) & 0xFF, 2)),
            new QStandardItem(toHex((v >> 8 * 7) & 0xFF, 2))
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
            refresh();
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
            refresh();
        } catch(std::exception& e) {
            QMessageBox::critical(this, "Error", "Invalid values");
        }
    }
}

void MemoryBrowserWidget::removeData(QModelIndex index) {
    persistentData.remove(index.siblingAtColumn(0).data().toULongLong());
    refresh();
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
