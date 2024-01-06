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
    populateScrollMenu();
}

Caspian::~Caspian()
{
    delete ui;
}

void Caspian::populateScrollMenu()
{
    QDir directory("/home/blackbox/Documents/gamedev/caspian-development/Caspian/caspian-local/assets");
    QStringList subDirs = directory.entryList(QDir::Dirs);

    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->tilePickerWidget->layout());

    if (!layout) {
        qDebug() << "Layout cast failed. Ensure tilePickerWidget has a QVBoxLayout.";
        return;
    }
    else{
        qDebug() << "Everything is good.";
    }

    QLayoutItem *item;
    while ((item = layout -> takeAt(0)) != nullptr) {
        delete item -> widget();
        delete item;
    }

    foreach (const QString &subDirName, subDirs) {
        QDir subDir(directory.absoluteFilePath(subDirName));
        QStringList pngFiles = subDir.entryList(QStringList() << "*.png", QDir::Files);
        qDebug() << "PNG files in" << subDir.absolutePath() << ":" << pngFiles;

        foreach (const QString &fileName, pngFiles) {
            QLabel *imageLabel = new QLabel;
            imageLabel->setMinimumSize(100, 100);
            QPixmap pixmap(subDir.absoluteFilePath(fileName));
            imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
            layout->addWidget(imageLabel);
        }
    }
}
