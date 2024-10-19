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

    ui->resetPushButton->setVisible(false);

    running = paused = false;
    curAssembly = nullptr;

    QObject::connect(ui->assembliesComboBox, &QComboBox::currentTextChanged, this, [this](QString v) {setAssembly(assemblies[v]);});

    registerAssembly("x86-64", new AMD64Assembly);

    QObject::connect(ui->textEdit, &QTextEdit::textChanged, this, [this](){ curAssembly->setCode(ui->textEdit->toPlainText().split("\n")); });

    QObject::connect(ui->runPushButton,  &QPushButton::clicked, this, [this](){
        if(running && !paused) {
            pause();
        } else {
            paused = false;
            run();
        }
    });
    QObject::connect(ui->runPausedButton,  &QPushButton::clicked, this, [this](){
        paused = true;
        run();
    });
    QObject::connect(ui->stepForwardPushButton, &QPushButton::clicked, this, [this]() {step(false);});
    QObject::connect(ui->stepBackwardPushButton, &QPushButton::clicked, this, [this]() {step(true);});
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
    if(curAssembly) {
        ui->stateFrame->layout()->removeWidget(curAssembly->getState()->getReprentationWidget());
    }
    ui->stateFrame->layout()->addWidget(a->getState()->getReprentationWidget());
    curAssembly = a;
}

void MainWindow::updateButtonStates() {
    if(running && !paused) {
        ui->runPushButton->setIcon(QIcon(":/icons/pause.ico"));
        ui->runPushButton->setIconSize(QSize(24, 24));
    } else {
        ui->runPushButton->setIcon(QIcon(":/icons/run.ico"));
        ui->runPushButton->setIconSize(QSize(12, 12));
    }
    ui->runPausedButton->setEnabled(!running);
    ui->stepForwardPushButton->setEnabled(paused);
    ui->textEdit->setEnabled(!running);
    ui->stopPushButton->setEnabled(running);
}

void MainWindow::run() {
    running = true;
    updateButtonStates();
    if(!paused) {
        curAssembly->execute();
        if(curAssembly->isFinished()) {
            reset();
        }
    }
}

void MainWindow::pause() {
    paused = true;
    updateButtonStates();
    curAssembly->stop();
}

void MainWindow::step(bool b) {
    if(curAssembly->isFinished()) {
        reset();
    } else {
        curAssembly->step();
    }
}

void MainWindow::stop() {
    curAssembly->stop();
    reset();
}

void MainWindow::reset() {
    running = false;
    paused  = false;
    updateButtonStates();
    curAssembly->reset();
    curAssembly->setCode(ui->textEdit->toPlainText().split("\n"));
}

void MainWindow::showDisasm() {

}

void MainWindow::showMemoryBrowser() {
    memory.setup(curAssembly);
    memory.show();
}
