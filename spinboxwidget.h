#ifndef SPINBOXWIDGET_H
#define SPINBOXWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>

class SpinBoxWidget : public QWidget {
    Q_OBJECT

public:
    explicit SpinBoxWidget(QWidget* parent = nullptr);
    int value() const;
    void setValue(int val);
    void setRange(int minValue, int maxValue);
    void setMinimum(int minValue);
    void setMaximum(int maxValue);
    void stepSize(int stepSize);

private:
    QSpinBox* spinBox;
};

#endif // SPINBOXWIDGET_H
