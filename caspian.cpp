#include "caspian.h"
#include "./ui_caspian.h"

Caspian::Caspian(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Caspian)
{
    ui->setupUi(this);
}

Caspian::~Caspian()
{
    delete ui;
}
