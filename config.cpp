#include "config.h"

Config::Config() : settings("caspian-local/preferences.ini", QSettings::IniFormat) {
    // Paths
    assetPath = settings.value("caspian-local/assets", "caspian-local/assets").toString();
    defaultTexturePath = settings.value("caspian-local/assets/default/default.png", "caspian-local/assets/default/default.png").toString();
    // Constants
    scrollSpeed = settings.value("Constants/ScrollSpeed", 72).toInt();
    zoomScale = settings.value("Constants/ZoomScale", 1.15).toDouble();
}
