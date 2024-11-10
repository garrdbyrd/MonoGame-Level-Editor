#include "caspian.h"
#include "customtoolbar.h"
#include "ui_caspian.h"

void Caspian::setupToolbar()
{
    CustomToolBar *toolbar = new CustomToolBar(this);
    connect(
        toolbar,
        &CustomToolBar::tilePickerRefresh,
        this,
        &Caspian::populateScrollMenu
    );
    this->addToolBar(toolbar);
    connect(
        ui->actionPreferences,
        &QAction::triggered,
        this,
        &Caspian::onPreferencesTriggered
    );
    connect(ui->actionUndo, &QAction::triggered, this, &Caspian::undo);
    connect(ui->actionRedo, &QAction::triggered, this, &Caspian::redo);
    updateActionStates();
}