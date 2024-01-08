#include "caspian.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon(
      "caspian.png")); // fix
  Caspian w;
  w.show();
  return a.exec();
}
