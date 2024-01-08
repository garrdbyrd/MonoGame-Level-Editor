#include "caspian.h"
#include "./ui_caspian.h"
#include "selectablelabel.h"
#include "maingraphicsview.h"

#include <QDir>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QAction>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>
#include <QDebug>
#include <QTimer>
#include <QDrag>
#include <QMimeData>
#include <QGraphicsPixmapItem>

Caspian::Caspian(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Caspian)
{
    ui->setupUi(this);

    QGridLayout *layout = new QGridLayout(ui->tilePickerWidget);
    ui->tilePickerWidget->setLayout(layout);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->selectedGraphicsView->setScene(scene);

    MainGraphicsView *mainGraphicsView = dynamic_cast<MainGraphicsView*>(ui->mainGraphicsView);
    QPixmap defaultTexture("/home/blackbox/Documents/gamedev/caspian/caspian/caspian-local/assets/default/default.png"); //.ini
    mainGraphicsView->setCurrentTexture(defaultTexture);
    mainGraphicsView->setupGrid(10, 10, 72);

    QTimer::singleShot(0, this, &Caspian::populateScrollMenu);
    setPropertiesTable();
}

Caspian::~Caspian()
{
    delete ui;
}

void Caspian::labelClicked(selectableLabel *label) {
    if (currentSelectedLabel) {
        currentSelectedLabel->setSelected(false);
        ui->selectedTileLabel->setText("");
    }

    if (label != currentSelectedLabel) {
        label->setSelected(true);
        currentSelectedLabel = label;

        // Set text in viewer
        ui->selectedTileLabel->setText(label->accessibleName());

        // // Clear existing items in the scene
        ui->selectedGraphicsView->scene()->clear();

        // // Get the copy of the pixmap from the label
        QPixmap pixmap = label->pixmap(Qt::ReturnByValue);

        // Get the texture from the label and set it as the current texture in the grid view
        // QPixmap selectedTexture = label->pixmap(Qt::ReturnByValue);
        QString texturePath = label->getTextureFilePath();
        QPixmap originalTexture(texturePath);
        MainGraphicsView *mainGraphicsView = dynamic_cast<MainGraphicsView*>(ui->mainGraphicsView);
        //mainGraphicsView->setCurrentTexture(selectedTexture);
        if (mainGraphicsView && !originalTexture.isNull()) {
            mainGraphicsView->setCurrentTexture(originalTexture);
        }

        // Check if the pixmap is valid
        if (!pixmap.isNull()) {
            // Create a QGraphicsPixmapItem with the label's pixmap
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
            item->setScale(3);
            ui->selectedGraphicsView->scene()->addItem(item);
        }
    } else {
        currentSelectedLabel = nullptr;
        ui->selectedGraphicsView->scene()->clear();  // Clear the scene if deselected
    }
}

void Caspian::populateScrollMenu()
{
    // Keep this or segfault
    currentSelectedLabel = nullptr;

    // Initial path information
    QDir directory("/home/blackbox/Documents/gamedev/caspian/caspian/caspian-local/assets"); //.ini
    QStringList subDirs = directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    QGridLayout *layout = qobject_cast<QGridLayout*>(ui->tilePickerWidget->layout());

    // Make sure it's not fucking up
    if (!layout) {
        qDebug() << "Layout cast failed. Ensure tilePickerWidget has a QGridLayout.";
        return;
    }

    // Clear existing
    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QWidget* widget = item->widget())
            delete widget;
        delete item;
    }

    layout->setAlignment(Qt::AlignCenter);
    int row = 0;
    int column = 0;

    int areaWidth = ui->tilePickerWidget->width();
    int margin = 6;
    int maxColumns = 3;
    int size = (areaWidth - margin * (maxColumns + 1)) / maxColumns;

    QLayoutItem *item;
    while ((item = layout -> takeAt(0)) != nullptr) {
        delete item -> widget();
        delete item;
    }

    foreach (const QString &subDirName, subDirs) {
        // Label
        QLabel *dirLabel = new QLabel(subDirName);
        dirLabel->setAlignment(Qt::AlignLeft);
        dirLabel->setStyleSheet("font-weight: bold");
        //dirLabel->setAutoFillBackground(true);
        layout->addWidget(dirLabel, row++, 0, 1, -1);

        QDir subDir(directory.absoluteFilePath(subDirName));
        QStringList pngFiles = subDir.entryList(QStringList() << "*.png", QDir::Files);
        //qDebug() << "PNG files in" << subDir.absolutePath() << ":" << pngFiles;

        foreach (const QString &fileName, pngFiles) {
            selectableLabel *imageLabel = new selectableLabel;
            QPixmap pixmap(subDir.absoluteFilePath(fileName));
            imageLabel->setPixmap(pixmap.scaled(size, size, Qt::KeepAspectRatio));
            imageLabel->setTextureFilePath(subDir.absoluteFilePath(fileName));

            QString accessibleName = subDirName + "/" + QFileInfo(fileName).baseName();
            imageLabel->setAccessibleName(accessibleName);

            connect(imageLabel, &selectableLabel::clicked, this, &Caspian::labelClicked);
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

    //qDebug() << layout->rowCount();
    //qDebug() << layout->columnCount();
    //qDebug() << layout->count();
}

void Caspian::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    populateScrollMenu();
}

void Caspian::setPropertiesTable(){
    QStringList headers;
    headers << "Property" << "Value";
    ui->selectedProperties->setHorizontalHeaderLabels(headers);
    ui->selectedProperties->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    // Chunk to make column 1 read-only
    int rowCount = ui->selectedProperties->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        QTableWidgetItem *item = ui->selectedProperties->item(row, 0); // Get the item in the first column
        if (!item) {
            item = new QTableWidgetItem(); // Create a new item if it doesn't exist
            ui->selectedProperties->setItem(row, 0, item);
        }
        item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Make the item read-only
    }

    // Chunk for default values in column 2
    for (int row = 0; row < rowCount; ++row) {
        // Determine the default value for this row
        QString defaultValue = QString("Value%1").arg(row); // Replace this with your logic

        QTableWidgetItem *item = ui->selectedProperties->item(row, 1); // Column index 1 for the second column
        if (!item) {
            item = new QTableWidgetItem(defaultValue);
            ui->selectedProperties->setItem(row, 1, item);
        } else {
            item->setText(defaultValue);
        }
    }
}

