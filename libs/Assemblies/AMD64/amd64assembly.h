#ifndef AMD64ASSEMBLY_H
#define AMD64ASSEMBLY_H

#include <QStringList>
#include "libs/LibAssembly/assembly.h"

#define MODE_IMM (1 << 0)
#define MODE_REG (1 << 1)
#define MODE_MEM (1 << 2)
#define MODE_ALL 0xFF

#define FL_CF (1 << 0)
#define FL_PF (1 << 2)
#define FL_AF (1 << 4)
#define FL_ZF (1 << 5)
#define FL_SF (1 << 6)
#define FL_DF (1 << 10)
#define FL_OF (1 << 11)

enum OP_TYPE {
    OP_INVALID = -1,
    LABEL,
    NOP,
    MOV,
    PUSH,
    POP,
    INC,
    DEC,
    ADD,
    SUB,
    DIV,
    MUL,
    AND,
    OR,
    XOR,
    SHL,
    SHR,
    CMP,
    JMP,
    JE,
    JNE,
    JG,
    JL,
    JB,
    JBE,
    JLE,
    JGE,
    JC,
    CALL,
    RET,
    XCHG,
    INT,
    TEST,
    LEA,
    NOT,
    NEG
};

enum OP_SIZE {
    S_INVALID = -1,
    S8  = 8,
    S16 = 16,
    S32 = 32,
    S64 = 64
};


class AMD64Assembly : public Assembly
{
public:
    AMD64Assembly();

    void executeLine(QString line) override;
    void reset() override;

    void    setFlag(uint16_t flag, uint8_t v);
    uint8_t getFlag(uint16_t flag);

    QSyntaxHighlighter* getSyntaxHighlighter() override;

private:
    class Context {
    public:
        Context();
        enum OP_TYPE op;
        QList<QString> args;
    };

    void parseContext(QString line, AMD64Assembly::Context* ctx);
    void executeContext(AMD64Assembly::Context& ctx);

    bool isSizeModifier(QString token);
    bool isLabel(QString token);
    bool isOperand(QString token);

    OP_SIZE  size(QString token);
    void     set(QString operand, uint64_t value);
    uint64_t value(QString operand, int mode = MODE_ALL);
    int      jump(QString arg);
    void     interrupt(int i);
    uint64_t lea(QString operand);

    static const QMap<QString, OP_TYPE> __ops;
    static const QMap<QString, OP_SIZE> __sizes;
};

#endif // AMD64ASSEMBLY_H
