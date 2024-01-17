#include "caspian.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon("build-assets/caspian.png")); // fix
	Caspian w;
	w.show();
	return a.exec();
}
