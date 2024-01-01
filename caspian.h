#ifndef CASPIAN_H
#define CASPIAN_H

#include <QMainWindow>

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

private:
    Ui::Caspian *ui;
};
#endif // CASPIAN_H
