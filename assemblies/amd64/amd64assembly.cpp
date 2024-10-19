#include "amd64assembly.h"
#include "amd64states.h"

#include <QTimer>

enum OP_TYPE {
    MOV,
    PUSH,
    POP,
    INC,
    DEC,
    ADD,
    SUB,
    DIV,
    MUL,
    JMP
};

static const QMap<QString, OP_TYPE> __ops = {
    {"mov" , MOV  },
    {"push", PUSH },
    {"pop" , POP  },
    {"inc" , INC  },
    {"dec" , DEC  },
    {"add" , ADD  },
    {"sub" , SUB  },
    {"div" , DIV  },
    {"mul" , MUL  },
    {"jmp" , JMP  }
};

#define parse_args(args, n) args = _args.split(","); if (args.size() < n) { throw std::runtime_error("more args required"); }

AMD64Assembly::AMD64Assembly() {
    state.setRepresentationWidget(new AMD64States());
    state.addRegister("rax");
    state.addRegister("rbx");
    state.addRegister("rcx");
    state.addRegister("rdx");
    state.addRegister("rdi");
    state.addRegister("rsi");
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

    if((mode & MODE_REG) && !(mode & MODE_IMM)) {
        goto reg;
    }

    if(s.startsWith("0") && s.size() > 3) {
        if(s[1] == 'x') {
            base = 16;
            s = s.last(s.size() - 2);
        } if(s[1] == 'b') {
            base = 2;
            s = s.last(s.size() - 2);
        }
    }

    tmp = s.toULongLong(&v, base);

reg:
    if(v) {
        return tmp;
    } else {
        if(!(mode & MODE_REG)) {
            throw std::runtime_error("immediate value required");
        }
        return state.get(s);
    }
}

void AMD64Assembly::executeLine(QString line) {

    QStringList splitted = line.split(" ");
    QString op;
    QString _args;
    QStringList args;

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
        case MOV:
            parse_args(args, 2);
            state.set(args[0], value(args[1]));
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
            state.set(args[0], value(args[0]) - value(args[1]));
            break;
        case MUL:
            parse_args(args, 2);
            state.set(args[0], value(args[0]) * value(args[1]));
            break;
        case DIV:
            parse_args(args, 2);
            if(value(args[1]) == 0) {
                throw std::runtime_error("zero division");
            }
            state.set(args[0], value(args[0]) / value(args[1]));
            break;
        case JMP:
            parse_args(args, 1);
            for(int line = 0; line < code.size(); line++) {
                if(code[line].startsWith(args[0]) && code[line].endsWith(":")) {
                    nextLine = line;
                    return;
                }
            }
            nextLine = value(args[0]);
            break;
        }
    }

    nextLine = currentLine + 1;
}
