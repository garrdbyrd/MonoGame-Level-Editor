#include "caspian.h"
#include "./ui_caspian.h"
#include "customtoolbar.h"
#include "maingraphicsview.h"
#include "selectablelabel.h"
#include "config.h"
#include "preferencesdialog.h"

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
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>

Caspian::Caspian(QWidget *parent) : QMainWindow(parent), ui(new Ui::Caspian) {
  ui->setupUi(this);

  // Setup other windows
  connect(ui->actionPreferences, &QAction::triggered, this, &Caspian::onPreferencesTriggered);

  // Boot logic
  Config settings;

  // ToolBar
  CustomToolBar *toolbar = new CustomToolBar("ToolBar", this);
  connect(toolbar, &CustomToolBar::tilePickerRefresh, this, &Caspian::populateScrollMenu);
  this->addToolBar(toolbar);

  QGridLayout *layout = new QGridLayout(ui->tilePickerWidget);
  ui->tilePickerWidget->setLayout(layout);

  QGraphicsScene *scene = new QGraphicsScene(this);
  ui->selectedGraphicsView->setScene(scene);

  MainGraphicsView *mainGraphicsView =
      dynamic_cast<MainGraphicsView *>(ui->mainGraphicsView);
  QPixmap defaultTexture(settings.defaultTexturePath);
  mainGraphicsView->setCurrentTexture(defaultTexture);
  mainGraphicsView->setupGrid(
      10, 10, 64); // Change '64' if textures are not 16x16. It should just be a
                   // multiple of your texture size.
  mainGraphicsView->noCurrentTexture();

  QTimer::singleShot(0, this, &Caspian::populateScrollMenu);
  setPropertiesTable();
}

Caspian::~Caspian() { delete ui; }

void Caspian::labelClicked(SelectableLabel *label) {
  MainGraphicsView *mainGraphicsView = dynamic_cast<MainGraphicsView *>(ui->mainGraphicsView);
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

    QString texturePath = label->getTextureFilePath();
    QPixmap originalTexture(texturePath);

    if (mainGraphicsView && !originalTexture.isNull()) {
      mainGraphicsView->setCurrentTexture(originalTexture);
    }

    // Check if the pixmap is valid
    if (!originalTexture.isNull()) {
      QGraphicsPixmapItem *item = new QGraphicsPixmapItem(originalTexture);
      int applicationHeight = qobject_cast<QLabel*>(sender())->window()->height();;
      item->setScale(12 * applicationHeight/1080);
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

  foreach (const QString &subDirName, subDirs) {
    QLabel *dirLabel = new QLabel(subDirName);
    dirLabel->setAlignment(Qt::AlignLeft);
    dirLabel->setStyleSheet("font-weight: bold");
    layout->addWidget(dirLabel, row++, 0, 1, -1);

    QDir subDir(directory.absoluteFilePath(subDirName));
    QStringList pngFiles =
        subDir.entryList(QStringList() << "*.png", QDir::Files);

    foreach (const QString &fileName, pngFiles) {
      SelectableLabel *imageLabel = new SelectableLabel;
      QPixmap pixmap(subDir.absoluteFilePath(fileName));
      imageLabel->setPixmap(pixmap.scaled(size, size, Qt::KeepAspectRatio));
      imageLabel->setTextureFilePath(subDir.absoluteFilePath(fileName));

      QString accessibleName =
          subDirName + "/" + QFileInfo(fileName).baseName();
      imageLabel->setAccessibleName(accessibleName);

      connect(imageLabel, &SelectableLabel::clicked, this,
              &Caspian::labelClicked);
      layout->addWidget(imageLabel, row, column);

      column++;
      if (column >= maxColumns) {
        column = 0;
        row++;
      }
    }
    column = 0;
    row++;
  }
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

// Other windows
void Caspian::onPreferencesTriggered() {
  preferencesDialog dialog(this);
  dialog.exec();
}
