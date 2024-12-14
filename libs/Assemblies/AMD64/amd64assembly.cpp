#include "amd64assembly.h"
#include "amd64states.h"
#include "amd64syntaxhighlighter.h"

#include "libs/LibParse/shunting-yard.h"

#include <QTimer>

const QMap<QString, OP_TYPE> AMD64Assembly::__ops = {
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
    {"jb"  , JB   },
    {"jbe" , JBE  },
    {"call", CALL },
    {"ret" , RET  },
    {"xchg", XCHG },
    {"int" , INT  },
    {"test", TEST },
    {"lea",  LEA },
    {"not", NOT},
    {"neg", NEG}
};

const QMap<QString, OP_SIZE> AMD64Assembly::__sizes = {
    {"byte",  S8  },
    {"word",  S16 },
    {"dword", S32 },
    {"qword", S64 }
};

#define parse_args(args, n) args = _args.split(","); if (args.size() < n) { throw std::runtime_error("more args required"); }

AMD64Assembly::Context::Context() {
    op   = OP_INVALID;
}

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
    if(i == 0x80) {
        switch(state.get("rax")) {
        case 1:
            emit outputRequested(QString("[SYS WRITE] %1")
                .arg(QString::number(state.get("rbx"), 16)));
            return;
        default:
            throw std::runtime_error("Unknown syscall");
        }
    }
    throw std::runtime_error("Unknown interrupt");
}

bool AMD64Assembly::isSizeModifier(QString token) {
    return __sizes.contains(token);
}

bool AMD64Assembly::isLabel(QString token) {
    return !__ops.contains("op") && token.endsWith(":");
}

bool AMD64Assembly::isOperand(QString token) {
    return __ops.contains(token);
}

OP_SIZE AMD64Assembly::size(QString token) {
    return __sizes[token];
}

void AMD64Assembly::parseContext(QString line, AMD64Assembly::Context* ctx) {
    QStringList splitted = line.simplified().split(" ");
    QString op = splitted[0];

    if(isOperand(op)) {
        ctx->op = __ops[op];
    } else if (isLabel(op)) {
        ctx->op = OP_TYPE::LABEL;
    } else {
        throw std::runtime_error("Unknown opcode");
    }

    if(splitted.size() > 1) {
        QString rawArgs;
        for(int i = 1; i < splitted.size(); i++) {
            rawArgs.append(splitted[i]);
        }
        QStringList args = rawArgs.split(",");
        for(int i = 0; i < args.size(); i++) {
            ctx->args.push_back(args[i]);
        }
    }
}

#define requires_args(n) if(args.size() < n) { throw std::runtime_error("more arguments required"); }

