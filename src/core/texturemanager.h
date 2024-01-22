#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <QMap>
#include <QPixmap>
#include <QString>

class TextureManager {
  public:
	TextureManager();
	~TextureManager();
	// Methods
	QPixmap *getTexture(const QString &key);
	void     loadTexture(const QString &key, const QString &filePath);
	void     unloadTexture(const QString &key);

  private:
	QMap<QString, QPixmap *> textureMaps;
};

#endif // TEXTUREMANAGER_H
