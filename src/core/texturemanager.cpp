#include "texturemanager.h"

#include <QMap>
#include <QPixmap>
#include <QString>

TextureManager::TextureManager() {}

TextureManager::~TextureManager() { qDeleteAll(textureMaps); }

QPixmap *TextureManager::getTexture(const QString &key) {
  return textureMaps.value(key, nullptr);
}

void TextureManager::loadTexture(const QString &key, const QString &filePath) {
  if (!textureMaps.contains(key)) {
    QPixmap *textureMap = new QPixmap(filePath);
    if (textureMap->isNull()) {
      delete textureMap;
    } else {
      textureMaps.insert(key, textureMap);
    }
  }
}

void TextureManager::unloadTexture(const QString &key) {
  // Remove and delete texture from the map
  QPixmap *texture = textureMaps.take(key);
  delete texture;
}
