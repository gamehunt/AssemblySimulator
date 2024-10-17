#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "utils.h"
#include <QLabel>
#include <QWidget>

class StateManager
{
public:
    StateManager(): _representation(nullptr), w(16) {;}

    void set(QString r, uint64_t v);
    uint64_t get(QString v) const;

    void addRegister(QString r);
    bool hasRegister(QString r) const;

    void setRepresentationWidget(QWidget* w);
    QWidget* getReprentationWidget();

    void setWidth(int w);
    int getWidth();

    void reset();
    void refresh();

private:
    QMap<QString, uint64_t> _state;
    QWidget*                _representation;

    int w;
};

#endif // STATEMANAGER_H
