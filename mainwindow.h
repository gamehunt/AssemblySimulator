#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "assembly.h"
#include "memorybrowserwidget.h"

#include <QComboBox>
#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void registerAssembly(QString name, Assembly*);

public slots:
    void updateStack(QStringList v);
    void setAssembly(Assembly* a);
    void showDisasm();
    void showMemoryBrowser();
    void execute();
    void step();
    void stop();
    void reset();

private:
    Ui::MainWindow *ui;

    MemoryBrowserWidget memory;

    QStandardItemModel stackModel;
    QMap<QString, Assembly*> assemblies;
    Assembly* curAssembly;
};
#endif // MAINWINDOW_H
