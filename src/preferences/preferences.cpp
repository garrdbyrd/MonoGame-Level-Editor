#include "caspian.h"
#include "preferencesdialog.h"

void Caspian::onPreferencesTriggered()
{
    preferencesDialog dialog(this);
    dialog.exec();
}