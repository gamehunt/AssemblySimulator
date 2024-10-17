#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "statemanager.h"

#include <QApplication>
#include <QObject>
#include <QStack>

class Assembly: public QObject
{
    Q_OBJECT;
public:
    explicit Assembly(QObject* o = nullptr);

    void push(uint64_t v);
    uint64_t pop();

    void setCode(QStringList c);

    StateManager* getState();
    QStack<uint64_t>* getStack();

public slots:
    virtual void error(QString err);
    virtual void execute();
    virtual void step();
    virtual void executeLine(QString l);
    virtual void stop();
    virtual void reset();

signals:
    void stackChanged(QStringList);
    void errorOccured(QString);
    void lineExecuted();

protected:
    QStack<uint64_t> stack;
    StateManager     state;
    QStringList      code;
    int              currentLine, nextLine;
};

#endif // ASSEMBLY_H
