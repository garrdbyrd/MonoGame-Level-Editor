#ifndef CUSTOMTOOLBAR_H
#define CUSTOMTOOLBAR_H

#include <QToolBar>

class CustomToolBar : public QToolBar {
    Q_OBJECT

public:
    explicit CustomToolBar(const QString &title, QWidget *parent = nullptr);
    void addTilePickerRefreshAction();

signals:
    void tilePickerRefresh();

private:

};

#endif // CUSTOMTOOLBAR_H