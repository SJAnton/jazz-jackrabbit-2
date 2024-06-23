#ifndef QSTRING_HASH_H
#define QSTRING_HASH_H

#include <QString>
#include <functional>

#ifndef QT_HASH_QSTRING_DEFINED
#define QT_HASH_QSTRING_DEFINED

// Especialización de std::hash para QString
namespace std {
template<>
struct hash<QString> {
    size_t operator()(const QString &key) const {
        return qHash(key);
    }
};
}
#endif

#endif // QSTRING_HASH_H
