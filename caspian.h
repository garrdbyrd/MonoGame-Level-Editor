#ifndef CASPIAN_H
#define CASPIAN_H

#include <selectablelabel.h>

#include <QMainWindow>
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class Caspian;
}
QT_END_NAMESPACE

class Caspian : public QMainWindow
{
    Q_OBJECT

public:
    Caspian(QWidget *parent = nullptr);
    ~Caspian();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void labelClicked(selectableLabel *label);

private:
    Ui::Caspian *ui;
    void populateScrollMenu();
    selectableLabel *currentSelectedLabel = nullptr;
};

#endif // CASPIAN_H
