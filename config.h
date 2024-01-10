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
    // Methods
    QMap<QString, QVariant> getSettings(const QString& section);
    QWidget* getSettingWidget(const QString& settingName);
private:
    QMap<QString, QWidget*> dialogMap;
};

#endif // CONFIG_H
