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
#include "customtoolbar.h"
#include "maingraphicsview.h"

Caspian::Caspian(QWidget *parent) : QMainWindow(parent), ui(new Ui::Caspian)
{
    ui->setupUi(this);
    Config settings;
    setupToolbar();
    setupActions();
    updateActionStates();
    setupShortcuts();
    // this->setupShortcuts();
    // // new QShortcut(Qt::CTRL + Qt::Key_Z, this, SLOT(undo()));
    // // new QShortcut(Qt::CTRL + Qt::Key_Y, this, SLOT(redo()));
    // // new QShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_Z, this, SLOT(redo()));
    // connect(
    //     ui->actionPreferences,
    //     &QAction::triggered,
    //     this,
    //     &Caspian::onPreferencesTriggered
    // );
    // connect(ui->actionUndo, &QAction::triggered, this, &Caspian::undo);
    // connect(ui->actionRedo, &QAction::triggered, this, &Caspian::redo);
    // updateActionStates();
    // // this->setupActions();

    // // Other
    // QGridLayout *layout = new QGridLayout(ui->tilePickerWidget);
    // ui->tilePickerWidget->setLayout(layout);

    // QGraphicsScene *scene = new QGraphicsScene(this);
    // ui->selectedGraphicsView->setScene(scene);

    // MainGraphicsView *mainGraphicsView =
    //     dynamic_cast<MainGraphicsView *>(ui->mainGraphicsView);

    // QPixmap defaultTexture(settings.defaultTexturePath);
    // mainGraphicsView->setCurrentTexture(defaultTexture);
    // mainGraphicsView->setupGrid(
    //     12, 20, 16
    // );  // Change '16' if textures are not 16x16. It
    //     // should just be a multiple of your texture size.
    // mainGraphicsView->noCurrentTexture();

    // this->populateScrollMenu();
    // this->setPropertiesTable();
    // this->setupStatusBar(mainGraphicsView);
    // ToolBar
    // CustomToolBar *toolbar = new CustomToolBar(this);
    // connect(
    //     toolbar,
    //     &CustomToolBar::tilePickerRefresh,
    //     this,
    //     &Caspian::populateScrollMenu
    // );
    // this->addToolBar(toolbar);

    // Actions / Shortcuts
    // new QShortcut(Qt::CTRL + Qt::Key_Z, this, SLOT(undo()));
    // new QShortcut(Qt::CTRL + Qt::Key_Y, this, SLOT(redo()));
    // new QShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_Z, this, SLOT(redo()));

    // Setup other windows and menu bar shortcuts
    // connect(
    //     ui->actionPreferences,
    //     &QAction::triggered,
    //     this,
    //     &Caspian::onPreferencesTriggered
    // );
    // connect(ui->actionUndo, &QAction::triggered, this, &Caspian::undo);
    // connect(ui->actionRedo, &QAction::triggered, this, &Caspian::redo);

    // Other
    QGridLayout *layout = new QGridLayout(ui->tilePickerWidget);
    ui->tilePickerWidget->setLayout(layout);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->selectedGraphicsView->setScene(scene);

    MainGraphicsView *mainGraphicsView =
        dynamic_cast<MainGraphicsView *>(ui->mainGraphicsView);
    connect(
        mainGraphicsView,
        &MainGraphicsView::executeCommand,
        this,
        &Caspian::recordCommand
    );

    QPixmap defaultTexture(settings.defaultTexturePath);
    mainGraphicsView->setCurrentTexture(defaultTexture);
    mainGraphicsView->setupGrid(
        12, 20, 16
    );  // Change '16' if textures are not 16x16. It
        // should just be a multiple of your texture size.
    mainGraphicsView->noCurrentTexture();

    populateScrollMenu();
    setPropertiesTable();
    setupStatusBar(mainGraphicsView);
}

Caspian::~Caspian()
{
    delete ui;
}