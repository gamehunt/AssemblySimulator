#ifndef MEMORYEDITDIALOG_H
#define MEMORYEDITDIALOG_H

#include <QDialog>

namespace Ui {
class MemoryEditDialog;
}

class MemoryEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MemoryEditDialog(QWidget *parent = nullptr);
    ~MemoryEditDialog();

    void setValues(uint64_t addr, uint64_t v);
    QPair<uint64_t, uint64_t> getValues();

private:
    Ui::MemoryEditDialog *ui;
};

#endif // MEMORYEDITDIALOG_H
