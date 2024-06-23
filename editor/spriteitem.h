#ifndef SPRITEITEM_H
#define SPRITEITEM_H

#include <QListWidgetItem>
#include <QIcon>

class SpriteItem : public QListWidgetItem {
public:
    SpriteItem(const QIcon &icon, const QSize &size, QListWidget *parent = nullptr);

    QSize getSize() const;

private:
    QSize spriteSize;
};

#endif // SPRITEITEM_H
