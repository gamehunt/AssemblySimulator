#ifndef DISASSEMBLERDIALOG_H
#define DISASSEMBLERDIALOG_H

#include <QDialog>

namespace Ui {
class DisassemblerDialog;
}

class DisassemblerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DisassemblerDialog(QWidget *parent = nullptr);
    ~DisassemblerDialog();

    void setCode(unsigned char*, size_t);

private:
    Ui::DisassemblerDialog *ui;
};

#endif // DISASSEMBLERDIALOG_H
