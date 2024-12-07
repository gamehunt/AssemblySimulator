#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "LibAssembly_global.h"
#include "../../utils.h"

#include <QWidget>

/*!
 *   \brief  Регистр
 *   \author Lizord
 *   \date   Декабрь 2024
 */
struct LIBASSEMBLY_EXPORT Register {
    /*!
     * \brief значение регистра
     */
    uint64_t value;

    /*!
     * \brief доступен ли регистр для прямого чтения
     */
    bool     direct;
};

/*!
 *  \brief  Подрегистр
 *  \author Lizord
 *  \date   Декабрь 2024
 *
 *  Используется для реализации регистров меньшей размерности (rax -> eax, ax, ...)
 *
 *  Значение подрегистра вычисляется из исходного регистра как
 *  (src & mask) >> shift
 */
struct LIBASSEMBLY_EXPORT Alias {
    /*!
     *  \brief Исходный регистр
     */
    QString  src;

    /*!
     *  \brief Маска исходного регистра
     */
    uint64_t mask;

    /*!
     *  \brief Смещение исходного регистра
     */
    int shift;
};

/*!
 *   \brief  Менеджер состояния
 *   \author Lizord
 *   \date   Декабрь 2024
 */
class LIBASSEMBLY_EXPORT StateManager
{
public:
    StateManager(): _representation(nullptr), w(16) {;}

    /*!
     * \brief Устанавливает значение регистра
     * \throw std::invalid_argument В случае, если регистр не найден или помечен как direct = false и allowIndirect = false
     * \param r - регистр
     * \param v - значение
     * \param allowIndirect - если true, то разрешен доступ к регистрам, со значением direct = false
     */
    void set(QString r, uint64_t v, bool allowIndirect = false);

    /*!
     * \brief  Получает значение регистра
     * \throw  std::invalid_argument В случае, если регистр не найден или помечен как direct = false и allowIndirect = false
     * \param  v - регистр
     * \param  allowIndirect если true, то разрешен доступ к регистрам, со значением direct = false
     * \return значение регистра
     */
    uint64_t get(QString v, bool allowIndirect = false) const;

    /*!
     * \brief Добавляет новый регистр
     * \param r - Название регистра
     * \param direct - Доступен ли регистр для прямого обращения, true если да
     */
    void addRegister(QString r, bool direct = true);

    /*!
     * \brief Добавляет подрегистр в регистр
     * \param r - Название подрегистра
     * \param src - Название регистра
     * \param mask - Маска регистра
     * \param shift - Смещение регистра
     */
    void addAlias(QString r, QString src, uint64_t mask, int shift);

    /*!
     * \brief Проверяет наличие регистра
     * \param r - Название регистра
     * \return если true, то регистр найден
     */
    bool hasRegister(QString r) const;

    /*!
     * \brief Устанавливает виджет состояния для главного экрана
     * \param w - виджет
     */
    void setRepresentationWidget(QWidget* w);

    /*!
     * \brief Получает виджет репрезентации
     * \return виджет репрезентации
     */
    QWidget* getReprentationWidget();

    /*!
     * \brief Устанавливает ширину значения регистра (кол-во символов)
     * \param w - значение ширины
     */
    void setWidth(int w);

    /*!
     * \brief Возвращает ширину значения регистра (кол-во символов)
     * \return значение ширины
     */
    int getWidth();

    /*!
     * \brief Сбрасывает состояние
     */
    void reset();

    /*!
     * \brief Получает список названий регистров
     * \param includeIndirect - Если true, то включает в список indirect регистры
     * \return список названий регистров
     */
    QStringList getRegisters(bool includeIndirect = false);

    /*!
     * \brief Получает список подрегистров
     * \param reg - Если значение не пустое, то возвращает подрегистры только конкретного регистра
     * \return список подрегистров
     */
    QStringList getAliases(QString reg = QString());

private:
    QMap<QString, Register> _state;
    QMap<QString, Alias>    _aliases;
    QWidget*                _representation;

    int w;
};

#endif // STATEMANAGER_H
