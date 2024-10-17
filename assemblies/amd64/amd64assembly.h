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

private:
    uint64_t value(QString operand, int mode = MODE_ALL);

};

#endif // AMD64ASSEMBLY_H
