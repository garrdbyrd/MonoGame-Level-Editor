#include "config.h"
#include "filebrowsewidget.h"

#include <QLineEdit>

Config::Config() : QSettings("caspian-local/preferences.ini", QSettings::IniFormat) {
    // Main
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, "caspian-local");
    // Paths
    assetPath = this->value("caspian-local/assets", "caspian-local/assets").toString();
    defaultTexturePath = this->value("caspian-local/assets/default/default.png", "caspian-local/assets/default/default.png").toString();
    // Constants
    scrollSpeed = this->value("Constants/ScrollSpeed", 72).toInt();
    zoomScale = this->value("Constants/ZoomScale", 1.15).toDouble();
    tileMenuColumns = this->value("Constants/TileMenuColumns", 4).toInt();

    // Set map
    dialogMap["AssetPath"] = new FileBrowseWidget();
    dialogMap["DefaultTexture"] = new FileBrowseWidget();
}

QMap<QString, QVariant> Config::getSettings(const QString& section) {
    QMap<QString, QVariant> settingsMap;

    // Begin reading from the specified section
    this->beginGroup(section);

    // Iterate over all keys in the section
    foreach (const QString &key, this->allKeys()) {
        settingsMap.insert(key, this->value(key));
    }

    // End reading from the section
    this->endGroup();

    return settingsMap;
}

QWidget* Config::getSettingWidget(const QString& settingName) {
    return dialogMap.value(settingName, nullptr);
}
