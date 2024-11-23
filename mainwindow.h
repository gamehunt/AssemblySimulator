#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "libs/LibAssembly/assembly.h"
#include "memorybrowserwidget.h"

#include <QComboBox>
#include <QFile>
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
    void run(bool unpaused = false);
    void step(bool b);
    void stop();
    void pause();
    void reset();

    void about();
    void help();

    void newFile();
    void saveFile(bool as);
    void openFile();

private slots:
    void updateButtonStates();
    void setFileName(QString name);

private:
    void createHelpWindow();

    Ui::MainWindow *ui;

    MemoryBrowserWidget memory;

    QStandardItemModel stackModel;
    QMap<QString, Assembly*> assemblies;
    Assembly* curAssembly;

    QWidget* helpWindow;

    bool running, paused;
    bool unsaved;
    bool unnamed;

    QFile   currentFile;
};
#endif // MAINWINDOW_H
