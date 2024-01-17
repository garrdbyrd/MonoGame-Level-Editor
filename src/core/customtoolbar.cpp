#include "customtoolbar.h"
#include "config.h"

CustomToolBar::CustomToolBar(QWidget *parent) : QToolBar(parent) {
	this->setStyleSheet("QToolBar {"
						"background-color: #1B1E20;"
						"spacing: 0px;"
						"padding: 3px;"
						// "padding-left: 6px;"
						// "padding-right: 6px;"
						// "padding-top: 0px;"
						// "padding-bottom: 0px;"
						"}"
						"QToolBar QToolButton { "
						"width: 18px;"
						"height: 18px;"
						"padding: 0px;"
						"spacing: 0px;"
						"icon-size: 18px;"
						"}");
	// this->setFixedHeight(32);
	// this->setIconSize(QSize(18,18));
	this->setMovable(false);
	this->setContextMenuPolicy(Qt::PreventContextMenu);
	addTilePickerRefreshAction();
}

void CustomToolBar::addTilePickerRefreshAction() {
	Config settings;
	QIcon refreshIcon      = QIcon(settings.iconsPath + "/actions/22/refactor.svg");
	QAction *refreshAction = this->addAction(refreshIcon, "Refresh");
	connect(refreshAction, &QAction::triggered, this, &CustomToolBar::tilePickerRefresh);
}
