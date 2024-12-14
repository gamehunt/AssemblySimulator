#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "memory.h"
#include "statemanager.h"
#include "LibAssembly_global.h"

#include <QApplication>
#include <QObject>
#include <QStack>
#include <QSyntaxHighlighter>

/*! \mainpage Создание своей реализации ассемблера
 *
 *  Для того, чтобы создать свою реализацию ассемблера, необходимо сделать несколько вещей:
 *  -# Создать подкласс исполнителя \ref Assembly
 *      - Переопределить необходимые методы - обычно \ref Assembly::executeLine(QString) и \ref Assembly::reset()
 *      - Создать подкласс QWidget для репрезентации \ref StateManager и установить его в конструкторе подкласса \ref Assembly
 *      - [Опционально] Создать подкласс QSyntaxHighlighter и переопределить \ref Assembly::getSyntaxHighlighter()
 *  -# Создать подкласс интерфейса \ref AssemblyInterface, см. https://doc.qt.io/qt-6/plugins-howto.html
 *  -# Скомпилировать всё в динамическую библиотеку и поместить её в папку assemblies корня приложения
 *
 *  Для упрощения создания интерпретатора ассемблера можно использовать библиотеку LibParse, которая является оболочкой над cparse (см. https://github.com/cparse/cparse)
 */

/*!
 *   \brief  Родительский класс всех реализаций ассемблера (исполнитель)
 *   \author Lizord
 *   \date   Декабрь 2024
 *
 *   Для того, чтобы создать свою реализацию ассемблера, необходимо наследовать этот класс
 *   и переопределить его виртуальные слоты
 */
class LIBASSEMBLY_EXPORT Assembly: public QObject
{
    Q_OBJECT
public:

    /*!
     *  \brief     Конструктор
     *  \param[in] o - Родитель
     */
    explicit Assembly(QObject* o = nullptr);

    /*!
     *  \brief     Загружает код в исполнитель
     *  \param[in] c Массив из строк кода
     */
    void setCode(QStringList c);

    /*!
     *  \brief  Возвращает менеджер состояния исполнителя
     *  \return Менеджер состояния
     */
    StateManager* getState();

    /*!
     *  \brief  Возвращает менеджер памяти исполнителя
     *  \return Менеджер памяти
     */
    Memory* getMemory();

    /*!
     *  \brief  Проверяет окончание выполнения программы
     *  \return true, если исполнение закончено, иначе false
     */
    bool isFinished() const;

    /*!
     *  \brief  Возвращает текущую исполняемую строку
     *  \return текущая строка
     */
    int  getCurrentLine();

    /*!
     *  \brief  Возвращает менеджер подсветки синтаксиса.
     *  \note   Переопределите этот метод для реализации своей подсветки.
     *  \return менеджер подсветки синтаксиса (по умолчанию nullptr - подсветка отключена)
     */
    virtual QSyntaxHighlighter* getSyntaxHighlighter() { return nullptr; }

public slots:
    /*!
     *  \brief Обработчик ошибок.
     *  Посылает сигнал \ref errorOccured(QString)
     *  \param[in] err - сообщение об ошибке
     */
    virtual void error(QString err);

    /*!
     *  \brief Начинает исполнение программы.
     *  По умолчанию вызывает \ref step(), пока исполнение не будет окончено или остановлено
     */
    virtual void execute();

    /*!
     *  \brief Делает один шаг исполнения.
     */
    virtual void step();

    /*!
     *  \brief Выполняет строку кода
     *  \throws std::exception Может генерировать любые исключения, в зависимости от хода исполнения
     *  \param[in] l - Строка кода
     *  \note Переопределите этот метод для реализации своей логики исполнения программы.
     */
    virtual void executeLine(QString l);

    /*!
     *  \brief Останавливает исполнение.
     */
    virtual void stop();

    /*!
     *  \brief Сбрасывает состояние исполнителя.
     */
    virtual void reset();

protected slots:
    /*!
     *  \brief Вызывается при изменении стека, чтобы обновить его отображение.
     *  Вызывает \ref stackChanged для дальнейшей пропагации изменений.
     *
     *  \param[in] ptr - Новый указатель на вершину стека
     */
    void emitStack(uint64_t ptr);

signals:
    /*!
     *   \brief Посылается при изменении стека.
     *   \param l - значения стека
     */
    void stackChanged(QStringList l);

    /*!
     *   \brief Посылается при ошибке.
     *   \param e - ошибка
     *   \note  Вам нужно вызывать это при переопределении \ref error()
     */
    void errorOccured(QString e);

    /*!
     *   \brief Посылается при успешном выполнении строки.
     *   \param line - исполненая строка
     *   \note  Вам нужно вызывать это перед вызовом \ref executeLine() при переопределении метода \ref step()
     */
    void lineExecuted(int line);

    /*!
     *   \brief Посылается при необходимости вывести значение в консоль.
     *   \param message - сообщение
     */
    void outputRequested(QString message);

protected:
    /*!
     *  \brief Менеджер памяти
     */
    Memory memory;

    /*!
     *  \brief Менеджер состояния
     */
    StateManager state;

    /*!
     *  \brief Массив строк кода
     */
    QStringList      code;

    /*!
     *  \brief Текущая строка
     *  \note При переопределении \ref step вам нужно изменять \ref currentLine на только что исполненую строку (индекс в \ref code)
     */
    int currentLine;

    /*!
     *  \brief Следущая строка
     *  \note  При переопределении \ref executeLine вам нужно изменять \ref nextLine на следующую к исполнению строку (индекс в \ref code)
     */
    int nextLine;

    /*!
     *  \brief Флаг остановки
     */
    bool stopped;
};

/*!
 *    \brief  Интерфейс библиотеки для QPluginLoader
 *    \author Lizord
 *    \date   Декабрь 2024
 *    \note   Наследуйте этот класс для создания модуля с реализацией ассемблера
 */
class AssemblyInterface: public QObject {
public:
    virtual ~AssemblyInterface() = default;

    /*!
     *  \brief  Возвращает название диалекта и архитектуры ассемблера
     *  \return название диалекта и архитектуры
     */
    virtual QString   getName() = 0;

    /*!
     *  \brief  Возвращает реализацию ассемблера
     *  \return реализация исполнителя
     */
    virtual Assembly* getAssembly() = 0;
};

Q_DECLARE_INTERFACE(AssemblyInterface, "ru.l1zz.asmsim.AssemblyInterface")

#endif // ASSEMBLY_H
