#ifndef SELECTABLELABEL_H
#define SELECTABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class selectableLabel : public QLabel {
    Q_OBJECT

public:
    explicit selectableLabel(QWidget *parent = nullptr);

    void setSelected(bool selected);
    bool isSelected() const;

signals:
    void clicked(selectableLabel *label);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    bool selected;
};

#endif // SELECTABLELABEL_H
