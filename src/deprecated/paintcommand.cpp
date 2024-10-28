#include "paintcommand.h"

PaintCommand::PaintCommand(
    QGraphicsPixmapItem *item,
    const QPixmap &prevPixmap,
    const QPixmap &newPixmap
)
    : item(item), prevPixmap(prevPixmap), newPixmap(newPixmap)
{
}

// Execute the painting action
void PaintCommand::execute()
{
    if (item) {
        item->setPixmap(newPixmap);
    }
}

// Undo the painting action
void PaintCommand::undo()
{
    if (item) {
        item->setPixmap(prevPixmap);
    }
}
