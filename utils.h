#ifndef UTILS_H
#define UTILS_H

#include <QString>

static QString toHex(uint64_t v, int w) {
    char hex[w + 3];
    snprintf(hex, w + 3, "0x%.*lx", w, v);
    return QString(hex);
}

#endif // UTILS_H
