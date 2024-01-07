#include "caspian.h"
#include "./ui_caspian.h"
#include "draggablelabel.h"

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

Caspian::Caspian(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Caspian)
{
    ui->setupUi(this);

    QGridLayout *layout = new QGridLayout(ui->tilePickerWidget);
    ui->tilePickerWidget->setLayout(layout);

    //populateScrollMenu();
    QTimer::singleShot(0, this, &Caspian::populateScrollMenu);
}

Caspian::~Caspian()
{
    delete ui;
}

// Classes

// Functions
void Caspian::populateScrollMenu()
{
    QDir directory("/home/blackbox/Documents/gamedev/caspian/caspian/caspian-local/assets");
    QStringList subDirs = directory.entryList(QDir::Dirs);

    QGridLayout *layout = qobject_cast<QGridLayout*>(ui->tilePickerWidget->layout());

    if (!layout) {
        qDebug() << "Layout cast failed. Ensure tilePickerWidget has a QGridLayout.";
        return;
    }
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
        QDir subDir(directory.absoluteFilePath(subDirName));
        QStringList pngFiles = subDir.entryList(QStringList() << "*.png", QDir::Files);
        //qDebug() << "PNG files in" << subDir.absolutePath() << ":" << pngFiles;

        foreach (const QString &fileName, pngFiles) {
            draggableLabel *imageLabel = new draggableLabel;
            QPixmap pixmap(subDir.absoluteFilePath(fileName));
            imageLabel->setPixmap(pixmap.scaled(size, size, Qt::KeepAspectRatio));
            layout->addWidget(imageLabel, row, column);

            column++;
            if (column >= maxColumns) {
                column = 0;
                row++;
            }
        }
    }

    for (int i = 0; i < maxColumns; ++i) {
        layout->setColumnStretch(i, 1);
    }

    const int maxRows = layout->rowCount();
    for (int i = 0; i < maxRows; ++i) {
        layout->setRowStretch(i, 1);
    }

    //qDebug() << layout->rowCount();
    //qDebug() << layout->columnCount();
    //qDebug() << layout->count();
}

void Caspian::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    populateScrollMenu();
}

