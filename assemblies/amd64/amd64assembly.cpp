#include "amd64assembly.h"
#include "amd64states.h"
#include "amd64syntaxhighlighter.h"

#include <QTimer>

#define FL_CF (1 << 0)
#define FL_PF (1 << 2)
#define FL_AF (1 << 4)
#define FL_ZF (1 << 5)
#define FL_SF (1 << 6)
#define FL_DF (1 << 10)
#define FL_OF (1 << 11)

enum OP_TYPE {
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
    JLE,
    JGE,
    JC,
    CALL,
    RET,
    XCHG,
    INT,
    TEST
};

static const QMap<QString, OP_TYPE> __ops = {
    {"nop" , NOP  },
    {"mov" , MOV  },
    {"push", PUSH },
    {"pop" , POP  },
    {"inc" , INC  },
    {"dec" , DEC  },
    {"add" , ADD  },
    {"sub" , SUB  },
    {"div" , DIV  },
    {"mul" , MUL  },
    {"and" , AND  },
    {"or"  , OR   },
    {"xor" , XOR  },
    {"shl" , SHL  },
    {"shr" , SHR  },
    {"cmp" , CMP  },
    {"jmp" , JMP  },
    {"je"  , JE   },
    {"jne" , JNE  },
    {"jz"  , JE   },
    {"jnz" , JNE  },
    {"jg"  , JG   },
    {"jl"  , JL   },
    {"jge" , JGE  },
    {"jle" , JLE  },
    {"jc"  , JC   },
    {"call", CALL },
    {"ret" , RET  },
    {"xchg", XCHG },
    {"int" , INT  },
    {"test", TEST }
};

#define parse_args(args, n) args = _args.split(","); if (args.size() < n) { throw std::runtime_error("more args required"); }

AMD64Assembly::AMD64Assembly() {
    state.setRepresentationWidget(new AMD64States());
    char dst = 'a';
    while(dst <= 'd') {
        QString src = QString("r%0x").arg(dst);
        state.addRegister(src);
        state.addAlias(QString("e%0x").arg(dst), src, 0xFFFFFFFF, 0);
        state.addAlias(QString("%0x").arg(dst), src, 0xFFFF, 0);
        state.addAlias(QString("%0l").arg(dst), src, 0xFF, 0);
        state.addAlias(QString("%0h").arg(dst), src, 0xFF00, 8);
        dst++;
    }
    state.addRegister("rdi");
    state.addAlias("edi", "rdi", 0xFFFFFFFF, 0);
    state.addAlias("di", "rdi", 0xFFFF, 0);
    state.addRegister("rsi");
    state.addAlias("esi", "rsi", 0xFFFFFFFF, 0);
    state.addAlias("si", "rsi", 0xFFFF, 0);
    state.addRegister("rbp");
    state.addRegister("rsp");
    state.addRegister("r8");
    state.addRegister("r9");
    state.addRegister("r10");
    state.addRegister("r11");
    state.addRegister("r12");
    state.addRegister("r13");
    state.addRegister("r14");
    state.addRegister("r15");
    state.addRegister("rip", false);
    state.addRegister("flags", false);
    QTimer::singleShot(1, this, &AMD64Assembly::reset);
}

void AMD64Assembly::reset() {
    Assembly::reset();
    state.set("rbp", Memory::getStackAddress());
    state.set("rsp", Memory::getStackAddress());
}

uint64_t AMD64Assembly::value(QString s, int mode) {
    bool v = false;
    int base = 10;
    uint64_t tmp = 0;

    if(s.startsWith("[") && s.endsWith("]")) {
        if(!(mode & MODE_MEM)) {
            throw std::runtime_error("non-memory value required");
        }
        return memory.get<uint64_t>(value(s.mid(1, s.length() - 2)));
    }

    if(mode & MODE_IMM) {
        if(s.startsWith("0") && s.size() >= 3) {
            if(s[1] == 'x') {
                base = 16;
                s = s.last(s.size() - 2);
            } else if(s[1] == 'b') {
                base = 2;
                s = s.last(s.size() - 2);
            }
        }
        tmp = s.toULongLong(&v, base);
    }

    if(v) {
        return tmp;
    } else {
        if(!(mode & MODE_REG)) {
            throw std::runtime_error("immediate value required");
        }
        return state.get(s);
    }
}

void AMD64Assembly::setFlag(uint16_t flag, uint8_t v){
    uint16_t fl = state.get("flags", true);
    if(v) {
        fl |= flag;
    } else {
        fl &= ~flag;
    }
    state.set("flags",  fl, true);
}

uint8_t AMD64Assembly::getFlag(uint16_t flag) {
    return !!(state.get("flags", true) & flag);
}

int AMD64Assembly::jump(QString arg) {
    for(int line = 0; line < code.size(); line++) {
        if(code[line].startsWith(arg) && code[line].endsWith(":")) {
            return line;
        }
    }
    return value(arg) / 8;
}

void AMD64Assembly::interrupt(int i) {
    throw std::runtime_error("Unknown interrupt");
}

