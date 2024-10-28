#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <QMap>
#include <QPixmap>
#include <QString>
#include <map>

class TextureManager
{
   public:
    TextureManager();
    ~TextureManager();
    // Methods
    QPixmap *getTexture(const QString &key);
    void loadTexture(const QString &key, const QString &filePath);
    void unloadTexture(const QString &key);
    void loadAllTextures(const QString &directoryPath);
    void addStringTexturePair(const QString name, const QPixmap *texture);

    std::map<QString, QPixmap *> textureMap;
    QList<QString> subDirList;

    // private:
    //   QMap<QString, QPixmap *> textureMap;
};

#endif  // TEXTUREMANAGER_H
