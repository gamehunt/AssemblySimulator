#include "assembly.h"

Assembly::Assembly(QObject* o){
    currentLine = 0;
    nextLine = 0;

    QObject::connect(&memory, &Memory::stackChanged, this, &Assembly::emitStack);
}

void Assembly::emitStack(uint64_t ptr) {
    QStringList r;
    while(ptr < memory.getStackAddress()) {
        r.push_back(toHex(memory.get<uint64_t>(ptr), state.getWidth()));
        ptr += 8;
    }
    emit stackChanged(r);
}


void Assembly::setCode(QStringList c) {
    code = c;
}

StateManager* Assembly::getState() {
    return &state;
}

Memory* Assembly::getMemory() {
    return &memory;
}

void Assembly::reset() {
    nextLine = currentLine = 0;
    memory.reset();
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
