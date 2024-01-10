#include "doublespinboxwidget.h"

DoubleSpinBoxWidget::DoubleSpinBoxWidget(QWidget *parent)
    : QWidget(parent), doubleSpinBox(new QDoubleSpinBox(this)) {

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(doubleSpinBox);
}

double DoubleSpinBoxWidget::value() const {
    return doubleSpinBox->value();
}

void DoubleSpinBoxWidget::setValue(double val) {
    doubleSpinBox->setValue(val);
}

void DoubleSpinBoxWidget::setRange(double minValue, double maxValue){
    doubleSpinBox->setRange(minValue, maxValue);
}

void DoubleSpinBoxWidget::setMinimum(double minValue) {
    doubleSpinBox->setMinimum(minValue);
}

void DoubleSpinBoxWidget::setMaximum(double maxValue) {
    doubleSpinBox->setMaximum(maxValue);
}

void DoubleSpinBoxWidget::stepSize(double stepSize){
    doubleSpinBox->setSingleStep(stepSize);
}

