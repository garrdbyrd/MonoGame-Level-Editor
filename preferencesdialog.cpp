#include "preferencesdialog.h"
#include "config.h"
#include "ui_preferencesdialog.h"

#include <QVBoxLayout>
#include <QCheckBox>
#include <QDebug>
#include <QSpacerItem>
#include <QScrollArea>

preferencesDialog::preferencesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::preferencesDialog)
{
    ui->setupUi(this);
    populatePreferences();
}

preferencesDialog::~preferencesDialog()
{
    delete ui;
}

void preferencesDialog::populatePreferences() {
    Config config;

    for (QString& sectionName : config.childGroups()){
        QScrollArea* scrollArea = new QScrollArea;
        QWidget* scrollWidget = new QWidget;
        QVBoxLayout* layout = new QVBoxLayout(scrollWidget);

        scrollArea->setWidgetResizable(true);
        scrollArea->setFrameShadow(QFrame::Raised);
        scrollArea->setWidget(scrollWidget);

        // auto settingsMap = config.getSettings(sectionName);

        config.beginGroup(sectionName);
        qDebug() << config.group();
        foreach (const QString &key, config.allKeys()) {
            qDebug() << key;
            QWidget* settingWidget = config.getSettingWidget(key);
            if (settingWidget != nullptr) {
                layout->addWidget(settingWidget);
            } else {
                QCheckBox* checkBox = new QCheckBox(key);
                layout->addWidget(checkBox);
            }
        }
        config.endGroup();

        QSpacerItem* verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Maximum, QSizePolicy::Expanding);
        layout->addSpacerItem(verticalSpacer);
        ui->preferencesTabs->addTab(scrollArea, sectionName);
    }
}
