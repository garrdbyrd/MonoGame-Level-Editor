#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <QMap>
#include <QPixmap>
#include <QString>

class TextureManager
{
    public:
    TextureManager();
    ~TextureManager();

    QList<QString> subDirList;
    QMap<QString, QPixmap> textureMap;

    QPixmap getTexture(const QString &textureName);
    void loadTexture(const QString &key, const QString &filePath);
    void unloadTexture(const QString &key);
    void loadAllTextures(const QString &directoryPath);
    void addStringTexturePair(const QString name, const QPixmap *texture);
};

#endif  // TEXTUREMANAGER_H
