#ifndef SPINBOXWIDGET_H
#define SPINBOXWIDGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QWidget>

class SpinBoxWidget : public QWidget {
	Q_OBJECT

  public:
	explicit SpinBoxWidget(int minValue = 0, int maxValue = 100, int stepSize = 1, QWidget *parent = nullptr);
	int  value() const;
	void setValue(int val);
	void setRange(int minValue, int maxValue);
	void setMinimum(int minValue);
	void setMaximum(int maxValue);
	void stepSize(int stepSize);

  private:
	QSpinBox *spinBox;
};

#endif // SPINBOXWIDGET_H
