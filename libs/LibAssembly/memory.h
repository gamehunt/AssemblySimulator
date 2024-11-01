#ifndef MEMORY_H
#define MEMORY_H

#include <QMap>
#include <QObject>
#include <QtDebug>

class Memory : public QObject
{
    Q_OBJECT
public:
    explicit Memory(QObject *parent = nullptr);

    template<typename T> void set(uint64_t address, T value) {
        int size = sizeof(T);
        if(size == 1) {
            uint8_t old = memory.value(address, 0);
            memory[address] = value;
            emit memoryChanged(address, old, value);
        } else {
            for(int i = 0; i < size; i++) {
                set<uint8_t>(address + i, ((value >> (i * 8)) & 0xFF));
            }
        }
    }

    template<typename T> T get(uint64_t address) const {
        if(!memory.contains(address)) {
            return 0;
        }
        int size = sizeof(T);
        if(size == 1) {
            return memory[address];
        } else {
            T value = 0;
            for(int i = size - 1; i >= 0; i--) {
                value <<= 8;
                value |= get<uint8_t>(address + i);
            }
            return value;
        }
    }

    uint64_t pop();
    void     push(uint64_t value);

    static uint64_t getStackAddress();
    static void setStackAddress(uint64_t newStackAddress);

    uint64_t getStackPointer() const;
    void setStackPointer(uint64_t newStackPointer);

    void reset();

    QMap<uint64_t, uint8_t>& getRaw();

signals:
    void memoryChanged(uint64_t addr, uint8_t oldValue, uint8_t newValue);
    void stackChanged(uint64_t stackPointer);

protected:
    static uint64_t stackAddress;
    uint64_t stackPointer;
    QMap<uint64_t, uint8_t> memory;
};

#endif // MEMORY_H
