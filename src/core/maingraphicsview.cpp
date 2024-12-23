#include "maingraphicsview.h"
#include "caspian.h"
#include "compoundpaintcommand.h"
#include "config.h"
#include "ui_caspian.h"

#include "config.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QMouseEvent>
#include <QScrollBar>
#include <QWheelEvent>

void Caspian::setupMainGraphicsView()
{
    mainGraphicsView = ui->mainGraphicsView;
    // mainGraphicsView(textureManager, ui->centralwidget);
    // mainGraphicsView->textureManager = this->textureManager;
    mainGraphicsView->setTextureManager(&this->textureManager);
    QGridLayout *layout = new QGridLayout(ui->tilePickerWidget);

    ui->tilePickerWidget->setLayout(layout);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->selectedGraphicsView->setScene(scene);

    // MainGraphicsView *mainGraphicsView = dynamic_cast<MainGraphicsView
    // *>(ui->mainGraphicsView);
    connect(
        mainGraphicsView,
        &MainGraphicsView::executeCommand,
        this,
        &Caspian::recordCommand
    );

    // QPixmap defaultTexture(settings.defaultTexturePath);
    textureManager.loadAllTextures(settings.assetPath);
    qWarning() << "Default texture" << settings.defaultTexturePath;
    mainGraphicsView->setCurrentTexture("default/default");
    mainGraphicsView->setupGrid(
        12, 20, 16
    );  // Change '16' if textures are not 16x16. It
        // should just be a multiple of your texture size.
    mainGraphicsView->noCurrentTexture();
}

MainGraphicsView::MainGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    setMouseTracking(true);

    isMiddleDragging = false;
    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);
}

void MainGraphicsView::setTextureManager(TextureManager *textureManager)
{
    this->textureManager = textureManager;
}

////////////////
// Grid setup //
////////////////
void MainGraphicsView::setupGrid(int rows, int cols, int tileSize)
{
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

void MainGraphicsView::setCurrentTexture(const QString &textureKey)
{
    currentTextureKey = textureKey;
    qWarning() << "Default texture" << textureKey;
    currentTexture = textureManager->getTexture(textureKey);
}

void MainGraphicsView::noCurrentTexture()
{
    currentTexture = nullTexture;
    currentTextureKey.clear();
}

////////////////////
// Mouse controls //
////////////////////
void MainGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QPointF scenePoint = mapToScene(event->pos());
    int row = static_cast<uint>(scenePoint.y()) / tileSize;
    int col = static_cast<uint>(scenePoint.x()) / tileSize;

    // Left Click on grid
    if (event->button() == Qt::LeftButton && row >= 0 && row < grid.size() &&
        col >= 0 && col < grid[row].size() && !currentTexture.isNull() &&
        grid[row][col]->pixmap().toImage() !=
            currentTexture.scaled(tileSize, tileSize, Qt::KeepAspectRatio)
                .toImage()) {
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

void MainGraphicsView::wheelEvent(QWheelEvent *event)
{
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
        horizontalScrollBar()->setValue(
            horizontalScrollBar()->value() -
            (event->angleDelta().y() / 120) * scrollAmount
        );
    } else {
        // Vertical scrolling without modifiers
        verticalScrollBar()->setValue(
            verticalScrollBar()->value() -
            (event->angleDelta().y() / 120) * scrollAmount
        );
    }

    // Reset the anchor to the default
    setTransformationAnchor(QGraphicsView::NoAnchor);
}

void MainGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF scenePoint = mapToScene(event->pos());
    int row = static_cast<uint>(scenePoint.y()) / tileSize;
    int col = static_cast<uint>(scenePoint.x()) / tileSize;
    if (isLeftDragging && row >= 0 && row < grid.size() && col >= 0 &&
        col < grid[row].size() && !currentTexture.isNull() &&
        grid[row][col]->pixmap().toImage() !=
            currentTexture.scaled(tileSize, tileSize, Qt::KeepAspectRatio)
                .toImage()) {
        applyPaint(grid[row][col]);
    }
    if (isMiddleDragging) {
        QPoint delta = event->pos() - lastMousePosition;
        lastMousePosition = event->pos();
        horizontalScrollBar()->setValue(
            horizontalScrollBar()->value() - delta.x()
        );
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
    }
    if (row >= 0 && row < grid.size() && col >= 0 && col < grid[row].size()) {
        emit mouseCoordinates(col, row);
    } else {
        emit mouseCoordinates(-1, -1);
    }
}

void MainGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
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

//////////////
// Painting //
//////////////
void MainGraphicsView::startPainting()
{
    paintedItems.clear();
    // prevPixmaps.clear();
    prevTextureKeys.clear();
}

void MainGraphicsView::applyPaint(QGraphicsPixmapItem *item)
{
    if (!paintedItems.contains(item)) {
        paintedItems.append(item);
        // prevPixmaps.append(item->pixmap());
        prevTextureKeys.append(item->data(0).toString());

        // item->setPixmap(
        //     currentTexture.scaled(tileSize, tileSize, Qt::KeepAspectRatio)
        // );
        item->setPixmap(textureManager->getTexture(currentTextureKey)
                            .scaled(tileSize, tileSize, Qt::KeepAspectRatio));
        item->setData(0, currentTextureKey);
    }
}

void MainGraphicsView::endPainting()
{
    if (!paintedItems.isEmpty()) {
        QList<QString> newTextureKeys;
        for (auto _ : qAsConst(paintedItems)) {
            newTextureKeys.append(currentTextureKey);
        }
        emit executeCommand(new CompoundPaintCommand(
            *textureManager, paintedItems, prevTextureKeys, newTextureKeys
        ));
        paintedItems.clear();
        prevTextureKeys.clear();
    }
}

void MainGraphicsView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
}

// Unused for now
void MainGraphicsView::fitInViewGrid()
{
    if (grid.isEmpty() || grid[0].isEmpty())
        return;

    const int padding = tileSize;

    // Calculate the size of the entire grid
    int gridWidth = grid[0].size() * tileSize + 2 * padding;
    int gridHeight = grid.size() * tileSize + 2 * padding;

    // Get the size of the view
    QRectF viewRect = this->viewport()->rect();
    viewRect.adjust(padding, padding, -padding, -padding);

    // Calculate scale factors for width and height
    qreal scaleX = viewRect.width() / gridWidth;
    qreal scaleY = viewRect.height() / gridHeight;

    // Use the smaller scale factor to ensure the entire grid fits
    qreal scaleFactor = qMin(scaleX, scaleY);

    // Reset the view transformation and scale the view
    this->resetTransform();
    this->scale(scaleFactor, scaleFactor);
    this->centerOn(gridWidth / 2.0, gridHeight / 2.0);
}