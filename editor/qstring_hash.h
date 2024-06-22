#ifndef QSTRING_HASH_H
#define QSTRING_HASH_H

#include <QString>
#include <functional>

// Especialización de std::hash para QString
namespace std {
template<>
struct hash<QString> {
    size_t operator()(const QString &key) const {
        return qHash(key);
    }
};
}

#endif // QSTRING_HASH_H
