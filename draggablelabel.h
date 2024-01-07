#ifndef DRAGGABLELABEL_H
#define DRAGGABLELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>

class draggableLabel : public QLabel {
    Q_OBJECT
public:
    using QLabel::QLabel; // Inherit constructors

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // DRAGGABLELABEL_H
