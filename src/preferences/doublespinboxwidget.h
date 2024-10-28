#ifndef DOUBLESPINBOXWIDGET_H
#define DOUBLESPINBOXWIDGET_H

#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

class DoubleSpinBoxWidget : public QWidget
{
    Q_OBJECT

   public:
    explicit DoubleSpinBoxWidget(
        double minValue = 0,
        double maxValue = 1,
        double stepSize = 0.05,
        QWidget *parent = nullptr
    );
    double value() const;
    void setValue(double val);
    void setRange(double minValue, double maxValue);
    void setMinimum(double minValue);
    void setMaximum(double maxValue);
    void stepSize(double stepSize);

   private:
    QDoubleSpinBox *doubleSpinBox;
};

#endif  // DOUBLESPINBOXWIDGET_H
