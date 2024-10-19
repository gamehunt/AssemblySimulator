#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "memory.h"
#include "statemanager.h"

#include <QApplication>
#include <QObject>
#include <QStack>

class Assembly: public QObject
{
    Q_OBJECT
public:
    explicit Assembly(QObject* o = nullptr);

    void setCode(QStringList c);

    StateManager* getState();
    Memory*       getMemory();

public slots:
    virtual void error(QString err);
    virtual void execute();
    virtual void step();
    virtual void executeLine(QString l);
    virtual void stop();
    virtual void reset();

protected slots:
    void emitStack(uint64_t ptr);

signals:
    void stackChanged(QStringList);
    void errorOccured(QString);
    void lineExecuted();

protected:
    Memory           memory;
    StateManager     state;
    QStringList      code;
    int              currentLine, nextLine;
};

#endif // ASSEMBLY_H
