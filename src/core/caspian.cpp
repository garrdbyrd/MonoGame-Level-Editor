#include "caspian.h"

#include <QAction>
#include <QDebug>
#include <QDir>
#include <QDrag>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QMainWindow>
#include <QMimeData>
#include <QPixmap>
#include <QPushButton>
#include <QScrollArea>
#include <QShortcut>
#include <QString>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include <cstdio>

#include "./ui_caspian.h"

Caspian::Caspian(QWidget *parent) : QMainWindow(parent), ui(new Ui::Caspian)
{
    ui->setupUi(this);

    setupToolbar();
    setupActions();
    updateActionStates();
    setupShortcuts();
    setupMainGraphicsView();
    populateScrollMenu();
    setPropertiesTable();
    setupStatusBar();
}

Caspian::~Caspian()
{
    delete ui;
}