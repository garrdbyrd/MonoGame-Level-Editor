#include "compoundpaintcommand.h"

CompoundPaintCommand::CompoundPaintCommand(
    const QList<QGraphicsPixmapItem *> &items,
    const QList<QPixmap> &prevPixmaps,
    const QList<QPixmap> &newPixmaps
)
    : items(items), prevPixmaps(prevPixmaps), newPixmaps(newPixmaps)
{
}

void CompoundPaintCommand::execute()
{
    for (int i = 0; i < items.size(); ++i) {
        if (i < newPixmaps.size() && items[i] != nullptr) {
            items[i]->setPixmap(newPixmaps[i]);
        }
    }
}

void CompoundPaintCommand::undo()
{
    for (int i = 0; i < items.size(); ++i) {
        if (i < prevPixmaps.size() && items[i] != nullptr) {
            items[i]->setPixmap(prevPixmaps[i]);
        }
    }
}
