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
#include "config.h"
#include "maingraphicsview.h"

Caspian::Caspian(QWidget *parent) : QMainWindow(parent), ui(new Ui::Caspian)
{
    ui->setupUi(this);
    Config settings;
    this->setupShortcuts();
    this->setupToolbar();

    // Other
    QGridLayout *layout = new QGridLayout(ui->tilePickerWidget);
    ui->tilePickerWidget->setLayout(layout);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->selectedGraphicsView->setScene(scene);

    MainGraphicsView *mainGraphicsView =
        dynamic_cast<MainGraphicsView *>(ui->mainGraphicsView);

    QPixmap defaultTexture(settings.defaultTexturePath);
    mainGraphicsView->setCurrentTexture(defaultTexture);
    mainGraphicsView->setupGrid(
        12, 20, 16
    );  // Change '16' if textures are not 16x16. It
        // should just be a multiple of your texture size.
    mainGraphicsView->noCurrentTexture();

    this->populateScrollMenu();
    this->setPropertiesTable();
    this->setupStatusBar(mainGraphicsView);
}

Caspian::~Caspian()
{
    delete ui;
}