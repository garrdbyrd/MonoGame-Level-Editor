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
#include <fstream>
#include <iostream>

#include "./ui_caspian.h"
#include "config.h"
#include "customtoolbar.h"
#include "maingraphicsview.h"
#include "preferencesdialog.h"
#include "selectablelabel.h"
#include "texturemanager.h"
#include "utility.h"

Caspian::Caspian(QWidget *parent) : QMainWindow(parent), ui(new Ui::Caspian) {
  ui->setupUi(this);

  // Boot logic
  Config settings;

  // ToolBar
  CustomToolBar *toolbar = new CustomToolBar(this);
  connect(toolbar, &CustomToolBar::tilePickerRefresh, this,
          &Caspian::populateScrollMenu);
  this->addToolBar(toolbar);

  // Actions / Shortcuts
  new QShortcut(Qt::CTRL + Qt::Key_Z, this, SLOT(undo()));
  new QShortcut(Qt::CTRL + Qt::Key_Y, this, SLOT(redo()));
  new QShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_Z, this, SLOT(redo()));

  // Setup other windows and menu bar shortcuts
  connect(ui->actionPreferences, &QAction::triggered, this,
          &Caspian::onPreferencesTriggered);
  connect(ui->actionUndo, &QAction::triggered, this, &Caspian::undo);
  connect(ui->actionRedo, &QAction::triggered, this, &Caspian::redo);
  updateActionStates();

  // Other
  QGridLayout *layout = new QGridLayout(ui->tilePickerWidget);
  ui->tilePickerWidget->setLayout(layout);

  QGraphicsScene *scene = new QGraphicsScene(this);
  ui->selectedGraphicsView->setScene(scene);

  MainGraphicsView *mainGraphicsView =
      dynamic_cast<MainGraphicsView *>(ui->mainGraphicsView);
  connect(mainGraphicsView, &MainGraphicsView::executeCommand, this,
          &Caspian::recordCommand);

  QPixmap defaultTexture(settings.defaultTexturePath);
  mainGraphicsView->setCurrentTexture(defaultTexture);
  mainGraphicsView->setupGrid(
      12, 20, 16); // Change '16' if textures are not 16x16. It should just be
                   // a multiple of your texture size.
  mainGraphicsView->noCurrentTexture();

  QTimer::singleShot(0, this, &Caspian::populateScrollMenu);
  setPropertiesTable();

  // StatusBar
  connect(mainGraphicsView, &MainGraphicsView::mouseCoordinates, this,
          &Caspian::updateStatusBar);
}

Caspian::~Caspian() { delete ui; }

void Caspian::labelClicked(SelectableLabel *label) {
  MainGraphicsView *mainGraphicsView =
      dynamic_cast<MainGraphicsView *>(ui->mainGraphicsView);
  if (currentSelectedLabel) {
    currentSelectedLabel->setSelected(false);
    ui->selectedTileLabel->setText("");
    mainGraphicsView->noCurrentTexture();
  }

  if (label != currentSelectedLabel) {
    label->setSelected(true);
    currentSelectedLabel = label;

    // Set text in viewer
    ui->selectedTileLabel->setText(label->accessibleName());

    // Clear existing items in the scene
    ui->selectedGraphicsView->scene()->clear();

    // QString texturePath = label->getTextureFilePath();
    // QPixmap originalTexture(texturePath);
    int applicationHeight =
        qobject_cast<QLabel *>(sender())->window()->height();
    ;
    QPixmap scaledTexture =
        label->pixmap().scaledToHeight(192 * applicationHeight / 1080);

    if (mainGraphicsView && !scaledTexture.isNull()) {
      mainGraphicsView->setCurrentTexture(scaledTexture);
    }

    // Check if the pixmap is valid
    if (!scaledTexture.isNull()) {
      QGraphicsPixmapItem *item = new QGraphicsPixmapItem(scaledTexture);
      // int applicationHeight =
      //     qobject_cast<QLabel *>(sender())->window()->height();
      // ;
      // item->setScale(12 * applicationHeight / 1080);
      ui->selectedGraphicsView->scene()->addItem(item);
    }
  } else {
    currentSelectedLabel = nullptr;
    ui->selectedGraphicsView->scene()->clear();
  }
}

