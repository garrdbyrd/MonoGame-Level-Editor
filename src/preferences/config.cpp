#include "config.h"
#include "doublespinboxwidget.h"
#include "filebrowsewidget.h"
#include "spinboxwidget.h"

#include <QLineEdit>

Config::Config()
        : QSettings("caspian-local/preferences.ini", QSettings::IniFormat) {
    // Main
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings::setPath(
        QSettings::IniFormat, QSettings::UserScope, "caspian-local");
    // Paths
    assetPath =
        this->value("FilePaths/AssetPath", "caspian-local/assets").toString();
    defaultTexturePath = this->value(
                                 "FilePaths/DefaultTexture",
                                 "caspian-local/assets/default/default.png")
                             .toString();
    iconsPath =
        this->value("FilePaths/IconsPath", "/usr/share/icons/breeze-dark")
            .toString();
    // Constants
    scrollSpeed = this->value("Constants/ScrollSpeed", 72).toInt();
    zoomScale = this->value("Constants/ZoomScale", 1.15).toDouble();
    tileMenuColumns = this->value("Constants/TileMenuColumns", 4).toInt();

    // Set maps
    // FilePaths
    dialogMap["AssetPath"] = new FileBrowseWidget();
    dialogMap["DefaultTexture"] = new FileBrowseWidget();
    dialogMap["IconsPath"] = new FileBrowseWidget();
    // Constants
    dialogMap["ScrollSpeed"] = new SpinBoxWidget(0, 960, 8);
    dialogMap["ZoomScale"] = new DoubleSpinBoxWidget(1, 16, 0.05);
    dialogMap["TileMenuColumns"] = new SpinBoxWidget(1, 8, 1);
}

QMap<QString, QVariant> Config::getSettings(const QString &section) {
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

QWidget *Config::getSettingWidget(const QString &settingName) {
    return dialogMap.value(settingName, nullptr);
}
