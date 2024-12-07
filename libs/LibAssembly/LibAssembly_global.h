/*!
 * \file
 * \brief Заголовочный файл с необходимыми определениями для библиотеки
 * \author Lizord
 * \date Декабрь 2024
 *
 * Вам нет причин его использовать
 */

#ifndef LIBASSEMBLY_GLOBAL_H
#define LIBASSEMBLY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBASSEMBLY_LIBRARY)
/*!
 *  Макрос для экспорта
 */
#define LIBASSEMBLY_EXPORT Q_DECL_EXPORT
#else
/*!
 *  Макрос для импорта
 */
#define LIBASSEMBLY_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBASSEMBLY_GLOBAL_H
