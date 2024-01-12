#ifndef DOUBLESPINBOXWIDGET_H
#define DOUBLESPINBOXWIDGET_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QHBoxLayout>

class DoubleSpinBoxWidget : public QWidget {
    Q_OBJECT

public:
    explicit DoubleSpinBoxWidget(double minValue = 0, double maxValue = 1, double stepSize = 0.05, QWidget* parent = nullptr);
    double value() const;
    void setValue(double val);
    void setRange(double minValue, double maxValue);
    void setMinimum(double minValue);
    void setMaximum(double maxValue);
    void stepSize(double stepSize);

private:
    QDoubleSpinBox* doubleSpinBox;
};

#endif // DOUBLESPINBOXWIDGET_H
