#include <QStatusBar>
#include <QString>
#include "caspian.h"

void Caspian::setupStatusBar()
{
    connect(
        mainGraphicsView,
        &MainGraphicsView::mouseCoordinates,
        this,
        &Caspian::updateStatusBar
    );
}

void Caspian::updateStatusBar(int x, int y)
{
    // Format the point as a string
    if (0 <= x && 0 <= y) {
        QString statusMessage = QString("X: %1, Y: %2").arg(x).arg(y);
        statusBar()->showMessage(statusMessage);
    } else {
        QString statusMessage = QString("X: , Y: ");
        statusBar()->showMessage(statusMessage);
    }
}