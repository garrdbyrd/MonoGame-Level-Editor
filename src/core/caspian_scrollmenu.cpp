#include "caspian.h"

#include <QDebug>
#include <QDir>

#include <fstream>

#include "./ui_caspian.h"
#include "config.h"
#include "qchar.h"
#include "selectablelabel.h"
#include "texturemanager.h"
#include "utility.h"

void Caspian::populateScrollMenu()
{
    // Import settings
    Config settings;

    // Keep this or segfault
    currentSelectedLabel = nullptr;

    // Initial path information
    QDir directory(settings.assetPath);  //.ini
    QStringList subDirs =
        directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    QGridLayout *layout =
        qobject_cast<QGridLayout *>(ui->tilePickerWidget->layout());

    // Make sure it's not fucking up
    if (!layout) {
        qDebug() << "Layout cast failed. Ensure tilePickerWidget has a "
                    "QGridLayout.";
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

        for (auto item = textureManager.textureMap.begin();
             item != textureManager.textureMap.end();
             ++item) {
            const QString key = item.key();

            const QList<QString> keyDirList = splitString(key, '/');

            std::ofstream errfile;
            errfile.open("stderr.log");
            errfile << key.toStdString() << '\n';
            errfile.close();

            if (keyDirList[0] == subDirName) {
                SelectableLabel *imageLabel = new SelectableLabel;

                QPixmap textureIcon = textureManager.getTexture(key);
                imageLabel->setPixmap(
                    textureIcon.scaled(size, size, Qt::KeepAspectRatio)
                );

                imageLabel->setAccessibleName(key);
                connect(
                    imageLabel,
                    &SelectableLabel::clicked,
                    this,
                    &Caspian::labelClicked
                );
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
    //     imageLabel->setPixmap(pixmap.scaled(size, size,
    //     Qt::KeepAspectRatio));
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

void Caspian::labelClicked(SelectableLabel *label)
{
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

        QString textureKey = label->accessibleName();
        QPixmap scaledTexture =
            label->pixmap().scaledToHeight(192 * applicationHeight / 1080);

        if (mainGraphicsView && !textureKey.isEmpty() &&
            !scaledTexture.isNull()) {
            mainGraphicsView->setCurrentTexture(textureKey);
        }

        // Check if the pixmap is valid
        if (!scaledTexture.isNull()) {
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(scaledTexture);
            // int applicationHeight =
            //     qobject_cast<QLabel
            //     *>(sender())->window()->height();
            // ;
            // item->setScale(12 * applicationHeight / 1080);
            ui->selectedGraphicsView->scene()->addItem(item);
        }
    } else {
        currentSelectedLabel = nullptr;
        ui->selectedGraphicsView->scene()->clear();
    }
}

void Caspian::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    populateScrollMenu();
}