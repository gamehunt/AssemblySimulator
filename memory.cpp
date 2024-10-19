#include "memory.h"

uint64_t Memory::stackAddress = 0xFFFFFFFF00000000;

Memory::Memory(QObject *parent)
    : QObject{parent}
{
    stackPointer = stackAddress;
}

uint64_t Memory::pop() {
    uint64_t v    = get<uint64_t>(stackPointer);
    stackPointer += 8;
    emit stackChanged(stackPointer);
    return v;
}

void Memory::push(uint64_t value) {
    stackPointer -= 8;
    set<uint64_t>(stackPointer, value);
    emit stackChanged(stackPointer);
}

uint64_t Memory::getStackAddress()
{
    return stackAddress;
}

void Memory::setStackAddress(uint64_t newStackAddress)
{
    stackAddress = newStackAddress;
}

uint64_t Memory::getStackPointer() const
{
    return stackPointer;
}

void Memory::setStackPointer(uint64_t newStackPointer)
{
    stackPointer = newStackPointer;
    emit stackChanged(stackPointer);
}

void Memory::reset() {
    setStackPointer(stackAddress);
    memory.clear();
}
