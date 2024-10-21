#include "memoryeditdialog.h"
#include "ui_memoryeditdialog.h"

#include <QIntValidator>

MemoryEditDialog::MemoryEditDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MemoryEditDialog)
{
    ui->setupUi(this);

    ui->addrLineEdit->setValidator(new QIntValidator);
    ui->valueLineEdit->setValidator(new QIntValidator);
}

MemoryEditDialog::~MemoryEditDialog()
{
    delete ui;
}

QPair<uint64_t, uint64_t> MemoryEditDialog::getValues() {
    uint64_t a, v;
    QString sa = ui->addrLineEdit->text();
    QString sv = ui->valueLineEdit->text();
    bool ok;
    if(sa.startsWith("0x")) {
        a = sa.toULongLong(&ok, 16);
    } else {
        a = sa.toULongLong(&ok, 10);
    }
    if(!ok) {
        throw std::runtime_error("");
    }
    if(sv.startsWith("0x")) {
        v = sv.toULongLong(&ok, 16);
    } else {
        v = sv.toULongLong(&ok, 10);
    }
    if(!ok) {
        throw std::runtime_error("");
    }
    return {
        a,
        v
    };
}

void MemoryEditDialog::setValues(uint64_t addr, uint64_t v) {
    ui->addrLineEdit->setText(QString::number(addr, 16));
    ui->valueLineEdit->setText(QString::number(v, 16));
}
