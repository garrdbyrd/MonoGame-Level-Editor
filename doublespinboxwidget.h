#ifndef DOUBLESPINBOXWIDGET_H
#define DOUBLESPINBOXWIDGET_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QHBoxLayout>

class DoubleSpinBoxWidget : public QWidget {
    Q_OBJECT

public:
    explicit DoubleSpinBoxWidget(QWidget* parent = nullptr);
    int value() const;
    void setValue(int val);

private:
    QDoubleSpinBox* doubleSpinBox;
};

#endif // DOUBLESPINBOXWIDGET_H
