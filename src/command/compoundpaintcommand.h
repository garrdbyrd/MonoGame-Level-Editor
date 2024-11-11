#ifndef COMPOUNDPAINTCOMMAND_H
#define COMPOUNDPAINTCOMMAND_H

#include "commandhistory.h"
#include "texturemanager.h"

#include <QGraphicsPixmapItem>
#include <QList>
#include <QString>

class CompoundPaintCommand : public Command
{
    public:
    CompoundPaintCommand(
        TextureManager &textureManager,
        const QList<QGraphicsPixmapItem *> &items,
        const QList<QString> &prevTextureKeys,
        const QList<QString> &newTextureKeys
    );

    void execute() override;
    void undo() override;

    private:
    TextureManager &textureManager;
    QList<QGraphicsPixmapItem *> items;  // List of affected items
    QList<QString> prevTextureKeys;      // List of previous pixmaps
    QList<QString> newTextureKeys;       // List of new pixmaps
};

#endif  // COMPOUNDPAINTCOMMAND_H
