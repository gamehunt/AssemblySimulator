#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "../../utils.h"

#include <QWidget>

struct Register {
    uint64_t value;
    bool     direct;
};

struct Alias {
    QString  src;
    uint64_t mask;
    int      shift;
};

class StateManager
{
public:
    StateManager(): _representation(nullptr), w(16) {;}

    void set(QString r, uint64_t v, bool allowIndirect = false);
    uint64_t get(QString v, bool allowIndirect = false) const;

    void addRegister(QString r, bool direct = true);
    void addAlias(QString r, QString src, uint64_t mask, int shift);

    bool hasRegister(QString r) const;

    void setRepresentationWidget(QWidget* w);
    QWidget* getReprentationWidget();

    void setWidth(int w);
    int getWidth();

    void reset();
    void refresh();

    QStringList getRegisters(bool includeIndirect = false);
    QStringList getAliases(QString reg = QString());

private:
    QMap<QString, Register> _state;
    QMap<QString, Alias>    _aliases;
    QWidget*                _representation;

    int w;
};

#endif // STATEMANAGER_H
