#include "caspian.h"
#include "./ui_caspian.h"

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

Caspian::Caspian(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Caspian)
{
    ui->setupUi(this);

    QGridLayout *layout = new QGridLayout(ui->tilePickerWidget);
    ui->tilePickerWidget->setLayout(layout);

    populateScrollMenu();
}

Caspian::~Caspian()
{
    delete ui;
}

void Caspian::populateScrollMenu()
{
    QDir directory("/home/blackbox/Documents/gamedev/caspian/caspian/caspian-local/assets");
    QStringList subDirs = directory.entryList(QDir::Dirs);

    QGridLayout *layout = qobject_cast<QGridLayout*>(ui->tilePickerWidget->layout());

    if (!layout) {
        qDebug() << "Layout cast failed. Ensure tilePickerWidget has a QGridLayout.";
        return;
    }

    layout->setAlignment(Qt::AlignCenter);
    int row = 0;
    int column = 0;
    const int maxColumns = 3;
    int maxRows = 0;
    int width;

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
            QLabel *imageLabel = new QLabel;
            //int size = 100;
            // imageLabel->setMinimumSize(size, size);
            QPixmap pixmap(subDir.absoluteFilePath(fileName));
            //imageLabel->setPixmap(pixmap.scaled(size, size, Qt::KeepAspectRatio));

            imageLabel->setPixmap(pixmap);
            imageLabel->setScaledContents(true);
            layout->addWidget(imageLabel, row, column);
            column++;
            if (column >= maxColumns) {
                column = 0;
                row++;
                maxRows++;
            }
        }
    }

    for (int i = 0; i < maxColumns; ++i) {
        layout->setColumnStretch(i, 1);
    }

    for (int i = 0; i <= maxRows; ++i) {
        layout->setRowStretch(i, 1);
    }
    //qDebug() << layout->count();
}



