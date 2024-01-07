#include "selectablelabel.h"
#include <QGraphicsDropShadowEffect>

selectableLabel::selectableLabel(QWidget *parent)
    : QLabel(parent), selected(false) {}

void selectableLabel::setSelected(bool selected) {
    this->selected = selected;
    if (selected) {
        auto effect = new QGraphicsDropShadowEffect(this);
        effect->setBlurRadius(32);
        effect->setColor(QColor(255, 255, 255));
        effect->setOffset(0);
        setGraphicsEffect(effect);
    } else {
        setGraphicsEffect(nullptr);
    }
}

bool selectableLabel::isSelected() const {
    return selected;
}

void selectableLabel::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setSelected(!isSelected());
        emit clicked(this);
    }
    QLabel::mousePressEvent(event);  // Ensures the base class event handling still occurs
}
