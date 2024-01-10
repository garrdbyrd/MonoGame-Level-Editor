#include "spinboxwidget.h"

SpinBoxWidget::SpinBoxWidget(QWidget *parent)
    : QWidget(parent), spinBox(new QSpinBox(this)) {

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(spinBox);
}

int SpinBoxWidget::value() const {
    return spinBox->value();
}

void SpinBoxWidget::setValue(int val) {
    spinBox->setValue(val);
}
