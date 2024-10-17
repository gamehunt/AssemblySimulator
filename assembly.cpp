#include "assembly.h"

Assembly::Assembly(QObject* o){
    currentLine = 0;
    nextLine = 0;
}

void Assembly::push(uint64_t v) {
    stack.push(v);
    QStringList r;
    for(uint64_t v : std::as_const(stack)) {
        r.push_back(toHex(v, state.getWidth()));
    }
    emit stackChanged(r);
}

uint64_t Assembly::pop() {
    uint64_t v = stack.pop();
    QStringList r;
    for(uint64_t _v : std::as_const(stack)) {
        r.push_back(toHex(_v, state.getWidth()));
    }
    emit stackChanged(r);
    return v;
}

void Assembly::setCode(QStringList c) {
    code = c;
}

StateManager* Assembly::getState() {
    return &state;
}

QStack<uint64_t>* Assembly::getStack() {
    return &stack;
}

void Assembly::reset() {
    nextLine = currentLine = 0;
    stack.clear();
    emit stackChanged({});
    code.clear();
    state.reset();
}

void Assembly::error(QString err) {
    stop();
    emit errorOccured(err);
}

void Assembly::execute() {
    currentLine = 0;
    nextLine = 0;
    while(currentLine >= 0 && currentLine < code.size()) {
        step();
        QApplication::processEvents();
    }
}

void Assembly::step() {
    if(currentLine < code.size()) {
        try {
            executeLine(code[currentLine]);
            emit lineExecuted();
        } catch(std::exception& e) {
            error(e.what());
        }
        currentLine = nextLine;
    }
}

void Assembly::executeLine(QString l) {
    error("Unimplemented");
}

void Assembly::stop() {
    nextLine = currentLine = -1;
}