void AMD64Assembly::executeLine(QString line) {
    state.set("rip", currentLine * 8, true);

    QStringList splitted = line.split(" ");
    QString op;
    QString _args;
    QStringList args;

    int64_t v = 0;
    int64_t v1, v2;
    v1 = v2 = 0;

    op = splitted[0];
    for(int i = 1; i < splitted.size(); i++) {
        _args.append(splitted[i]);
    }

    if(!__ops.contains(op)) {
        if(!op.endsWith(":")) {
            throw std::runtime_error("Unknown opcode");
        }
        // It's a label, skip it
    } else {
        switch(__ops[op]) {
        case NOP:
            break;
        case MOV:
            parse_args(args, 2);
            set(args[0], value(args[1]));
            if(args[0] == "rsp") {
                memory.setStackPointer(state.get("rsp"));
            }
            break;
        case PUSH:
            parse_args(args, 1);
            memory.push(value(args[0]));
            state.set("rsp", memory.getStackPointer());
            break;
        case POP:
            parse_args(args, 1);
            state.set(args[0], memory.pop());
            state.set("rsp", memory.getStackPointer());
            break;
        case INC:
            parse_args(args, 1);
            state.set(args[0], value(args[0]) + 1);
            break;
        case DEC:
            parse_args(args, 1);
            state.set(args[0], value(args[0]) - 1);
            break;
        case ADD:
            parse_args(args, 2);
            state.set(args[0], value(args[0]) + value(args[1]));
            break;
        case SUB:
            parse_args(args, 2);
            v1 = value(args[0]);
            v2 = value(args[1]);
            state.set(args[0], v1 - v2);
            break;
        case MUL:
            parse_args(args, 2);
            state.set(args[0], value(args[0]) * value(args[1]));
            break;
        case DIV:
            parse_args(args, 1);
            v1 = value(args[1]);
            v2 = value("rax");
            if(v1 == 0) {
                throw std::runtime_error("zero division");
            }
            state.set("rax", v2 / v1);
            state.set("rdx", v2 % v1);
            break;
        case AND:
            parse_args(args, 2);
            v1 = value(args[0], MODE_REG | MODE_MEM);
            v2 = value(args[1]);
            state.set(args[0], v1 & v2);
            break;
        case OR:
            parse_args(args, 2);
            v1 = value(args[0], MODE_REG | MODE_MEM);
            v2 = value(args[1]);
            state.set(args[0], v1 | v2);
            break;
        case XOR:
            parse_args(args, 2);
            v1 = value(args[0], MODE_REG | MODE_MEM);
            v2 = value(args[1]);
            state.set(args[0], v1 ^ v2);
            break;
        case SHL:
            parse_args(args, 2);
            v1 = value(args[0], MODE_REG | MODE_MEM);
            v2 = value(args[1], MODE_IMM);
            state.set(args[0], v1 << v2);
            break;
        case SHR:
            parse_args(args, 2);
            v1 = value(args[0], MODE_REG | MODE_MEM);
            v2 = value(args[1], MODE_IMM);
            state.set(args[0], v1 >> v2);
            break;
        case CMP:
            parse_args(args, 2);

            v1 = value(args[0]);
            v2 = value(args[1]);
            v = v1 - v2;

            setFlag(FL_ZF, v == 0);

            // TODO proper logic
            if(v1 < v2) {
                setFlag(FL_SF, 1);
                setFlag(FL_OF, 0);
            } else {
                setFlag(FL_SF, 0);
                setFlag(FL_OF, 0);
            }

            break;
        case JE:
            parse_args(args, 1);
            if(getFlag(FL_ZF)) {
                nextLine = jump(args[0]);
                return;
            }
            break;
        case JNE:
            parse_args(args, 1);
            if(!getFlag(FL_ZF)) {
                nextLine = jump(args[0]);
                return;
            }
            break;
        case JL:
            parse_args(args, 1);
            if(getFlag(FL_SF) != getFlag(FL_OF)) {
                nextLine = jump(args[0]);
                return;
            }
            break;
        case JLE:
            parse_args(args, 1);
            if(getFlag(FL_ZF) || (getFlag(FL_SF) != getFlag(FL_OF))) {
                nextLine = jump(args[0]);
                return;
            }
            break;
        case JG:
            parse_args(args, 1);
            if(!getFlag(FL_ZF) && (getFlag(FL_SF) == getFlag(FL_OF))) {
                nextLine = jump(args[0]);
                return;
            }
            break;
        case JGE:
            parse_args(args, 1);
            if(getFlag(FL_SF) == getFlag(FL_OF)) {
                nextLine = jump(args[0]);
                return;
            }
            break;
        case JMP:
            parse_args(args, 1);
            nextLine = jump(args[0]);
            return;
        case CALL:
            parse_args(args, 1);
            memory.push((currentLine + 1) * 8);
            state.set("rsp", memory.getStackPointer());
            nextLine = jump(args[0]);
            return;
        case RET:
            v = memory.pop();
            state.set("rsp", memory.getStackPointer());
            nextLine = v / 8;
            return;
        case XCHG:
            parse_args(args, 2);
            v = value(args[0]);
            set(args[0], value(args[1]));
            set(args[1], v);
            break;
        case INT:
            parse_args(args, 1);
            interrupt(value(args[0], MODE_IMM));
            break;
        case TEST:
            parse_args(args, 2);
            v1 = value(args[0], MODE_REG | MODE_MEM);
            v2 = value(args[1]);
            v  = v1 & v2;
            setFlag(FL_ZF, v == 0);
            setFlag(FL_OF, 0);
            setFlag(FL_CF, 0);
            setFlag(FL_SF, v < 0);
            // TODO PF
            break;
        default:
            throw std::runtime_error("unimplemented/unknown opcode");
        }

    }

    nextLine = currentLine + 1;
}

QSyntaxHighlighter* AMD64Assembly::getSyntaxHighlighter() {
    static AMD64SyntaxHighlighter highlighter;
    return &highlighter;
}

void AMD64Assembly::set(QString operand, uint64_t val) {
    if(operand.startsWith("[") && operand.endsWith("]")) {
        memory.set(value(operand), val);
    } else {
        state.set(operand, val);
    }
}
