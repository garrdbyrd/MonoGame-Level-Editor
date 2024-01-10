#include "customtoolbar.h"

CustomToolBar::CustomToolBar(const QString &title, QWidget *parent)
    : QToolBar(parent) {
    addTilePickerRefreshAction();
}

void CustomToolBar::addTilePickerRefreshAction(){
    QAction *refreshAction = this->addAction(QIcon("icons/actions/16/refactor.svg"), "Refresh");
    connect(refreshAction, &QAction::triggered, this, &CustomToolBar::tilePickerRefresh);
}
