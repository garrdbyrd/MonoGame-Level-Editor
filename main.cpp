#include "caspian.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon(
      "/home/blackbox/Documents/gamedev/caspian/caspian/caspian.png")); // fix
                                                                        // later
  Caspian w;
  w.show();
  return a.exec();
}
