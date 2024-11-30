#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "memory.h"
#include "statemanager.h"

#include <QApplication>
#include <QObject>
#include <QStack>
#include <QSyntaxHighlighter>



class Assembly: public QObject
{
    Q_OBJECT
public:
    explicit Assembly(QObject* o = nullptr);

    void setCode(QStringList c);

    StateManager* getState();
    Memory*       getMemory();

    bool isFinished() const;
    int  getCurrentLine();

    virtual QSyntaxHighlighter* getSyntaxHighlighter() { return nullptr; }

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
    void lineExecuted(int line);

protected:
    Memory           memory;
    StateManager     state;
    QStringList      code;
    int              currentLine, nextLine;
    bool             stopped;
};

class AssemblyInterface: public QObject {
public:
    virtual ~AssemblyInterface() = default;
    virtual QString   getName() = 0;
    virtual Assembly* getAssembly() = 0;
};

Q_DECLARE_INTERFACE(AssemblyInterface, "ru.l1zz.asmsim.AssemblyInterface")

#endif // ASSEMBLY_H
