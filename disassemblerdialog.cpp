#include "disassemblerdialog.h"
#include "ui_disassemblerdialog.h"

#include <QTableWidgetItem>

DisassemblerDialog::DisassemblerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DisassemblerDialog)
{
    ui->setupUi(this);
    ui->buttonBox->setVisible(false);

    ui->tableWidget->setHorizontalHeaderLabels(
        {"+1", "+2", "+3", "+4"}
    );
}

DisassemblerDialog::~DisassemblerDialog()
{
    delete ui;
}

void DisassemblerDialog::setCode(unsigned char* encode, size_t size) {
    ui->tableWidget->clear();
    for (int i = 0; i < size / 4 + !!(size % 4); i++) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(QString("+") + QString::number(i * 4)));
        for(int j = 0; j < 4; j++) {
            if(i * 4 + j >= size) {
                break;
            }
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(QString("0x") + QString::number(encode[i * 4 + j], 16)));
        }
    }
    ui->tableWidget->resizeColumnsToContents();
}