void AMD64Assembly::executeContext(AMD64Assembly::Context& ctx) {
    int64_t v = 0;
    int64_t v1, v2;
    v1 = v2 = 0;
    QList<QString> args = ctx.args;
    switch(ctx.op) {
    case LABEL:
    case NOP:
        break;
    case MOV:
        requires_args(2)
        set(args[0], value(args[1]));
        if(args[0] == "rsp") {
            memory.setStackPointer(state.get("rsp"));
        }
        break;
    case PUSH:
        requires_args(1)
        memory.push(value(args[0]));
        state.set("rsp", memory.getStackPointer());
        break;
    case POP:
        requires_args(1)
        state.set(args[0], memory.pop());
        state.set("rsp", memory.getStackPointer());
        break;
    case INC:
        requires_args(1)
        v = value(args[0]) + 1;
        state.set(args[0], v);
        setFlag(FL_ZF, v == 0);
        setFlag(FL_SF, v < 0);
        break;
    case DEC:
        requires_args(1)
        v = value(args[0]) - 1;
        state.set(args[0], v);
        setFlag(FL_ZF, v == 0);
        setFlag(FL_SF, v < 0);
        break;
    case ADD:
        requires_args(2)
        v = value(args[0]) + value(args[1]);
        state.set(args[0], v);
        setFlag(FL_ZF, v == 0);
        setFlag(FL_SF, v < 0);
        break;
    case SUB:
        requires_args(2)
        v1 = value(args[0]);
        v2 = value(args[1]);
        state.set(args[0], v1 - v2);
        setFlag(FL_SF, v1 - v2 < 0);
        break;
    case MUL:
        requires_args(1)
        state.set("rax", state.get("rax") * value(args[0]));
        break;
    case DIV:
        requires_args(1)
        v1 = value(args[1]);
        v2 = value("rax");
        if(v1 == 0) {
            throw std::runtime_error("zero division");
        }
        state.set("rax", v2 / v1);
        state.set("rdx", v2 % v1);
        break;
    case AND:
        requires_args(2)
        v1 = value(args[0], MODE_REG | MODE_MEM);
        v2 = value(args[1]);
        state.set(args[0], v1 & v2);
        break;
    case OR:
        requires_args(2)
        v1 = value(args[0], MODE_REG | MODE_MEM);
        v2 = value(args[1]);
        state.set(args[0], v1 | v2);
        break;
    case XOR:
        requires_args(2)
        v1 = value(args[0], MODE_REG | MODE_MEM);
        v2 = value(args[1]);
        state.set(args[0], v1 ^ v2);
        break;
    case SHL:
        requires_args(2)
        v1 = value(args[0], MODE_REG | MODE_MEM);
        v2 = value(args[1], MODE_IMM);
        v = v1 << v2;
        state.set(args[0], v);
        setFlag(FL_ZF, v == 0);
        setFlag(FL_CF, (v1 & (((uint64_t) 1) << (63 - v2))) != 0);
        break;
    case SHR:
        requires_args(2)
        v1 = value(args[0], MODE_REG | MODE_MEM);
        v2 = value(args[1], MODE_IMM);
        v = v1 >> v2;
        state.set(args[0], v);
        setFlag(FL_ZF, v == 0);
        setFlag(FL_CF, (v1 & (1 << v2)) != 0);
        break;
    case CMP:
        requires_args(2)
        v1 = value(args[0]);
        v2 = value(args[1]);
        v = v1 - v2;
        setFlag(FL_ZF, v == 0);
        setFlag(FL_SF, v < 0);
        setFlag(FL_OF, 0); // TODO
        break;
    case JE:
        requires_args(1)
        if(getFlag(FL_ZF)) {
            nextLine = jump(args[0]);
            return;
        }
        break;
    case JNE:
        requires_args(1)
        if(!getFlag(FL_ZF)) {
            nextLine = jump(args[0]);
            return;
        }
        break;
    case JL:
        requires_args(1)
        if(getFlag(FL_SF) != getFlag(FL_OF)) {
            nextLine = jump(args[0]);
            return;
        }
        break;
    case JB:
        requires_args(1)
        if(getFlag(FL_CF)) {
            nextLine = jump(args[0]);
            return;
        }
        break;
    case JBE:
        requires_args(1)
        if(getFlag(FL_CF) || getFlag(FL_ZF)) {
            nextLine = jump(args[0]);
            return;
        }
        break;
    case JLE:
        requires_args(1)
        if(getFlag(FL_ZF) || (getFlag(FL_SF) != getFlag(FL_OF))) {
            nextLine = jump(args[0]);
            return;
        }
        break;
    case JG:
        requires_args(1)
        if(!getFlag(FL_ZF) && (getFlag(FL_SF) == getFlag(FL_OF))) {
            nextLine = jump(args[0]);
            return;
        }
        break;
    case JGE:
        requires_args(1)
        if(getFlag(FL_SF) == getFlag(FL_OF)) {
            nextLine = jump(args[0]);
            return;
        }
        break;
    case JMP:
        requires_args(1)
        nextLine = jump(args[0]);
        return;
    case CALL:
        requires_args(1)
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
        requires_args(2)
        v = value(args[0]);
        set(args[0], value(args[1]));
        set(args[1], v);
        break;
    case INT:
        requires_args(1)
        interrupt(value(args[0], MODE_IMM));
        break;
    case TEST:
        requires_args(2)
        v1 = value(args[0], MODE_REG | MODE_MEM);
        v2 = value(args[1]);
        v  = v1 & v2;
        setFlag(FL_ZF, v == 0);
        setFlag(FL_OF, 0);
        setFlag(FL_CF, 0);
        setFlag(FL_SF, v < 0);
        // TODO PF
        break;
    case LEA:
        requires_args(2)
        set(args[0], lea(args[1]));
        break;
    case NOT:
        requires_args(1)
        v = value(args[0], MODE_REG | MODE_MEM);
        set(args[0], ~v);
        break;
    case NEG:
        requires_args(1)
        v = value(args[0], MODE_REG | MODE_MEM);
        set(args[0], (~v) + 1);
        break;
    default:
        throw std::runtime_error("unimplemented/invalid opcode");
    }
     nextLine = currentLine + 1;
}

void AMD64Assembly::executeLine(QString line) {
    line = line.simplified();
    if(line.isEmpty()) {
        nextLine = currentLine + 1;
        return;
    }
    state.set("rip", currentLine * 8, true);
    Context ctx;
    parseContext(line, &ctx);
    executeContext(ctx);
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

uint64_t AMD64Assembly::lea(QString operand) {
    if(!operand.startsWith("[") && !operand.endsWith("]")) {
        throw std::runtime_error("memory operand required");
    }
    cparse::TokenMap vars;
    for(QString reg: state.getRegisters()) {
        vars[reg.toStdString().c_str()] = state.get(reg);
    }
    for(QString reg: state.getAliases()) {
        vars[reg.toStdString().c_str()] = state.get(reg);
    }
    cparse::packToken tok = cparse::calculator::calculate(operand.sliced(1, operand.size() - 2).toStdString().c_str(), &vars);
    return tok.asInt();
}
