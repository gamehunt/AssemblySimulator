#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "states/amd64states.h"

#include <QActionGroup>
#include <QStandardItemModel>
#include <keystone/keystone.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stateFrame->layout()->addWidget(new AMD64States);

    QStandardItemModel* model = new QStandardItemModel;

    for(int i = 0; i < 16; i++) {
        char hex[32];
        snprintf(hex, 32, "0x%.16lx", (ulong) i * 16);
        model->appendRow({
            new QStandardItem(QString("+%1").arg(i * 16)),
            new QStandardItem(hex)
        });
    }

    ui->stackView->setModel(model);
    ui->stackView->resizeColumnsToContents();

    QActionGroup* groupTool = new QActionGroup(this);
    groupTool->addAction(ui->actionModeX86);
    groupTool->addAction(ui->actionModeX86_64);
    groupTool->setExclusive(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
