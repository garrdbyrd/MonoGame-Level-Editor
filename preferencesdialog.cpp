#include "preferencesdialog.h"
#include "config.h"
#include "ui_preferencesdialog.h"

#include <QVBoxLayout>
#include <QCheckBox>
#include <QDebug>
#include <QSpacerItem>

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
    QVBoxLayout* completeLayout = new QVBoxLayout();

    for (QString& sectionName : config.childGroups()){
        auto settingsMap = config.getSettings(sectionName);
        for(auto item = settingsMap.begin(); item != settingsMap.end(); ++item) {
            QCheckBox* checkBox = new QCheckBox(item.key());
            checkBox->setChecked(item.value().toBool());
            completeLayout->addWidget(checkBox);

            // connect(checkBox, &QCheckBox::toggled, this, &preferencesDialog::onSettingChanged);
        }
    }

    QSpacerItem* verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Maximum, QSizePolicy::Expanding);
    completeLayout->addSpacerItem(verticalSpacer);

    ui->preferencesScrollWidget->setLayout(completeLayout);
}
