#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "assemblies/amd64/amd64assembly.h"
#include "utils.h"

#include <QMessageBox>
#include <QStandardItemModel>
#include <keystone/keystone.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackView->setModel(&stackModel);
    ui->stackView->resizeColumnsToContents();

    QObject::connect(ui->assembliesComboBox, &QComboBox::currentTextChanged, this, [this](QString v) {setAssembly(assemblies[v]);});

    registerAssembly("x86-64", new AMD64Assembly);

    QObject::connect(ui->textEdit, &QTextEdit::textChanged, this, [this](){ curAssembly->setCode(ui->textEdit->toPlainText().split("\n")); });

    QObject::connect(ui->runPushButton,  &QPushButton::clicked, this, &MainWindow::execute);
    QObject::connect(ui->stepPushButton, &QPushButton::clicked, this, &MainWindow::step);
    QObject::connect(ui->stopPushButton, &QPushButton::clicked, this, &MainWindow::stop);
    QObject::connect(ui->resetPushButton, &QPushButton::clicked, this, &MainWindow::reset);
    QObject::connect(ui->disasmPushButton, &QPushButton::clicked, this, &MainWindow::showDisasm);
    QObject::connect(ui->memPushButton, &QPushButton::clicked, this, &MainWindow::showMemoryBrowser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::registerAssembly(QString l, Assembly* as) {
    assemblies[l] = as;
    QObject::connect(as, &Assembly::stackChanged, this, &MainWindow::updateStack);
    QObject::connect(as, &Assembly::errorOccured, this, [this](QString err) {QMessageBox::critical(this, "Error", err);});
    ui->assembliesComboBox->addItem(l);
}

void MainWindow::updateStack(QStringList v) {
    stackModel.clear();

    int i = 0;
    for(QString& e : v) {
        stackModel.appendRow({
            new QStandardItem(QString("+%1").arg(i * 16)),
            new QStandardItem(e)
        });
        i++;
    }

    ui->stackView->setModel(&stackModel);
    ui->stackView->resizeColumnsToContents();
}

void MainWindow::setAssembly(Assembly* a) {
    stackModel.clear();
    ui->stateFrame->layout()->removeWidget(curAssembly->getState()->getReprentationWidget());
    ui->stateFrame->layout()->addWidget(a->getState()->getReprentationWidget());
    curAssembly = a;
}

void MainWindow::execute() {
    ui->runPushButton->setEnabled(false);
    ui->stepPushButton->setEnabled(false);
    ui->textEdit->setEnabled(false);
    ui->stopPushButton->setEnabled(true);
    curAssembly->execute();
    ui->runPushButton->setEnabled(true);
    ui->stepPushButton->setEnabled(true);
    ui->textEdit->setEnabled(true);
    ui->stopPushButton->setEnabled(false);
}

void MainWindow::step() {
    curAssembly->step();
}

void MainWindow::stop() {
    curAssembly->stop();
}

void MainWindow::reset() {
    curAssembly->reset();
    curAssembly->setCode(ui->textEdit->toPlainText().split("\n"));
}

void MainWindow::showDisasm() {

}

void MainWindow::showMemoryBrowser() {
    memory.show();
}
