#include <QDebug>

#include "caspian.h"
#include "config.h"
#include "maingraphicsview.h"
#include "ui_caspian.h"

void Caspian::setupMainGraphicsView(Config &settings)
{
    mainGraphicsView = ui->mainGraphicsView;
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
    // return mainGraphicsView;
}

// MainGraphicsView Caspian::setupMainGraphicsView(Config &settings)
// {
//     mainGraphicsView = ui->mainGraphicsView;
//     if (!mainGraphicsView) {
//         qDebug() << "Error: mainGraphicsView is nullptr!";
//         return mainGraphicsView;
//     }
//     QGridLayout *layout = new QGridLayout(ui->tilePickerWidget);
//     ui->tilePickerWidget->setLayout(layout);

//     QGraphicsScene *scene = new QGraphicsScene(this);
//     ui->selectedGraphicsView->setScene(scene);

//     // MainGraphicsView *mainGraphicsView =
//     //     dynamic_cast<MainGraphicsView *>(ui->mainGraphicsView);

//     QPixmap defaultTexture(settings.defaultTexturePath);
//     mainGraphicsView->setCurrentTexture(defaultTexture);
//     mainGraphicsView->setupGrid(
//         12, 20, 16
//     );  // Change '16' if textures are not 16x16. It
//         // should just be a multiple of your texture size.
//     mainGraphicsView->noCurrentTexture();
// }