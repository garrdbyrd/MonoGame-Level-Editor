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

void SpinBoxWidget::setRange(int minValue, int maxValue){
    spinBox->setRange(minValue, maxValue);
}

void SpinBoxWidget::setMinimum(int minValue) {
    spinBox->setMinimum(minValue);
}

void SpinBoxWidget::setMaximum(int maxValue) {
    spinBox->setMaximum(maxValue);
}

void SpinBoxWidget::stepSize(int stepSize){
    spinBox->setSingleStep(stepSize);
}
