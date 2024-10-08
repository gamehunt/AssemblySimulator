#ifndef AMD64STATES_H
#define AMD64STATES_H

#include <QWidget>

namespace Ui {
class AMD64States;
}

class AMD64States : public QWidget
{
    Q_OBJECT

public:
    explicit AMD64States(QWidget *parent = nullptr);
    ~AMD64States();

private:
    Ui::AMD64States *ui;
};

#endif // AMD64STATES_H
