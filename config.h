#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QString>

class Config : public QSettings
{
public:
    Config();
    // Paths
    QString assetPath;
    QString defaultTexturePath;
    // Constants
    int scrollSpeed;
    double zoomScale;
    int tileMenuColumns;
    QMap<QString, QVariant> getSettings(const QString& section);
};

#endif // CONFIG_H
