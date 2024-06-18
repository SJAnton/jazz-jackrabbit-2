#include "spriteitem.h"

SpriteItem::SpriteItem(const QIcon &icon, const QSize &size, QListWidget *parent)
    : QListWidgetItem(icon, "", parent), spriteSize(size) {}

QSize SpriteItem::getSize() const {
    return spriteSize;
}
