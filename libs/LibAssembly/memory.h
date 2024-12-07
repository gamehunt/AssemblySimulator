#ifndef MEMORY_H
#define MEMORY_H

#include <QMap>
#include <QObject>
#include <QtDebug>

#include "LibAssembly_global.h"

/*!
 *   \brief Менеджер памяти
 *   \author Lizord
 *   \date Декабрь 2024
 *
 *   Отвечает за управление памятью, в т.ч стеком
 */
class LIBASSEMBLY_EXPORT Memory : public QObject
{
    Q_OBJECT

public:
    /*!
     *  \brief Конструктор
     *  \param parent - родитель
     */
    explicit Memory(QObject *parent = nullptr);

    /*!
     *  \brief Устанавливает значение по адресу
     *  \param address - Адрес памяти
     *  \param value - значение
     */
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

    /*!
     *  \brief Получает значение по адресу
     *  \param address - Адрес памяти
     *  \returns значение
     */
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

    /*!
     *  \brief Убирает значение с вершины стека
     *  \return значение с вершины стека
     */
    uint64_t pop();

    /*!
     *  \brief Кладёт значение на вершину стека
     *  \param value - значение
     */
    void push(uint64_t value);

    /*!
     *  \brief  Возвращает адрес стека
     *  \return адрес стека
     */
    static uint64_t getStackAddress();

    /*!
     *  \brief Устанавливает адрес стека
     *  \param newStackAddress - новый адрес стека
     */
    static void setStackAddress(uint64_t newStackAddress);

    /*!
     *  \brief  Возвращает указатель на вершину стека
     *  \return адрес вершины стека
     */
    uint64_t getStackPointer() const;

    /*!
     *  \brief Устанавливает указатель на вершину стека
     *  \param newStackPointer - адрес новой вершины стека
     */
    void setStackPointer(uint64_t newStackPointer);

    /*!
     *  \brief Сбрасывает состояние памяти
     */
    void reset();

    /*!
     *  \brief  Возвращает ссылку на словарь со всеми значениями в памяти
     *  \return Ссылка на словарь со всеми значениями в памяти
     */
    QMap<uint64_t, uint8_t>& getRaw();

signals:
    /*!
     *  \brief Отправляется когда изменяется значение в памяти
     *  \param addr - адрес ячейки
     *  \param oldValue - старое значение
     *  \param newValue - новое значение
     */
    void memoryChanged(uint64_t addr, uint8_t oldValue, uint8_t newValue);

    /*!
     *  \brief Отправляется когда изменяется стек
     *  \param stackPointer - новое значение стека
     */
    void stackChanged(uint64_t stackPointer);

protected:
    /*!
     *  \brief Адрес стека
     */
    static uint64_t stackAddress;

    /*!
     *  \brief Адрес вершины стека
     */
    uint64_t stackPointer;

    /*!
     *  \brief Словарь со значениями памяти
     */
    QMap<uint64_t, uint8_t> memory;
};

#endif // MEMORY_H
