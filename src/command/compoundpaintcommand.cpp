#include "compoundpaintcommand.h"
#include "texturemanager.h"

CompoundPaintCommand::CompoundPaintCommand(

    TextureManager &textureManager,
    const QList<QGraphicsPixmapItem *> &items,
    const QList<QString> &prevTextureKeys,
    const QList<QString> &newTextureKeys
)
    : textureManager(textureManager),
      items(items),
      prevTextureKeys(prevTextureKeys),
      newTextureKeys(newTextureKeys)
{
}

void CompoundPaintCommand::execute()
{
    for (int i = 0; i < items.size(); ++i) {
        if (i < newTextureKeys.size() && items[i] != nullptr) {
            QPixmap newPixmap = textureManager.getTexture(newTextureKeys[i]);
            items[i]->setPixmap(newPixmap);
        }
    }
}

void CompoundPaintCommand::undo()
{
    for (int i = 0; i < items.size(); ++i) {
        if (i < prevTextureKeys.size() && items[i] != nullptr) {
            QPixmap prevPixmap = textureManager.getTexture(prevTextureKeys[i]);
            items[i]->setPixmap(prevPixmap);
        }
    }
}
