#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QString>

class Config
{
public:
    Config();
    // Paths
    QString assetPath;
    QString defaultTexturePath;
    // Constants
    int scrollSpeed;
    double zoomScale;

private:
    QSettings settings;
};

#endif // CONFIG_H