void Caspian::populateScrollMenu() {
  // Import settings
  Config settings;

  // Keep this or segfault
  currentSelectedLabel = nullptr;

  // Initial path information
  QDir directory(settings.assetPath); //.ini
  QStringList subDirs = directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
  QGridLayout *layout =
      qobject_cast<QGridLayout *>(ui->tilePickerWidget->layout());

  // Make sure it's not fucking up
  if (!layout) {
    qDebug()
        << "Layout cast failed. Ensure tilePickerWidget has a QGridLayout.";
    return;
  }

  // Clear existing
  while (QLayoutItem *item = layout->takeAt(0)) {
    if (QWidget *widget = item->widget())
      delete widget;
    delete item;
  }

  layout->setAlignment(Qt::AlignCenter);
  int row = 0;
  int column = 0;

  int areaWidth = ui->tilePickerWidget->width();
  int margin = 6;
  int maxColumns = settings.tileMenuColumns;
  int size = (areaWidth - margin * (maxColumns + 1)) / maxColumns;

  QLayoutItem *item;
  while ((item = layout->takeAt(0)) != nullptr) {
    delete item->widget();
    delete item;
  }

  TextureManager textureManager;
  textureManager.loadAllTextures(settings.assetPath);

  for (QString &subDirName : subDirs) {
    QLabel *dirLabel = new QLabel(subDirName);
    dirLabel->setAlignment(Qt::AlignLeft);
    dirLabel->setStyleSheet("font-weight: bold");
    layout->addWidget(dirLabel, row++, 0, 1, -1);

    for (const auto &pair : textureManager.textureMap) {
      const QString key = pair.first;
      const QPixmap *value = pair.second;
      const QList<QString> keyDirList = splitString(key, '/');

      std::ofstream errfile;
      errfile.open("stderr.log");
      errfile << key.toStdString() << '\n';
      errfile.close();

      if (keyDirList[0] == subDirName) {
        SelectableLabel *imageLabel = new SelectableLabel;
        QPixmap textureIcon(*value);

        imageLabel->setPixmap(
            textureIcon.scaled(size, size, Qt::KeepAspectRatio));
        // imageLabel->setTextureFilePath(subDir.absoluteFilePath(key)); //
        // Deals with painting

        imageLabel->setAccessibleName(key);
        connect(imageLabel, &SelectableLabel::clicked, this,
                &Caspian::labelClicked);
        layout->addWidget(imageLabel, row, column);

        column++;
        if (column >= maxColumns) {
          column = 0;
          row++;
        }
      }
    }
    column = 0;
    row++;
  }

  // foreach (const QString &subDirName, subDirs) {
  //   QLabel *dirLabel = new QLabel(subDirName);
  //   dirLabel->setAlignment(Qt::AlignLeft);
  //   dirLabel->setStyleSheet("font-weight: bold");
  //   layout->addWidget(dirLabel, row++, 0, 1, -1);

  //   QDir subDir(directory.absoluteFilePath(subDirName));
  //   QStringList pngFiles =
  //       subDir.entryList(QStringList() << "*.png", QDir::Files);

  //   foreach (const QString &fileName, pngFiles) {
  //     SelectableLabel *imageLabel = new SelectableLabel;
  //     QPixmap pixmap(subDir.absoluteFilePath(fileName));
  //     imageLabel->setPixmap(pixmap.scaled(size, size, Qt::KeepAspectRatio));
  //     imageLabel->setTextureFilePath(subDir.absoluteFilePath(fileName));

  //     QString accessibleName =
  //         subDirName + "/" + QFileInfo(fileName).baseName();
  //     imageLabel->setAccessibleName(accessibleName);

  //     connect(imageLabel, &SelectableLabel::clicked, this,
  //             &Caspian::labelClicked);
  //     layout->addWidget(imageLabel, row, column);

  //     column++;
  //     if (column >= maxColumns) {
  //       column = 0;
  //       row++;
  //     }
  //   }
  //   column = 0;
  //   row++;
  // }
}

void Caspian::resizeEvent(QResizeEvent *event) {
  QMainWindow::resizeEvent(event);
  populateScrollMenu();
}

void Caspian::setPropertiesTable() {
  QStringList headers;
  headers << "Property"
          << "Value";
  ui->selectedProperties->setHorizontalHeaderLabels(headers);
  ui->selectedProperties->horizontalHeader()->setDefaultAlignment(
      Qt::AlignLeft);

  // Chunk to make column 1 read-only
  int rowCount = ui->selectedProperties->rowCount();
  for (int row = 0; row < rowCount; ++row) {
    QTableWidgetItem *item = ui->selectedProperties->item(row, 0);
    if (!item) {
      item = new QTableWidgetItem();
      ui->selectedProperties->setItem(row, 0, item);
    }
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
  }

  // Chunk for default values in column 2
  for (int row = 0; row < rowCount; ++row) {
    QString defaultValue = QString("Value%1").arg(row);

    QTableWidgetItem *item = ui->selectedProperties->item(row, 1);
    if (!item) {
      item = new QTableWidgetItem(defaultValue);
      ui->selectedProperties->setItem(row, 1, item);
    } else {
      item->setText(defaultValue);
    }
  }
}

// Status Bar
void Caspian::updateStatusBar(const int x, const int y) {
  // Format the point as a string
  if (0 <= x && 0 <= y) {
    QString statusMessage = QString("X: %1, Y: %2").arg(x).arg(y);
    statusBar()->showMessage(statusMessage);
  } else {
    QString statusMessage = QString("X: , Y: ");
    statusBar()->showMessage(statusMessage);
  }
}

// Other windows
void Caspian::onPreferencesTriggered() {
  preferencesDialog dialog(this);
  dialog.exec();
}

// Actions/shortcuts
void Caspian::undo() {
  commandHistory.undo();
  updateActionStates();
}

void Caspian::redo() {
  commandHistory.redo();
  updateActionStates();
}

void Caspian::recordCommand(Command *command) {
  commandHistory.executeCommand(command);
  updateActionStates();
}

void Caspian::updateActionStates() {
  ui->actionUndo->setEnabled(!commandHistory.isUndoStackEmpty());
  ui->actionRedo->setEnabled(!commandHistory.isRedoStackEmpty());
}
