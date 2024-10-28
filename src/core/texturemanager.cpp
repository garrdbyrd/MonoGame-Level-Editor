#include "texturemanager.h"

#include <QDir>
#include <QDirIterator>
// #include <QMap>
#include <QDebug>
#include <QPixmap>
#include <QString>
#include <iostream>

TextureManager::TextureManager() {}

TextureManager::~TextureManager()
{
    // qDeleteAll(textureMap);
    // textureMap.clear();
    for (auto &pair : textureMap) {
        delete pair.second;
    }
    textureMap.clear();
}

QPixmap *TextureManager::getTexture(const QString &key)
{
    // return textureMap.value(key, nullptr);
}

void TextureManager::loadTexture(const QString &key, const QString &filePath)
{
    // if (!textureMap.contains(key)) {
    //   QPixmap *textureMap = new QPixmap(filePath);
    //   if (textureMap->isNull()) {
    //     delete textureMap;
    //   } else {
    //     textureMap.insert(key, textureMap);
    //   }
    // }
}

void TextureManager::unloadTexture(const QString &key)
{
    // QPixmap *texture = textureMap.take(key);
    // delete texture;
}

void TextureManager::addStringTexturePair(
    const QString textureName,
    const QPixmap *textureLoc
)
{
    if (!(textureMap.find(textureName) != textureMap.end())) {
        textureMap[textureName] = const_cast<QPixmap *>(textureLoc);
    }
}

void TextureManager::loadAllTextures(const QString &directoryPath)
{
    QDir directory(directoryPath);
    QStringList subDirs =
        directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QString &subDirName : subDirs) {
        QDir subDir(directory.absoluteFilePath(subDirName));
        QStringList pngFiles =
            subDir.entryList(QStringList() << "*.png", QDir::Files);
        for (const QString &fileName : pngFiles) {
            QString accessibleName =
                subDirName + "/" + QFileInfo(fileName).baseName();
            QPixmap *pixmap = new QPixmap(subDir.absoluteFilePath(fileName));
            if (!pixmap->isNull()) {
                addStringTexturePair(accessibleName, pixmap);
            } else {
                delete pixmap;
            }
        }
    }
}
