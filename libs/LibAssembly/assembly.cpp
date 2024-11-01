#include "assembly.h"

Assembly::Assembly(QObject* o){
    currentLine = 0;
    nextLine = 0;
    stopped = false;

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
    stopped = false;
    memory.reset();
    code.clear();
    state.reset();
}

void Assembly::error(QString err) {
    currentLine = nextLine = -1;
    emit errorOccured(err);
}

void Assembly::execute() {
    stopped = false;
    while(!stopped && !isFinished()) {
        step();
        QApplication::processEvents();
    }
}

void Assembly::step() {
    if(!isFinished()) {
        try {
            emit lineExecuted(currentLine);
            executeLine(code[currentLine]);
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
    stopped = true;
}

bool Assembly::isFinished() const {
    return currentLine < 0 || currentLine >= code.size();
}

int Assembly::getCurrentLine() {
    return currentLine;
}
