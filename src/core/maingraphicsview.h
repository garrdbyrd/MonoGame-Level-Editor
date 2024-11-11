#ifndef MAINGRAPHICSVIEW_H
#define MAINGRAPHICSVIEW_H

#include "commandhistory.h"
#include "texturemanager.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QInputEvent>

class MainGraphicsView : public QGraphicsView
{
    Q_OBJECT

    public:
    MainGraphicsView(QWidget *parent = nullptr);
    void update();
    void setCurrentTexture(const QString &textureKey);
    void noCurrentTexture();
    void setupGrid(int rows, int cols, int tileSize);
    // TextureManager textureManager;
    void setTextureManager(TextureManager *textureManager);

    protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    private:
    TextureManager *textureManager = nullptr;
    QPixmap currentTexture;
    QPixmap nullTexture = QPixmap();
    QVector<QVector<QGraphicsPixmapItem *>> grid;
    int tileSize;
    bool isLeftDragging;
    bool isMiddleDragging;
    QPoint lastMousePosition;
    // Paint commands
    bool isPainting = false;
    QList<QGraphicsPixmapItem *> paintedItems;
    // QList<QPixmap> prevPixmaps;
    QList<QString> prevTextureKeys;
    QString currentTextureKey;
    void startPainting();
    void applyPaint(QGraphicsPixmapItem *item);
    void endPainting();
    void fitInViewGrid();
    void resizeEvent(QResizeEvent *event) override;

    signals:
    void executeCommand(Command *command);
    void mouseCoordinates(const int x, const int y);
};

#endif  // MAINGRAPHICSVIEW_H
