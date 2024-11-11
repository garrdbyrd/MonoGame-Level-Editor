#include "texturemanager.h"

#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QMap>
#include <QPixmap>
#include <QString>
#include "qpixmap.h"

TextureManager::TextureManager()
{
    QMap<QString, QPixmap> textureMap;
}

TextureManager::~TextureManager()
{
    // qDeleteAll(textureMap);
    // textureMap.clear();
}

QPixmap TextureManager::getTexture(const QString &textureKey)
{
    if (textureMap.contains(textureKey)) {
        QPixmap pixmap = textureMap.value(textureKey);
        if (pixmap.isNull()) {
            qWarning() << "Pixmap for key" << textureKey << "is null.";
        }
        return pixmap;
    }
    return QPixmap();
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
    // if (!(textureMap.find(textureName) != textureMap.end())) {
    //     textureMap[textureName] = const_cast<QPixmap *>(textureLoc);
    // }
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
            QString filePath = subDir.absoluteFilePath(fileName);
            textureMap[accessibleName] = filePath;
        }
    }
}
