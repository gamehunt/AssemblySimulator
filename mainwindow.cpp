#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "assemblies/amd64/amd64assembly.h"
#include "utils.h"

#include <QMessageBox>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QTimer>
#include <disassemblerdialog.h>
#include <keystone/keystone.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackView->setModel(&stackModel);
    ui->stackView->resizeColumnsToContents();

    ui->resetPushButton->setVisible(false);
    ui->stepBackwardPushButton->setVisible(false);

    running = paused = false;
    curAssembly = nullptr;

    QObject::connect(ui->assembliesComboBox, &QComboBox::currentTextChanged, this, [this](QString v) {setAssembly(assemblies[v]);});

    registerAssembly("x86-64", new AMD64Assembly);

    QObject::connect(ui->textEdit, &QPlainTextEdit::textChanged, this, [this](){ curAssembly->setCode(ui->textEdit->toPlainText().split("\n")); });

    QObject::connect(ui->runPushButton,  &QPushButton::clicked, this, [this](){
        if(running && !paused) {
            pause();
        } else {
            paused = false;
            run(running);
        }
    });
    QObject::connect(ui->runPausedButton,  &QPushButton::clicked, this, [this](){
        paused = true;
        run(false);
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
            new QStandardItem(QString("+%1").arg(i * 8)),
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
        QSyntaxHighlighter* highlight = curAssembly->getSyntaxHighlighter();
        if(highlight) {
            highlight->setDocument(nullptr);
        }
        QObject::disconnect(curAssembly->getMemory(), &Memory::memoryChanged, &memory, &MemoryBrowserWidget::refresh);
        QObject::disconnect(curAssembly, &Assembly::lineExecuted, ui->textEdit, &CodeEdit::setExecutedLine);
        ui->stateFrame->layout()->removeWidget(curAssembly->getState()->getReprentationWidget());
    }
    QWidget* repr = a->getState()->getReprentationWidget();
    ui->stateFrame->layout()->addWidget(repr);
    ui->splitter->setSizes({ui->textEdit->maximumWidth(), repr->minimumWidth()});
    curAssembly = a;
    QSyntaxHighlighter* highlight = curAssembly->getSyntaxHighlighter();
    if(highlight) {
        highlight->setDocument(ui->textEdit->document());
    }
    QObject::connect(curAssembly->getMemory(), &Memory::memoryChanged, &memory, &MemoryBrowserWidget::refresh);
    QObject::connect(curAssembly, &Assembly::lineExecuted, ui->textEdit, &CodeEdit::setExecutedLine);
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
    ui->textEdit->setReadOnly(running);
    if(!ui->textEdit->isReadOnly()) {
        ui->textEdit->highlightCurrentLine();
    } else {
        ui->textEdit->setExtraSelections({});
    }
    ui->stopPushButton->setEnabled(running);
}

void MainWindow::run(bool up) {
    running = true;
    updateButtonStates();
    if(!up) {
        qDebug() << "Inj!";
        memory.setup(curAssembly);
        memory.injectMemory();
    }
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
    QTimer::singleShot(1, this, [this]() {
        curAssembly->reset();
        curAssembly->setCode(ui->textEdit->toPlainText().split("\n"));
    });
}

void MainWindow::showDisasm() {
    ks_engine* ks;
    ks_err     err;

    err = ks_open(KS_ARCH_X86, KS_MODE_64, &ks);

    if (err != KS_ERR_OK) {
        QMessageBox::critical(this, "Error", "Failed on ks_open()");
        return;
    }

    size_t count;
    unsigned char *encode;
    size_t size;

    if (ks_asm(ks, ui->textEdit->toPlainText().toStdString().c_str(), 0, &encode, &size, &count) != KS_ERR_OK) {
        QMessageBox::critical(this, "Error", QString("ks_asm() failed & count = %0, error = %1\n").arg(count).arg(ks_strerror(ks_errno(ks))));
    } else {
        DisassemblerDialog disasm;
        disasm.setCode(encode, size);
        disasm.exec();
    }

    ks_free(encode);
    ks_close(ks);
}

void MainWindow::showMemoryBrowser() {
    memory.setup(curAssembly);
    memory.show();
}
