#ifndef MAINGRAPHICSVIEW_H
#define MAINGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QInputEvent>

class MainGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    MainGraphicsView(QWidget *parent = nullptr);

    void setCurrentTexture(const QPixmap &texture);
    void noCurrentTexture();
    void setupGrid(int rows, int cols, int tileSize);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QPixmap currentTexture;
    QPixmap nullTexture = QPixmap();
    QVector<QVector<QGraphicsPixmapItem*>> grid;
    int tileSize;
    bool isLeftDragging;
    bool isMiddleDragging;
    QPoint lastMousePosition;
};

#endif // MAINGRAPHICSVIEW_H
