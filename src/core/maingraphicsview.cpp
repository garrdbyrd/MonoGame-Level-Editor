#include "maingraphicsview.h"
#include "config.h"
#include "compoundpaintcommand.h"

#include <QGraphicsScene>
#include <QMouseEvent>
#include <QScrollBar>
#include <QWheelEvent>

MainGraphicsView::MainGraphicsView(QWidget *parent) : QGraphicsView(parent) {
  isMiddleDragging = false;
  QGraphicsScene *scene = new QGraphicsScene(this);
  setScene(scene);
}

////////////////
// Grid setup //
////////////////
void MainGraphicsView::setupGrid(int rows, int cols, int tileSize) {
  this->tileSize = tileSize;

  for (int row = 0; row < rows; ++row) {
    QVector<QGraphicsPixmapItem *> gridRow;
    for (int col = 0; col < cols; ++col) {
      QGraphicsPixmapItem *item = scene()->addPixmap(nullTexture);
      item->setPos(col * tileSize, row * tileSize);
      item->setPixmap(currentTexture.scaled(tileSize, tileSize));
      gridRow.push_back(item);
    }
    grid.push_back(gridRow);
  }
}

void MainGraphicsView::setCurrentTexture(const QPixmap &texture) {
  currentTexture = texture;
}

void MainGraphicsView::noCurrentTexture() { currentTexture = nullTexture; }

////////////////////
// Mouse controls //
////////////////////
void MainGraphicsView::mousePressEvent(QMouseEvent *event) {
  QPointF scenePoint = mapToScene(event->pos());
  int row = static_cast<uint>(scenePoint.y()) / tileSize;
  int col = static_cast<uint>(scenePoint.x()) / tileSize;

  // Left Click on grid
  if (event->button() == Qt::LeftButton && row >= 0 && row < grid.size() && col >= 0 && col < grid[row].size() && !currentTexture.isNull() && grid[row][col]->pixmap().toImage() != currentTexture.scaled(tileSize, tileSize, Qt::KeepAspectRatio).toImage()) {
    isLeftDragging = true;
    isPainting = true;
    startPainting();
    applyPaint(grid[row][col]);
  }

  // Middle click
  if (event->button() == Qt::MiddleButton) {
    isMiddleDragging = true;
    lastMousePosition = event->pos();
    setCursor(Qt::ClosedHandCursor);
  }

  QGraphicsView::mousePressEvent(event);
}

void MainGraphicsView::wheelEvent(QWheelEvent *event) {
  Config settings;
  const int scrollAmount = settings.scrollSpeed;
  const double scaleFactor = settings.zoomScale;

  // Ignore if dragging
  if (isMiddleDragging) {
    // Ignore the wheel event if middle mouse button is pressed
    event->ignore();
    return;
  }

  // Set the anchor to zoom on the mouse position
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

  if (event->modifiers() & Qt::ControlModifier) {
    // Zooming with Ctrl + scroll
    if (event->angleDelta().y() > 0) {
      scale(scaleFactor, scaleFactor);
    } else {
      scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
  } else if (event->modifiers() & Qt::ShiftModifier) {
    // Horizontal scrolling with Shift + scroll
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() -
                                    (event->angleDelta().y() / 120) *
                                        scrollAmount);
  } else {
    // Vertical scrolling without modifiers
    verticalScrollBar()->setValue(verticalScrollBar()->value() -
                                  (event->angleDelta().y() / 120) *
                                      scrollAmount);
  }

  // Reset the anchor to the default
  setTransformationAnchor(QGraphicsView::NoAnchor);
}

void MainGraphicsView::mouseMoveEvent(QMouseEvent *event) {
  QPointF scenePoint = mapToScene(event->pos());
  int row = static_cast<uint>(scenePoint.y()) / tileSize;
  int col = static_cast<uint>(scenePoint.x()) / tileSize;
  if (isLeftDragging && row >= 0 && row < grid.size() && col >= 0 && col < grid[row].size() && !currentTexture.isNull() && grid[row][col]->pixmap().toImage() != currentTexture.scaled(tileSize, tileSize, Qt::KeepAspectRatio).toImage()) {
    applyPaint(grid[row][col]);
  }
  if (isMiddleDragging) {
    QPoint delta = event->pos() - lastMousePosition;
    lastMousePosition = event->pos();
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
    verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
  }
}

void MainGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    isLeftDragging = false;
    if (isPainting) {
      endPainting();
      isPainting = false;
    }
  }

  if (event->button() == Qt::MiddleButton) {
    isMiddleDragging = false;
    setCursor(Qt::ArrowCursor);
  }
}

// Paint
void MainGraphicsView::startPainting() {
  paintedItems.clear();
  prevPixmaps.clear();
}

void MainGraphicsView::applyPaint(QGraphicsPixmapItem* item) {
  if (!paintedItems.contains(item)) {
    paintedItems.append(item);
    prevPixmaps.append(item->pixmap());
    item->setPixmap(currentTexture.scaled(tileSize, tileSize, Qt::KeepAspectRatio));
  }
}

void MainGraphicsView::endPainting() {
  if (!paintedItems.isEmpty()) {
    QList<QPixmap> newPixmaps;
    for (auto item : qAsConst(paintedItems)) {
      newPixmaps.append(item->pixmap());
    }
    emit executeCommand(new CompoundPaintCommand(paintedItems, prevPixmaps, newPixmaps));
  }
}
