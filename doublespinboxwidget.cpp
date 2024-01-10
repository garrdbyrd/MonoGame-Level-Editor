#include "doublespinboxwidget.h"

DoubleSpinBoxWidget::DoubleSpinBoxWidget(QWidget *parent)
    : QWidget(parent), doubleSpinBox(new QDoubleSpinBox(this)) {

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(doubleSpinBox);
}

int DoubleSpinBoxWidget::value() const {
    return doubleSpinBox->value();
}

void DoubleSpinBoxWidget::setValue(int val) {
    doubleSpinBox->setValue(val);
}
