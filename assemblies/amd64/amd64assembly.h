#ifndef AMD64ASSEMBLY_H
#define AMD64ASSEMBLY_H

#include <QStringList>
#include "../../assembly.h"

#define MODE_IMM (1 << 0)
#define MODE_REG (1 << 1)
#define MODE_ALL (MODE_IMM | MODE_REG)

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
    void     set(QString operand, uint64_t value);
    uint64_t value(QString operand, int mode = MODE_ALL);
    int      jump(QString arg);
};

#endif // AMD64ASSEMBLY_H
