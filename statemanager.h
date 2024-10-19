#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "utils.h"
#include <QLabel>
#include <QWidget>

struct Register {
    uint64_t value;
    bool direct;
};

class StateManager
{
public:
    StateManager(): _representation(nullptr), w(16) {;}

    void set(QString r, uint64_t v, bool allowIndirect = false);
    uint64_t get(QString v, bool allowIndirect = false) const;

    void addRegister(QString r, bool direct = true);
    bool hasRegister(QString r) const;

    void setRepresentationWidget(QWidget* w);
    QWidget* getReprentationWidget();

    void setWidth(int w);
    int getWidth();

    void reset();
    void refresh();

private:
    QMap<QString, Register> _state;
    QWidget*                _representation;

    int w;
};

#endif // STATEMANAGER_H
