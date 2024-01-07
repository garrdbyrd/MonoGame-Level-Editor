#include "maingraphicsview.h"
#include <QGraphicsScene>
#include <QMouseEvent>

MainGraphicsView::MainGraphicsView(QWidget *parent)
    : QGraphicsView(parent), tileSize(72) {
    // Set up the scene
    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);
}

void MainGraphicsView::setupGrid(int rows, int cols, int tileSize) {
    this->tileSize = tileSize;
    for (int row = 0; row < rows; ++row) {
        QVector<QGraphicsPixmapItem*> gridRow;
        for (int col = 0; col < cols; ++col) {
            QGraphicsPixmapItem *item = scene()->addPixmap(QPixmap());
            item->setPos(col * tileSize, row * tileSize);
            gridRow.push_back(item);
        }
        grid.push_back(gridRow);
    }
}

void MainGraphicsView::setCurrentTexture(const QPixmap &texture) {
    currentTexture = texture;
}

void MainGraphicsView::mousePressEvent(QMouseEvent *event) {
    QPointF scenePoint = mapToScene(event->pos());
    int row = static_cast<int>(scenePoint.y()) / tileSize;
    int col = static_cast<int>(scenePoint.x()) / tileSize;

    if (row >= 0 && row < grid.size() && col >= 0 && col < grid[row].size()) {
        QGraphicsPixmapItem *item = grid[row][col];
        item->setPixmap(currentTexture.scaled(tileSize, tileSize));
    }

    QGraphicsView::mousePressEvent(event); // Call the base class implementation
}
