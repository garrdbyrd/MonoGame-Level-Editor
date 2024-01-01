#include "caspian.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Caspian w;
    w.show();
    return a.exec();
}
