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
        scrollArea->setWidget(scrollWidget);

        auto settingsMap = config.getSettings(sectionName);
        for(auto item = settingsMap.begin(); item != settingsMap.end(); ++item) {
            QCheckBox* checkBox = new QCheckBox(item.key());
            checkBox->setChecked(item.value().toBool());
            layout->addWidget(checkBox);

            // connect(checkBox, &QCheckBox::toggled, this, &preferencesDialog::onSettingChanged);
        }

        QSpacerItem* verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Maximum, QSizePolicy::Expanding);
        layout->addSpacerItem(verticalSpacer);
        ui->preferencesTabs->addTab(scrollArea, sectionName);
    }
}
